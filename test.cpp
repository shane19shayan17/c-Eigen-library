#include <iostream>
#include <chrono>
#include <eigen3/Eigen/Dense>
// #include <eigen3/Eigen/Sparse>

using namespace Eigen;
using namespace std;
using namespace chrono;

const double DT = 0.1;
const int N_INPUT = 2;
const int N_HORIZON = 5;
const int N_STATE = 4;
const int m = N_STATE * (N_HORIZON + 1);

// power in matrix
Matrix4d matrix_power(const Matrix4d &A, int k)
{
    if (k == 0)
        return Matrix4d::Identity();
    if (k == 1)
        return A;
    Matrix4d result = Matrix4d::Identity();
    Matrix4d base = A;
    while (k > 0)
    {
        if (k % 2 == 1)
            result *= base;
        base *= base;
        k /= 2;
    }
    return result;
}

int main()
{
    // Q = {X, Y, YAW, VELOCITY}
    Matrix4d Q;
    Q << 50, 0, 0, 0,
        0, 50, 0, 0,
        0, 0, 500, 0,
        0, 0, 0, 50;
    Matrix4d QF = Q * 2; // final state

    Matrix2d R;
    R << 10, 0,
        0, 0.50;

    Vector4d X_CURRENT;
    X_CURRENT << 1, 2, 0, 0.5;

    Vector4d state_ref;
    state_ref << 5, 6, 1.5, 1;

    Matrix4d A = Matrix4d::Identity();
    Matrix<double, 4, 2> B;
    B << 0.1, 0,
        0, 0.1,
        0, DT,
        DT, 0;

    Matrix<double, m, 1> X_BIG_REF;
    for (int i = 0; i < N_HORIZON + 1; ++i)
    {
        X_BIG_REF.segment<N_STATE>(i * N_STATE) = state_ref;
    }

    // Q_BIG ##################################################################
    Matrix<double, m, m> Q_BIG;
    Q_BIG = Q_BIG.setZero();
    // for make the true value of Q_BIG
    for (int i = 0; i < N_HORIZON; ++i)
    {
        Q_BIG.block<N_STATE, N_STATE>(i * N_STATE, i * N_STATE) = Q;
    }
    Q_BIG.block<N_STATE, N_STATE>(N_HORIZON * N_STATE, N_HORIZON * N_STATE) = QF;
    // Q_BIG ##################################################################

    // PHI ####################################################################
    Matrix<double, m, N_INPUT * N_HORIZON> PHI = MatrixXd::Zero(m, N_INPUT * N_HORIZON);
    for (int i = 0; i <= N_HORIZON; ++i)
    {
        if (i > 0)
        {
            for (int j = 0; j < i; ++j)
            {
                PHI.block<N_STATE, N_INPUT>(i * N_STATE, j * N_INPUT) =
                    matrix_power(A, i - j - 1) * B;
            }
        }
    }
    // PHI ####################################################################

    // PSI ####################################################################
    Matrix<double, m, N_STATE> PSI;
    for (int i = 0; i < N_HORIZON + 1; i++)
    {
        PSI.block<N_STATE, N_STATE>(i * N_STATE, 0) = matrix_power(A, i);
    }
    // PSI ####################################################################

    // G_MPC ##################################################################
    //         10*24   24*24   24*4  4*1  24*1    => 10*1
    // G_MPC = PHI_T * Q_BIG ( PSI * X0 - X_BIG_ref )
    Matrix<double, N_INPUT * N_HORIZON, 1> G_MPC;
    G_MPC = PHI.transpose() * Q_BIG * (PSI * X_CURRENT - X_BIG_REF);
    // G_MPC ##################################################################

    cout << G_MPC << endl;

    return 0;
}
