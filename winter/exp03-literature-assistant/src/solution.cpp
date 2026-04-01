#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

// Build next array for KMP (Multiple matching).
std::vector<int> buildNext(const std::string& pattern)
{
    std::vector<int> next{-1};
    next.reserve(pattern.size() + 1);

    int t = -1;
    for (std::size_t j = 0; j < pattern.size();) {
        while (t >= 0 && pattern[j] != pattern[t]) {
            t = next[t];
        }
        ++t, ++j;

        if (pattern[j] == pattern[t]) {
            next.push_back(next[t]);
        } else {
            next.push_back(t);
        }
    }
    return next;
}

void readPatterns(std::ifstream& fPattern, std::vector<std::string>& patterns,
                  std::vector<std::vector<int>>& nexts)
{
    constexpr std::size_t maxNumPatterns = 100;
    patterns.reserve(maxNumPatterns);
    nexts.reserve(maxNumPatterns);

    std::unordered_set<std::string> seenPatterns;
    std::string pattern;
    while (fPattern >> pattern) {
        // Check if the pattern is valid.
        // A valid pattern should only contain: A-Z, a-z, and '-'.
        bool isValid = true;
        for (char& c : pattern) {
            if ((bool) std::isalpha(c)) {
                // Convert uppercase to lowercase.
                c = std::tolower(c);
            } else if (c != '-') {
                // Ignore non-alphabetic characters.
                isValid = false;
                break;
            }
        }
        if (!isValid || pattern.empty()) {
            continue;
        }

        // it: iterator to the inserted pattern in the set.
        // isNew: whether the pattern is newly inserted.
        auto [it, isNew] = seenPatterns.emplace(std::move(pattern));
        if (isNew) {
            patterns.push_back(*it);
            nexts.push_back(buildNext(*it));
        }
    }
}

void runTask(const std::filesystem::path& patternPath, const std::filesystem::path& textPath,
             const std::filesystem::path& outputDir)
{
    std::println("Reading patterns from \"{}\"...", patternPath.string());
    std::ifstream patFile(patternPath);
    if (!patFile.is_open()) {
        std::println("\nFailed to read patterns!\n");
        return;
    }

    std::vector<std::string> patterns;
    std::vector<std::vector<int>> nexts;
    readPatterns(patFile, patterns, nexts);
    patFile.close();

    if (patterns.empty()) {
        std::println("No patterns found!");
        return;
    }
    std::println("Done.");

    std::println("Opening text file \"{}\"...", textPath.string());
    std::ifstream textFile(textPath);
    if (!textFile.is_open()) {
        std::println("Failed to open text file!");
        return;
    }

    std::println("Counting patterns...");
    std::vector<int> patternPtrs(nexts.size(), 0);  // Pattern pointers.

    using CountInfo = std::pair<std::size_t, std::size_t>;  // line, column
    std::vector<std::vector<CountInfo>> count(nexts.size());

    std::string lineStr;
    lineStr.reserve(128);

    std::size_t line = 0;
    while (std::getline(textFile, lineStr)) {
        if (!lineStr.empty() && lineStr.back() == '\r') {
            lineStr.pop_back();
        }

        for (std::size_t col = 0; col < lineStr.size(); ++col) {
            char c = std::tolower(lineStr[col]);

            // Apply the KMP algorithm for each pattern.
            for (std::size_t pIdx = 0; pIdx < patterns.size(); ++pIdx) {
                const std::string& pat = patterns[pIdx];
                const std::vector<int>& next = nexts[pIdx];
                int& p = patternPtrs[pIdx];

                while (p >= 0 && c != pat[p]) {
                    p = next[p];
                }
                ++p;

                if (p == static_cast<int>(pat.size()))  // Pattern matched.
                {
                    count[pIdx].emplace_back(line + 1, col - p + 2);
                    p = next[p];
                }
            }
        }

        // Move to the next line.
        ++line;
        // Reset the pattern pointers.
        std::ranges::fill(patternPtrs, 0);
    }
    textFile.close();
    std::println("Done.");

    // Save the result.
    std::filesystem::create_directories(outputDir);
    std::filesystem::path outputPath = outputDir / "result.txt";
    std::ofstream fout(outputPath);
    for (std::size_t i = 0; i < patterns.size(); ++i) {
        std::println(fout, "{0}: {1} has occurred {2} times.", i + 1, patterns[i], count[i].size());
        if (!count[i].empty()) {
            for (const auto& [ln, col] : count[i]) {
                std::println(fout, "    Ln {0}, Col {1}", ln, col);
            }
        }
        std::println(fout);
        fout.flush();
    }
    fout.close();

    std::println("The result has been saved to \"{}\".", outputPath.string());
}