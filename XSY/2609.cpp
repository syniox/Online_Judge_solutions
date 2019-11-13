#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005;
int n,m,q,s,sz[26][N][N];
lint sum[26][N][N],ans[27][N][N];
char mp[N][N];
struct data{
	int x1,y1,x2,y2;
	char c;
}dt[(int)3e5+5];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline lint get_res(const int x,const int y,const int c){
	lint up=sum[25][x][y]-sum[c][x][y]-c*(sz[25][x][y]-sz[c][x][y]);
	lint dn=c?c*sz[c-1][x][y]-sum[c-1][x][y]:0;
	return up+dn;
}

template <class T> void do_psum(T v,const int t){
	for(int i=0; i<t; ++i){
		for(int j=1; j<=n; ++j){
			for(int k=1; k<=m; ++k){
				v[i][j][k]+=v[i][j][k-1];
			}
		}
		for(int j=1; j<=n; ++j){
			for(int k=1; k<=m; ++k){
				v[i][j][k]+=v[i][j-1][k];
			}
		}
	}
}

void get_utils(){
	do_psum(sz,26);
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			int c=mp[i][j]-'a',others=0;
			for(int k=0; k<26; ++k){
				if(k!=c) others+=sz[k][i][j];
			}
			sz[c][i][j]=q-others;
			for(int k=1; k<26; ++k){
				sum[k][i][j]=sum[k-1][i][j]+(lint)sz[k][i][j]*k;
				sz[k][i][j]+=sz[k-1][i][j];
			}
		}
	}
}

void build_ans(){
	for(int i=0; i<26; ++i){
		for(int j=1; j<=n; ++j){
			for(int k=1; k<=m; ++k){
				ans[i][j][k]=get_res(j,k,i);
			}
		}
	}
	for(int j=1; j<=n; ++j){
		for(int k=1; k<=m; ++k){
			ans[26][j][k]=get_res(j,k,mp[j][k]-'a');
		}
	}
	do_psum(ans,27);
}

inline lint getsum(const lint v[N][N],int x1,int y1,int x2,int y2){
	return v[x2][y2]-v[x1-1][y2]-v[x2][y1-1]+v[x1-1][y1-1];
}

int main(){
	n=nxi(),m=nxi(),q=nxi(),s=nxi();
	for(int i=1; i<=n; ++i){
		scanf("%s",mp[i]+1);
	}
	for(int i=1; i<=q; ++i){
		int x1=nxi(),y1=nxi(),x2=nxi(),y2=nxi();
		char c;
		while((c=getchar())>'z'||c<'a');
		dt[i]=(data){x1,y1,x2,y2,c};
		int p=c-'a';
		++sz[p][x1][y1],++sz[p][x2+1][y2+1];
		--sz[p][x1][y2+1],--sz[p][x2+1][y1];
	}
	get_utils();
	build_ans();
	lint nans=1e16;
	int id=0;
	for(int i=1; i<=q; ++i){
		lint cans=ans[26][n][m];
		cans-=getsum(ans[26],dt[i].x1,dt[i].y1,dt[i].x2,dt[i].y2);
		cans+=getsum(ans[dt[i].c-'a'],dt[i].x1,dt[i].y1,dt[i].x2,dt[i].y2);
		if(cans<nans) nans=cans,id=i;
	}
	printf("%lld %d\n",nans,id);
	return 0;
}
