#include <fstream>
#include <iostream>
#include <string>

#include "word_counter.h"

int main() {
    word_counter wc;
    std::ifstream infile("../moby_dick.txt");
    if (!infile.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    wc.add_words(infile);
    std::cout << "File read\n";
    infile.close();

    std::ofstream outfile("../moby_dick_counter_data.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    outfile << wc;
    outfile.close();

    return 0;
}