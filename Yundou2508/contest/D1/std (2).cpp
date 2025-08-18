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
const int N=1e6+10,K=30;
int T,n,m,a[N],cnt[N];
struct ques{
	int w,l,r;
}o[N];
int tar[N],sum[N],ans[N],one[N];
void work(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&o[i].l,&o[i].r);
		sum[i]=one[i]=tar[i]=ans[i]=0;
	}
	for(int k=K-1;k>=0;k--){
		for(int i=1;i<=n;i++)cnt[i]=a[i]>>k&1;
		for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
		for(int i=1;i<=m;i++){
			sum[i]=sum[i]<<1|(cnt[o[i].r]!=cnt[o[i].l-1]);
			one[i]=one[i]<<1|(cnt[o[i].r]==cnt[o[i].l-1]+1);
		}
	}
	static int tot,idx[N],his[N];
	tot=0;
	for(int i=1;i<=m;i++){
		if(!sum[i])continue;
		tar[i]=(2<<__lg(sum[i]))-1;
		if(sum[i]==tar[i])continue;
		o[i].w=__builtin_ctz(~sum[i]);
		idx[++tot]=i;
	}
	fill(cnt,cnt+1+n,0);
	for(int i=1;i<=tot;i++){
		cnt[o[idx[i]].r]++;
	}
	for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
	for(int i=tot;i>=1;i--){
		his[cnt[o[idx[i]].r]--]=idx[i];
	}
	fill(cnt,cnt+K,0);
	for(int i=1;i<=tot;i++){
		cnt[o[his[i]].w]++;
	}
	for(int i=1;i<K;i++)cnt[i]+=cnt[i-1];
	for(int i=tot;i>=1;i--){
		idx[cnt[o[his[i]].w]--]=his[i];
	}
	for(int k=0,p=1;k<K;k++){
		static int pre[N],cur[K];
		fill(cur,cur+K,0);
		for(int i=1;i<=n;i++){
			if(a[i]>=(1<<k)){
				int x=__builtin_ctz(a[i]&~((1<<k)-1));
				pre[i]=cur[x];
				cur[x]=i;
			}
			for(;p<=tot&&o[idx[p]].w==k&&o[idx[p]].r==i;p++){
				int id=idx[p],l=o[idx[p]].l;
				ans[id]=[&](){
					for(int x=__lg(sum[id]),t=K+1;(sum[id]>>x&1)&&t>0;x--){
						for(int i=cur[x];i>=l;i=pre[i],t--){
							if(!(a[i]&a[i]-(1<<k)&one[id]))return 1;
						}
					}
					return 2;
				}();
			}
		}
	}
	for(int i=1;i<=m;i++){
		printf("%d %d\n",tar[i],ans[i]);
	}
}
int main(){
	for(scanf("%*d%d",&T);T--;)work();
	return 0;
}
#ifdef DEBUG
#include"debug.hpp"
#endif