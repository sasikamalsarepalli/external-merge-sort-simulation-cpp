#include "run_creator.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

void ensure_directories() {
    std::vector<std::string> folders = {"initial_runs", "sorted_runs"};
    for (const auto& folder : folders) {
        if (!fs::exists(folder)) fs::create_directories(folder);
    }
}

void save_run_elements(const std::vector<int>& chunk, int run_num) {
    fs::path run_file = fs::path("initial_runs") / ("initial_run_" + std::to_string(run_num) + ".txt");
    std::ofstream f(run_file);
    if (f.is_open()) {
        for (int num : chunk) f << num << "\n";
    }
}

std::vector<std::string> create_sorted_runs(const std::string& input_file, int memory_limit) {
    ensure_directories();
    std::vector<std::string> run_files;
    std::ifstream f(input_file);
    std::vector<int> chunk;
    std::string line;
    int run_num = 0;

    auto process_chunk = [&](std::vector<int>& c, int rn) {
        save_run_elements(c, rn);
        std::sort(c.begin(), c.end());
        fs::path sorted_path = fs::path("sorted_runs") / ("run_" + std::to_string(rn) + ".txt");
        std::ofstream sf(sorted_path);
        for (int num : c) sf << num << "\n";
        return sorted_path.string();
    };

    while (std::getline(f, line)) {
        if (line.empty()) continue;
        chunk.push_back(std::stoi(line));
        if (chunk.size() >= (size_t)memory_limit) {
            run_files.push_back(process_chunk(chunk, run_num++));
            chunk.clear();
        }
    }
    if (!chunk.empty()) {
        run_files.push_back(process_chunk(chunk, run_num));
    }
    std::cout << "Created " << run_files.size() << " sorted runs" << std::endl;
    return run_files;
}