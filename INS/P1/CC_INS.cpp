#include <bits/stdc++.h>
using namespace std;
string cc_encrypt(string text, int key)
{
    char c;
    for (int i = 0; i < text.length(); i++)
    {
        c = text[i];
        if (isalpha(c))
        {
            if (islower(c))
            {
                c = (c - 'a' + key) % 26 + 'a';
            }
            if (isupper(c))
            {
                c = (c - 'A' + key) % 26 + 'A';
            }
        }
        text[i] = c;
    }
    return text;
}
string cc_decrypt(string text, int key)
{
    char c;
    for (int i = 0; i < text.length(); i++)
    {

        c = text[i];
        if (isalpha(c))
        {
            if (islower(c))
            {
                c = (c - 'a' - key + 26) % 26 + 'a';
            }
            if (isupper(c))
            {
                c = (c - 'A' - key + 26) % 26 + 'A';
            }
        }
        text[i] = c;
    }
    return text;
}
int main()
{

    FILE *ptr;
    fstream f;
    char ch;
    string s = "";
    string cipher_text, plain_text;
    ptr = fopen("input.txt", "r");
    f.open("output.txt", fstream::out);
    if (NULL == ptr)
    {
        printf("Cannot open\n");
    }
    printf("Plain text: \n");
    while (!feof(ptr))
    {
        ch = fgetc(ptr);
        s += ch;
        printf("%c", ch);
    }
    cout << "\n";
    int key;
    cout << "Enter key: \n";

    cin >> key;
    cout << cc_encrypt(s, key);
    cipher_text = cc_encrypt(s, key);
    cout << "\nEncryption"
         << "\n"
         << "Cipher Text: " << cipher_text;
    for (int i = 0; i < cipher_text.length(); i++)
    {
        f << cipher_text[i];
    }
    plain_text = cc_decrypt(cipher_text, key);
    cout << "\nDecryption"
         << "\n"
         << "Plain Text: " << plain_text;
    f.close();
    fclose(ptr);
    return 0;
}