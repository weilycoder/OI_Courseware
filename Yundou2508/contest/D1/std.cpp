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
const int N=1e3+10;
int T,n,m,h,w;
char a[N][N],b[N][N];
vector<pair<int,int>>p;
bool chk(int x,int y){
	return 1<=x&&x<=n&&1<=y&&y<=m;
}
bool get(){
	scanf("%d%d%d%d",&n,&m,&h,&w);
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=h;i++)scanf("%s",b[i]+1);
	int x=0,y=0;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(!x&&b[i][j]=='x')x=i,y=j;
		}
	}
	if(!x)return 0;
	p.clear();
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(b[i][j]=='x')p.push_back({i-x,j-y});
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='x'){
				for(auto x:p){
					int tx=i+x.first,ty=j+x.second;
					if(!chk(tx,ty)||a[tx][ty]=='.')return 0;
					a[tx][ty]='.';
				}
			}
		}
	}
	return 1;
}
int main(){
	for(scanf("%d",&T);T--;){
		puts(get()?"TAK":"NIE");
	}
}
#ifdef DEBUG
#include"debug.hpp"
#endif