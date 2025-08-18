#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#ifdef DEBUG
template<typename T>
ostream& operator << (ostream &out,const vector<T> &x){
	out<<'[';
	for(auto y:x)out<<y<<',';
	return out<<']';
}
template<typename T>
vector<T> ary(const T *a,int l,int r){
	return vector<T>{a+l,a+1+r};
}
template<typename T>
void debug(T x){
	cerr<<x<<endl;
}
template<typename T,typename ... S>
void debug(T x,S...y){
	cerr<<x<<' ',debug(y...);
}
#else
#define debug(...) void()
#endif
const int N=2e5+10;
int T,n,a[N],las[N];
struct zj{
	int val,col;
};
struct node{
	zj fi,se;
	void ins(zj x){
		if(x.val>fi.val)swap(fi,x);
		if(x.col^fi.col){
			if(se.val<x.val)se=x;
		}
	}
}f[N];
void get(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int len=1;
	for(int i=2;i<=n;i++){
		if(a[i]!=a[len])a[++len]=a[i];
	}
	n=len;
	las[1]=las[2]=0;
	for(int i=3;i<=n;i++){
		if(a[i-2]==a[i])las[i]=las[i-1];
		else las[i]=i-2;
	}
	for(int i=0;i<=n;i++){
		f[i]={{0,0},{0,0}};
	}
	int ans=0;
	map<int,int>s;
	for(int i=1;i<=n;i++){
		if(s.count(a[i])){
			int x=s[a[i]];
			f[i]=f[x];
		}
		f[i].ins({1,0});
		s[a[i]]=i;
		for(zj x:{f[i-1].fi,f[i-1].se}){
			if(x.col!=a[i])f[i].ins({x.val+1,a[i-1]});
		}
		for(zj x:{f[las[i]].fi,f[las[i]].se}){
			if(x.col!=a[i])f[i].ins({x.val+1,a[las[i]]});
		}
		int j=i-3;
		if(j>0){
			if(a[j]!=a[i]){
				for(zj x:{f[j].fi,f[j].se}){
					if(x.col!=a[i])f[i].ins({x.val+1,a[j]});
				}
			}
		}
		ans=max({ans,f[i].fi.val});
		// debug(i,f[i].fi.val,f[i].fi.col,f[i].se.val,f[i].se.col);
	}
	// debug(ary(a,1,n));
	// debug(ary(f,1,n));
	// debug(ary(g,1,n));
	printf("%d\n",ans);
}
int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	for(scanf("%d",&T);T--;)get();
	return 0;
}