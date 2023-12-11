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

