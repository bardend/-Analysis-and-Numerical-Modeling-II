#include <iostream>
#include "../matplotlibcpp.h"
#include <functional> // Necesario para std::function
#include <vector>
#include <cmath>

namespace plt = matplotlibcpp;
using namespace std;
using namespace plt;


class CubicSpline {
private:
    vector<double> x, y, A, B, C; // Declara a, b, c como miembros de la clase

public:
    CubicSpline(const std::vector<double>& x, const std::vector<double>& y) {
        // Assuming x is sorted in ascending order
        this->x = x;
        this->y = y;

        int n = x.size();

        vector<double> b(n-1);
        vector<double> h(n-1);
        vector<double> v(n-1);
        vector<double> u(n-1);
        vector<double> z(n);

        for (int i = 0; i < n - 1; ++i) {
            h[i] = x[i + 1] - x[i];
            b[i] = 6*(y[i+1] - y[i]) / h[i];
        }

        u[1] = 2*(h[0] + h[1]);
        v[1] = b[1] - b[0];

        for(int i = 2; i < n-1; i++){
            u[i] = 2 * (h[i]-h[i-1]) - (h[i-1]*h[i-1])/u[i-1];
            v[i] = b[i] - b[i-1] - h[i-1] * v[i-1] / u[i-1];
        }

        z[n-1] = 0;
        
        for(int i = n-2; i > 0; i--){
            z[i] = (v[i] - h[i]*z[i+1]) / u[i];
        }

        z[0] = 0;
        A.resize(n-1);
        B.resize(n-1);
        C.resize(n-1);

        for(int i = 0; i < n-1; i++){
            A[i] = 1/(6*h[i]) * (z[i+1] - z[i]);
            B[i] = z[i] / 2;
            C[i] = -h[i]*z[i+1]/6 - h[i]*z[i]/3 + 1/h[i]*(y[i+1] - y[i]);
        }

        cout << "size : " << b.size() << endl;
    }

    double interpolate(double tt, int idx){
        return y[idx] + (tt - x[idx]) * (C[idx] + (tt - x[idx]) * (B[idx] + (tt - x[idx]) * A[idx]));
    }
};

int main() {
    // Ejemplo de uso
    vector<double> x = {0, 1, 2, 3, 4};
    vector<double> y = {0, 1, 8, 27, 64};



    CubicSpline spline(x, y);

    const double eps = 0.001;

    int n = (int)x.size();

    for(int i = 0; i < n-1; i++){

        pair<vector<double>, vector<double>>v;

        for(double ii = x[i]; ii < x[i+1]; ii += eps){

            v.first.push_back(ii);
            v.second.push_back(spline.interpolate(ii, i));
        }
        plt::plot(v.first, v.second, "r-");
    }
    plt::show();

    return 0;
}

