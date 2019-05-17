#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=12;
int n,val[N][N],stat[N],len[N],turn_p[N][N];
int dp[1<<10][N][N];

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}

	template <class T>
		inline void apx(T &x,const T y){
			x<y?x=y:0;
		}

	template <class T>
		inline void apn(T &x,const T y){
			x>y?x=y:0;
		}
}
using namespace utils;

void get_turn(const int x){
	static int tr[N][N],cur[N];
	memset(cur,0,sizeof(cur));
	for(int i=1; i<=len[x]+1; ++i){
		memcpy(tr[i],cur,sizeof(cur));
		cur[val[x][i]]=i;
	}
	for(int i=1; i<=n; ++i){
		int p=len[x]+1,j=len[i];
		for(; j&&p; ){
			int nxt=tr[p][val[i][j]];
			if(!nxt) break;
			p=nxt,--j;
		}
		turn_p[i][x]=j+1;
	}
}

int solve(){
	for(int i=1; i<=n; ++i){
		dp[1<<(i-1)][i][0]=1;
	}
	for(int t=0; t<60; ++t){
		for(int i=1; i<1<<n; ++i){
			for(int j=1; j<=n; ++j){
				if((i>>(j-1)&1)==0) continue;
				for(int k=1; k<=n; ++k){
					if((stat[j]|stat[k])!=stat[j]) continue;
					if((i>>(k-1)&1)) continue;
					bool flag=0;
					for(int l=turn_p[j][k]-1; !flag&&l<=len[j]; ++l){
						flag|=dp[i][j][l];
					}
					dp[i|1<<(k-1)][k][0]|=flag;
				}
			}
		}
		for(int i=1; i<=n; ++i){
			if(dp[(1<<n)-1][i][len[i]]) return t;
		}
		for(int i=1; i<1<<n; ++i){
			for(int j=1; j<=n; ++j){
				if((i>>(j-1)&1)==0) continue;
				for(int k=len[j]-1; ~k; --k){
					dp[i][j][k+1]|=dp[i][j][k];
				}
			}
		}
	}
	return -1;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		int j=1;
		for(int k=nxi(); k; ++j,k=nxi()){
			val[i][j]=k;
			stat[i]|=1<<(k-1);
		}
		len[i]=j-1;
	}
	for(int i=1; i<=n; ++i){
		get_turn(i);
	}
	int res=solve();
	printf("%d\n",res);
	return 0;
}
