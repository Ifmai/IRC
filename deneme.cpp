#include <iostream>
#include <string>

int main() {
    std::string a = "hello\0";
    std::string b = "world\0";

    a += b.data(); // b'nin tamamını a'ya ekler, NULL karakterler dahil

    std::cout << "Combined string: " << a << std::endl;

    return 0;
}
