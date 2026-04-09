#include "data_generator.h"
#include <iostream>
#include <fstream>
#include <random>
#include <filesystem>

namespace fs = std::filesystem;

void generate_data(const std::string& file_path, int num_elements) {
    // 1. Point to the parent directory (where folders are actually created)
    fs::path parent_dir = ".."; 

    // 2. SCALABLE CLEANUP: Scan the parent folder and remove old project-related directories
    if (fs::exists(parent_dir)) {
        for (const auto& entry : fs::directory_iterator(parent_dir)) {
            std::string name = entry.path().filename().string();
            
            // This checks if the folder name starts with "merge_pass_" 
            // or matches our other specific run folders
            if (name.find("merge_pass_") == 0 || 
                name == "initial_runs" || 
                name == "sorted_runs") {
                
                fs::remove_all(entry.path()); // Deletes the entire folder and its contents
            }
        }
    }

    // 3. FILE CREATION: Open the file in 'truncate' mode to overwrite any old data
    std::ofstream f(file_path, std::ios::trunc); 
    
    // 4. RANDOMNESS: High-quality Mersenne Twister engine
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);

    if (f.is_open()) {
        for (int i = 0; i < num_elements; ++i) {
            f << dis(gen) << "\n";
        }
        f.close();
    }
    
    std::cout << "Cleanup finished and " << num_elements << " new numbers generated in " << file_path << std::endl;
}