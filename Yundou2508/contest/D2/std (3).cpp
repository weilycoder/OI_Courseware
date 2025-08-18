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
const int N=5e5+10;
int q,m;
ll n,k,a[N];
ll t[N<<2],laz[N<<2],cov[N<<2];
void pushup(int rt){
	t[rt]=max(t[rt<<1],t[rt<<1|1]);
}
void pushlaz(int rt,ll x){
	t[rt]+=x,laz[rt]+=x;
}
void pushcov(int rt,ll x){
	laz[rt]=0,t[rt]=cov[rt]=x;
}
void pushdown(int rt){
	if(cov[rt]!=-1){
		pushcov(rt<<1,cov[rt]);
		pushcov(rt<<1|1,cov[rt]);
		cov[rt]=-1;
	}
	if(laz[rt]){
		pushlaz(rt<<1,laz[rt]);
		pushlaz(rt<<1|1,laz[rt]);
		laz[rt]=0;
	}
}
void build(int l=1,int r=m,int rt=1){
	laz[rt]=0,cov[rt]=-1;
	if(l==r)return t[rt]=0,void();
	int mid=(l+r)>>1;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	pushup(rt);
}
void update(int L,int R,ll x,int l=1,int r=m,int rt=1){
	if(R<l||r<L)return;
	if(L<=l&&r<=R)return pushlaz(rt,x);
	int mid=(l+r)>>1;
	pushdown(rt);
	update(L,R,x,l,mid,rt<<1);
	update(L,R,x,mid+1,r,rt<<1|1);
	pushup(rt);
}
void cover(int L,int R,ll x,int l=1,int r=m,int rt=1){
	if(R<l||r<L)return;
	if(L<=l&&r<=R)return pushcov(rt,x);
	int mid=(l+r)>>1;
	pushdown(rt);
	cover(L,R,x,l,mid,rt<<1);
	cover(L,R,x,mid+1,r,rt<<1|1);
	pushup(rt);
}
int find(int L,int R,ll x,int l=1,int r=m,int rt=1){
	if(t[rt]<x)return 0;
	if(l==r)return l;
	int mid=(l+r)>>1,s=0;
	pushdown(rt);
	if(L<=mid)s=find(L,R,x,l,mid,rt<<1);
	if(s)return s;
	if(mid<R)s=find(L,R,x,mid+1,r,rt<<1|1);
	return s;
}
int getid(ll x){
	return lower_bound(a+1,a+1+m,x)-a;
}
int main(){
	scanf("%lld%d%lld",&n,&q,&k);
	vector<pair<ll,int>>s;
	for(ll l,r;q--;){
		scanf("%lld%lld",&l,&r);
		a[++m]=l%k;
		if(r%k+1<k)a[++m]=r%k+1;
		s.push_back({l,1});
		s.push_back({r+1,-1});
	}
	a[++m]=0;
	sort(a+1,a+1+m);
	m=unique(a+1,a+1+m)-a-1;
	a[m+1]=k;
	sort(all(s));
	for(int l=0,r,x=0;l<s.size();l=r){
		ll st=s[l].first;
		for(r=l+1;r<s.size()&&s[r].first==st;r++);
		if(r==s.size())break;
		ll len=s[r].first-st;
		for(int i=l;i<r;i++)x+=s[i].second;
		ll val=t[1];
		int id=getid(st%k);
		for(;;){
			int k=find(id,m,val-x);
			if(k==id)break;
			if(!k)k=m+1;
			if(a[k]-a[id]>len){
				cover(id,getid(a[id]+len)-1,val),len=0;
				break;
			}else{
				cover(id,k-1,val);
				len-=a[k]-a[id],id=k<=m?k:1;
			}
		}
		update(1,m,len/k*x),len%=k;
		if(a[id]+len>k){
			update(id,m,x);
			update(1,getid(a[id]+len-k)-1,x);
		}else update(id,getid(a[id]+len)-1,x);
	}
	printf("%lld\n",t[1]);
}
#ifdef DEBUG
#include"debug.hpp"
#endif