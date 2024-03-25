#include "../matplotlibcpp.h"
#include <iostream>
#include <functional> // Necesario para std::function
#include <iostream>
#include <vector>
#include <utility> // Necesario para std::pair
#include <cmath>

namespace plt = matplotlibcpp;
using namespace std;
using namespace plt;

template <class T>
class Laguerre{
private:
    int n;
    T ob; // Cambiado a un puntero a función

public:
    Laguerre(T obj, int n) : ob(obj), n(n){}

    double rec_lag(int n, double x){
        if (n == 0) return 1.0;
        else if(n == 1) return 1-x;
        else 
            return 1.0/n*((2*n-1-x)*rec_lag(n-1, x) - (n-1)*rec_lag(n-2, x));
    }

    void generate(){

        const int maxn = 10000;
        vector<string> colors = {"r-", "g-", "b-", "c-", "m-", "y-", "k-"}; // Paleta de colores

        for(int i = 0; i <= n; i++){
            pair<vector<double>, vector<double>>vec;
            for(int j = 0; j < maxn; j++){
                double jj = j/ 10.0;
                vec.first.push_back(jj); vec.second.push_back(rec_lag(i, jj));
            }
            plt::plot(vec.first, vec.second, colors[i % colors.size()]); // Asignación de colores
        }
        plt::show();
    }
};

double f(double x){
    return x*x*x;
}

int main() {

    Laguerre<decltype(f)*> ob(f, 6);
    ob.generate();

    return 0;
}
