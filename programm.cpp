#include "src/decimal.h"
#include <iostream>

int main() {
    Decimal a;
    Decimal b(12345);
    Decimal c("6789");
    Decimal d({9,8,7,6});
    Decimal d2(d);

    std::cout << "a = "; a.printTo(); std::cout << "\n";
    std::cout << "b = "; b.printTo(); std::cout << "\n";
    std::cout << "c = "; c.printTo(); std::cout << "\n";
    std::cout << "d = "; d.printTo(); std::cout << "\n";
    std::cout << "&d = " << &d << "&d2 = " << &d2 << "\n";

    Decimal sum = b.sum(c);
    Decimal diff = b.addition_minus(c);

    std::cout << "b + c = "; sum.printTo(); std::cout << "\n";
    std::cout << "b - c = "; diff.printTo(); std::cout << "\n";

    std::cout << "b == c: " << b.check_eq(c) << "\n";
    std::cout << "b > c: " << b.check_more(c) << "\n";
    std::cout << "b < c: " << b.check_less(c) << "\n";
}
