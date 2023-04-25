#include<iostream>
#include<stdlib.h>
using namespace std;

int key[3][3];
int mod26(int x){
    return (x>=0) ? (x%26) : 26-(abs(x)%26);
}
int det(int m[3][3],int n){
    int res=0;
    if(n==2)
      res=(m[0][0]*m[1][1]-m[1][0]*m[0][1]);
    else if(n==3)
    res = m[0][0]*(m[1][1]*m[2][2]-m[2][1]*m[1][2]) - m[0][1]*(m[1][0]*m[2][2]-m[2][0]*m[1][2]) + m[0][2]*(m[1][0]*m[2][1]-m[2][0]*m[1][1]);

    return mod26(res);
}

int detinv(int a,int m){
    for(int i=1;i<m;i++){
        if(((a%m)*(i%m))% m ==1)
            return i;
    }
    
}

void multiplymatrix(int P[1000][3],int rowP,int colP,int C[1000][3],int rowC,int colC,int r[1000][3]){
    for(int i=0;i<rowP;i++){
        for(int j=0;j<colC;j++){
            for(int k=0;k<rowC;k++){
                r[i][j]+=(P[i][k]*C[k][j]);
            }
            r[i][j] = mod26(r[i][j]);
        }
    }
}
void findinv(int m[3][3] , int n , int m_inverse[3][3] )
{
	int adj[3][3] = {0};

	int a = det(m , n); // findDet(matrix , order_of_matrix)
	int b = detinv(a,26);
    cout<<b<<endl;

	if(n==2)
	{
		adj[0][0] = m[1][1];
		adj[1][1] = m[0][0];
		adj[0][1] = -m[0][1];
		adj[1][0] = -m[1][0];
	}
	else if(n==3)
	{
		int temp[5][5] = {0} ;
		// fill the 5x5 matrix
		for(int i=0; i<5; i++)
		{
			for(int j=0; j<5; j++)
			{
				temp[i][j] = m[i%3][j%3] ;
			}
		}
		/* except first row and first column, multiply elements along rows and place them along columns */
		for(int i=1; i<=3 ; i++)
		{
			for(int j=1; j<=3 ; j++)
			{
				adj[j-1][i-1] = temp[i][j]*temp[i+1][j+1] - temp[i][j+1]*temp[i+1][j];
			}
		}
	}

	for(int i=0; i<n ; i++)
	{
		for(int j=0; j<n ; j++)
		{
			m_inverse[i][j] = mod26(adj[i][j] * b) ;
		}
	}
}

string encrypt(string pt,int n){
   int P[1000][3]={0};
   int C[1000][3]={0};
   int itr=0;
   while(pt.length()%n!=0){
    pt+='x';
   }
   int rowP=(pt.length()/n);
   for (int i = 0; i < rowP; i++){
        for (int j = 0; j < n; j++)
        {
            P[i][j]=pt[itr++]-'a';
        }
   }
   multiplymatrix(P,rowP,n,key,n,n,C);
   string ct="";
   for(int i=0;i<rowP;i++){
    for(int j=0;j<n;j++){
        ct+=(C[i][j]+'a');
    }
   }
   return ct;
}
string decrypt(string ct,int n){
   int C[1000][3]={0};
   int P[1000][3]={0};
   int itr=0;
   
   int rowC=(ct.length()/n);
   for (int i = 0; i < rowC; i++){
        for (int j = 0; j < n; j++)
        {
            C[i][j]=ct[itr++]-'a';
        }
   }
    int keyinv[3][3]={0};
    findinv(key,n,keyinv);

   multiplymatrix(C,rowC,n,keyinv,n,n,P);
   for(int i=0;i<rowC;i++){
    for(int j=0;j<n;j++){
        cout<<P[i][j]<<" ";
    }
    cout<<endl;
   }
   string pt="";
   for(int i=0;i<rowC;i++){
    for(int j=0;j<n;j++){
    pt+=(P[i][j]+'a');
    }
   }
   return pt;
}
int main(){
    string pt ;
	int n ;

	cout << "Enter the text to be encrypted    : " ;
	cin >> pt;

	cout << "Enter order of key matrix : ";
	cin >> n ;

	cout<<"Enter key matrix: " <<endl;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cin >> key[i][j];
		}
	}

	cout << "\nOriginal text  : " << pt << endl;

	string ct = encrypt(pt, n) ;
	cout << "Encrypted text : " << ct << endl;

	string dt = decrypt(ct, n);
	cout << "Decrypted text : " << dt << endl;
    return 0;
}
