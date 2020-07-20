#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=1e5+5;
const int S=1500,B=N/S+5;
int n,m,bel[N],offs[B],blen[B];
struct data{
	int id,v;
	friend bool operator < (const data &a,const data &b){
		return a.v<b.v;
	}
}dt[B][S+5];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

namespace G{
	int cnt,dfn[N],sz[N],fir[N],dis[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs_dis(const int x,const int d){
		static int cnd;
		dfn[x]=++cnd;
		dis[dfn[x]]=d;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			assert(!sz[y]);
			dfs_dis(y,d+eg[i].wi);
			sz[x]+=sz[y];
		}
	}
}

void addv_B(const int p,const int l,const int r,const int v){
	static data p1[S+5],p2[S+5];
	const int len=min(p*S,n)-(p-1)*S;
	int c1=0,c2=0;
	for(int i=1; i<=len; ++i){
		const int id=dt[p][i].id;
		if(id>=l&&id<=r){
			p1[++c1]=(data){id,dt[p][i].v+v};
		}else{
			p2[++c2]=dt[p][i];
		}
	}
	merge(p1+1,p1+c1+1,p2+1,p2+c2+1,dt[p]+1);
}

void addv(const int l,const int r,const int v){
	if(bel[l]==bel[r]){
		addv_B(bel[l],l,r,v);
		return;
	}
	addv_B(bel[l],l,r,v);
	addv_B(bel[r],l,r,v);
	for(int i=bel[l]+1; i<bel[r]; ++i){
		offs[i]+=v;
	}
}

int qans(const int l,const int r,const int rk){
	static int buk[S*2+5];
	int cnt=0;
	if(bel[l]==bel[r]){
		const int p=bel[l];
		for(int i=1; i<=blen[p]; ++i){
			if(dt[p][i].id>=l&&dt[p][i].id<=r){
				buk[++cnt]=dt[p][i].v+offs[p];
			}
		}
	}else{
		int c1=0;
		for(int i=1; i<=blen[bel[l]]; ++i){
			if(dt[bel[l]][i].id>=l){
				buk[++c1]=dt[bel[l]][i].v+offs[bel[l]];
			}
		}
		cnt=c1;
		for(int i=1; i<=blen[bel[r]]; ++i){
			if(dt[bel[r]][i].id<=r){
				buk[++cnt]=dt[bel[r]][i].v+offs[bel[r]];
			}
		}
		inplace_merge(buk+1,buk+c1+1,buk+cnt+1);
	}
	//最小的数使得区间内小于等于其的个数>=rk
	int pl=0,pr=2e6,mid;
	while(pl!=pr){
		mid=(pl+pr)>>1;
		int res=upper_bound(buk+1,buk+cnt+1,mid)-buk-1;
		for(int i=bel[l]+1; i<bel[r]; ++i){
			res+=upper_bound(dt[i]+1,dt[i]+blen[i]+1,(data){0,mid-offs[i]})-dt[i]-1;
		}
		if(res>=rk) pr=mid;
		else pl=mid+1;
	}
	return pl;
}

int main(){
	n=nxi(),m=nxi(),nxi();
	for(int i=1; i<=n; ++i){
		bel[i]=(i-1)/S+1;
	}
	for(int i=2; i<=n; ++i){
		const int f=nxi(),v=nxi();
		G::add(f,i,v);
	}
	G::dfs_dis(1,0);
	for(int i=1; i<=bel[n]; ++i){
		int l=(i-1)*S+1,r=min(n,i*S),len=r-l+1;
		for(int j=1; j<=len; ++j){
			dt[i][j]=(data){l+j-1,G::dis[l+j-1]};
		}
		blen[i]=len;
		sort(dt[i]+1,dt[i]+len+1);
	}
	for(int i=1; i<=m; ++i){
		int op=nxi(),l=nxi(),r,v=nxi();
		r=G::dfn[l]+G::sz[l]-1;
		l=G::dfn[l];
		if(op==2){
			addv(l,r,v);
		}else{
			if(v>r-l+1) puts("-1");
			else printf("%d\n",qans(l,r,v));
		}
	}
	return 0;
}
