#include "Matrix.hpp"

void    fillJacobian(Matrix &J, Matrix &R)
{
   J[0][0] = (R[0][0] * 8);
   J[0][1] = (R[1][0] * R[1][0] * (-3));
   J[1][0] = (R[0][0] * R[0][0] * 9);
   J[1][1] = (R[1][0] * 8);

}

double f1(double x, double y)
{
    return (4 * pow(x, 2) - pow(y, 3) + 28);
}

double f2(double x, double y)
{
    return (3 * pow(x, 3) + 4 * pow(y, 2) - 145);
}

bool    stopCondition(Matrix &R, Matrix &R_old)
{
    double eps = 0.00000001;
    double d1 = std::abs(R[0][0]) - std::abs(R_old[0][0]);
    double d2 = std::abs(R[1][0]) - std::abs(R[1][0]);

    if (std::abs(d1) < eps && std::abs(d2) < eps)
        return (false);
    return (true);
}

void    newton()
{
    //4 * x^2 - y^3 + 28 = 0;
    //3 * x^3 + 4 * y^2 - 145 = 0;
    std::vector<std::vector<double>> r = {{1}, {1}};
    Matrix R(r);
    Matrix R_old(2, 1);
    Matrix J(2, 2);
    Matrix F(2, 1);

    while (true)
    {
        R.print();
        std::cout << std::endl;
        fillJacobian(J, R);

        J = J.inverse();
        F[0][0] = f1(R[0][0], R[1][0]);
        F[1][0] = f2(R[0][0], R[1][0]);

        R_old = R;
        R = R - J * F;
        if (!stopCondition(R, R_old))
            break ;
    }

}


double maxMatrix(Matrix &vec)
{
    double max;
    auto v = vec.getMatrix();

    max = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        if (std::abs(max) < std::abs(v[i][0]))
            max = v[i][0];
    }
    return (max);

}

void    findMaxMin(Matrix &A)
{

    std::vector<std::vector<double>> vectX = {{1}, {1}, {1}};

    double lambda;


    Matrix x(vectX);
    Matrix y(3, 1);

    int i = 0;
    while (i < 100)
    {
        y = A * x;
        lambda = maxMatrix(y);
        x = y * (1 / std::abs(maxMatrix(y)));
        ++i;
    }
    std::cout << "Lambda: "<< lambda << std::endl;
    std::cout << "Vector: "<< x[0][0] << " " << x[1][0] << " " << x[2][0] << std::endl;
}

void    findEigenValues()
{
    std::vector<std::vector<double>> matrix = {{5, 6 ,3}, {-1, 0 ,1}, {1, 2, -1}};
    Matrix A(matrix);

    std::cout << "MAX LAMBDA:" << std::endl;
    findMaxMin(A);
    std::cout << "**********************" << std::endl;

    std::cout << "MIN LAMBDA:" << std::endl;
    A = A.inverse();
    findMaxMin(A);


}

int main()
{
    //newton();
    findEigenValues();
    return (0);
}