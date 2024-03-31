#include <bits/stdc++.h>
#define N 3
using namespace std;

float en[N][1], de[N][1], b[N][N], msg[N][1], m[N][N];
int a[N][N];
string key;
void key_matrix()
{
    cout << "Enter key: ";
    cin >> key;
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {

            if (isupper(key[k]))
            {
                a[i][j] = (key[k]) % 65;
            }
            if (islower(key[k]))
            {
                a[i][j] = (key[k]) % 97;
            }
            k++;
        }
    }
    int i, j;
    char mes[3];
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            m[i][j] = a[i][j];
        }

    FILE *ptr;
    fstream fp;
    char ch;
    string s = "";
    string cp, pt;
    ptr = fopen("hill_input.txt", "r");
    fp.open("hill_output.txt", fstream::out);
    if (NULL == ptr)
    {
        printf("Error \n");
    }
    int it = 0;
    printf("PLAIN TEXT: ");
    while (!feof(ptr))
    {
        ch = fgetc(ptr);
        mes[it] = ch;
        it++;
        printf("%c", ch);
    }
    for (i = 0; i < N; i++)
    {
        if (isupper(mes[i]))
            msg[i][0] = mes[i] - 65;
        if (islower(mes[i]))
            msg[i][0] = mes[i] - 97;
    }
    msg[i][0] = mes[i] - 65;
}
void hill_encrypt()
{
    string s = "";
    int i, j, k;
    for (i = 0; i < N; i++)
        for (j = 0; j < 1; j++)
            for (k = 0; k < N; k++)
                en[i][j] = en[i][j] + a[i][k] * msg[k][j];
    cout << "\nEncrypted string: ";
    for (i = 0; i < N; i++)
        s = s + (char)(fmod(en[i][0], 26) + 65);
    cout << s;
    fstream fp;
    fp.open("hill_output.txt", fstream::out);

    for (int i = 0; i < s.length(); i++)
    {
        fp << s[i];
    }
}

void inverse_matrix()
{
    int i, j, k;
    float p, q;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            if (i == j)
                b[i][j] = 1;
            else
                b[i][j] = 0;
        }
    for (k = 0; k < N; k++)
    {
        for (i = 0; i < N; i++)
        {
            p = m[i][k];
            q = m[k][k];
            for (j = 0; j < N; j++)
            {
                if (i != k)
                {
                    m[i][j] = m[i][j] * q - p * m[k][j];
                    b[i][j] = b[i][j] * q - p * b[k][j];
                }
            }
        }
    }
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            b[i][j] = b[i][j] / m[i][i];
    cout << "Inverse Matrix: \n";
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            cout << b[i][j] << " ";
        cout << "\n";
    }
}
void hill_decrypt()
{
    int i, j, k;
    inverse_matrix();
    for (i = 0; i < N; i++)
        for (j = 0; j < 1; j++)
            for (k = 0; k < N; k++)
                de[i][j] = de[i][j] + b[i][k] * en[k][j];
    cout << "\nDecrypted string: ";
    for (i = 0; i < N; i++)
        cout << (char)(fmod(de[i][0], 26) + 65);
    cout << "\n";
}
int main()
{
    key_matrix();
    hill_encrypt();
    hill_decrypt();
}
