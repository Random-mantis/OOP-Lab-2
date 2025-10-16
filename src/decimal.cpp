#include "decimal.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

std::vector<int> Decimal::normalize(const std::vector<int>& d) {
    std::vector<int> res = d;
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    if (res.empty()) res.push_back(0);
    return res;
}

std::vector<int> Decimal::fromString(const std::string& s) {
    if (s.empty()) return {0};
    std::vector<int> res;
    res.reserve(s.size());
    for (auto i = s.rbegin(); i != s.rend(); ++i) {
        res.push_back(*i - '0');
    }
    return normalize(res);
}

Decimal::Decimal(const std::vector<int>& d)
    : digits(normalize(d)) {}

std::string Decimal::toString() const {
    if (digits.empty()) return "0";
    std::string result;
    result.reserve(digits.size());
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) result.push_back('0' + *it);
    return result;
}

size_t Decimal::size() const noexcept {
    return digits.size();
}

Decimal::Decimal(const std::initializer_list<int>& t) {
    if (t.size() == 0) {
        digits = {0};
        return;
    }
    std::vector<int> tmp(t);
    std::reverse(tmp.begin(), tmp.end());
    for (int d : tmp) {
        if (d < 0 || d > 9) throw std::invalid_argument("Digit must be 0..9");
    }
    digits = normalize(tmp);
}

Decimal::Decimal(const std::string& s)
    : digits(fromString(s)) {}

Decimal::Decimal(int value) {
    if (value < 0) throw std::invalid_argument("Negative numbers not supported");
    if (value == 0) {
        digits = {0};
        return;
    }
    while (value > 0) {
        digits.push_back(value % 10);
        value /= 10;
    }
    digits = normalize(digits);
}

bool Decimal::check_eq(const Decimal& rhs) const noexcept {
    return digits == rhs.digits;
}

bool Decimal::check_not_eq(const Decimal& rhs) const noexcept {
    return !check_eq(rhs);
}

bool Decimal::check_less(const Decimal& rhs) const noexcept {
    if (digits.size() != rhs.digits.size())
        return digits.size() < rhs.digits.size();
    for (size_t i = digits.size(); i-- > 0;) {
        if (digits[i] != rhs.digits[i]) return digits[i] < rhs.digits[i];
    }
    return false;
}

bool Decimal::check_less_or_eq(const Decimal& rhs) const noexcept {
    return check_less(rhs) || check_eq(rhs);
}

bool Decimal::check_more(const Decimal& rhs) const noexcept {
    return rhs.check_less(*this);
}

bool Decimal::check_more_or_eq(const Decimal& rhs) const noexcept {
    return !check_less(rhs);
}

Decimal Decimal::sum(const Decimal& rhs) const {
    std::vector<int> res;
    const size_t n = std::max(digits.size(), rhs.digits.size());
    res.reserve(n + 1);
    int carry = 0;
    for (size_t i = 0; i < n || carry; ++i) {
        int sum = carry;
        if (i < digits.size()) sum += digits[i];
        if (i < rhs.digits.size()) sum += rhs.digits[i];
        res.push_back(sum % 10);
        carry = sum / 10;
    }
    return Decimal(res);
}

Decimal Decimal::addition_minus(const Decimal& rhs) const {
    if (check_less(rhs))
        throw std::underflow_error("Negative result not supported");

    std::vector<int> res;
    res.reserve(digits.size());
    int borrow = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        int diff = digits[i] - borrow;
        if (i < rhs.digits.size()) diff -= rhs.digits[i];
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.push_back(diff);
    }
    return Decimal(normalize(res));
}

void Decimal::printTo() const {
    for (auto it = digits.rbegin(); it != digits.rend(); ++it)
        std::cout << *it;
}