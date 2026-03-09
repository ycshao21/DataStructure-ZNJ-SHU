#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

struct Cursor
{
    std::size_t line = 1;
    std::size_t column = 1;
};

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
    std::unordered_set<std::string> seenPatterns;
    std::string pattern;
    while (fPattern >> pattern) {
        // Check if the pattern is valid.
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
        if (!isValid) {
            continue;
        }

        // Ignore the pattern if it is already seen.
        if (seenPatterns.find(pattern) != seenPatterns.end()) {
            continue;
        }

        seenPatterns.emplace(pattern);
        patterns.push_back(pattern);
        nexts.push_back(buildNext(pattern));
    }
}

void runTask(const std::filesystem::path& patternPath, const std::filesystem::path& textPath,
             const std::filesystem::path& outputDir)
{
    std::cout << std::format("Reading patterns from \"{}\"...", patternPath.string());
    std::ifstream fPattern(patternPath);
    if (!fPattern.is_open()) {
        std::cout << "\nFailed to read patterns!\n";
        return;
    }

    std::vector<std::string> patterns;
    std::vector<std::vector<int>> nexts;
    readPatterns(fPattern, patterns, nexts);
    fPattern.close();

    if (patterns.empty()) {
        std::cout << "\nNo patterns found!\n";
        return;
    }
    std::cout << "done.\n";

    std::cout << std::format("Opening text file \"{}\"...\n", textPath.string());
    std::ifstream fText(textPath);
    if (!fText.is_open()) {
        std::cout << "Failed to open text file!\n";
        return;
    }

    std::cout << "Counting patterns...";
    Cursor cursor{.line = 1, .column = 1};
    std::vector<int> patternPtrs(nexts.size(), 0);  // Pattern pointers.
    std::vector<std::vector<Cursor>> count(nexts.size());

    char c;
    while ((c = fText.get()) != std::char_traits<char>::eof()) {
        if (c == '\n' || c == '\r') {  // End of line
            // Move cursor to the next line.
            ++cursor.line;
            cursor.column = 1;
            // Reset the pattern pointers.
            std::ranges::fill(patternPtrs, 0);
            continue;
        }

        // Convert to lowercase.
        c = std::tolower(c);

        // Apply the KMP algorithm for each pattern.
        for (std::size_t i = 0; i < patterns.size(); ++i) {
            const auto& pattern = patterns[i];
            const auto& next = nexts[i];
            auto& p = patternPtrs[i];

            while (p >= 0 && c != pattern[p]) {
                p = next[p];
            }

            ++p;

            if (p == (int) pattern.size())  // Pattern matched.
            {
                count[i].emplace_back(cursor.line, cursor.column - p + 1);
                p = next[p];
            }
        }
        ++cursor.column;
    }
    fText.close();
    std::cout << "done.\n";

    // Save the result.
    if (!std::filesystem::exists(outputDir)) {
        std::filesystem::create_directories(outputDir);
    }

    std::filesystem::path outputPath = outputDir / "result.txt";
    std::ofstream fout(outputPath);
    for (std::size_t i = 0; i < patterns.size(); ++i) {
        fout << std::format("{0}: {1} has occurred {2} times.\n", i + 1, patterns[i],
                            count[i].size());
        if (!count[i].empty()) {
            for (const auto& cs : count[i]) {
                fout << std::format("    Ln {0}, Col {1}\n", cs.line, cs.column);
            }
        }
        fout << '\n' << std::flush;
    }
    fout.close();

    std::cout << std::format("The result has been saved to \"{}\".", outputPath.string());
}