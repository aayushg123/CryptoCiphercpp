#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cout<<"Enter the plaintext:";
    getline(cin,s);
    cout<<"Enter the key:";
    int key;
    cin>>key;
    int n=s.size();
    vector<vector<char>> a(key,vector<char>(s.size(),' '));
    int flag=1;int j=0;
    for(int i=0;i<s.size();i++){
        a[j][i]=s[i];
        if(j==key-1)
            flag=0;
        if(j==0)
            flag=1;
        if(flag==1) j++;
        else j--;
    }
    for(int i=0;i<key;i++){
        for(int j=0;j<s.size();j++){
            if(a[i][j]!=' ') cout<<a[i][j];
        }
    }
 cout<<endl;
 a.clear();
 // Decryption of rail fence

     j=0;
     flag=0;
    for(int i=0;i<s.size();i++){
        a[j][i] = '0';
         if(j==key-1){
            flag=1;
        }
        else if(j==0)
            flag=0;
        if(flag==0){
            j++;
        }
        else j--;
    }
    int temp =0;
    for(int i=0;i<key;i++){
        for(j=0;j<s.size();j++){
                if(a[i][j]=='0')
                    a[i][j]= s[temp++];
        }
    }
    flag=0;
    j=0;
    for(int i=0;i<s.size();i++){
        cout<<a[j][i];
         if(j==key-1){
            flag=1;
        }
        else if(j==0)
            flag=0;
        if(flag==0){
            j++;
        }
        else j--;
    }
    cout<<'\n';   
    }


