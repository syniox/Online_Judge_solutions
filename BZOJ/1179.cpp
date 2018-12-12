#include <iostream>
#include <cstdio>
#include <cstring>
const int N=5e5+5;
int n,m,hx[N];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

class Graph{
	protected:
		int cnt;
	public:
		int fir[N];
		struct edge{
			int to,nx;
		}eg[N<<1];
		inline void add(const int a,const int b){
			eg[++cnt]=(edge){b,fir[a]};
			fir[a]=cnt;
		}
};

class ORG_G:public Graph{
	public:
		bool vis[N];
		int cnf,bel[N];

		void tarjan(const int x){
			static int cnd,top,stk[N],dfn[N],low[N];
			stk[++top]=x;
			dfn[x]=low[x]=++cnd;
			for(int i=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to;
				if(!dfn[y]){
					tarjan(y);
					apn(low[x],low[y]);
				}
				else if(!vis[y]){
					apn(low[x],dfn[y]);
				}
			}
			if(dfn[x]==low[x]){
				++cnf;
				for(int i=stk[top--];;i=stk[top--]){
					bel[i]=cnf;
					vis[i]=1;
					if(i==x) break;
				}
			}
		}
}OG;

class NEW_G:public Graph{
	public:
		bool get[N],des[N];
		int sval[N];
}NG;

inline void build(){
	for(int i=1;i<=n;++i){
		NG.sval[OG.bel[i]]+=hx[i];
		for(int j=OG.fir[i];j;j=OG.eg[j].nx){
			const int k=OG.eg[j].to;
			if(OG.bel[i]!=OG.bel[k]){
				NG.add(OG.bel[i],OG.bel[k]);
			}
		}
	}
	NG.get[OG.bel[nxi()]]=1;
	for(int i=OG.cnf;i;--i){
		if(!NG.get[i]) continue;
		for(int j=NG.fir[i];j;j=NG.eg[j].nx){
			NG.get[NG.eg[j].to]=1;
		}
	}
	for(int p=nxi();p;--p){
		NG.des[OG.bel[nxi()]]=1;
	}
}

inline int get_ans(){
	int ans=0;
	for(int i=1;i<=OG.cnf;++i){
		if(!NG.get[i]) continue;
		int temp=0;
		for(int j=NG.fir[i];j;j=NG.eg[j].nx){
			const int k=NG.eg[j].to;
			if(!NG.des[k]) continue;
			NG.des[i]=1;
			apx(temp,NG.sval[k]);
		}
		NG.sval[i]+=temp;
		if(NG.des[i]){
			apx(ans,NG.sval[i]);
		}
	}
	return ans;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int x=nxi(),y=nxi();
		OG.add(x,y);
	}
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	for(int i=1;i<=n;++i){
		if(!OG.vis[i]) OG.tarjan(i);
	}
	build();
	printf("%d\n",get_ans());
	return 0;
}
