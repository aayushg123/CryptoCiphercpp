#include<bits/stdc++.h>
using namespace std;
string encrypt(string txt,int key){
    string result="";
    for(int i=0;i<txt.length();i++){
        if(txt[i]==' ') continue;
        if(isupper(txt[i]))
          result+=char(int(txt[i]+key-65)%26+65);

          else 
           result+=char(int(txt[i]+key-97)%26+97);
    }
 return result;

}

int main(){
    string txt;
    getline(cin,txt);
    cout<<txt<<endl;
    int s=4;
    string en=encrypt(txt,s);
    string den=encrypt(en,26-s);
    cout<<"Encrypt:"<<en<<endl;
    cout<<"Decyption:"<<den<<endl;
}
