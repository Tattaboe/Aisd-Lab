#ifndef LIST_INCLUDE_LIST_H
#define LIST_INCLUDE_LIST_H

#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>
#include <cmath>


template <typename T>
struct Node {
    Node* next, * prev;
    T data;

    Node(T data) : data(data), prev(nullptr), next(nullptr) {};
};

template <typename T>
class Cycl_List {
    Node<T>* _head, * _tail;
    size_t _size;
public:
    Cycl_List() : _head(nullptr), _tail(nullptr), _size(0) {};

    Cycl_List(const Cycl_List& other) {
        _head = nullptr;
        _tail = nullptr;
        Node<T>* tmp = other._head;
        push_tail(tmp->data);
        tmp = tmp->next;
        while (tmp != other._head) {
            push_tail(tmp->data);
            tmp = tmp->next;
        }
    }


    Cycl_List(size_t size, T low_bound, T up_bound) :Cycl_List() {
        std::random_device rd;
        std::mt19937 gen(rd());

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(low_bound, up_bound);

            for (size_t i = 0; i < size; ++i) {
                T data = dist(gen);
                push_tail(data);
            }
        }
        else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(low_bound, up_bound);

            for (size_t i = 0; i < size; ++i) {
                T data = dist(gen);
                push_tail(data);
            }
        }
        _size = size;
    }


    Cycl_List& operator=(const Cycl_List& other) {
        if (this != &other) {
            Cycl_List tmp(other); 
            std::swap(_head, tmp._head); 
            std::swap(_tail, tmp._tail); 
            _size = tmp._size; 
        }
        return *this;
    }

    size_t size() const {
        return _size;
    }



