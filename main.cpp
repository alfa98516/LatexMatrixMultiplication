#include "Matrix.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main(int argc, char* argv[]) {
    if (argc != 7) {
        fprintf(stderr,
                "Incorrect Usage: ./matrix [RNUM1] [CNUM1] [RNUM2] [CNUM2] [MFILE1] [MFILE2]\n");
        exit(1);
    }

    size_t row1 = std::stol(argv[1]);
    size_t column1 = std::stol(argv[2]);
    size_t row2 = std::stol(argv[3]);
    size_t column2 = std::stol(argv[4]);
    std::string strmat1;
    // IDEA: pretty much the only current way to input a matrix, maybe i will implement more.
    std::ifstream f(argv[5]);
    std::string line;
    while (std::getline(f, line)) {
        strmat1 += line;
    }

    std::string strmat2;
    std::ifstream f2(argv[6]);

    while (std::getline(f2, line)) {
        strmat2 += line;
    }

    Matrix mat1 = Matrix(strmat1, row1, column1);
    Matrix mat2 = Matrix(strmat2, row2, column2);

    std::string result = mat1 * mat2;
    std::cout << result << '\n';
}
