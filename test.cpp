#include <iostream>
#include <eigen3/Eigen/Dense>
// #include <eigen3/Eigen/Sparse>

using namespace Eigen;
using namespace std;

int main()
{
    Matrix3d H(3, 3);
    H << 4, 1, 1,
        1, 5, 1,
        1, 1, 3;

    Vector3d G = {1, 2, 3};

    LDLT<Matrix3d> solver;
    solver.compute(H);
    Vector3d X = solver.solve(G);

    cout << X << endl;

    Vector3d error = H * X - G;
    cout << error << endl;

    return 0;
}
