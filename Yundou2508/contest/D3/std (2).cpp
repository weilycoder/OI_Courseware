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
vector<int>to[N];
int even,odd,len;
int cov[N],dep[N],vis[N],f[N];
void dfs1(int u,int fa=0){
	dep[u]=dep[fa]+1,vis[u]=f[u]=1;
	for(int v:to[u])if(v^fa){
		if(!vis[v]){
			dfs1(v,u);
			len=max(len,f[u]+f[v]);
			f[u]=max(f[u],f[v]+1);
		}else if(dep[u]>dep[v]){
			if((dep[u]&1)==(dep[v]&1))odd=1;
			else even=1;
			cov[u]++,cov[v]--;
			if(dep[v]+2==dep[u]&&(to[u].size()>2||to[v].size()>2||to[fa].size()>2)){
				len=4;
			}
		}
	}
}
void dfs2(int u,int fa=0){
	vis[u]=1;
	for(int v:to[u])if(v^fa){
		if(!vis[v]){
			dfs2(v,u);
			cov[u]+=cov[v];
		}
	}
	if(cov[u]>1)even=1;
}
int work(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		to[u].push_back(v);
		to[v].push_back(u);
	}
	for(int i=1;i<=n;i++)if(!vis[i])dfs1(i);
	fill(vis,vis+1+n,0);
	for(int i=1;i<=n;i++)if(!vis[i])dfs2(i);
	if(n<=3)return -1;
	if(m<=2)return 5-m;
	if(even){
		if(odd)return 0;
		else return 1;
	}else{
		if(odd)return 5-min(4,len);
		else{
			if(len==3){
				for(int i=1;i<=n;i++){
					if(to[i].size()>=3){
						return 2;
					}
				}
			}else if(len==2){
				return 5-min(2,m);
			}
			return 6-min(4,len);
		}
	}
}
int main(){
	cout<<work()<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif
