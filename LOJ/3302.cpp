#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=23;
int n,m,q,lg2[1<<N];
int tox[2][N][1<<12],xto[2][N][1<<12];
int go[N][N],dp[1<<N],cbit[1<<N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline int get(const int v[2][N][1<<12],const int x,const int stat){
	return v[0][x][stat&((1<<12)-1)]+v[1][x][stat>>12];
}

int main(){
	m=nxi(),n=nxi(),q=nxi();
	for(int i=1; i<N; ++i){
		lg2[1<<i]=i;
	}
	for(int cur,lst=nxi()-1,i=2; i<=m; lst=cur,++i){
		cur=nxi()-1;
		if(lst==cur) continue;
		++go[lst][cur];
	}
	for(int i=0; i<n; ++i){
		const int lim=std::min(1<<12,1<<n);
		for(int j=1; j<lim; ++j){
			int lb=j&-j,p=lg2[lb];
			tox[0][i][j]=tox[0][i][j^lb]+go[p][i];
			xto[0][i][j]=xto[0][i][j^lb]+go[i][p];
		}
	}
	for(int i=0; i<n; ++i){
		if(n<=12) continue;
		const int lim=1<<(n-12);
		for(int j=1; j<lim; ++j){
			int lb=j&-j,p=lg2[lb]+12;
			tox[1][i][j]=tox[1][i][j^lb]+go[p][i];
			xto[1][i][j]=xto[1][i][j^lb]+go[i][p];
		}
	}
	for(int i=1; i<1<<n; ++i){
		const int all=(1<<n)-1;
		cbit[i]=cbit[i^(i&-i)]+1;
		int res=1e9;
		for(int tmp=i,j=tmp&-tmp; tmp; tmp^=j,j=tmp&-tmp){
			int p=lg2[j];
			int x_to=get(xto,p,i)*q-get(xto,p,all^i);
			int to_x=get(tox,p,i)+get(tox,p,all^i)*q;
			apn(res,dp[i^j]+(to_x+x_to)*cbit[i]);
		}
		dp[i]=res;
	}
	printf("%d\n",dp[(1<<n)-1]);
	return 0;
}
