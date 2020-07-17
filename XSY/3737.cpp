#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <map>
using namespace std;
typedef long long lint;
const int N=1e5+5;
int n,idx[N];
lint req[N];
map<lint,int> qf;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline bool cmp_req(const int a,const int b){
	return req[a]<req[b];
}

namespace G{
	int cnt(1),fir[N],sz[N],sz_e[N<<1];//清除sz_e
	lint dlen[N<<1],res[N];
	struct edge{
		int to,nx;
	}eg[N<<1];//偶数边为正边

	inline void add(const int a,const int b){
		//eprintf("add: %d->%d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	void dfs1(const int x,const int e){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(i&1) continue;
			dfs1(y,i);
			dlen[e]+=dlen[i]+sz[y];
		}
		sz_e[e]=sz[x];
		sz_e[e^1]=n-sz[x];
	}
	void dfs2(const int x,const int e){
		lint dsum=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			dsum+=dlen[i]+sz_e[i];
		}
		res[x]=dsum;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i&1) assert(dlen[i^1]==dsum-dlen[i]-sz_e[i]);
			dlen[i^1]=dsum-dlen[i]-sz_e[i];
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(!(i&1)) dfs2(eg[i].to,i);
		}
	}

	bool solve(){
		for(int i=n,x=idx[i]; i>1; x=idx[--i]){
			lint reqf=req[x]+2*++sz[x]-n;
			map<lint,int>::iterator it=qf.find(reqf);
			if(it==qf.end()) return 0;
			add(it->second,x);
			sz[it->second]+=sz[x];
		}
		dfs1(idx[1],0);
		dfs2(idx[1],0);
		for(int i=1; i<=n; ++i){
			if(res[i]!=req[i]) return 0;
		}
		for(int i=1; i<=n; ++i){
			for(int j=fir[i]; j; j=eg[j].nx){
				if((j&1)==0) printf("%d %d\n",i,eg[j].to);
			}
		}
		return 1;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		qf[req[i]=nxi()]=idx[i]=i;
	}
	sort(idx+1,idx+n+1,cmp_req);
	if(!G::solve()) puts("-1");
	return 0;
}
