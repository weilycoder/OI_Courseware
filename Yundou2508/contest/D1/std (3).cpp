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
int n,siz[N],mx[N],cnt[N];
ll ans;
vector<int>to[N];
bitset<N/2>f;
void dfs1(int u,int fa=0){
	siz[u]=1;
	for(int v:to[u])if(v^fa){
		dfs1(v,u);
		mx[u]=max(mx[u],siz[v]);
		siz[u]+=siz[v];
	}
}
void dfs2(int u,int fa=0,int d=0){
	ans+=d,siz[u]=1;
	for(int v:to[u])if(v^fa){
		dfs2(v,u,d+1);
		siz[u]+=siz[v];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		to[u].push_back(v);
		to[v].push_back(u);
	}
	dfs1(1);
	int rt=1;
	for(int i=1;i<=n;i++){
		mx[i]=max(mx[i],n-siz[i]),rt=mx[i]<mx[rt]?i:rt;
	}
	dfs2(rt);
	for(int v:to[rt])cnt[siz[v]]++;
	for(int i=1;i<=n;i++)for(;cnt[i]>2;cnt[i]-=2)cnt[i*2]++;
	f[0]=1;
	for(int i=1;i<=n/2;i++){
		for(int j=1;j<=cnt[i];j++)f|=f<<i;
	}
	for(int i=(n-1)/2;~i;i--)if(f[i]){
		ans+=1ll*i*(n-1-i);break;
	}
	cout<<ans+n<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif