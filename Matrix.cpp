#include "Matrix.hpp"


Matrix::Matrix(Matrix &matrix)
{
    std::vector<std::vector<double>>    tmp = matrix.getMatrix();
    std::vector<double>                 tmpLine;

    for (int y = 0; y < tmp.size(); ++y)
    {
        for (int x = 0; x < tmp[0].size(); ++x)
        {
            tmpLine.push_back(tmp[y][x]);
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

bool Matrix::operator==(const Matrix &matrix)const
{
    std::vector<std::vector<double>> tmp = matrix.getMatrix();

    if (this->matrix.size() != tmp.size() || this->matrix[0].size() != tmp[0].size())
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
    this->setMatrix(matrix.getMatrix());
    return (*this);

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

int main()
{
    std::vector<std::vector<double>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    Matrix B(A);
    Matrix C(A);

   B =  B + B;

    B.print();
    return (0);
}