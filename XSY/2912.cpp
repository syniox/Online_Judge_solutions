#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1005;
int n,m,fa[N];
class _Lim{
	public:
		int x,y;
		bool type;
}dt[N*10];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,disabled,ind[N],fir[N];
	int len,*buk;
	bool vis[N];
	class edge{
		public:
			int to,nx;
	}eg[N*20];

	inline void clear(){
		cnt=0;
		memset(ind,0,sizeof(ind));
		memset(fir,0,sizeof(fir));
		memset(vis,0,sizeof(vis));
	}

	inline void add(const int a,const int b){
		++ind[b];
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	void dfs(const int x){
		buk[len++]=x;
		vis[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=disabled&&!vis[y]) dfs(y);
		}
	}

	inline int get_list(const int disabled,int x,int *buk){
		len=0,G::buk=buk;
		G::disabled=disabled;
		dfs(x);
		return len;
	}
}

int dfs(int *pnt,int cpnt){
	static bool inq[N],mrk[N];
	static int buk[N];
	int clist=0,len[N],*list[N];
	memset(inq,0,sizeof(inq));
	memset(mrk,0,sizeof(mrk));
	for(int i=0; i<cpnt; ++i){
		inq[pnt[i]]=1;
	}
	G::clear();
	for(int i=1; i<=m; ++i){
		if(inq[dt[i].x]&&inq[dt[i].y]){
			if(dt[i].type==0) G::add(dt[i].x,dt[i].y);
			else ++G::ind[dt[i].x];
		}
	}
	int rt=0;
	for(int i=0; !rt&&i<cpnt; ++i){
		if(!G::ind[pnt[i]]) rt=pnt[i];
	}
	assert(rt);
	mrk[rt]=1;
	for(int i=1; i<=n; ++i){
		if(!mrk[i]&&inq[i]){
			len[clist]=G::get_list(rt,i,buk);
			for(int i=0; i<len[clist]; ++i){
				mrk[buk[i]]=1;
			}
			list[clist]=new int[len[clist]];
			memcpy(list[clist],buk,len[clist]*sizeof(int));
			++clist;
		}
	}
	for(int i=0; i<clist; ++i){
		fa[dfs(list[i],len[i])]=rt;
		//delete[] list[i];
	}
	return rt;
}

inline void solve(){
	static int pnt[N];
	for(int i=1; i<=n; ++i){
		pnt[i-1]=i;
	}
	dfs(pnt,n);
}

int main(){
	n=nxi();
	int lim1=nxi(),lim2=nxi();
	m=lim1+lim2;
	for(int i=1; i<=m; ++i){
		dt[i].x=nxi(),dt[i].y=nxi();
		dt[i].type=i>lim1;
	}
	solve();
	for(int i=1; i<=n; ++i){
		printf("%d ",fa[i]);
	}
	puts("");
	return 0;
}
