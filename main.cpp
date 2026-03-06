#include "Matrix.hpp"
#include <iostream>
#include <string>
int main(int argc, char* argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Incorrect Usage: ./matrix [RNUM] [CNUM]");
        exit(1);
    }

    size_t row = std::stol(argv[1]);
    size_t collumn = std::stol(argv[2]);
    std::string strmat1;
    // for (size_t i = 0; i < row; ++i) {
    //     std::string curr;
    //     std::cin >> curr;
    //     strmat1 += curr;
    // }
    strmat1 = "0 & 0 & 0 & 1 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 1 & 0 & 0 & 0 \\";

    std::string strmat2;

    // for (size_t j = 0; j < row; ++j) {
    //     std::string curr;
    //     std::cin >> curr;
    //     strmat2 += curr;
    // }

    strmat2 = "0 & 0 & 5 & -5 \\ -2 & 1 & -2 & -1 \\ 0 & 4 & 3 & -1 \\ 2 & 1 & 3 & 1";
    Matrix mat1 = Matrix(strmat1, row, collumn);
    Matrix mat2 = Matrix(strmat2, row, collumn);
    std::string result = mat1 * mat2;
    std::cout << result;
}
