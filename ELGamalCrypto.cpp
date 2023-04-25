//Program for Elgamal
#include<bits/stdc++.h>
using namespace std;
#define ld long

ld ModInv(ld b, ld n){
  ld r1=n,r2=b,t1=0,t2=1;
  while(r2>0){
    ld q=r1/r2;
    ld r=r1-q*r2;
    r1=r2;r2=r;
    ld t=t1-q*t2;
    t1=t2;t2=t;
  }
  if(t1<0)t1+=n;
  return t1;
}

ld powerLL(ld x, ld n, ld MOD) { 
	ld result = 1; 
	while (n) { 
		if (n&1) 
			result = result * x % MOD; 
		n = n / 2; 
		x = x * x % MOD; 
	} 
	return result; 
} 

ld powerStrings(string sa, string sb, ld MOD) { 

	ld a = 0, b = 0; 
	for (int i = 0; i < sa.length(); i++) 
		a = (a * 10 + (sa[i] - '0')) % MOD; 

	for (int i = 0; i < sb.length(); i++) 
		b = (b * 10 + (sb[i] - '0')) % (MOD - 1); 
	return powerLL(a, b, MOD); 
} 

ld mod(string num, ld a) { 
	ld res = 0; 

	// One by one process all digits of 'num' 
	for (int i = 0; i < num.length(); i++) 
		res = (res*10 + (int)num[i] - '0') %a; 

	return res; 
} 




int main(){
    
  ld p,e1,d,m,r,MOD;
  cout<<" Enter the values for p,e1,d,m,r :"<<endl;
  cin>>p>>e1>>d>>m>>r;
  ld e2,s1,s2,v1,v2,a,b;
  e2=powerStrings(to_string(e1),to_string(d),p);if(e2<0)e2+=p;
  s1=powerStrings(to_string(e1),to_string(r),p);if(s1<0)s1+=p;
  s2=(((m-d*s1)%(p-1))*ModInv(r,p-1))%(p-1);if(s2<0)s2+=(p-1);
  v1=powerStrings(to_string(e1),to_string(m),p);if(v1<0)v1+=p;
  a=powerStrings(to_string(e2),to_string(s1),p);if(a<0)a+=p;
  b=powerStrings(to_string(s1),to_string(s2),p);if(b<0)b+=p;
  v2=(a*b)%p;
  cout<<"e2="<<e2<<"\n";
  cout<<"s1="<<s1<<"\n";
  cout<<"s2="<<s2<<"\n";
  cout<<"v1="<<v1<<"\n";
  cout<<"v2="<<v2<<"\n";
  return 0;

}