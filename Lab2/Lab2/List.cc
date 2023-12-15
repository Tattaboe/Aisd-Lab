#include "List.h"

#include<cmath>
#include <iostream>

int main() {
    Cycl_List<int> list;
    list.push_tail(6);
    list.push_tail(7);
    list.push_tail(8);
    list.push_tail(9);
    list.push_tail(10);
    list.push_head(5);
    list.push_head(4);
    list.push_head(3);
    list.push_head(2);
    list.push_head(1);

    std::cout << "Original list: ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    reverse(list);

    std::cout << "Reversed list: ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;


    Cycl_List<int> rand_list(5, 1, 8);

    std::cout << "Random_Original list: ";
    for (size_t i = 0; i < rand_list.size(); i++) {
        std::cout << rand_list[i] << " ";
    }
    std::cout << std::endl;

    reverse(rand_list);

    std::cout << "Random_Reversed list: ";
    for (size_t i = 0; i < rand_list.size(); i++) {
        std::cout << rand_list[i] << " ";
    }
    std::cout << std::endl;


    list.pop_head();
    list.pop_tail();

    std::cout << "Reversed list (pop_head() and pop_tail()): ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;

    reverse(list);

    std::cout << "Original list (pop_head() and pop_tail()): ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;


    list.delete_node(5);

    std::cout << "List with 'delete_node()': ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}