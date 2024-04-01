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

template <class T, class U>
class Casteljau{
    T t;
    vector<U> points;

public :
    Casteljau(T t, vector<U> &points): t(t), points(points){}

    U recCasteljau(int nivel, int cur, T t){
        if(nivel == 1) return points[cur];

    return make_pair((1-t)*recCasteljau(nivel-1, cur, t).first + t * recCasteljau(nivel-1, cur+1, t).first, 
                    (1-t)*recCasteljau(nivel-1, cur, t).second + t * recCasteljau(nivel-1, cur+1, t).second);
    }

    U getPoint(){
        return recCasteljau((int)points.size(), 0, t);
    }
};

int main(){

    vector<pair<double, double>> points = {{0.0, 0.0}, {1.0, 1.5}, {2.0, 2.0}, {3.3, 0.0}}; // Example points

    pair<vector<double>, vector<double>>v;


    for(int i = 0; i < 1000; i++){
        double t = i/1000.0;
        Casteljau<double, pair<double, double>> casteljau(t, points);
        v.first.push_back(casteljau.getPoint().first);
        v.second.push_back(casteljau.getPoint().second);
    }
    vector<double> x_points, y_points;
    for (auto point : points) {
        x_points.push_back(point.first);
        y_points.push_back(point.second);
    }

    plt::plot(v.first, v.second, "r-");
    plt::scatter(x_points, y_points, {{"color", "red"}, {"label", "a circle!"}});



    plt::show();

    return 0;
}

