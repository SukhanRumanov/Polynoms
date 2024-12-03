#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

template<int Prime>
class Polynomial {
private:
    std::vector<int> coefficients;

    void trim() {
        while (!coefficients.empty() && coefficients.back() == 0) {
            coefficients.pop_back();
        }
        if (coefficients.empty()) {
            coefficients.push_back(0);
        }
    }

    int mod(int value) const {
        value %= Prime;
        if (value < 0) value += Prime;
        return value;
    }

public:
    template<typename T>
    explicit Polynomial(T&& coeffs) {
        static_assert(Prime > 1, "Error");

        coefficients.assign(std::begin(coeffs), std::end(coeffs));
        for (auto& coeff : coefficients) {
            coeff = mod(coeff);
        }
        trim();
    }

    Polynomial operator+(const Polynomial& other) const {
        size_t maxSize = std::max(coefficients.size(), other.coefficients.size());
        std::vector<int> result(maxSize);

        for (size_t i = 0; i < maxSize; ++i) {
            int a = (i < coefficients.size()) ? coefficients[i] : 0;
            int b = (i < other.coefficients.size()) ? other.coefficients[i] : 0;
            result[i] = mod(a + b);
        }

        return Polynomial(std::move(result));
    }

    Polynomial operator*(const Polynomial& other) const {
        size_t newSize = coefficients.size() + other.coefficients.size() - 1;
        std::vector<int> result(newSize, 0);

        for (size_t i = 0; i < coefficients.size(); ++i) {
            for (size_t j = 0; j < other.coefficients.size(); ++j) {
                result[i + j] = mod(result[i + j] + mod(coefficients[i] * other.coefficients[j]));
            }
        }

        return Polynomial(std::move(result));
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
        for (size_t i = 0; i < poly.coefficients.size(); ++i) {
            if (i > 0) os << " + ";
            os << poly.coefficients[i] << "x^" << i;
        }
        return os;
    }
};
