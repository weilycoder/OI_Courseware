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
const int N=1e3+10;
int n,m,cnt[128];
char a[N][N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	int res=0;
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++)cnt[a[i][j]]++;
		int ans=0;
		for(int i=1;i<=n;i++)ans=max(ans,cnt[a[i][j]]);
		res+=n-ans;
		for(int i=1;i<=n;i++)cnt[a[i][j]]=0;
	}
	cout<<res<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif