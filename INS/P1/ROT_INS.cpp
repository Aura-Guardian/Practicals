#include <bits/stdc++.h>
using namespace std;

string ROT_encrypt(string text)
{
    char c;
    for (int i = 0; i < text.length(); i++)
    {
        c = text[i];
        if (isalpha(c))
        {
            if (islower(c))
            {
                c = (c - 'a' + 13) % 26 + 'a';
            }
            if (isupper(c))
            {
                c = (c - 'A' + 13) % 26 + 'A';
            }
        }
        text[i] = c;
    }
    return text;
}

string ROT_decrypt(string text)
{
    char c;
    for (int i = 0; i < text.length(); i++)
    {
        c = text[i];
        if (isalpha(c))
        {
            if (islower(c))
            {
                c = (c - 'a' + 13) % 26 + 'a';
            }
            if (isupper(c))
            {
                c = (c - 'A' + 13) % 26 + 'A';
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
        printf("File cannot open\n");
    }
    printf("Plain text: \n");
    while (!feof(ptr))
    {
        ch = fgetc(ptr);
        s += ch;
        printf("%c", ch);
    }
    cipher_text = ROT_encrypt(s);
    cout << "\nEncryption"
         << "\n"
         << "Cipher Text: " << cipher_text;
    for (int i = 0; i < cipher_text.length(); i++)
    {
        f << cipher_text[i];
    }
    plain_text = ROT_decrypt(cipher_text);
    cout << "\nDecryption"
         << "\n"
         << "Plain Text: " << plain_text;
    f.close();
    fclose(ptr);
    return 0;
}