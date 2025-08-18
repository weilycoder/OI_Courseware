#include<bits/stdc++.h>
using namespace std;
#ifdef DEBUG
#include"debug.h"
#else
#define debug(...) void()
#endif
#define all(x) (x).begin(),(x).end()
template<class T>
auto ary(T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
using ll=long long;
using ull=unsigned long long;
const int N=32;
int n;
ll f[N][N];
char a[N],str[10]="[]<>{}()";
int main(){
	scanf("%s",a+1),n=strlen(a+1);
	for(int i=1;i<=n+1;i++)f[i][i-1]=1;
	for(int l=n;l>=1;l--){
		for(int r=l+1;r<=n;r+=2){
			for(int i=0;i<8;i+=2){
				if(a[l]!=str[i]&&a[l]!='?')continue;
				for(int j=l+1;j<=r;j++){
					if(a[j]!=str[i+1]&&a[j]!='?')continue;
					f[l][r]+=f[l+1][j-1]*f[j+1][r];
				}
			}
		}
	}
	cout<<f[1][n]<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif