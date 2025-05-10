#include <iostream>
#include <fstream>
#include <string>

#include "Smoother.h"

int main() {
    std::cout << "Enter the name of the source file: ";
    std::string file;
    std::cin >> file;

    Smoother smoother;
    smoother.readData(file);
    smoother.smooth();
    smoother.print();

    return 0;
}
