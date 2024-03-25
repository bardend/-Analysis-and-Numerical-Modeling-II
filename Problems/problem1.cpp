#define _USE_MATH_DEFINES // for sin/log
#include "../matplotlibcpp.h"
#include <cmath>
#include <iostream>
namespace plt = matplotlibcpp;
using namespace std;
using namespace plt;

int main(){
    int n = 5000;

    vector<double>x(n), y(n), z(n), w(n,2);

    for(int i = 0; i < n; i++){
        x[i] = i *i;
        y[i] = sin(2 * M_PI * i / 360.0);
        z[i] =  log(i);
    }

    plt::plot(x, y); // automatic coloring: tab:blue
    plt::plot(x, w, "r--"); // red dashed line
    plt::plot(x, z, {{"label", "log(x)"}}); // legend label "log(x)"
    plt::xlim(0, 1000 * 1000); // x-axis interval: [0, 1e6]
    plt::title("Standard usage"); // set a title
    plt::legend(); // enable the legend
    plt::show();

    return 0;
}

