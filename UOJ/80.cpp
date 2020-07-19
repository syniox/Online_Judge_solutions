#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=405;
int n,mp[N][N],lnk1[N],lnk2[N],lab1[N],lab2[N],slack[N];

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

void zg(int x){
	static int from[N];
	static bool vis[N];
	memset(slack,127,(n+1)*sizeof(slack[0]));
	memset(vis,0,(n+1)*sizeof(vis[0]));
	vis[0]=1;
	int npos=0;
	do{
		npos=0;
		for(int i=1; i<=n; ++i){
			if(vis[i]) continue;
			if(slack[i]>lab1[x]+lab2[i]-mp[x][i]){
				slack[i]=lab1[x]+lab2[i]-mp[x][i];
				from[i]=x;
			}
			if(slack[i]<slack[npos]) npos=i;
		}
		const int nslack=slack[npos];
		for(int i=1; i<=n; ++i){
			if(vis[lnk1[i]]) lab1[i]-=nslack;
		}
		for(int i=1; i<=n; ++i){
			if(vis[i]){
				lab2[i]+=nslack;
			}else{
				slack[i]-=nslack;
			}
		}
		vis[npos]=1;
		x=lnk2[npos];
	}while(x);
	for(int i=npos; i; ){
		int fr=from[i],lk=lnk1[fr];
		lnk1[fr]=i;
		lnk2[i]=fr;
		i=lk;
	}
}

int main(){
	int nl=nxi(),nr=nxi();
	n=max(nl,nr);
	for(int i=nxi(); i; --i){
		const int a=nxi(),b=nxi();
		mp[a][b]=nxi();
	}
	for(int i=1; i<=nl; ++i){
		for(int j=1; j<=nr; ++j){
			apx(lab1[i],mp[i][j]);
		}
	}
	for(int i=1; i<=n; ++i){
		zg(i);
	}
	lint ans=0;
	for(int i=1; i<=nl; ++i){
		ans+=mp[i][lnk1[i]];
	}
	printf("%lld\n",ans);
	for(int i=1; i<=nl; ++i){
		printf("%d ",mp[i][lnk1[i]]?lnk1[i]:0);
	}
	puts("");
	return 0;
}
