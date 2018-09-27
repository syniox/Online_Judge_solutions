#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
int n,m,cm,dp[N],col[N],mrk[N],endp1[N],endp2[N];

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

namespace G{
	int cnd,cnt,sz[N],fa[N],idx[N],dfn[N],dep[N],fir[N],son[N],top[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void dfs1(const int x){
		sz[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!sz[y]){
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs1(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}
	void dfs2(const int x){
		dfn[x]=++cnd;
		idx[cnd]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs2(son[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) dfs2(y);
		}
	}
	void dfs_mrk(const int x){
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa[x]){
				dfs_mrk(y);
				mrk[x]+=mrk[y];
			}
		}
	}
	void dfs_dp(const int x){
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(fa[x]!=y){
				dp[y]=dp[x]+cm-mrk[y];
				dfs_dp(y);
			}
		}
	}
	inline int get_lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}
	inline int jmp(int x,int t){
		if(dep[x]<t) return 0;
		while(dep[x]-dep[top[x]]<t){
			t-=dep[x]-dep[top[x]]+1;
			x=fa[top[x]];
		}
		return idx[dfn[x]-t];
	}
	inline int get_dis(const int x,const int y){
		if(!(x&&y)) return 0;
		return dep[x]+dep[y]-(dep[get_lca(x,y)]<<1);
	}
	inline void get_mid(const int x,const int y,int &a,int &b){
		const int z=get_lca(x,y),dis=dep[x]+dep[y]-(dep[z]<<1);
		if(dis&1){
			a=jmp(x,dis>>1);
			b=jmp(y,dis>>1);
			if(!a||dep[a]<dep[z]) a=fa[b];
			if(!b||dep[b]<dep[z]) b=fa[a];
		}
		else{
			a=b=dep[x]-dep[z]>=dis>>1?jmp(x,dis>>1):jmp(y,dis>>1);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		col[i]=nxi();
	}
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs1(1);
	G::dfs2(1);
	for(int i=1;i<=n;++i){
		const int cur=col[i];
		if(!endp1[cur]) endp1[cur]=i;
		else if(!endp2[cur]) endp2[cur]=i;
		else{
			const int x=endp1[cur],y=endp2[cur];
			const int fc=G::get_dis(x,y);
			const int fb=G::get_dis(x,i);
			const int fa=G::get_dis(y,i);
			if(fc>fa&&fc>fb) continue;
			endp1[cur]=i;
			endp2[cur]=fa<fb?x:y;
		}
	}
	for(int i=1;i<=m;++i){
		int x,y,tp=0;
		if(endp1[i]){
			++cm;
			tp=G::get_dis(1,endp1[i]);
			if(endp2[i]){
				G::get_mid(endp1[i],endp2[i],x,y);
				++mrk[x];
				++mrk[y];
				apx(tp,G::get_dis(1,endp2[i]));
			}
			else mrk[endp1[i]]+=2;
		}
		dp[1]+=tp;
	}
	G::dfs_mrk(1);
	G::dfs_dp(1);
	for(int i=1;i<=n;++i){
		printf("%d\n",dp[i]);
	}
	return 0;
}
