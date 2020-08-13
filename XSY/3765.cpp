#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=5005,K=21;
const int mod=998244353;
int n,q,dp[N][K][K],fp[N][K][K];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

namespace G{
	int fa[N],ch[N][2];
	bool dep[N];

	inline void add(const int a,const int b){
		if(ch[a][0]) ch[a][1]=b;
		else ch[a][0]=b;
	}

	void zy(const int x,const int i,const int j,const int pw,const int pl,const bool d){
		//d==1时bob（后的）选，d==0时alice（前的）选
		//pw: 重儿子,pl: 轻儿子
		int wgt=d?fp[pl][q][j]:fp[pl][i][q];
		dp[x][i][j]=(dp[x][i][j]+(lint)dp[pw][i][j]*wgt)%mod;
		fp[x][i][j]=(fp[x][i][j]+(lint)fp[pw][i][j]*wgt)%mod;
	}

	void dfs(const int x){
		if(!ch[x][0]){
			for(int i=1; i<=q; ++i){
				for(int j=1; j<=q; ++j){
					dp[x][i][j]=1;
					fp[x][i][j]=i*j;
				}
			}
			return;
		}
		dep[ch[x][0]]=dep[x]^1;
		dep[ch[x][1]]=dep[x]^1;
		dfs(ch[x][0]);
		dfs(ch[x][1]);
		for(int i=1; i<=q; ++i){
			for(int j=1; j<=q; ++j){
				for(int k=0; k<2; ++k){
					int pw=ch[x][k],pl=ch[x][k^1];
					zy(x,i,j,pw,pl,dep[x]);
				}
			}
		}
	}
}

int main(){
	n=ni,q=ni;
	for(int i=2; i<=n; ++i){
		G::fa[i]=(int)ni+1;
		G::add(G::fa[i],i);
	}
	G::dfs(1);
	int ans=0;
	for(int i=1; i<=q; ++i){
		for(int j=1; j<=q; ++j){
			ans=(ans+dp[1][i][j])%mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
