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

    vector<std::string> colors = {"r-", "g-", "b-", "c-", "m-", "y-", "k-"};

    for(int grade = 2; grade <= 15; grade++){
        Berstein<decltype(f)*> ob2(f2, grade);
        pair<vector<double>, vector<double>> tmp2 = ob2.generate();
        string color = colors[grade % colors.size()];
        plt::plot(tmp2.first, tmp2.second, color);
       // plt::plot(tmp2.first, tmp2.second, color, "Polinomio de grado " + to_string(grade));
        //plt::legend();
    }

    plt::show();

    return 0;
}
