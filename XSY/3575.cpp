#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=305;
int n,m,lik[N][N],pt[N],cnt[N];
bool used[N];

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

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			lik[i][j]=nxi();
		}
		pt[i]=1;
		++cnt[lik[i][1]];
	}
	int ans=n;
	for(int i=1; i<=m; ++i){
		int res=0;
		for(int j=1; j<=m; ++j){
			if(!used[j]) apx(res,cnt[j]);
		}
		apn(ans,res);
		if(i==m) break;
		int xp=1;
		for(int j=2; j<=m; ++j){
			if(!used[j]&&cnt[j]>cnt[xp]) xp=j;
		}
		used[xp]=1;
		for(int j=1; j<=n; ++j){
			--cnt[lik[j][pt[j]]];
			while(pt[j]<=m&&used[lik[j][pt[j]]]) ++pt[j];
			assert(pt[j]<=m);
			++cnt[lik[j][pt[j]]];
		}
	}
	printf("%d\n",ans);
	return 0;
}
