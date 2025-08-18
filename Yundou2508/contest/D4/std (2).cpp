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
int T,n;
void work(){
	scanf("%d",&n);
	vector<pair<int,int>>E(n);
	for(auto &[x,y]:E){
		scanf("%d%d",&x,&y);
	}
	sort(all(E));
	ll cur=0,ans=0;
	for(auto [x,y]:E){
		cur+=y;
		ans=max(ans,(cur+x-1)/x);
	}
	printf("%lld\n",ans);
}
int main(){
	for(scanf("%d",&T);T--;)work();
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif