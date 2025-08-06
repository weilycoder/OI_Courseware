#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

int n,m,cnt[10],x[10],y[10];
bool vis[1010][1010];
string s[1010];

int dx[]={0,1,0,-1},dy[]={-1,0,1,0};
char seq[3]={'R','G','B'};
inline void readAndCheckAnswer(InStream& in,int te) {
	++te;
	for (int i=0;i<n;i++) {
    	s[i] = in.readWord(); 
    	for (int j=0;j<m;j++) vis[i][j]=0;
    	for(int j=0;j<m;j++)if(s[i][j]!='R'&&s[i][j]!='G'&&s[i][j]!='B')in.quitf(_wa, "Wrong Answer 1on test %d!",te);
    	if (int(s[i].length()) != m)
        	in.quitf(_wa, "Wrong Answer  2 on test %d!",te);
    }
    for (int i=0;i<3;i++) {
    	if (s[x[i]][y[i]]!=seq[i]) {in.quitf(_wa, "Wrong Answer3  on test %d!",te);
    	}
    }
    for (int i=0;i<3;i++) {
    	int sz=0;
    	function<void(int,int)> dfs=[&](int x,int y) {
    		sz+=1;
    		vis[x][y]=1;
    		for (int dd=0;dd<4;dd++) {
    			int nx=(x+n+dx[dd])%n,ny=(y+m+dy[dd])%m;
    			if (!vis[nx][ny]&&s[nx][ny]==s[x][y]) {
    				dfs(nx,ny);
    			}
    		}
    	};
    	dfs(x[i],y[i]);
    	if (sz!=cnt[i]) in.quitf(_wa, "Wrong Answer 4on test %d!",te);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int T=inf.readInt();
    for (int i=0;i<T;i++) {
        //setTestCase(i+1);
	    n = inf.readInt();
	    m=inf.readInt();
	    for (int j=0;j<3;j++) {
	    	x[j]=inf.readInt(),y[j]=inf.readInt();
	    	--x[j]; --y[j];
	    }
	    for (int j=0;j<3;j++) cnt[j]=inf.readInt();
	    //readAndCheckAnswer(ans);
	    readAndCheckAnswer(ouf,i);
	}
	quitf(_ok, "ok");
}
