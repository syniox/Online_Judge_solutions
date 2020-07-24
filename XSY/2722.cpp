#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=1e6+5;
int n,val[N],dgr[N];//出度-入度

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

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_dgr(const int x,const int fa){
		for(int i=fir[x]; i; i=eg[i].nx){
			if(eg[i].to!=fa) dfs_dgr(eg[i].to,x);
		}
		val[fa]-=val[x];
		int flow=val[x]*(x<fa?1:-1);
		dgr[x]+=flow;
		dgr[fa]-=flow;
	}
}

void oput_ans(){
	static int b1[N],b2[N];
	int c1=0,c2=0,sum=0;
	for(int i=1; i<=n; ++i){
		if(dgr[i]>0) b1[++c1]=i,sum+=dgr[i];
		if(dgr[i]<0) b2[++c2]=i;
	}
	sort(b1+1,b1+c1+1);
	sort(b2+1,b2+c2+1);
	printf("%d\n",sum);
	for(int i=1,j=1; i<=c1&&j<=c2; ){
		printf("%d %d\n",b1[i],b2[j]);
		if(!--dgr[b1[i]]) ++i;
		if(!++dgr[b2[j]]) ++j;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b),G::add(b,a);
	}
	G::dfs_dgr(1,0);
	oput_ans();
	return 0;
}
