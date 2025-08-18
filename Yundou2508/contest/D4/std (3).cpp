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
const int N=2e5+10,K=6;
int T,n;
struct node{
	pair<int,int>fi,se;
	void insert(pair<int,int>x){
		for(auto t:{&fi,&se}){
			if(t->second==x.second){
				t->first=max(t->first,x.first);
				if(fi.first<se.first)swap(fi,se);
				return;
			}
		}
		for(auto t:{&fi,&se}){
			if(x>*t)swap(x,*t);
		}
	}
	int query(int x){
		for(auto t:{fi,se}){
			if(t.second!=x)return t.first;
		}
		assert(0);
	}
}o;
void work(){
	scanf("%d",&n);
	int a[K]={0,0,0,0,0,0},ans=0;
	node f[K]={o,o,o,o,o,o};
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		node cur=o;
		for(int j=0,now=x;j<K;j++){
			swap(cur,f[j]);
			swap(now,a[j]);
			if(now==x)break;
		}
		for(int j=1;j<K;j++){
			f[0].insert({f[j].query(x)+1,a[j]});
		}
		ans=max(ans,f[0].query(-1));
	}
	printf("%d\n",ans);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	for(scanf("%d",&T);T--;)work();
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif