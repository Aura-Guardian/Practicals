#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

long long power_mod(long long base, long long exponent, long long modulus) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent >>= 1;
    }
    return result;
}

vector<long long> blum_blum_shub(long long Xo, long long n, int num_random) {
    vector<long long> random_numbers;
    long long Xi = Xo;
    for (int i = 0; i < num_random; i++) {
        Xi = (Xi * Xi) % n;
        random_numbers.push_back(Xi);
    }
    return random_numbers;
}

int main() {
    long long p, q, Xo;
    int num_random;
    ifstream f("bbs_parameters.txt");
    f >> p >> q >> Xo;
    long long n = p * q;

    cout << "Enter number of random numbers to generate: ";
    cin >> num_random;

    vector<long long> random_numbers = blum_blum_shub(Xo, n, num_random);
    for (int i = 0; i < random_numbers.size(); i++) {
        cout << random_numbers[i] << endl;
    }

    return 0;
}
