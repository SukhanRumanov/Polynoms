#pragma once
#include <vector>
#include <iostream>

class Polynomial {
private:
    std::vector<int> coefficients; 
    void trim();                   

public:
    template<typename T>
    Polynomial(T&& coeffs) {
        for (const auto& coeff : coeffs) {
            coefficients.push_back(coeff);
        }
        trim();
    }

    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const; 
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
};


