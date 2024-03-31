#include <bits/stdc++.h>
using namespace std;

string encrypt(char msg[], int key)
{
    int count = 0;
    for (int i = 0; msg[i]; i++)
        if (msg[i] != ' ')
            msg[count++] = msg[i];
    msg[count] = '\0';
    int msg_len = strlen(msg);
    char CT_matrix[key][key];
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < key; j++)
        {
            CT_matrix[i][j] = '*';
        }
    }
    int k = 0;
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < key; j++)
        {
            if (k < msg_len)
            {
                CT_matrix[i][j] = msg[k];
                k++;
            }
            else
            {
                CT_matrix[i][j] = '*';
            }
        }
    }
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < key; j++)
        {
            if (CT_matrix[i][j] == '\0')
                break;
            cout << CT_matrix[i][j] << " ";
        }
        cout << endl;
    }
    string cipher_text = "";
    cout << "CT: ";
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < key; j++)
        {
            if (CT_matrix[j][i] != '*')
            {
                cipher_text = cipher_text + CT_matrix[j][i];
                cout << CT_matrix[j][i] << "";
            }
        }
    }
    fstream fp;
    fp.open("rail_op.txt", fstream::out);
    for (int i = 0; i < cipher_text.length(); i++){fp << cipher_text[i];}
    return cipher_text;
}
void decrypt(string msg, int key)
{
    int count = 0;
    for (int i = 0; msg[i]; i++)
        if (msg[i] != ' ')
            msg[count++] = msg[i];
    msg[count] = '\0';
    char dex[key][key];
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < key; j++)
        {
            dex[i][j] = '*';
        }
    }
    int msg_len = msg.length();
    cout << "\n";
    int k = 0;
    int x = msg_len % key;
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < key; j++)
        {
            if (i <= (x - 1) || j <= (key - 2))
            {
                dex[j][i] = msg[k];
                k++;
            }
            else
            {
                dex[j][i] = '*';
            }
        }
    }
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < key; j++)
        {

            if (dex[i][j] == '\0')
                break;
            cout << dex[i][j] << " ";
        }
        cout << endl;
    }
    string plain_text = " ";
    cout << "PT: ";
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < key; j++)
        {
            if (dex[i][j] != '*')
            {
                plain_text = plain_text + dex[j][i];
                cout << dex[i][j] << "";
            }
        }
    }
}

int main()
{
    char str[100000];
    int no_of_chars = 0;
    int i = 0;
    ifstream myfile("rail_ip.txt");
    while (!myfile.eof())
    {
        myfile.get(str[i]);
        i++;
        no_of_chars++;
    }
    string op_str;
    int l;
    cout << "Length of key: ";
    cin >> l;
    op_str = encrypt(str, l);
    decrypt(op_str, l);
    return 0;
}
