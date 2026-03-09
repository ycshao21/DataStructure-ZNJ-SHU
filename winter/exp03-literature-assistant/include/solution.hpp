#pragma once
#include <filesystem>

void runTask(const std::filesystem::path& patternPath, const std::filesystem::path& textPath,
          const std::filesystem::path& outputDir);