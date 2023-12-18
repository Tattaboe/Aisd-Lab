#include "Sort.h"

void PrintVector(const std::vector<int>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {
   

    std::vector<int> arr = { 6, 23, 14, 0, 8, 2, 34, 12, 4, 5 };

    std::cout << "Source array:" << std::endl;
    PrintVector(arr);

    Stats bubble_stats = Bubble_Sort(arr);
    std::cout << "\nBubble sort result:" << std::endl;
    PrintVector(arr);
    std::cout << bubble_stats;

    std::vector<int> arr_cocktail = { 6, 23, 14, 0, 8, 2, 34, 12, 4, 5 };
    Stats cocktail_stats = Cocktail_Sort(arr_cocktail);
    std::cout << "\nCocktail sort result:" << std::endl;
    PrintVector(arr_cocktail);
    std::cout << cocktail_stats;

    std::vector<int> arr_merge = { 6, 23, 14, 0, 8, 2, 34, 12, 4, 5 };
    Stats merge_stats = NaturalMergeSortWrapper(arr_merge);
    std::cout << "\nNatural merge sort result:" << std::endl;
    PrintVector(arr_merge);
    std::cout << merge_stats;

    return 0;
}