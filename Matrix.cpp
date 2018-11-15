#include "Matrix.hpp"


const int Matrix::getSizeColomn()const
{
    return ((int)matrix[0].size());
}

const int Matrix::getSizeRows()const
{
    return ((int)matrix.size());
}

Matrix::Matrix(Matrix &other)
{
    std::vector<double>         tmpLine;

    for (int y = 0; y < other.getSizeRows(); ++y)
    {
        for (int x = 0; x < other.getSizeColomn(); ++x)
        {
            tmpLine.push_back(other[y][x]);
        }
        this->matrix.push_back(tmpLine);
        tmpLine.clear();
    }
}

std::vector<std::vector<double>> Matrix::getMatrix()const
{
    return (matrix);
}

Matrix::Matrix(std::vector<std::vector<double>> matrix)
{
    setMatrix(matrix);
}

void Matrix::setMatrix(const std::vector<std::vector<double>> &matrix)
{
    std::vector <double>    tmp;

    if (matrix.empty())
        throw std::runtime_error("Could not set empty matrix.");
    for (int i = 0; i < matrix.size(); ++i)
	{
    	if (matrix[i].size() != matrix[0].size())
    		throw std::runtime_error("Wrong matrix, number of elements in rows are not equal");
	}

    this->matrix.clear();
    for (int y = 0; y < matrix.size(); ++y)
    {
        for (int x = 0; x < matrix[0].size(); ++x)
        {
            tmp.push_back(matrix[y][x]);
        }
        this->matrix.push_back(tmp);
        tmp.clear();
    }
}

bool Matrix::operator==(const Matrix &other)const
{
    std::vector<std::vector<double>> tmp = other.getMatrix();

    if (this->matrix.size() != other.getSizeRows() || this->matrix[0].size() != tmp[0].size())
        return (false);

    for (int y = 0; y < this->matrix.size(); ++y)
    {
        for (int x = 0; x < this->matrix.size(); ++x)
        {
            if (std::abs(std::abs(this->matrix[y][x]) - std::abs(tmp[y][x])) > epsilon)
                return (false);
        }
    }
    return (true);
}

Matrix& Matrix::operator=(const Matrix &matrix)
{
    if (!(*this == matrix))
    {
        this->setMatrix(matrix.getMatrix());
        return (*this);
    }

}

Matrix Matrix::operator+(const Matrix &matrix)
{
    std::vector<std::vector<double>> tmp = matrix.getMatrix();
    std::vector<double> line;
    std::vector<std::vector<double>> res;

    if (this->matrix.size() != tmp.size() || this->matrix[0].size() != tmp[0].size())
        throw std::runtime_error("Could not add matrices with different size");

    for (int y = 0; y < this->matrix.size(); ++y)
    {
        for (int x = 0; x < this->matrix[0].size(); ++x)
        {
            line.push_back(this->matrix[y][x] + tmp[y][x]);
        }
        res.push_back(line);
        line.clear();
    }
    Matrix r(res);
    return (r);
}

Matrix Matrix::operator-(const Matrix &matrix)
{
    std::vector<std::vector<double>> tmp = matrix.getMatrix();

    std::vector<double> line;
    std::vector<std::vector<double>> res;

    if (this->matrix.size() != tmp.size() || this->matrix[0].size() != tmp[0].size())
        throw std::runtime_error("Could not add matrices with different size");

    for (int y = 0; y < this->matrix.size(); ++y)
    {
        for (int x = 0; x < this->matrix[0].size(); ++x)
        {
            line.push_back(this->matrix[y][x] - tmp[y][x]);
        }
        res.push_back(line);
        line.clear();
    }
    Matrix r(res);
    return (r);
}

void Matrix::print()
{
    for (auto item : matrix)
    {
        for (auto num : item)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::operator*(const double &value)
{
    std::vector<double> line;
    std::vector<std::vector<double>> res;

    for (auto item : this->matrix)
    {
        for (auto num : item)
        {
            line.push_back(num * value);
        }
        res.push_back(line);
        line.clear();
    }
    Matrix r(res);
    return (r);
}

Matrix::Row::Row(Matrix &parent, int row) :_m_parent(parent), _m_row(row)
{
}

Matrix::Row Matrix::operator[](int row)
{
    if (row >= matrix.size())
        throw std::runtime_error("Could not get not existing number of matrix (operator [][](row))");
	return {*this,row};
}

double& Matrix::Row::operator[](int col)
{
    if (col >= _m_parent.getMatrix()[_m_row].size())
        throw std::runtime_error("Could not get not existing number of matrix (operator [][](column))");
    return (_m_parent.matrix[_m_row][col]);
}

Matrix Matrix::operator*(const Matrix &other)
{
    std::vector<std::vector<double>> otherMatrix = other.getMatrix();
    std::vector<double> line;
    std::vector<std::vector<double>> res;
    double tmp;


    if (this->matrix[0].size() != otherMatrix.size())
        throw std::runtime_error("Could not multiply matrices");
    for (int c = 0; c < matrix.size(); ++c)
    {
        for (int x = 0; x < otherMatrix[0].size(); ++x)
        {
            tmp = 0;
            for (int y = 0; y < otherMatrix.size(); ++y)
            {
                tmp += otherMatrix[y][x] * matrix[c][y];
            }
            line.push_back(tmp);
        }
        res.push_back(line);
        line.clear();
    }

    Matrix r(res);
    return (r);

}

Matrix::Matrix(int row, int col)
{
    if (row <= 0 || col < 0)
        throw std::runtime_error("Matrix can not have columns < 0 or rows <= 0");
    std::vector<double> line;
    for (int x = 0; x < col; ++x)
    {
        line.push_back(0);
    }
    for (int y = 0; y < row; ++y)
    {
       matrix.push_back(line);
    }

}

double Matrix::determinant()
{
	if (matrix.size() != matrix[0].size() && !(matrix.size() == 1 && matrix[0].empty()))
		throw std::runtime_error("Could not find determinant of not square matrix");
	return (det(matrix, (int)matrix.size()));
}

std::vector<std::vector<double>> Matrix::getCofactor(std::vector<std::vector<double>> m, int n, int size)
{
    std::vector<std::vector<double>> tmp;
    std::vector<double> line;

    for (int i = 1; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (j != n)
            {
                line.push_back(m[i][j]);
            }

        }
        tmp.push_back(line);
        line.clear();
    }
    return (tmp);
}

double Matrix::det(std::vector<std::vector<double>> m, int size)
{
    int sign = 1;
    double D = 0;

	if (size == 1)
	    return (m[0][0]);
	if (size == 2)
	    return (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
	 for (int i = 0; i < size; ++i)
     {

	     D += sign * m[0][i] * det(getCofactor(m, i, size), size - 1);
	     sign = -sign;
     }

    return (D);
}

Matrix Matrix::transpose()
{
    std::vector<std::vector<double>>    result;
    std::vector<double>                 line;

    for (int x = 0; x < matrix[0].size(); ++x)
    {
        for (int y = 0; y < matrix.size(); ++y)
        {
            line.push_back(matrix[y][x]);
        }
        result.push_back(line);
        line.clear();
    }
    Matrix r(result);
    return (r);
}

int main()
{
    std::vector<std::vector<double>> A = {{1,2, 3},{4, 5, 6}, {7,8,9}};
    std::vector<std::vector<double>> A1 = {{1}};
    Matrix B(A);
    B.print();
    std::cout << std::endl;
    Matrix C(B);
    C = B.transpose();
    C.print();


    return (0);
}