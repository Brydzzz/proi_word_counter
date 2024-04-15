#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "word_counter.h"

int main() {
    // constructing word counter section
    word_counter wc;
    std::ifstream infile("../moby_dick.txt");
    if (!infile.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    std::cout << "moby_dick.txt read\n\n";

    std::cout << "Counting words...\n";
    auto start_time = std::chrono::high_resolution_clock::now();
    wc.add_words(infile);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    std::cout << "Words counted.\n";

    std::cout << "Ellapsed time: " << time / std::chrono::milliseconds(1)
              << " ms.\n";
    infile.close();

    std::cout << "\n----------------------------\n";

    // lex section
    std::cout << "Writing word counter to file in lexicographical order...\n";
    std::ofstream outfile_lex("../moby_dick_counter_lex_data.txt");
    if (!outfile_lex.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    auto start_time_lex = std::chrono::high_resolution_clock::now();
    outfile_lex << wc;
    auto end_time_lex = std::chrono::high_resolution_clock::now();
    auto time_lex = end_time_lex - start_time_lex;
    std::cout << "Word counter was written to file in lexicographical order.\n";
    std::cout << "Ellapsed time: " << time_lex / std::chrono::milliseconds(1)
              << " ms.\n";
    outfile_lex.close();

    std::cout << "\n------------------------------------------------------\n\n";

    // freq section
    std::cout << "Writing word counter to file in frequency order...\n";
    std::ofstream outfile_freq("../moby_dick_counter_freq_data.txt");
    if (!outfile_freq.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    auto start_time_freq = std::chrono::high_resolution_clock::now();
    auto fit = wc.freq_begin();
    for (; fit != wc.freq_end(); ++fit) {
        outfile_freq << *fit << std::endl;
    }
    outfile_freq << *fit << std::endl;
    auto end_time_freq = std::chrono::high_resolution_clock::now();
    auto time_freq = end_time_freq - start_time_freq;
    std::cout << "Word counter was written to file in frequency order.\n";
    std::cout << "Ellapsed time: " << time_freq / std::chrono::milliseconds(1)
              << " ms.\n";
    outfile_freq.close();

    return 0;
}