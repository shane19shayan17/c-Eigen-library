#include <iostream>
#include <eigen3/Eigen/Dense>
// #include <eigen3/Eigen/Sparse>

using namespace Eigen;
using namespace std;

int main()
{
    const float dt = 0.1;

    // state transition matrix
    MatrixXd A(4, 4);
    A.setIdentity();
    A(0, 2) = dt;
    A(1, 3) = dt;

    // input matrix
    MatrixXd B(4, 2);
    B(0, 0) = pow(dt, 2) / 2;
    B(1, 1) = pow(dt, 2) / 2;
    B(2, 0) = dt;
    B(3, 1) = dt;

    // current state
    MatrixXd x_k(4, 1);
    x_k << 1.0, 2.0, 0.5, 0.1;

    // current input
    MatrixXd u_k(2, 1);
    u_k << 0.2, -0.1;

    // next state x(k + 1) = A x(k) + B u(k)
    Vector4d x_k1 = A * x_k + B * u_k;
    cout << x_k1 << endl;
    return 0;
}
