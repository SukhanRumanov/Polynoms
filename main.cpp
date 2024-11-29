#include <vector>
#include <iostream>
#include "Polynom.hpp"

int main(){
    Polynomial poly1 = Polynomial(std::vector<int>{1, 2, 3});
    Polynomial poly2 = Polynomial(std::vector<int>{6, 5, 4});
    auto sum = poly1 + poly2;     
    auto product = poly1 * poly2;
    std::cout << "Poly1: " << poly1 << "\n";    
    std::cout << "Poly2: " << poly2 << "\n";    
    std::cout << "Sum: " << sum << "\n";        
    std::cout << "Product: " << product << "\n";

    return 0;
}
