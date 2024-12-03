#include "Polynom.hpp"

template<int Prime>
int Polynomial<Prime>::mod(int value) const {
    value %= Prime;
    if (value < 0) value += Prime;
    return value;
}

template<int Prime>
void Polynomial<Prime>::trim() {
    while (!coefficients.empty() && coefficients.back() == 0) {
        coefficients.pop_back();
    }
    if (coefficients.empty()) {
        coefficients.push_back(0);
    }
}


template<int Prime>
template<typename T>
Polynomial<Prime>::Polynomial(T&& coeffs) {
    static_assert(Prime > 1, "Error");

    coefficients.assign(std::begin(coeffs), std::end(coeffs));

    for (auto& coeff : coefficients) {
        coeff = mod(coeff);
    }

    trim();

}

template<int Prime>
Polynomial<Prime> Polynomial<Prime>::operator+(const Polynomial& other) const {
    size_t maxSize = std::max(coefficients.size(), other.coefficients.size());
    std::vector<int> result(maxSize);

    for (size_t i = 0; i < maxSize; ++i) {
        int a = (i < coefficients.size()) ? coefficients[i] : 0;
        int b = (i < other.coefficients.size()) ? other.coefficients[i] : 0;
        result[i] = mod(a + b);
    }

    return Polynomial(std::move(result));
}

template<int Prime>
Polynomial<Prime> Polynomial<Prime>::operator*(const Polynomial& other) const {
    size_t newSize = coefficients.size() + other.coefficients.size() - 1;
    std::vector<int> result(newSize, 0);

    for (size_t i = 0; i < coefficients.size(); ++i) {
        for (size_t j = 0; j < other.coefficients.size(); ++j) {
            result[i + j] = mod(result[i + j] + mod(coefficients[i] * other.coefficients[j]));
        }
    }

    return Polynomial(std::move(result));
}

template class Polynomial<7>;
