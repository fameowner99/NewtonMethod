#ifndef MATRIX_HPP

#define  MATRIX_HPP

#include <vector>
#include <iostream>
#include <cmath>

class Matrix
{
public:
    Matrix(Matrix&);
    Matrix(std::vector<std::vector<double>>);
    bool    operator==(const Matrix&)const;
    Matrix  &operator=(const Matrix&);
    Matrix  operator+(const Matrix&);
    Matrix  operator-(const Matrix&);
    Matrix  &operator*(const Matrix&);
    Matrix  &operator*(const double&);
    Matrix  determinant();
    Matrix  inverse();
    Matrix  transposition();
    Matrix

    void    setMatrix(const std::vector<std::vector<double>>&);
    std::vector<std::vector<double>> getMatrix()const;
    void    print();


private:
    std::vector<std::vector<double>> matrix;
    const double epsilon = 0.00000000000005;
};

#endif