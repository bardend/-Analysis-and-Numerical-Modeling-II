#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

template <typename t> class student{
    private:
        string name;
        t total_marks;
    public:
        student();
        student(string n, t m){
            name = n;
            total_marks = m;
        }
        void getinfo(){
            cout << "total : " << total_marks << endl;
            cout << "Type Id : " << typeid(total_marks).name() << endl;
        }
};

int main()
{
    // student <int> is used to fulfill
      // template requirements
    student<int> s1("vipul", 100);
    student<int> s2("yash", 100.0);
 
    s1.getinfo();
    s2.getinfo();
 
    return 0;
}

