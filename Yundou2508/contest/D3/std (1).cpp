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
const int N=1e5+10,M=1e6+10;
int n,m,a[N],vis[M];
vector<int>to[N],id[M];
int fa[N],f[N],dep[N];
void dfs(int u){
	dep[u]=dep[fa[u]]+1;
	for(int v:to[u])if(v^fa[u]){
		fa[v]=u,dfs(v);
	}
}
bool cmp(int x,int y){
	return dep[x]>dep[y];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		m=max(m,a[i]);
		id[a[i]].push_back(i);
	}
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		to[u].push_back(v),to[v].push_back(u);
	}
	dfs(1);
	int ans=0;
	for(int i=2;i<=m;i++){
		if(vis[i])continue;
		for(int j=i+i;j<=m;j+=i)vis[j]=1;
		vector<int>cur;
		for(int j=i;j<=m;j+=i){
			for(int x:id[j])cur.push_back(x);
		}
		sort(cur.begin(),cur.end(),cmp);
		for(int x:cur){
			ans=max(ans,++f[x]);
			f[fa[x]]+=f[x];
		}
		for(int x:cur)f[x]=f[fa[x]]=0;
	}
	cout<<ans<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif