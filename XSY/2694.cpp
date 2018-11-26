#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
const int N=1e5+5,P=1e7+5,S=3200;
int T,n,cnp,prm[S];

int gcd(const int x,const int y){
	return y?gcd(y,x%y):x;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void xswp(T &x,T &y){
	if(x<y) std::swap(x,y);
}

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
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

inline void init_npr(){
	static bool npr[S];
	for(int i=2;i<S;++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1;j<=cnp&&i*prm[j]<S;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

namespace G{
	int cnt,x_chunk,sz_chunk,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<6];

	inline void add(const int a,const int b){
//		printf("add: %d %d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	namespace G1{
		int cnf,sz[N],bel[N];
		bool vis[N];
		inline void init(){
			cnf=0;
			memset(vis,0,sizeof(vis));
			memset(sz,0,sizeof(sz));
		}
		inline void dfs(const int x){
			bel[x]=cnf;
			++sz[cnf];
			vis[x]=1;
			for(int i=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to;
				if(!vis[y]) dfs(y);
			}
		}
	}

	namespace G2{
		int rt,cnd,sz[N],xsz[N],bel[N],dfn[N],low[N];
		inline void init(){
			cnd=rt=0;
			memset(sz,0,sizeof(sz));
			memset(dfn,0,sizeof(dfn));
			memset(xsz,0,sizeof(xsz));
		}
		void tarjan(const int x){
			low[x]=dfn[x]=++cnd;
			sz[x]=1;
			int del_size=0;
			for(int i=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to;
				if(!dfn[y]){
					tarjan(y);
					if(low[y]<dfn[x]) apn(low[x],low[y]);
					else{
						apx(xsz[x],sz[y]);
						del_size+=sz[y];
					}
					sz[x]+=sz[y];
				}
				else apn(low[x],dfn[y]);
			}
			apx(xsz[x],sz_chunk-del_size-1);
		}
	}

	inline void init(){
		cnt=sz_chunk=0;
		memset(fir,0,sizeof(fir));
		G1::init();
		G2::init();
	}

	inline void get_rt(){
		for(int i=1;!G2::rt&&i<=n;++i){
			if(G1::bel[i]==x_chunk) G2::rt=i;
		}
	}

	inline void get_x_chunk(){
		for(int i=1;i<=n;++i){
			if(!G1::vis[i]) ++G1::cnf,G1::dfs(i);
		}
		for(int i=1;i<=G1::cnf;++i){
			if(sz_chunk<G1::sz[i]){
				x_chunk=i,sz_chunk=G1::sz[i];
			}
		}
	}

	inline int get_ans(){
		G2::tarjan(G2::rt);
		int ans=sz_chunk-1;
		for(int i=1;i<=n;++i){
			if(G2::xsz[i]) apn(ans,G2::xsz[i]);
		}
		int sz1=0,sz2=0;
		for(int i=1;i<=G1::cnf;++i){
			int tp=G1::sz[i];
			xswp(sz1,tp);
			xswp(sz2,tp);
		}
		return std::max(ans,sz2);
	}
}

inline void calc(const int x,const int v){
	static std::vector <int> buk[P];
	static int que[N],tick[P];
	int top=0,tp=v;
	for(int i=1;i<=cnp;++i){
		if(tp%prm[i]==0){
			que[++top]=prm[i];
			tp/=prm[i];
			if(tp%prm[i]==0) que[++top]=prm[i];
			while(tp%prm[i]==0) tp/=prm[i];
		}
	}
	if(tp>1) que[++top]=tp;
	for(int i=1;i<top;++i){
		if(que[i]==que[i-1]) continue;
		for(int j=i+1;j<=top;++j){
			if(j<top&&que[j]==que[j+1]) continue;
			int k=que[i]*que[j];
			if(tick[k]!=T) tick[k]=T,buk[k].clear();
			int sz=buk[k].size();
			if(sz>0) G::add(buk[k][0],x);
			if(sz>1) G::add(buk[k][sz-1],x);
			buk[k].push_back(x);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("d.in","r",stdin);
#endif
	init_npr();
	T=nxi();
	while(T--){
		G::init();
		n=nxi();
		for(int i=1;i<=n;++i) calc(i,nxi());
		G::get_x_chunk();
		G::get_rt();
		printf("%d\n",G::get_ans());
	}
	return 0;
}
