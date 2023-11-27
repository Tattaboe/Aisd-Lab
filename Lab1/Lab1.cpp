#include <cmath>
#define VECTOR_H_
#include <iostream>
#include "Lab1.h"

using namespace std;

int main()
{
	int size_b, size_a;
	double value_b, value_a;
	
	
	
	cout << "Enter the size and value of an arbitrary vector" << endl;
	cout << "Size: ";
	cin >> size_b;
	Vector<double> b(size_b, value_b);
	for (size_t i = 0; i < size_b; ++i) {
		cout << "Enter the size and value of an arbitrary vector" << endl;
		cin >> b[i];
	}
	
	

	cout << "Enter size and value for the specified vector" << endl;
	cout << "Size: ";
	cin >> size_a;
	while (size_a != size_b) {
		cout << "The sizes of vectors l and a must be the same" << endl;
		cout << "Enter size and value for the specified vector" << endl;
		cout << "Size: ";
		cin >> size_a;
		break;
	}
	cout << "Value: ";
	cin >> value_a;
	Vector<double> a(size_a, value_a);

	Vector<double> p = Perpendicular(a, b);
	cout << "Perpendicular:" << '(' << p.Get_Dim() << ',' << p << ')' << endl;
	

};
