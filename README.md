# LatexMatrixMultiplication

I made this for the course T-201-LINC course taught at Reykjavík University. This is a linear algebra course. <br>
The reason I decided to do this is because I was working on an assignment, and I was about to do a matrix multiplication between two 4x4 matrices, then I thought I could just automate it.

## Prerequisites

The only actual prerequisite is having the gcc compiler installed on your system, which you probably do.

## Compiling
You just run 
```Bash
make
```
## Running
The compiling will give you the binary file *matrix*. To run the binary you run:
```Bash
./matrix [RNUM1] [CNUM1] [RNUM2] [CNUM2] [MATFILE1] [MATFILE2]
```
*RNUM* and *CNUM* are the number of rows and columns in the matrix. <br>
The *MATFILE*s are the LaTeX matrices you are multiplying together, they are formatted thusly:
```LaTeX
1 & 3 \\ 
6 & 4
```
Do not include \begin{bmatrix} or any other matrix format, this will mess up the parsing.

