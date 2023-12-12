#include <iostream>
#include "vector.cc"

int main()
{
    Vector<double> a;
    a.input_from_keyboard();

    Vector<double> b = find_pu_vector(a);
    double p = a ^ b;
    std::cout << "Perpendicular unit vector: " << b << std::endl;
    std::cout << "Perpendicular unit vector: " << p << std::endl;
    return 0;
}