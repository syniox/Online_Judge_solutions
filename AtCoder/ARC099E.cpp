#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <bitset>
typedef long long lint;
const int N=705;
int n,cnt[2],col[N];
bool mp[N][N];
std::bitset <N> bans;

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

bool dfs_col(const int x,const bool f){
	col[x]=f,++cnt[f];
	for(int i=1; i<=n; ++i){
		if(i!=x&&!mp[x][i]){
			if(col[i]==-1&&!dfs_col(i,col[x]^1)) return 0;
			else if(col[i]==col[x]) return 0;
		}
	}
	return 1;
}

int main(){
	n=nxi();
	memset(col+1,-1,n*sizeof(int));
	for(int i=nxi(); i; --i){
		int a=nxi(),b=nxi();
		mp[a][b]=mp[b][a]=1;
	}
	bans[0]=1;
	for(int i=1; i<=n; ++i){
		if(~col[i]) continue;
		cnt[0]=cnt[1]=0;
		if(!dfs_col(i,0)){
			return puts("-1"),0;
		}
		bans=bans<<cnt[0]|bans<<cnt[1];
	}
	int ans=1e9;
	for(int i=0; i<=n; ++i){
		if(bans[i]) apn(ans,(i*(i-1)+(n-i)*(n-i-1))>>1);
	}
	printf("%d\n",ans);
	return 0;
}
