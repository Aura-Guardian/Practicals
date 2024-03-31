#include <bits/stdc++.h>
using namespace std;

string encrypt(string text, string key)
{
    string CT = "";
    int cipher[key.length()];

    for (int i = 0; i < key.length(); i++)
    {
        cipher[i] = text.at(i) - 'A' + key.at(i) - 'A';
        if (cipher[i] > 25)
        {
            cipher[i] = cipher[i] - 26;
        }
    }

    for (int i = 0; i < key.length(); i++)
    {
        int x = cipher[i] + 'A';
        CT += (char)x;
    }

    return CT;
}

static string decrypt(string s, string key)
{
    string PT = "";
    int plain[key.length()];

    for (int i = 0; i < key.length(); i++)
    {
        plain[i] = s.at(i) - 'A' - (key.at(i) - 'A');
        if (plain[i] < 0)
        {
            plain[i] = plain[i] + 26;
        }
    }

    for (int i = 0; i < key.length(); i++)
    {
        int x = plain[i] + 'A';
        PT += (char)x;
    }

    return PT;
}

int main()
{
    string PT;
    ifstream inputFile("pad_ip.txt");
    if (inputFile.is_open())
    {
        getline(inputFile, PT);
        inputFile.close();
    }
    else
    {
        cout << "Error";
        return 1;
    }

    string key;
    ifstream keyFile("key.txt");
    if (keyFile.is_open())
    {
        getline(keyFile, key);
        keyFile.close();
    }
    else
    {
        cout << "Error";
        return 1;
    }

    for (int i = 0; i < PT.length(); i++)
    {
        PT[i] = toupper(PT[i]);
    }
    for (int i = 0; i < key.length(); i++)
    {
        key[i] = toupper(key[i]);
    }

    string encryptedText = encrypt(PT, key);

    ofstream outputFile("pad_op.txt");
    if (outputFile.is_open())
    {
        outputFile << "Cipher text: " << encryptedText << endl;
        outputFile << "Original message: " << decrypt(encryptedText, key);
        outputFile.close();
    }
    else
    {
        cout << "Error";
        return 1;
    }

    return 0;
}
