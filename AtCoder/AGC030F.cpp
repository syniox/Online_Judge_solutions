#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=305;
const int mod=1e9+7;
int n,fac[N<<1],dp[2][N][N],val[N<<1];
bool used[N<<1],disable[N<<1];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

inline void init(){
	fac[0]=1;
	for(int i=1; i<N; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
}

int main(){
	int cnt_free=0,cnt_used=0;
	init();
	n=nxi();
	for(int i=1; i<=n<<1; ++i){
		val[i]=nxi();
		if((i&1)==0){
			if(val[i]!=-1&&val[i-1]!=-1){
				disable[val[i]]=disable[val[i-1]]=1;
			}
			else if(val[i]==-1&&val[i-1]==-1){
				++cnt_free;
			}
			else{
				++cnt_used;
				used[val[i-(val[i]==-1)]]=1;
			}
		}
	}
	dp[0][0][0]=1;
	int cur=1;
	for(int i=n<<1; i; --i){
		if(disable[i]) continue;
		cur^=1;
		memset(dp[cur^1],0,sizeof(dp[cur^1]));
		for(int j=0; j<=n; ++j){
			for(int k=0; k<=cnt_used; ++k){
				const int tmp=dp[cur][j][k];
				if(tmp==0) continue;
				if(used[i]==1){
					//变成特殊待匹配位置
					dp[cur^1][j][k+1]=(dp[cur^1][j][k+1]+tmp)%mod;
					//拉一个普通待匹配位置过来匹配掉
					if(j) dp[cur^1][j-1][k]=(dp[cur^1][j-1][k]+tmp)%mod;
				}
				else{
					//变成待匹配位置
					dp[cur^1][j+1][k]=(dp[cur^1][j+1][k]+tmp)%mod;
					//匹配一个特殊待匹配位置
					if(k) dp[cur^1][j][k-1]=(dp[cur^1][j][k-1]+(lint)tmp*k)%mod;
					//匹配一个普通待匹配位置
					if(j) dp[cur^1][j-1][k]=(dp[cur^1][j-1][k]+tmp)%mod;
				}
			}
		}
	}
	printf("%lld\n",(lint)dp[cur^1][0][0]*fac[cnt_free]%mod);
	return 0;
}
