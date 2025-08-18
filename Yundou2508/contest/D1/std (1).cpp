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
const int N=5e5+10,mod=1e9+7;
int n;
vector<pair<int,int>>to[N];
pair<ll,int> dfs(int u,int fa=-1){
	pair<ll,int>mx(0,u);
	for(auto [v,w]:to[u])if(v^fa){
		auto x=dfs(v,u);
		x.first+=w,mx=max(mx,x);
	}
	return mx;
}
ll d[N];
void cover(int u,int fa=-1,ll x=0){
	d[u]=max(d[u],x);
	for(auto [v,w]:to[u])if(v^fa)cover(v,u,x+w);
}
int main(){
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		to[u].push_back({v,w});
		to[v].push_back({u,w});
	}
	auto [d1,s]=dfs(0);
	auto [d2,t]=dfs(s);
	cover(s),cover(t);
	sort(d,d+n,greater<>());
	int ans=0;
	for(int i=0;i<n;i++)ans=(ans+d[i]%mod*i)%mod;
	cout<<ans*2%mod<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif