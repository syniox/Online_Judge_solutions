#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=40005;
int n,m,q,ans[N];
struct route{
	int a,b,w,id;
}rou[N],qry[N];

bool w_cmp(const route &x,const route &y){
	return x.w<y.w;
}

bool a_cmp(const route &x,const route &y){
	return x.a<y.a;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace B{
	int tick,tm[N],tr[N];
	inline void upd(const int x){
		if(tm[x]<tick) tm[x]=tick,tr[x]=0;
	}
	inline void mod(int x,const int v){
		for(;x<=n;x+=x&-x) upd(x),tr[x]+=v;
	}
	inline int ask(int x){
		int ans=0;
		for(;x;x-=x&-x) upd(x),ans+=tr[x];
		return ans;
	}
}

namespace G{
	int cnt,cnd,fa[N],sz[N],fir[N],idx[N],dep[N],son[N],dfn[N],top[N];
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
			if(fa[x]!=y){
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs1(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}

	void dfs2(const int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		dfn[x]=++cnd;
		idx[cnd]=x;
		if(son[x]){
			dfs2(son[x]);
			for(int i=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to;
				if(!top[y]) dfs2(y);
			}
		}
	}

	inline int jump(int x,int step){
		while(dep[x]-dep[top[x]]<step){
			step-=dep[x]-dep[top[x]]+1;
			x=fa[dep[x]];
		}
		return idx[dfn[x]-step];
	}
}

inline void get_route(route ru[],const int limit,const bool f){
	for(int i=1;i<=limit;++i){
		using G::dfn;
		int a=nxi(),b=nxi(),v=nxi();
		if(dfn[a]>dfn[b]) std::swap(a,b);
		if(f&&dfn[a]+G::sz[a]>dfn[b]){
			a=G::jump(b,G::dep[a]-G::dep[b]-1);
		}
		ru[i]=(route){a,b,v,i};
	}
	std::sort(ru+1,ru+m+1,f?w_cmp:a_cmp);
}

inline void build(int &top,route que[],const int x1,const int x2,const int y1,const int y2){
	if(x1>x2||y1>y2) return;
	que[++top]=(route){x1,y1,1,0};
	if(y2<n) que[++top]=(route){x1,y2+1,-1,0};
	if(x2<n) que[++top]=(route){x2+1,y1,-1,0};
	if(x2<n&&y2<n) que[++top]=(route){x2+1,y2+1,1,0};
}

void solve(const int rl,const int rr,const int ql,const int qr){
	static route tq[N],que[N<<2];
	if(rl==rr){
		for(int i=ql;i<=qr;++i) ans[qry[i].id]=rl;
		return;
	}
	const int mid=(rl+rr)>>1;
	int top=0,ptl=ql-1,ptr=qr+1;
	++B::tick;
	memcpy(tq+ql,qry+ql,(qr-ql+1)*sizeof(route));
	std::sort(tq+ql,tq+qr+1,a_cmp);
	for(int i=rl;i<=rr;++i){
		using G::dfn;
		const int a=rou[i].a,b=rou[i].b;
		if(dfn[a]+G::sz[a]>dfn[b]){
			build(top,que,1,dfn[a]-1,dfn[b],dfn[b]+G::sz[b]-1);
			build(top,que,dfn[a]+1,n,dfn[b],dfn[b]+G::sz[b]-1);
		}
		else{
			build(top,que,dfn[a],dfn[a]+G::sz[a]-1,dfn[b],dfn[b]+G::sz[b]-1);
		}
	}
	std::sort(que+1,que+top+1,a_cmp);
	for(int i=1,j=1,k=ql;i<=n;++i){
		for(;j<=top&&que[j].a<=i;++j){
			B::mod(que[j].b,que[j].w);
		}
		for(;k<=qr&&tq[k].a==i;++k){
			if(B::ask(tq[k].b)>=tq[k].w) qry[++ptl]=tq[k];
			else qry[--ptr]=tq[k];
		}
	}
	if(rl<=mid) solve(rl,mid,ql,ptl);
	if(rr>mid) solve(mid+1,rr,ptr,qr);
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs1(1);
	G::dfs2(1);
	get_route(rou,m,1);
	get_route(qry,q,0);
	solve(1,m,1,q);
	for(int i=1;i<=n;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
