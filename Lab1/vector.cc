#include <stdexcept> 
#include <iostream> 
#include <random> 
#include <cmath> 
#include <complex> 

template <typename T>
class Vector {
private:
	T* _elem;
	size_t _size;

public:
	Vector() : _size(0), _elem(nullptr) {}

	explicit Vector(size_t size, const T& value = T()) : _size(size), _elem(new T[size]) {
		for (size_t i = 0; i < _size; ++i) {
			_elem[i] = value;
		}
	}

	Vector(size_t size, T low_bound, T up_bound) : _size(size), _elem(new T[size]) {
		std::random_device rd;
		std::mt19937 gen(rd());

		if constexpr (std::is_integral<T>::value) {
			std::uniform_int_distribution<T> dist(low_bound, up_bound);
			for (size_t i = 0; i < _size; ++i) {
				_elem[i] = dist(gen);
			}
		}
		else if constexpr (std::is_floating_point<T>::value) {
			std::uniform_real_distribution<T> dist(low_bound, up_bound);
			for (size_t i = 0; i < _size; ++i) {
				_elem[i] = dist(gen);
			}
		}
		else {
			throw std::invalid_argument("Type not supported");
		}
	}

	T& operator[](size_t index) {
		if (index >= _size) {
			throw std::out_of_range("Index out of range");
		}
		return _elem[index];
	}

	const T& operator[](size_t index) const {
		if (index >= _size) {
			throw std::out_of_range("Index out of range");
		}
		return _elem[index];
	}

	Vector operator+(const Vector& other) const {
		if (_size != other._size) {
			throw std::invalid_argument("Vectors must have the same dimension");
		}
		Vector result(_size);
		for (size_t i = 0; i < _size; ++i) {
			result._elem[i] = _elem[i] + other._elem[i];
		}
		return result;
	}

	Vector operator-(const Vector& other) const {
		if (_size != other._size) {
			throw std::invalid_argument("Vectors must have the same dimension");
		}
		Vector result(_size);
		for (size_t i = 0; i < _size; ++i) {
			result._elem[i] = _elem[i] - other._elem[i];
		}
		return result;
	}

	Vector<T> operator*(const Vector<T>& other) const {
		if (_size != other._size) {
			throw std::invalid_argument("Vectors must have the same dimension");
		}
		Vector<T> result(_size);
		for (size_t i = 0; i < _size; ++i) {
			result._elem[i] = _elem[i] * other._elem[i];
		}
		return result;
	}

	T operator^(const Vector<T>& other) const {
		if (_size != other._size) {
			throw std::invalid_argument("Vectors must have the same dimension");
		}
		T result=0;
		for (size_t i = 0; i < _size; ++i) {
			result+= _elem[i] * other._elem[i];
		}
		return result;
	}

	template <typename U>
	auto operator*(const U& operand) const {
		if constexpr (std::is_same_v<U, T>) {

			Vector result(_size);
			for (size_t i = 0; i < _size; ++i) {
				result._elem[i] = _elem[i] * operand;
			}
			return result;
		}
		else if constexpr (std::is_same_v < U, std::complex < double>>) {

			std::complex<double> result = 0.0;
			for (size_t i = 0; i < _size; ++i) {
				result += _elem[i] * std::conj(operand.elements_[i]);
			}
			return result;
		}
		else {
			throw std::invalid_argument("Unsupported operand type");
		}
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
			throw std::invalid_argument("Cannot divide by zero");
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

	~Vector() {
		delete[] _elem;
	}

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
		if (std::abs(_size - other._size) > eps) {
			return false;
		}

		for (size_t i = 0; i < _size; ++i) {
			if (std::abs(_elem[i] - other._elem[i]) > eps) {
				return false;
			}
		}

		return true;
	}

	bool operator!=(const Vector& other) const { return !(*this == other); }

	friend std::ostream& operator<<(std::ostream& os, const Vector& vector) {
		for (size_t i = 0; i < vector._size; ++i) {
			os <<
				vector._elem[i];
			if (i != vector._size - 1) {
				os << " ";
			}
		}

		return os;
	}

	void input_from_keyboard() {
		std::cout << "Input size: ";
		std::cin >> _size;

		if (_elem != nullptr) {
			delete[] _elem;
		}

		_elem = new T[_size];

		for (size_t i = 0; i < _size; ++i) {
			std::cout << "Enter element " << i << " of the vector: ";
			std::cin >> _elem[i];
		}
	}

	void swap(size_t index1, size_t index2) {
		if (index1 >= _size || index2 >= _size) {
			throw std::out_of_range("Index out of range");
		}

		T temp = _elem[index1];
		_elem[index1] = _elem[index2];
		_elem[index2] = temp;
	}

	T get_length() const {
		T length_squared = static_cast<T>(0);

		for (size_t i = 0; i < _size; ++i) {
			length_squared += _elem[i] * _elem[i];
		}

		return std::sqrt(length_squared);
	}
};



template <typename T>
Vector<T> FindPerpendicularUnitVector(const Vector<T>& a) {
	if (a.Get_Dim() != 2) {
		throw std::invalid_argument("Perpendicular vector calculation is only supported for 2D vectors.");
	}

	//T length = a.get_length();

	//if (length == T(0)) {
	//	throw std::invalid_argument("Cannot normalize zero vector");
	//}

	Vector<T> perp(2);
	perp[0] = -a[1];
	perp[1] = a[0];
	T length = perp.get_length();
	perp = perp / length;
	return perp;
}


//template<typename T>
//Vector<T> FindPerpendicularUnitVector(const Vector<T>& a) {
//	// Вычисляем перпендикулярный вектор, меняя координаты местами и меняя знак одной из них
//	Vector<T> perpendicular(-a.y, a.x);
//
//	// Нормализуем вектор, чтобы получить единичный вектор
//	double length = sqrt(perpendicular.x * perpendicular.x + perpendicular.y * perpendicular.y);
//	perpendicular.x /= length;
//	perpendicular.y /= length;
//
//	return perpendicular;
//}