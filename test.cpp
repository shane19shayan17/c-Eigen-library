#include <iostream>
#include <eigen3/Eigen/Dense>
// #include <eigen3/Eigen/Sparse>

using namespace Eigen;
using namespace std;

int main()
{
    double data[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    Map<Vector4d> current_state(data);
    Map<Vector2d> current_input(data + 4);
    Map<Vector4d> ref_state(data + 6);

    Vector2d current_position = current_state.head<2>();
    Vector2d ref_position = ref_state.head<2>();

    Vector2d error = ref_position - current_position;

    cout << error << endl;

    return 0;
}
