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
const int N=510;
int n;
unsigned mod,C[N][N],f[N][N],s[N][N];
int main(){
	cin>>n>>mod;
	for(int i=0;i<=n;i++){
		for(int j=C[i][0]=1;j<=i;j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
	}
	f[1][1]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=n;j++){
			s[i-1][j]=(s[i-1][j-1]+f[i-1][j])%mod;
		}
		for(int d=1;d<=i;d++){
			f[i][d]=f[i-1][d-1];
			for(int j=1;j+1<i;j++){
				f[i][d]=(f[i][d]+(1ull*s[j][d-1]*f[i-j][d]+1ull*f[j][d-1]*s[i-j][d-1])%mod*C[i-2][j-1])%mod;
			}
		}
	}
	for(int i=1;i<=n;i++){
		unsigned ans=0;
		for(int j=1;j<=i;j++){
			ans=(ans+1ull*j*f[i][j])%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif