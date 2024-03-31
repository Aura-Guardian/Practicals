#include <iostream>
#include <fstream>
#include <map>
using namespace std;

string const key = "HACK";
map<int, int> key_map;

void permutation_order() {for (int i = 0; i < key.length(); i++){key_map[key[i]] = i;}}


string read_data(const string &filename) {
    ifstream file(filename);
    string content;
    getline(file, content);
    file.close();
    return content;
}


void write_data(const string &filename, const string &content) {
    ofstream file(filename);
    file << content;
    file.close();
}

string encryptMessage(string msg) {
    int row, col, j;
    string cipher = "";
    //calc col length
    col = key.length();
    //calc max row length
    row = msg.length() / col;
    if (msg.length() % col)
        row += 1;
    char matrix[row][col];
    for (int i = 0, k = 0; i < row; i++) {
        for (int j = 0; j < col;) {
            if (msg[k] == '\0') {
                //padding to char
                matrix[i][j] = '_';
                j++;
            }

            if (isalpha(msg[k]) || msg[k] == ' ') {
                //only space and char to mat
                matrix[i][j] = msg[k];
                j++;
            }
            k++;
        }
    }

    for (map<int, int>::iterator ii = key_map.begin(); ii != key_map.end(); ++ii)
    {
        j = ii->second;
        //CT from col text using key
        for (int i = 0; i < row; i++)
        {
            if (isalpha(matrix[i][j]) || matrix[i][j] == ' ' || matrix[i][j] == '_')
                cipher += matrix[i][j];
        }
    }

    return cipher;
}

string decryptMessage(string cipher) {
    int col = key.length(); //col length
    int row = cipher.length() / col; //max row length
    char CT_matrix[row][col];
    //add char to mat
    for (int j = 0, k = 0; j < col; j++)
        for (int i = 0; i < row; i++)
            CT_matrix[i][j] = cipher[k++];
    //update order of key for dec
    int index = 0;
    for (map<int, int>::iterator ii = key_map.begin(); ii != key_map.end(); ++ii)
        ii->second = index++;
    //arrange matrix col-wise to permutation order
    char decCipher[row][col];
    map<int, int>::iterator ii = key_map.begin();
    int k = 0;
    for (int l = 0, j; key[l] != '\0'; k++) {
        j = key_map[key[l++]];
        for (int i = 0; i < row; i++) {
            decCipher[i][k] = CT_matrix[i][j];
        }
    }
    string msg = ""; //msg from matrix
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (decCipher[i][j] != '_')
                msg += decCipher[i][j];
        }
    }
    return msg;
}

int main(void) {
    string msgFile = "keyword_inp.txt";
    string keyFile = "keyword_key.txt";
    string msg = read_data(msgFile);
    string key = read_data(keyFile);
    permutation_order();
    string cipher = encryptMessage(msg);
    write_data("keyword_enc_op.txt", cipher);
    string decryptedMsg = decryptMessage(cipher);
    write_data("keyword_dec_op.txt", decryptedMsg);
    return 0;
}

