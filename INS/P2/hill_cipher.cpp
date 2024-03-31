#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int determinant(int a, int b, int c, int d) {
    return a * d - b * c;
}

int modInverse(int a, int m) {
    for (int i = 1; i < m; i++)
        if ((a * i) % m == 1)
            return i;
    return 1;
}

void cofactor(vector<vector<int>>& mat, vector<vector<int>>& temp, int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = mat[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void adjugate(vector<vector<int>>& mat, vector<vector<int>>& adj, int n) {
    if (n == 1) {
        adj[0][0] = 1;
        return;
    }

    int sign = 1;
    vector<vector<int>> temp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cofactor(mat, temp, i, j, n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp[0][0], temp[0][1], temp[1][0], temp[1][1]) % 26 + 26) % 26;
        }
    }
}

bool isMatrixInvertible(vector<vector<int>>& key) {
    return determinant(key[0][0], key[0][1], key[1][0], key[1][1]) != 0;
}

string hillCipherEncrypt(const string& message, const vector<vector<int>>& key) {
    int n = key.size();

    if (!isMatrixInvertible(key)) {
        cerr << "Error: Key matrix is not invertible.\n";
        return "";
    }

    int padding = message.length() % n;
    if (padding != 0) {
        for (int i = 0; i < n - padding; i++) {
            message.push_back('X');
        }
    }

    string ciphertext = "";
    for (int i = 0; i < message.length(); i += n) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += (key[j][k] * (message[i + k] - 'A')) % 26;
            }
            ciphertext.push_back((sum % 26) + 'A');
        }
    }

    return ciphertext;
}

string hillCipherDecrypt(const string& ciphertext, const vector<vector<int>>& key) {
    int n = key.size();

    if (!isMatrixInvertible(key)) {
        cerr << "Error: Key matrix is not invertible.\n";
        return "";
    }

    int det = determinant(key[0][0], key[0][1], key[1][0], key[1][1]);
    int detInverse = modInverse(det, 26);

    vector<vector<int>> adj(n, vector<int>(n, 0));
    adjugate(key, adj, n);

    vector<vector<int>> keyInverse(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            keyInverse[i][j] = (detInverse * adj[i][j] + 26) % 26;
        }
    }

    string decryptedText = "";
    for (int i = 0; i < ciphertext.length(); i += n) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += (keyInverse[j][k] * (ciphertext[i + k] - 'A')) % 26;
            }
            decryptedText.push_back((sum % 26) + 'A');
        }
    }

    return decryptedText;
}

int main() {
    int n;
    cout << "Enter the size of the key matrix: ";
    cin >> n;

    vector<vector<int>> key(n, vector<int>(n));
    cout << "Enter the key matrix elements:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> key[i][j];

    cin.ignore(); // Clear newline from the input buffer

    string message;
    cout << "Enter the message to encrypt: ";
    getline(cin, message);

    string ciphertext = hillCipherEncrypt(message, key);
    cout << "Encrypted: " << ciphertext << endl;

    string decryptedText = hillCipherDecrypt(ciphertext, key);
    cout << "Decrypted: " << decryptedText << endl;

    return 0;
}
