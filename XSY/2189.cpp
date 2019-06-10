#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
int n,ans[N],val[N],pos[N],dp[N][2];
//dp[x][0]: 最大子树 1: 含根

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void flip(int x){
	int lst=dp[x][1],cur=dp[x][1]+=2;
	apx(dp[x][0],cur);
	for(int f=x>>1; f; x=f,f=x>>1){
		int tmp=dp[f][1];
		if(cur>0){
			dp[f][1]+=cur-std::max(0,lst);
		}
		apx(dp[f][0],dp[f][1]);
		apx(dp[f][0],dp[x][0]);
		lst=tmp;
		cur=dp[f][1];
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		pos[val[i]]=i;
	}
	for(int i=1; i<=n; ++i){
		dp[i][0]=0;
		dp[i][1]=-1;
	}
	int lsta=-1;
	for(int i=n; i; --i){
		flip(pos[i]);
		int cura=dp[1][0]-1;
		for(int j=lsta+1; j<=cura; ++j){
			ans[j]=i;
		}
		lsta=cura;
	}
	for(int i=0; i<n; ++i){
		printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
