#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<int> linear_congruential(int a, int c, int m, int Xo, int n) {
    vector<int> random_number(n); 
    random_number[0] = Xo;
    for (int i = 1; i < n; i++) {
        random_number[i] = ((a * random_number[i - 1]) + c) % m;
    }
    return random_number;
}



int main(){
    int a, c, m, Xo1;
    int p, q, n, Xo2;
    int no;
    ifstream f1("bbs_parameters.txt");
    // ifstream f2("lc_parameters.txt");
    f1>>a>>c>>m>>Xo1;
    // f2 >> p >> q >> Xo2;
    cout<<a<<endl;
    cout<<c<<endl;
    cout<<m<<endl;
    cout<<Xo1<<endl;
    cout<<"Enter number of random numbers to generate: "<<endl;
    cin>>no;
    vector<int> nos1 = linear_congruential(a, c, m, Xo1, no);
    for(int i = 0; i < nos1.size(); i++){
        cout<<nos1[i]<<endl;
    }
}