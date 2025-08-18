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
int T,n,m;
struct item{
	ll x,y;
	bool operator < (const item &a)const{
		return y<a.y;
	}
}a[N];
bool check(ll x){
	__int128 now=0;
	int cnt=0;
	priority_queue<ll>q;
	for(int i=1;i<=n;i++){
		if(a[i].y-now-a[i].x>=x){
			cnt++;
			now+=a[i].x;
			q.push(a[i].x);
		}else{
			if(!q.empty()&&q.top()>a[i].x){
				now-=q.top();
				now+=a[i].x;
				q.pop();
				q.push(a[i].x);
			}
		}
	}
	return cnt>m;
}
void work(){
	scanf("%d%d",&n,&m);
	debug(n,m);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].x,&a[i].y);
	}
	sort(a+1,a+1+n);
	ll l=0,r=(ll)1e18+1,mid;
	for(;l+1<r;){
		mid=(l+r)>>1;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%lld\n",l);
}
int main(){
	for(scanf("%d",&T);T--;)work();
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif