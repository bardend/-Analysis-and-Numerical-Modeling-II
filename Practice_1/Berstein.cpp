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
class Berstein {
private:
    int n;
    T ob; // Cambiado a un puntero a función

public:
    Berstein(T obj, int n) : ob(obj), n(n){}

    
    double rec_bers(int n, int k, double x){
        if(k == 0)
            return pow(1 - x, n);

        else if(k == n)
            return x * rec_bers(n-1, k-1, x);
        else 
            return (1-x)*rec_bers(n-1, k, x) + x * rec_bers(n-1, k-1, x);
    }

    pair<vector<double>, vector<double>>generate(){
        const int maxn = 1000;
        pair<vector<double>, vector<double>>ret;
        for(int i = 0; i < maxn; i++){ //this is the point
            double ii = 1.0 * i / maxn;
            double sum = 0;
            for(int j = 0; j <= n; j++){ // this is the polinomy
                sum += ob(1.0*j/n) * rec_bers(n, j, ii);
            }
            ret.first.push_back(ii); ret.second.push_back(sum);
        }
        return ret;
    }

};

double f(double x){
    return (5*x);
}

double f2(double x){
    return x*x*x;
}

int main(){
    Berstein<decltype(f)*> ob1(f, 12);
    Berstein<decltype(f)*> ob2(f2, 15);

    pair<vector<double>, vector<double>> tmp = ob1.generate();
    pair<vector<double>, vector<double>> tmp2 = ob2.generate();

    plt::plot(tmp2.first, tmp2.second, "r-");
    plt::plot(tmp.first, tmp.second, "b-");

    plt::show();

    return 0;
}
