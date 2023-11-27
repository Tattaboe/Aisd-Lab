#include <stdexcept>
#include <complex> 
#include <cmath>
#include <iostream>
#include <random>
#define VECTOR_H_

using namespace std;

const double PI = 3.14159265358979323846;

template <typename T>
class Vector {
private: 
	T* _elem;
	size_t _size;

public:


	Vector(size_t size, const T& value = T()): _size(size), _elem(new T[size]) {
        for (size_t i = 0; i < _size; ++i) {
            _elem[i] = value;
        }
    }

    Vector(size_t size, T low_bound, T up_bound): _size(size), _elem(new T[size]) {
        std::random_device rd;
        std::mt19937 gen(rd());

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
    _size
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




    T operator*(const Vector& other) const {
        if (_size != other._size) {
            throw invalid_argument("Vectors must have the same dimension");
        }
        T result = T();
        for (size_t i = 0; i < _size; ++i) {
            result += _elem[i] * other._elem[i];
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


	Vector operator/(const T& scalar) const;

	Vector(const Vector& other);
	~Vector();

	Vector& operator=(const Vector& other);
	size_t Get_Dim() const;

	bool operator==(const Vector& other) const;
	bool operator!=(const Vector& other) const;
	friend ostream& operator<<(ostream& os, const Vector& vector);
};





