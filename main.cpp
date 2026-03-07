#include "Matrix.hpp"
#include <fstream>
#include <iostream>
#include <string>
int main(int argc, char* argv[]) {

    if (argc != 5) {
        fprintf(stderr, "Incorrect Usage: ./matrix [RNUM] [CNUM] [MFILE1] [MFILE2]");
        exit(1);
    }

    size_t row = std::stol(argv[1]);
    size_t collumn = std::stol(argv[2]);
    std::string strmat1;

    std::ifstream f(argv[3]);
    std::string line;
    while (std::getline(f, line)) {
        strmat1 += line;
    }

    std::cout << strmat1;
    std::string strmat2;
    std::ifstream f2(argv[3]);

    while (std::getline(f2, line)) {
        strmat2 += line;
    }

    Matrix mat1 = Matrix(strmat1, row, collumn);
    Matrix mat2 = Matrix(strmat2, row, collumn);
    std::string result = mat1 * mat2;
    std::cout << result << '\n';
}
