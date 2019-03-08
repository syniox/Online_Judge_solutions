#include <iostream>
#include <cstdio>
#include <cstring>
const int N=3e5+5;
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],col_tr[N],col_other[N];
	int top,stk[N];
	bool vis[N],vis_pt[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void init(){
		cnt=1;
		memset(col_other,-1,(n+1)*sizeof(int));
	}

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_tr(const int x){
		vis_pt[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(vis_pt[y]) continue;
			vis[i>>1]=1;
			col_tr[eg[i].to]=col_tr[x]^1;
			dfs_tr(eg[i].to);
		}
	}

	bool paint(const int x){
		stk[++top]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(vis[i>>1]) continue;
			const int y=eg[i].to;
			if(col_other[y]!=-1){
				if(col_other[y]==col_other[x]){
					stk[++top]=y;
					return 0;
				}
			}
			else{
				col_other[y]=col_other[x]^1;
				if(!paint(y)) return 0;
			}
		}
		--top;
		return 1;
	}

	void oput_stk(){
		int end=stk[top],st=top-1;
		for(; stk[st]!=end; --st);
		printf("B %d ",top-st);
		for(int i=st+1; i<=top; ++i){
			printf("%d ",stk[i]);
		}
		puts("");
	}
}

int main(){
	n=nxi(),m=nxi();
	G::init();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_tr(1);
	for(int i=1; i<=n; ++i){
		if(G::col_other[i]==-1){
			G::col_other[i]=0;
			if(!G::paint(i)){
				G::oput_stk();
				return 0;
			}
		}
	}
	printf("A ");
	for(int i=1; i<=n; ++i){
		printf("%d ",(G::col_tr[i]<<1|G::col_other[i])+1);
	}
	puts("");
	return 0;
}
