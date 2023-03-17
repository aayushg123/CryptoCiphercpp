#include <bits/stdc++.h>
using namespace std;
vector<vector<char>> generatekeymat(string key, vector<vector<char>> keymat)
{
    vector<int> x(26, 0);
    int r = 0, c = 0;
    for (int i = 0; i < key.length(); i++)
    {
        if (x[key[i] - 'a'] == 0)
        {
            if (key[i] == 'i' || key[i] == 'j')
            {
                keymat[r][c] = 'i';
                x['i' - 'a'] = 1;
                x['j' - 'a'] = 1;
            }
            else if (key[i] != 'i' && key[i] != 'j')
            {
                keymat[r][c] = key[i];
                x[key[i] - 'a'] = 1;
            }
            c++;
            if (c == 5)
            {
                c = 0;
                r++;
            }
        }
    }
    for (int i = 0; i < 26; i++)
    {
        char temp = char(i + 'a');
        if (x[i] == 0)
        {
            if (temp == 'i')
            {
                keymat[r][c] = 'i';
                x[i] = 1;
                x[i + 1] = 1;
            }
            else
            {
                keymat[r][c] = temp;
                x[i] = 1;
            }
            c++;
            if (c == 5)
            {
                c = 0;
                r++;
            }
        }
    }
    return keymat;
}
vector<pair<char, char>> prepare(string s)
{
    for (int j = 0; j < s.length(); j++)
    {
        if (s[j] == 'j')
            s[j] == 'i';
    }
    vector<pair<char, char>> v;
    int i = 0;
    while (i < s.length())
    {
        if (i == s.length() - 1)
        {
            v.push_back({s[i], 'x'});
            break;
        }
        if (s[i + 1] == s[i])
        {
            v.push_back({s[i], 'x'});
            i++;
        }
        else
        {
            v.push_back({s[i], s[i + 1]});
            i += 2;
        }
    }
    return v;
}
vector<int> search(vector<vector<char>> keymat, char x)
{
    if (x == 'j')
        x = 'i';
    vector<int> v;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (x == keymat[i][j])
            {
                v.push_back(i);
                v.push_back(j);
                return v;
            }
        }
    }
    return v;
}
string encrypt(string s, vector<vector<char>> keymat)
{
    vector<pair<char, char>> v = prepare(s);
    string res = "";
    for (int i = 0; i < v.size(); i++)
    {
        vector<int> v1 = search(keymat, v[i].first);
        vector<int> v2 = search(keymat, v[i].second);
        int r1 = v1[0];
        int c1 = v1[1];
        int r2 = v2[0];
        int c2 = v2[1];
        if (r1 == r2)
        {
            res += keymat[r1][(c1 + 1) % 5];
            res += keymat[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            res += keymat[(r1 + 1) % 5][c1];
            res += keymat[(r2 + 1) % 5][c2];
        }
        else
        {
            res += keymat[r1][c2];
            res += keymat[r2][c1];
        }
    }
    return res;
}
string decrypt(string s, vector<vector<char>> keymat)
{
    vector<pair<char, char>> v = prepare(s);
    string res = "";
    for (int i = 0; i < v.size(); i++)
    {
        vector<int> v1 = search(keymat, v[i].first);
        vector<int> v2 = search(keymat, v[i].second);
        int r1 = v1[0];
        int c1 = v1[1];
        int r2 = v2[0];
        int c2 = v2[1];
        if (r1 == r2)
        {
            res += keymat[r1][(c1 - 1 + 5) % 5];
            res += keymat[r2][(c2 - 1 + 5) % 5];
        }
        else if (c1 == c2)
        {
            res += keymat[(r1 - 1 + 5) % 5][c1];
            res += keymat[(r2 - 1 + 5) % 5][c2];
        }
        else
        {
            res += keymat[r1][c2];
            res += keymat[r2][c1];
        }
    }
    return res;
}
int main()
{
    string s;
    cout << "Enter the string: ";
    cin >> s;
    string key;
    cout << "Enter the key: ";
    cin >> key;
    vector<vector<char>> keymat(5, vector<char>(5, '0'));
    keymat = generatekeymat(key, keymat);
    cout << "Key Table: " << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            cout << keymat[i][j] << " ";
        cout << endl;
    }
    string es = encrypt(s, keymat);
    cout << "Encrypted string: " << es << endl;
    cout << "Decrypted string: " << decrypt(es, keymat) << endl;
    return 0;
}