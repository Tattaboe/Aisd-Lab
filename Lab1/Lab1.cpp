#include <cmath>
#define VECTOR_H_
#include <iostream>
#include "Lab1.h"

using namespace std;

int main()
{
	int  size_a;
	double  value_a;
	
	
	
	cout << "Enter the size and value of an arbitrary vector" << endl;
	cout << "Size: ";
	cin >> size_a;
	Vector<double> a(size_a, value_a);
	for (size_t i = 0; i < size_a; ++i) {
		cout << "Enter the size and value of an arbitrary vector" << endl;
		cin >> a[i];
	}
	
	
    Vector<double> b = find_pu_vector(a);
	cout << "Перпендикулярный единичный вектор: " << b << endl;

	return 0;
};
