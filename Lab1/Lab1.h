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
	T* _elements;
	size_t _size;

public:
	Vector(size_t size, const T& value = T());
	Vector(size_t size, T low_bound, T up_bound);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;

	T operator*(const Vector& other) const;
	Vector operator*(const T& scalar) const;

	Vector operator/(const T& scalar) const;

	Vector(const Vector& other);
	~Vector();

	Vector& operator=(const Vector& other);
	size_t Get_Dim() const;

	bool operator==(const Vector& other) const;
	bool operator!=(const Vector& other) const;
	friend ostream& operator<<(ostream& os, const Vector& vector);
};