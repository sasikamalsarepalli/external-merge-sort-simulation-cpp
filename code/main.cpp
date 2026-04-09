#include <iostream>
#include <vector>
#include <string>
#include "data_generator.h"
#include "run_creator.h"
#include "merger.h"

int main() {
    const std::string DATA_FILE = "large_dataset.txt";
    const std::string FINAL_OUTPUT = "sorted_output.txt";
    const int MEMORY_LIMIT = 1000;
    const int NUM_ELEMENTS = 10000;
    const int K_WAY = 4;

    generate_data(DATA_FILE, NUM_ELEMENTS);
    
    std::vector<std::string> runs = create_sorted_runs(DATA_FILE, MEMORY_LIMIT);
    
    merge_runs(runs, FINAL_OUTPUT, K_WAY);

    std::cout << "External Merge Sort Completed!" << std::endl;
    
    return 0;
}