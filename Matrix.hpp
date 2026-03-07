#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#ifndef MATRIX
#define MATRIX
struct Matrix {
    std::string LatexMatrix;
    size_t row;
    size_t column;
    std::shared_ptr<std::vector<std::vector<std::string> > > mat;

    Matrix(std::string _LatexMatrix, size_t _row, size_t _column)
        : LatexMatrix(_LatexMatrix), row(_row), column(_column) {
        mat = parse();
    }

    Matrix(std::vector<std::vector<std::string> > _mat, size_t _row, size_t _column)
        : row(_row), column(_column) {
        mat = std::make_unique<std::vector<std::vector<std::string> > >(_mat);
    }

    std::string operator*(const Matrix& other) {

        if (column != other.row) {
            throw std::runtime_error("Matrix dimensions incompatible for multiplication: "
                                     "left columns (" +
                                     std::to_string(column) +
                                     ") != "
                                     "right rows (" +
                                     std::to_string(other.row) + ")");
        }
        std::ostringstream result;
        result << "\\begin{bmatrix}\n";
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < other.column; ++j) {
                // Build the sum for entry (i,j)
                std::string entry;
                for (size_t k = 0; k < column; ++k) {
                    if (k > 0) entry += " + ";
                    entry += (*mat)[i][k] + " \\cdot " + (*other.mat)[k][j];
                }
                result << entry;

                // Separate columns with &, except after the last column
                if (j < other.column - 1) result << " & ";
            }
            // End the row with \\, except for the last row
            if (i < row - 1) result << " \\\\\n";
        }

        result << "\n\\end{bmatrix}";
        return result.str();
    }

    void operator*(const double scaler) {
        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < column; ++j) {
                double val;
                try {
                    val = std::stod((*mat)[i][j]);
                    val *= scaler;

                } catch (std::invalid_argument) {
                    val = (double)std::stoi((*mat)[i][j]);
                    val *= scaler;
                }
                (*mat)[i][j] = std::to_string(val);
            }
        }
    }

  private:
    /*
     * @brief: parese the LatexMatrix and turns it into a matrix.
     * @return: shared_ptr of a matrix, this is to avoid manual allocation.
     */
    std::shared_ptr<std::vector<std::vector<std::string> > > parse() {
        // HACK: The parsing and matrix construction could be done at the same time. Might fix
        // later.
        std::vector<std::string> vals = std::vector<std::string>(0);
        std::string curr;
        bool integer = false;
        bool variable = false; // IDEA: I'll do this later if i need it.
        for (char c : LatexMatrix) {
            if (std::isspace(c)) continue;

            if (integer) {
                if (!std::isdigit(c)) {

                    integer = false;
                    vals.push_back(curr);
                    curr = "";

                } else {
                    curr += c;
                    continue;
                }
            }

            switch (c) {
            case '\\':
                continue;
            case '&':
                continue;
            case '-':
                curr += c;
                integer = true;
                continue;
            default:
                integer = std::isdigit(c);

                curr += c;
                if ((!integer)) {
                    fprintf(stderr, "Error: Invalid Latex Matrix: %c", c);
                    exit(1);
                }
            }
        }
        if (integer) {
            vals.push_back(curr);
        }

        std::shared_ptr<std::vector<std::vector<std::string> > > _mat =
            std::make_shared<std::vector<std::vector<std::string> > >();

        size_t index = 0;
        for (size_t i = 0; i < row; ++i) {
            std::vector<std::string> vec;
            vec.reserve(column);
            for (size_t j = 0; j < column; ++j) {
                if (index >= vals.size()) {
                    throw std::runtime_error("Matrix has fewer elements than expected");
                }
                vec.push_back(vals[index++]);
            }
            _mat->push_back(vec);
        }

        return _mat;
    }
};
#endif
