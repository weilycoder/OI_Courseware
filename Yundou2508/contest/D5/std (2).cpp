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
const int N=2e5+10,K=N*22,V=1e6;
const ll INF=1e18;
int n,a[N];
vector<int>to[N];
ll calc(ll k,ll b,int x){
	return k*x+b;
}
struct tree{
	int ls,rs;
	ll k,b,laz;
	tree(){
		ls=rs=k=laz=0,b=INF;
	}
}t[K];
int k,root[N];
void pushadd(int rt,ll x){
	if(rt)t[rt].b+=x,t[rt].laz+=x;
}
void pushdown(int rt){
	if(t[rt].laz){
		pushadd(t[rt].ls,t[rt].laz);
		pushadd(t[rt].rs,t[rt].laz);
		t[rt].laz=0;
	}
}
void insert(int &rt,ll k,ll b,int l=1,int r=V){
	if(!rt)rt=++::k;
	int mid=(l+r)>>1;
	if(calc(k,b,mid)<calc(t[rt].k,t[rt].b,mid))swap(k,t[rt].k),swap(b,t[rt].b);
	pushdown(rt);
	if(calc(k,b,l)<calc(t[rt].k,t[rt].b,l))insert(t[rt].ls,k,b,l,mid);
	if(calc(k,b,r)<calc(t[rt].k,t[rt].b,r))insert(t[rt].rs,k,b,mid+1,r);
}
ll query(int rt,int x,int l=1,int r=V){
	if(!rt)return INF;
	ll val=calc(t[rt].k,t[rt].b,x);
	if(l==r)return val;
	int mid=(l+r)>>1;
	pushdown(rt);
	if(x<=mid)return min(val,query(t[rt].ls,x,l,mid));
	else return min(val,query(t[rt].rs,x,mid+1,r));
}
void merge(int &x,int y,int l=1,int r=V){
	if(!x||!y){
		x|=y;return;
	}
	if(l==r){
		if(calc(t[x].k,t[x].b,l)>calc(t[y].k,t[y].b,l))swap(x,y);
		return;
	}
	int mid=(l+r)>>1;
	insert(x,t[y].k,t[y].b,l,r);
	pushdown(x),pushdown(y);
	merge(t[x].ls,t[y].ls,l,mid);
	merge(t[x].rs,t[y].rs,mid+1,r);
}
void dfs(int u){
	if(to[u].empty()){
		insert(root[u],a[u],0);
		return;
	}
	for(int v:to[u]){
		dfs(v);
		if(!root[u])root[u]=root[v];
		else{
			ll x=query(root[u],a[u]),y=query(root[v],a[u]);
			pushadd(root[u],y),pushadd(root[v],x);
			merge(root[u],root[v]);
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=2,x;i<=n;i++){
		scanf("%d",&x),to[x].push_back(i);
	}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	dfs(1);
	cout<<query(root[1],a[1])<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif