#include<iostream>
#include<cstdio>
#include<cstring>
const int N=2e5+2;
int n,q,fir[N],dp[N<<1],len[N<<1],endl[N<<1],endp1[N<<1],endp2[N<<1];
int sz[N],fa[N],son[N],dfn[N],idx[N],top[N],dep[N],e_to_f[N];
struct edge{
	int to,nx;
}eg[N<<1];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void xswp(T &x,T &fx,T &y,T &fy){
	if(x<y){
		std::swap(x,y);
		std::swap(fx,fy);
	}
}

inline void add(const int x,const int y){
	static int cnt=1;
	eg[++cnt]=(edge){y,fir[x]};
	fir[x]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
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
	static int cnd;
	dfn[x]=++cnd;
	idx[cnd]=x;
	top[x]=son[fa[x]]==x?top[fa[x]]:x;
	if(son[x]) dfs2(son[x]);
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(!top[y]) dfs2(y);
	}
}

//e: point to x
void dfs_down(const int x,const int e){
	endp1[e]=endp2[e]=endl[e]=x;
	for(int i=fir[x];i;i=eg[i].nx){
		if((i^1)==e) continue;
		const int y=eg[i].to;
		e_to_f[y]=i^1;
		dep[y]=dep[x]+1;
		dfs_down(y,i);
		if(dp[e]<dp[i]){
			dp[e]=dp[i];
			endp1[e]=endp1[i];
			endp2[e]=endp2[i];
		}
		const int v=len[e]+len[i]+1;
		if(dp[e]<v){
			dp[e]=v;
			endp1[e]=endl[e];
			endp2[e]=endl[i];
		}
		if(len[e]<len[i]+1){
			len[e]=len[i]+1;
			endl[e]=endl[i];
		}
	}
}

void dfs_up(const int x,const int e){
	int cson=0,nln[3]={0},ndp[2]={0};
	int frl[3]={0},frd[2]={0};
	for(int i=fir[x];i;i=eg[i].nx){
		++cson;
		int tp=len[i]+1,pt=i;
		xswp(nln[0],frl[0],tp,pt);
		xswp(nln[1],frl[1],tp,pt);
		xswp(nln[2],frl[2],tp,pt);
		tp=dp[i],pt=i;
		xswp(ndp[0],frd[0],tp,pt);
		xswp(ndp[1],frd[1],tp,pt);
	}
	for(int i=fir[x];i;i=eg[i].nx){
		const int p=i^1;
		if(p==e) continue;
		const int fr_l=frl[len[i]+1==nln[0]];
		len[p]=len[fr_l]+(fr_l!=0);
		endl[p]=fr_l?endl[fr_l]:x;
		const int fr_d=frd[dp[i]==ndp[0]];
		dp[p]=dp[fr_d];
		endp1[p]=fr_d?endp1[fr_d]:x;
		endp2[p]=fr_d?endp2[fr_d]:x;
		if(cson>2){
			int tp=nln[0]+nln[1],cur=len[i]+1;
			if(cur==nln[0]||cur==nln[1]) tp+=nln[2]-cur;
			if(tp>dp[p]){
				dp[p]=tp;
				endp1[p]=endl[frl[cur==nln[0]]];
				endp2[p]=endl[frl[1+((cur==nln[0])||(cur=nln[1]))]];
			}
		}
		else if(dp[p]<len[p]){
			dp[p]=len[p];
			endp1[p]=eg[p].to;
			endp2[p]=endl[p];
		}
		dfs_up(eg[i].to,i);
	}
}

inline int get_lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

inline int jmp(int x,int step){
	while(dep[x]-dep[top[x]]<step){
		step-=dep[x]-dep[top[x]]+1;
		x=fa[top[x]];
	}
	return idx[dfn[x]-step];
}

inline int get_dis(const int x,const int y){
	if(!(x&&y)) return 0;
	const int z=get_lca(x,y);
	return dep[x]+dep[y]-(dep[z]<<1);
}

inline bool run_able(const int x,const int y,const int z,const int lx,const int ly){
	const int dis=dep[x]+dep[y]-(dep[z]<<1);
	if(dis<=ly) return 0;
	const int cut=dep[y]-dep[z]>ly? e_to_f[jmp(y,ly)] : e_to_f[jmp(x,dis-ly-1)]^1;
	return std::max(get_dis(endp1[cut],x),get_dis(endp2[cut],x))>=lx;
}

inline int solve(const int x,const int y,const int step){
	int z=get_lca(x,y),dis=dep[x]+dep[y]-(dep[z]<<1);
	if((dis&1)^(step&1)) return step&1;
	if(dis&1) return run_able(y,x,z,step>>1,(step+1)>>1)?1:2;
	return run_able(x,y,z,(step+1)>>1,step>>1)?0:-1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1;i<n;++i){
		const int x=nxi(),y=nxi();
		add(x,y);
		add(y,x);
	}
	dfs1(1);
	dfs2(1);
	dfs_down(1,0);
	dp[0]=len[0]=endl[0]=endp1[0]=endp2[0]=0;
	dfs_up(1,0);
	while(q--){
		const int x=nxi(),y=nxi(),step=nxi();
		printf("%d\n",solve(x,y,step));
	}
	return 0;
}
