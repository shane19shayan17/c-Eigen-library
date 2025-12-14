#include <iostream>
#include <chrono>
#include <eigen3/Eigen/Dense>
// #include <eigen3/Eigen/Sparse>

using namespace Eigen;
using namespace std;
using namespace chrono;

int main()
{
    MatrixXd a(10, 10);
    MatrixXd b(10, 10);
    a.setIdentity();
    b.setIdentity();

    auto start_2 = high_resolution_clock::now();
    MatrixXd d(10, 10);
    d.setIdentity();
    cout << d << endl;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            d(i, j) = a(i, j) * b(i, j);
        }
    }
    auto end_2 = high_resolution_clock::now();
    auto time_2 = duration_cast<microseconds>(end_2 - start_2).count();
    cout << "second time : " << time_2 << endl;

    auto start_3 = high_resolution_clock::now();
    MatrixXd e = (a.array() * b.array()).matrix();
    auto end_3 = high_resolution_clock::now();
    auto time_3 = duration_cast<microseconds>(end_3 - start_3).count();
    cout << "third time : " << time_3 << endl;

    return 0;
}
