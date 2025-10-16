#pragma once
#include <vector>
#include <string>
#include <initializer_list>
#include <ostream>

class Decimal {
private:
    std::vector<int> digits;

    static std::vector<int> normalize(const std::vector<int>& d);
    static std::vector<int> fromString(const std::string& s);
    Decimal(const std::vector<int>& d);

public:
    Decimal() = default;
    Decimal(const std::initializer_list<int>& t);
    Decimal(const std::string& s);
    Decimal(int value);
    Decimal(const Decimal& d) = default;
    Decimal(Decimal&& d) noexcept = default;
    ~Decimal() = default;

    std::string toString() const;
    size_t size() const noexcept;

    Decimal sum(const Decimal& rhs) const;
    Decimal addition_minus(const Decimal& rhs) const;

    bool check_eq(const Decimal& rhs) const noexcept;
    bool check_not_eq(const Decimal& rhs) const noexcept;
    bool check_more(const Decimal& rhs) const noexcept;
    bool check_more_or_eq(const Decimal& rhs) const noexcept;
    bool check_less(const Decimal& rhs) const noexcept;
    bool check_less_or_eq(const Decimal& rhs) const noexcept;

    void printTo() const;
};