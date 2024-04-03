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

vector<int> blum_blum_shub(int n, int Xo, int no) {
    vector<int> random_numbers;
    int Xi = Xo;
    for (int i = 0; i < no; i++) {
        Xi = (Xi * Xi) % n;
        random_numbers.push_back(Xi);
    }
    return random_numbers;
}

int main(){
    int a, c, m, Xo1;
    int p, q, n, Xo2;
    int no;
    ifstream f1("lc_parameters.txt");
    ifstream f2("bbs_parameters.txt");
    f1>>a>>c>>m>>Xo1;
    f2 >> p >> q >> Xo2;
    cout<<"Enter number of random numbers to generate: ";
    cin>>no;
    cout<<"Linear Congruential: "<<endl;
    vector<int> nos1 = linear_congruential(a, c, m, Xo1, no);
    for(int i = 0; i < nos1.size(); i++){
        cout<<nos1[i]<<endl;
    }

    n = p * q;
    cout<<"\nBlum Blum Shub : "<<endl;
    vector<int> nos2 = blum_blum_shub(n, Xo2, no);
        for(int i = 0; i < nos2.size(); i++){
        cout<<nos2[i]<<endl;
    }
}