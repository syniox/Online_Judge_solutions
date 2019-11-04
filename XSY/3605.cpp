#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=10005;
int n,val[N],dis[N*2];

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

void dij(){
	static bool vis[N*2];
	memset(dis,127,sizeof(dis));
	dis[0]=0;
	for(int i=0; i<val[1]; ++i){
		int x=0;
		for(int j=0; j<val[1]; ++j){
			if(!vis[j]&&((x==0&&i)||dis[j]<dis[x])) x=j;
		}
		vis[x]=1;
		for(int j=2; j<=n; ++j){
			apn(dis[(x+val[j])%val[1]],dis[x]+val[j]);
		}
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	dij();
	for(int q=nxi(); q; --q){
		int p=nxi();
		puts(dis[p%val[1]]<=p?"Acesrc!":"Acesrc?");
	}
	return 0;
}
