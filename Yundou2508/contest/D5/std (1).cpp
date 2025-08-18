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
int n,l[N],r[N],q[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&l[i],&r[i]);
	}
	int L=1,R=0,ans=0;
	for(int i=1;i<=n;i++){
		for(;L<=R&&l[q[R]]<=l[i];R--);
		q[++R]=i;
		for(;L<=R&&l[q[L]]>r[i];L++);
		ans=max(ans,i-q[L-1]);
	}
	cout<<ans<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif