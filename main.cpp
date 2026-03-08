#include "Matrix.hpp"
#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum struct Options { s1, s2, o, c };

void error() {
    fprintf(stderr, "Incorrect Usage: ./matrix [Options] [Rnum1] [Cnum1] [Rnum2] [Cnum2] "
                    "[Mfile1] [Mfile2]\n");
    exit(1);
}

void help() {

    fprintf(stderr,
            "Usage: ./matrix [Options] [Rnum1] [Cnum1] [Rnum2] [Cnum2] [Mfile1] [Mfile2]\n");
    fprintf(stderr,
            "Options: \n   -h: Outputs this text\n   -s1 [Double]: Scales the first matrix "
            "by a double value\n   "
            "-s2 [Double]: Scales the second matrix by a double value\n   "
            "-o [Outfile]: Output matrix to a file\n   -c [Outfile]: Outputs the actual "
            "calculation between the matrices to the outfile. \n                 If file is "
            "ommited, outputs to standard out instead.\nSee README.md for more instructions.\n");
    exit(0);
}

void flags(int argc, char* argv[], double& scaler1, double& scaler2, std::string& outf,
           bool& calculate, std::string coutf) {
    for (int i = 1; i < argc; ++i) { // starting at one to only parse the options.
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j] != '\0'; ++i) { // also starts at one to skip the hyphen
                if (argv[i][j] == 's') {
                    switch (argv[i][2]) {
                    case '1':
                        scaler1 = std::stod(argv[i + 1]);
                        break;
                    case '2':
                        scaler2 = std::stod(argv[i + 1]);
                        break;
                    }
                } else if (argv[i][j] == 'o') {
                    outf = argv[i + 1];
                } else if (argv[i][j] == 'c') {
                    calculate = true;
                    if (argv[i + 1][0] != '-' && !std::isdigit(argv[i + 1][0])) {
                        coutf = argv[i + 1];
                    }
                } else if (argv[i][j] == 'h') {
                    help();
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        error();
    }

    double scaler1 = 1;
    double scaler2 = 1;
    bool calculate = false;
    std::string outf = "";
    std::string coutf = "";
    if (argv[1][0] == '-') {
        flags(argc, argv, scaler1, scaler2, outf, calculate, coutf);
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
    std::unique_ptr<std::ofstream> file;
    std::ostream* out = &std::cout;

    if (!outf.empty()) {
        file = std::make_unique<std::ofstream>(outf);
        out = file.get();
    }

    *out << result << '\n'; // we are technically always outputting to a file stream, we just
                            // sometimes treat stdout as a file.
}
