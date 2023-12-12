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


    void push_tail(T data) {
        Node<T>* tmp = new Node<T>(data);
        if (_head == nullptr) {
            _head = tmp;
            _tail = tmp;
            tmp->next = tmp;
            tmp->prev = tmp;
        }
        else {
            tmp->prev = _tail;
            tmp->next = _head;
            _tail->next = tmp;
            _head->prev = tmp;
            _tail = tmp;
        }
        ++_size;
    }

    void push_tail(const Cycl_List<T>& other) {
        if (other.empty()) {
            return;
        }
        if (empty()) {
            *this = other;
            return;
        }
        Node<T>* other_head = other._head;
        Node<T>* other_tail = other._tail;
        Node<T>* tmp = other_head;
        do {
            push_tail(tmp->data);
            tmp = tmp->next;
        } while (tmp != other_head);
    }



    void push_head(T data) {
        Node<T>* tmp = new Node<T>(data);
        if (_head == nullptr) {
            _head = tmp;
            _tail = tmp;
            tmp->next = tmp;
            tmp->prev = tmp;
        }
        else {
            tmp->prev = _tail;
            tmp->next = _head;
            _tail->next = tmp;
            _head->prev = tmp;
            _head = tmp;
        }
        ++_size;
    }

    

    void push_head(const Cycl_List<T>& other) {
        if (other.empty()) {
            return;
        }
        if (empty()) {
            *this = other;
            return;
        }
        Node<T>* other_head = other._head;
        Node<T>* other_tail = other._tail;
        Node<T>* tmp = other_tail;
        do {
            push_head(tmp->data);
            tmp = tmp->prev;
        } while (tmp != other_tail);
    }

    void pop_head() {
        if (_head == nullptr) {
            return;
        }
        if (_head == _tail) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else {
            Node<T>* new_head = _head->next;
            new_head->prev = _tail;
            _tail->next = new_head;
            Node<T>* old_head = _head;
            _head = new_head;
            delete old_head;
        }
        --_size;
    }

    void pop_tail() {
        if (_tail == nullptr) {
            return;
        }
        if (_head == _tail) {
            delete _tail;
            _head = nullptr;
            _tail = nullptr;
        }
        else {
            Node<T>* new_tail = _tail->prev;
            new_tail->next = _head;
            _head->prev = new_tail;
            Node<T>* old_tail = _tail;
            _tail = new_tail;
            delete old_tail;
        }
        --_size;
    }

    
    int get_len() {
        if (_head == nullptr)
            return 0;
        int len = 1;
        Node<T>* node = _head->next;
        while (node != _head) {
            len += 1;
            node = node->next;
        }
        return len;
    }



    void delete_node(T data) {
        Node<T>* tmp = _head;
        int len = get_len();
        for (int i = 0; i < len; ++i) {
            if (tmp->data == data) {
                if (tmp == _head) {
                    pop_head();
                }
                else if (tmp == _tail) {
                    pop_tail();
                }
                else {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                    delete tmp;
                    _size--;
                }
               
                return;
            }
            tmp = tmp->next;
        }
        
    }



    T& operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* current = nullptr;
        if (index < _size / 2) {
            current = _head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
        }
        else {
            current = _tail;
            for (size_t i = _size - 1; i > index; --i) {
                current = current->prev;
            }
        }

        return current->data;
    }


    const T& operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }

        const Node<T>* current = nullptr;
        if (index < _size / 2) {
            current = _head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
        }
        else {
            current = _tail;
            for (size_t i = _size - 1; i > index; --i) {
                current = current->prev;
            }
        }

        return current->data;
    }


    void clear() {
        while (!empty()) {
            pop_head();
        }
    }

    ~Cycl_List() {
        clear();
    }

    bool empty() const {
        return (_size == 0);
    }

    
};



template<typename T>
void reverse(Cycl_List<T>& list) {
    if (list._head == nullptr || list._head == list._tail) {
        return;
    }

    Node<T>* current = list._head;
    Node<T>* new_tail = list._head;

    do {
        Node<T>* temp_next = current->next;

        current->next = current->prev;
        current->prev = temp_next;

        current = temp_next;
    } while (current != list._head);

    list._head = list._tail;
    list._tail = new_tail;
}


#endif
