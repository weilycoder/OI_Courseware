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
const int N=1e5+10;
int n,m;
vector<pair<int,int>>to[N];
int fa[N],faw[N],dep[N],siz[N],son[N],top[N];
ll d[N],f[N],g[N];
void dfs1(int u){
	dep[u]=dep[fa[u]]+1,siz[u]=1;
	for(auto [v,w]:to[u]){
		to[v].erase(find(all(to[v]),make_pair(u,w)));
		fa[v]=u,faw[v]=w;
		d[v]=d[u]+w;
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
		f[u]=max(f[u],f[v]+w);
	}
}
int dft,dfn[N],pos[N];
void dfs2(int u,int t){
	top[u]=t;
	pos[dfn[u]=++dft]=u;
	ll fi=g[u]+faw[u],se=0;
	for(auto [v,w]:to[u]){
		if(f[v]+w>fi)se=fi,fi=f[v]+w;
		else se=max(se,f[v]+w);
	}
	for(auto [v,w]:to[u]){
		g[v]=f[v]+w==fi?se:fi;
	}
	if(son[u])dfs2(son[u],t);
	for(auto [v,w]:to[u])if(v^son[u])dfs2(v,v);
	sort(all(to[u]),[&](pair<int,int>x,pair<int,int>y){
		return dfn[x.first]<dfn[y.first];
	});
}
bool check1(int u,int x,int t,int v,int v1,int v2){ // v1 <= v2
	ll d1=d[u]-d[x];
	ll d2=d[x]+d[v]-d[t]*2;
	return d1*v2>d2*v1;
}
bool check2(int u,int x,int t,int v,ll w,int v1,int v2){ // v1 > v2
	ll d1=d[u]-d[x]+w;
	ll d2=d[x]+d[v]-d[t]*2+w;
	return d1*v2>d2*v1;
}
bool check3(int u,int t,int x,int v,int v1,int v2){ // v1 <= v2
	ll d1=d[u]+d[x]-d[t]*2;
	ll d2=d[v]-d[x];
	return d1*v2>d2*v1;
}
bool check4(int u,int t,int x,int v,int v1,int v2){ // v1 > v2
	ll d1=d[u]+d[x]-d[t]*2+f[x];
	ll d2=d[v]-d[x]+f[x];
	return d1*v2>d2*v1;
}
int LCA(int u,int v){
	for(;top[u]^top[v];u=fa[top[u]]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
	}
	return dep[u]<dep[v]?u:v;
}
int findson(int t,int u){
	int l=0,r=to[t].size(),mid;
	for(;l+1<r;){
		mid=(l+r)>>1;
		if(dfn[u]<dfn[to[t][mid].first])r=mid;
		else l=mid;
	}
	return to[t][l].first;
}
struct frac{
	ll x;
	int y;
};
bool operator < (const frac &a,const frac &b){
	return a.x*b.y<b.x*a.y;
}
frac query(int u,int v,int v1,int v2){
	int t=LCA(u,v);
	if(v1<=v2){
		if(u!=t&&(v==t||check1(u,t,t,v,v1,v2))){
			int x=u;
			for(;dep[fa[top[x]]]>dep[t];x=fa[top[x]]){
				if(check1(u,fa[top[x]],t,v,v1,v2))break;
			}
			int l=dep[t]>dep[fa[top[x]]]?dfn[t]:dfn[top[x]]-1,r=dfn[x],mid;
			for(;l+1<r;){
				mid=(l+r)>>1;
				if(check1(u,pos[mid],t,v,v1,v2))l=mid;
				else r=mid;
			}
			x=pos[r];
			return {d[u]-d[fa[x]]+g[x],v1};
		}else{
			int x=v;
			for(;dep[fa[top[x]]]>dep[t];x=fa[top[x]]){
				if(!check3(u,t,fa[top[x]],v,v1,v2))break;
			}
			int l=dep[t]>dep[fa[top[x]]]?dfn[t]:dfn[top[x]]-1,r=dfn[x],mid;
			for(;l+1<r;){
				mid=(l+r)>>1;
				if(!check3(u,t,pos[mid],v,v1,v2))l=mid;
				else r=mid;
			}
			x=pos[r];
			return {d[u]+d[x]-d[t]*2+f[x],v1};
		}
	}else{
		int x;
		if(u!=t&&(v==t||(x=findson(t,u),check2(u,t,t,v,g[x],v1,v2)))){
			x=u;
			for(;dep[fa[top[x]]]>dep[t];x=fa[top[x]]){
				if(check2(u,fa[top[x]],t,v,g[top[x]],v1,v2))break;
			}
			int l=dep[t]>dep[fa[top[x]]]?dfn[t]:dfn[top[x]]-1,r=dfn[x],mid;
			for(;l+1<r;){
				mid=(l+r)>>1;
				if(check2(u,pos[mid],t,v,g[pos[mid+1]],v1,v2))l=mid;
				else r=mid;
			}
			x=pos[r];
			frac ans=min((frac){d[u]-d[fa[x]]+g[x],v1},(frac){(d[u]-d[fa[x]])-(d[fa[x]]+d[v]-d[t]*2),v1-v2});
			if(check1(u,x,t,v,v1,v2)){
				ans=max(ans,(frac){(d[u]-d[x])-(d[x]+d[v]-d[t]*2),v1-v2});
			}
			return ans;
		}else{
			int x=v;
			for(;dep[fa[top[x]]]>dep[t];x=fa[top[x]]){
				if(!check4(u,t,fa[top[x]],v,v1,v2))break;
			}
			int l=dep[t]>dep[fa[top[x]]]?dfn[t]:dfn[top[x]]-1,r=dfn[x],mid;
			for(;l+1<r;){
				mid=(l+r)>>1;
				if(!check4(u,t,pos[mid],v,v1,v2))l=mid;
				else r=mid;
			}
			x=pos[r];
			frac ans=min((frac){d[u]+d[x]-d[t]*2+f[x],v1},(frac){(d[x]+d[u]-d[t]*2)-(d[v]-d[x]),v1-v2});
			if(check3(u,t,fa[x],v,v1,v2)){
				ans=max(ans,(frac){(d[fa[x]]+d[u]-d[t]*2)-(d[v]-d[fa[x]]),v1-v2});
			}
			return ans;
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		to[u+1].push_back({v+1,w});
		to[v+1].push_back({u+1,w});
	}
	dfs1(1);
	dfs2(1,1);
	for(int u,v,v1,v2;m--;){
		scanf("%d%d%d%d",&u,&v1,&v,&v2);
		auto res=query(u+1,v+1,v1,v2);
		ll g=__gcd(res.x,(ll)res.y);
		printf("%lld/%lld\n",res.x/g,res.y/g);
	}
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif