#include "merger.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <filesystem>

namespace fs = std::filesystem;

struct HeapNode {
    int val, idx;
    bool operator>(const HeapNode& other) const { return val > other.val; }
};

void merge_k_runs(const std::vector<std::string>& run_files, const std::string& output_file) {
    std::vector<std::ifstream> files;
    std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<HeapNode>> heap;

    for (int i = 0; i < (int)run_files.size(); ++i) {
        files.emplace_back(run_files[i]);
        std::string line;
        if (std::getline(files[i], line)) {
            heap.push({std::stoi(line), i});
        }
    }

    std::ofstream out(output_file);
    while (!heap.empty()) {
        HeapNode top = heap.top();
        heap.pop();
        out << top.val << "\n";
        std::string next;
        if (std::getline(files[top.idx], next)) {
            heap.push({std::stoi(next), top.idx});
        }
    }
}

void merge_runs(std::vector<std::string> run_files, const std::string& output_file, int k_way) {
    int pass_num = 0;
    while (run_files.size() > 1) {
        std::string folder = "merge_pass_" + std::to_string(pass_num);
        fs::create_directories(folder);
        std::vector<std::string> new_files;

        for (size_t i = 0; i < run_files.size(); i += k_way) {
            std::vector<std::string> group;
            for (size_t j = i; j < i + k_way && j < run_files.size(); ++j) {
                group.push_back(run_files[j]);
            }
            std::string merged_file = (fs::path(folder) / ("merged_" + std::to_string(pass_num) + "_" + std::to_string(i/k_way) + ".txt")).string();
            merge_k_runs(group, merged_file);
            new_files.push_back(merged_file);
        }
        run_files = new_files;
        std::cout << "Pass " << pass_num << " done -> Remaining: " << run_files.size() << std::endl;
        pass_num++;
    }
    if (fs::exists(output_file)) {
        fs::remove(output_file);
    }
    fs::copy(run_files[0], output_file);    
std::cout << "Final sorted file: " << output_file << std::endl;
}