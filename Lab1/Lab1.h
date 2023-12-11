﻿
#include <stdexcept>
#include <complex> 
#include <cmath>
#include <iostream>
#include <random>

using namespace std;

template <typename T>
class Vector {
private:
    T* _elem;
    size_t _size;

public:
    Vector(size_t size, const T& value = T()) : _size(size), _elem(new T[size]) {
        for (size_t i = 0; i < _size; ++i) {
            _elem[i] = value;
        }
    }

    Vector(size_t size, T low_bound, T up_bound) : _size(size), _elem(new T[size]) {
        random_device rd;
        mt19937 gen(rd());

        if constexpr (is_integral<T>::value) {
            uniform_int_distribution<T> dist(low_bound, up_bound);
            for (size_t i = 0; i < _size; ++i) {
                _elem[i] = dist(gen);
            }
        }
        else if constexpr (is_floating_point<T>::value) {
            uniform_real_distribution<T> dist(low_bound, up_bound);
            for (size_t i = 0; i < _size; ++i) {
                _elem[i] = dist(gen);
            }
        }
        else {
            throw invalid_argument("Type not supported");
        }
    }

    T& operator[](size_t index) {
        if (index >= _size) {
            throw out_of_range("Index out of range");
        }
        return _elem[index];
    }

    const T& operator[](size_t index) const {
        if (index >= _size) {
            throw out_of_range("Index out of range");
        }
        return _elem[index];
    }

    Vector operator+(const Vector& other) const {
        if (_size != other._size) {
            throw invalid_argument("Vectors must have the same dimension");
        }
        Vector result(_size);
        for (size_t i = 0; i < _size; ++i) {
            result._elem[i] = _elem[i] + other._elem[i];
        }
        return result;
    }

    Vector operator-(const Vector& other) const {
        if (_size != other._size) {
            throw invalid_argument("Vectors must have the same dimension");
        }
        Vector result(_size);
        for (size_t i = 0; i < _size; ++i) {
            result._elem[i] = _elem[i] - other._elem[i];
        }
        return result;
    }

     T operator*(const Vector<T>& other) const {
        if (_size != other._size) {
            throw invalid_argument("Vectors must have the same dimension");
        }
        Vector<T> result(_size);
        for (size_t i = 0; i < _size; ++i) {
            result._elem[i] = _elem[i] * other._elem[i];
        }
        return result;
    }

    Vector operator*(const T& scalar) const {
        Vector result(_size);
        for (size_t i = 0; i < _size; ++i) {
            result._elem[i] = _elem[i] * scalar;
        }
        return result;
    }

    Vector operator/(const T& scalar) const {
        if (scalar == T()) {
            throw invalid_argument("Cannot divide by zero");
        }
        Vector result(_size);
        for (size_t i = 0; i < _size; ++i) {
            result._elem[i] = _elem[i] / scalar;
        }
        return result;
    }

    Vector(const Vector& other) : _size(other._size), _elem(new T[other._size]) {
        for (size_t i = 0; i < _size; ++i) {
            _elem[i] = other._elem[i];
        }
    }

    ~Vector() { delete[] _elem; }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            if (_size != other._size) {
                delete[] _elem;
                _size = other._size;
                _elem = new T[_size];
            }

            for (size_t i = 0; i < _size; ++i) {
                _elem[i] = other._elem[i];
            }
        }
        return *this;
    }

    size_t Get_Dim() const { return _size; }

    bool operator==(const Vector& other) const {
        const double eps = 1.0E-5;
        if (abs(_size - other._size) > eps) {
            return false;
        }

        for (size_t i = 0; i < _size; ++i) {
            if (abs(_elem[i] - other._elem[i]) > eps) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector& other) const { return !(*this == other); }

    friend ostream& operator<<(ostream& os, const Vector& vector) {
        for (size_t i = 0; i < vector._size; ++i) {
            os << vector._elem[i];
            if (i != vector._size - 1) {
                os << " ";
            }
        }

        return os;
    }
};


template <typename T>
Vector<T> find_pu_vector(const Vector<T>& a) {
    // Нормализация вектора a
    Vector<T> a_norm = a / sqrt(a * a);

    // Генерация случайного вектора b
    Vector<T> b(a.Get_Dim(), T(-1), T(1));

    // Вычисление проекции вектора b на вектор a_norm
    Vector<T> proj = (b * a_norm) * a_norm;

    // Вычисление ортогонального вектора b_orth
    Vector<T> b_orth = b - proj;

    // Нормализация вектора b_orth
    Vector<T> b_orth_norm = b_orth / sqrt(b_orth * b_orth);

    return b_orth_norm;
}
