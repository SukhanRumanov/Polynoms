#pragma once
#include <vector>
#include <iostream>

template<int Prime>
class Polynomial {
private:
    std::vector<int> coefficients;

    void trim();
    int mod(int value) const;

public:
    template<typename T>
    explicit Polynomial(T&& coeffs);

    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
        for (size_t i = 0; i < poly.coefficients.size(); ++i) {
            if (i > 0) os << " + ";
            os << poly.coefficients[i] << "x^" << i;
        }
        return os;
    }
};
