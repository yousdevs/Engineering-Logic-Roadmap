#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

class FileUtils {

 public:

  static std::vector<std::string> readLines(const std::string& path) {
    std::vector<std::string> lines;

    std::ifstream file(path);

    if (!file.is_open()) return lines;

    std::string line;

    while (std::getline(file, line)) {
      if (!line.empty()) lines.push_back(line);
    }

    return lines;
  }

  static void writeLines(const std::string& path,
                         const std::vector<std::string>& lines) {
    std::ofstream file(path, std::ios::trunc);

    if (!file.is_open()) throw std::runtime_error("Failed to open file");

    for (const auto& line : lines) {
      file << line << "\n";
    }
  }
};