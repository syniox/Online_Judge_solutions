#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
const int N=105;
const int M=20005;
int n,m,q,dp[M],pep[N][N],wgt[N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	q=nxi(),n=nxi(),m=nxi();
	for(int i=1; i<=q; ++i){
		for(int j=1; j<=n; ++j){
			pep[i][j]=nxi();
		}
	}
	for(int i=1; i<=n; ++i){
		int *buk=wgt[i];
		for(int j=1; j<=q; ++j){
			buk[j]=pep[j][i]*2+1;
		}
		std::sort(buk+1,buk+q+1);
	}
	for(int i=1; i<=n; ++i){
		int *val=wgt[i];
		for(int j=m; j; --j){
			for(int k=1; k<=q&&j>=val[k]; ++k){
				apx(dp[j],dp[j-val[k]]+i*k);
			}
		}
	}
	printf("%d\n",dp[m]);
	return 0;
}
