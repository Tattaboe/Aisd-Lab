#include <iostream> 
#include "vector.cc" 

int main()
{
	Vector<double> a;
	a.input_from_keyboard();

	Vector<double> b = FindPerpendicularUnitVector(a);
	double p = a ^ b;
	std::cout << "Perpendicular unit vector: " << p << std::endl;


	return 0;
}
