#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2005;
int n,min_mp,val[N],mp[N][N];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[200000];
	if(h==t){
		t=(h=buf)+fread(buf,1,200000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

inline void dij(){
	static bool vis[N];
	val[0]=2e9+5;
	for(int i=1; i<=n; ++i){
		int x=0;
		for(int j=1; j<=n; ++j){
			if(!vis[j]&&val[j]<val[x]) x=j;
		}
		vis[x]=1;
		for(int j=1; j<=n; ++j){
			apn(val[j],val[x]+mp[x][j]);
		}
	}
}

int main(){
	memset(val,127,sizeof(val));
	n=nxi();
	min_mp=1e9+5;
	for(int i=1; i<=n; ++i){
		for(int j=i+1; j<=n; ++j){
			mp[i][j]=mp[j][i]=nxi();
			apn(min_mp,mp[i][j]);
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			if(j!=i) apn(val[i],(mp[i][j]-=min_mp)<<1);
		}
	}
	dij();
	for(int i=1; i<=n; ++i){
		printf("%lld\n",val[i]+(lint)(n-1)*min_mp);
	}
	return 0;
}
