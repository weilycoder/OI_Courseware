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
using LL=__int128;
const int N=1e5+10;
const LL INF=1e36;
int n;
ll a[N];
LL f[N];
struct line{
	ll k;
	LL b;
	LL calc(ll x)const{
		return (LL)k*x+b;
	}
};
namespace SGT{
	const int M=N*2;
	const ll V=2e14;
	struct node{
		int ls,rs;
		line x;
	}t[M];
	int k,root;
	void insert(line x,int &rt=root,ll l=1,ll r=V){
		if(!rt)rt=++k,t[rt]={0,0,{0,-INF}};
		ll mid=(l+r)>>1;
		if(x.calc(mid)>t[rt].x.calc(mid))swap(x,t[rt].x);
		if(x.calc(l)>t[rt].x.calc(l))insert(x,t[rt].ls,l,mid);
		if(x.calc(r)>t[rt].x.calc(r))insert(x,t[rt].rs,mid+1,r);
	}
	LL query(ll x,int rt=root,ll l=1,ll r=V){
		if(!rt)return -INF;
		LL val=t[rt].x.calc(x);
		if(l==r)return val;
		ll mid=(l+r)>>1;
		if(x<=mid)return max(val,query(x,t[rt].ls,l,mid));
		else return max(val,query(x,t[rt].rs,mid+1,r));
	}
	void clear(){
		k=root=0;
	}
}
void solve(int l,int r){
	if(r-l+1<3){
		for(int i=l;i<=r;i++)f[i]=max(f[i],f[i-1]);
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	set<ll>s;
	for(int i=mid;i>=l;i--){
		auto it=s.lower_bound(a[i]);
		auto ins=[&](ll a,ll b){
			SGT::insert({2*(a+b),-LL(a-b)*(a-b)+f[i-1]});
		};
		if(it!=s.end())ins(*it,a[i]);
		if(it!=s.begin())ins(*prev(it),a[i]);
		s.insert(a[i]);
	}
	for(int i=mid+1;i<=r;i++){
		f[i]=max(f[i],-(LL)a[i]*a[i]+SGT::query(a[i]));
	}
	s.clear(),SGT::clear();
	for(int i=mid;i>=l;i--){
		SGT::insert({2*a[i],-(LL)a[i]*a[i]+f[i-1]});
	}
	for(int i=mid+1;i<=r;i++){
		auto it=s.lower_bound(a[i]);
		auto qry=[&](ll a,ll b){
			f[i]=max(f[i],SGT::query(a+b)-LL(a-b)*(a-b));
		};
		if(it!=s.end())qry(*it,a[i]);
		if(it!=s.begin())qry(*prev(it),a[i]);
		s.insert(a[i]);
	}
	s.clear(),SGT::clear();
	solve(mid+1,r);
}
ostream& operator << (ostream &out,__int128 a){
	if(a>9)out<<a/10;
	return out<<int(a%10);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	fill(f+1,f+1+n,-INF);
	solve(1,n);
	cout<<f[n]<<endl;
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif