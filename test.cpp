#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // بررسی اینکه دقیقا 4 آرگومان وارد شده باشد (اسم برنامه و سه آرگومان)
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " param1 param2 param3" << std::endl;
        return 1;
    }

    // دریافت پارامترها
    std::string param1 = argv[1];
    std::string param2 = argv[2];
    std::string param3 = argv[3];

    // نمایش پارامترها
    std::cout << "Param 1: " << param1 << std::endl;
    std::cout << "Param 2: " << param2 << std::endl;
    std::cout << "Param 3: " << param3 << std::endl;

    return 0;
}
