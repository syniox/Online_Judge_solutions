#include<iostream>
#include<cstdio>
#include<cstring>
const int N=3002;
int n;

inline char gtc(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int fir[N],son[N],sz[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(int a,int b){
		static int cnt;
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
}
namespace T{
	struct node{
		//hex sum_hx size father child
		int hx,sx,sz,ans,fa,c[2];
		bool rev;
	}tr[N];
	inline void upd(int k){
		tr[k].sz=tr[tr[k].c[0]].sz+tr[tr[k].c[1]].sz+1;
	}
	inline bool side(int k){
		return tr[tr[k].fa].c[1]==k;
	}
	inline bool isrt(int k){
		return tr[tr[k].fa].c[0]!=k&&tr[tr[k].fa].c[1]!=k;
	}
	void getrev(int x){
		if(tr[x].fa) getrev(tr[x].fa);
		if(tr[x].rev){
			std::swap(tr[x].c[0],tr[x].c[1]);
			tr[tr[x].c[0]].rev^=1;
			tr[tr[x].c[1]].rev^=1;
			tr[x].rev=0;
		}
	}
	inline void rot(int x){
		int f=tr[k].fa,ff=tr[f].fa;
		bool k=side(x);
		int &p=tr[x].c[k^1];
		if(!isrt(f)) tr[ff].c[side(f)]=x;
		tr[x].fa=ff;
		tr[f].fa=x;
		tr[f].c[k]=p;
		if(p) tr[p].fa=f;
		p=f;
		upd(f);
		upd(x);
	}
	inline void splay(int x){
		getrev(x);
		while(!isrt(x)){
			int f=tr[x].fa;
			if(!isrt(f)){
				rot(side(x)==side(f)?f:x);
			}
			rot(x);
		}
	}
	inline int get_rt(int x){
		splay(x);
		while(tr[x].fa){
			x=tr[x].fa;
			splay(x);
		}
		while(tr[x].c[0]) x=tr[x].c[0];
		return x;
	}
	inline void acs(int x){
		int y=0;
		while(x){
			splay(x);
			tr[x].c[1]=y;
			upd(x);
			y=x;
			x=tr[x].fa;
		}
	}
	inline void mrt(int x){
		acs(x);
		tr[x].rev^=1;
	}
}

void dfs1(int x){
	using namespace G;
	sz[x]=1;
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(!sz[y]){
			sz[y]=1;
			init(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}
}

void dfs2(int x){
	T::tr[x].sz=1;
	using namespace G;
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(!T::tr[y].sz){
			dfs(y);
			if(y==son[x]){
				tr[x].c[1]=y;
				T::upd(x);
			}
		}
	}
}

int main(){
	n=nxi();
	int m=nxi();
	for(int i=1;i<=n;++i){
		tr[i].hx=nxi();
	}
	for(int i=1;i<n;++i){
		int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	dfs1(1);
	dfs2(1);
	while(m--){
		int d,op=nxi(),x=nxi(),y=nxi();
		switch(op){
			case 1:
				if(get_rt(x)==get_rt(y)){
					T::mrt(x);
					T::acs(y);
					T::splay(y);
					if(tr[x].fa==y){
						tr[x].fa=0;
						tr[y].c[0]=0;
						upd(y);
					}
				}
				break;
			case 2:
				if(get_rt(x)!=get_rt(y)){
					mrt(y);
					tr[y].fa=x;
				}
				break;
			case 3:
				d=nxi();
				if(get_rt(x)==get_rt(y)){

				}
				break;
			case 4:

				break;
		}
	}
}
