#include "../include/RSR_array.h"

void runExperiment() {
    std::vector<int> sizes = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000 };

    for (int size : sizes) {
        std::cout << "Size array: " << size << std::endl;

        Stats average_stats;
        std::vector<int> randomStats = ReverseSortedArray(size);
        average_stats += NaturalMergeSortWrapper(randomStats);
        std::cout << "Randomly filled array:" << average_stats << std::endl;
    }
}


int main() {
   

    runExperiment();
    return 0;
}