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
int n,m;
ll s,a[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%lld",&a[i]);
	for(int i=0;i<n;i++)s+=i*a[i];
	if(s%(n-1))a[s%(n-1)]--;
	for(int i=1;i<n;i++)a[i]+=a[i-1];
	for(ll k;m--;){
		scanf("%lld",&k);
		if(k>=a[n-1])puts("-1");
		else printf("%ld\n",upper_bound(a,a+n,k)-a);
	}
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif