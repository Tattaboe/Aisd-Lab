#include "RSR_array.h"

void runExperiment() {
    std::vector<int> sizes = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000 };

    for (int size : sizes) {
        std::cout << "Size array: " << size << std::endl;


        Stats randomStats = RandomStats(size);
        std::cout << "Randomly filled array:" << randomStats << std::endl;
    }
}


int main() {
   

    runExperiment();
    return 0;
}