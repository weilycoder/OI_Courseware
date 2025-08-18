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
const int N=1e6+10;
int T,n,m,a[N],b[N],c[N],ans[N];
void work(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		ll x;
		scanf("%lld",&x);
		ll d=x/(n+n-1);
		if(d>m){
			ans[1]++;
			continue;
		}
		x=x%(n+n-1)+1;
		if(i==n||x>n+n-i-i)a[d]++;
		else if(x>i+i-1)b[d]++;
		else c[d]++;
	}
	for(int d=0;d<=m;d++){
		for(int i=1;i<=m;i+=d+1)ans[i]+=a[d];
		for(int i=1,o=0;i<=m;i+=d+o,o=1)ans[i]+=b[d];
		for(int i=1,o=0;i<=m;i+=d+o,o^=1)ans[i]+=c[d];
	}
	for(int i=1;i<=m;i++){
		printf("%d%c",ans[i],"\n "[i<m]);
	}
}
void clr(){
	fill(a,a+1+m,0);
	fill(b,b+1+m,0);
	fill(c,c+1+m,0);
	fill(ans,ans+1+m,0);
}
int main(){
	for(scanf("%d",&T);T--;clr())work();
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif