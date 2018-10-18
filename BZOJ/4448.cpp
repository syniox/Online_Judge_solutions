#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=2e5+5;
int n,q,chn_tick,ask_tick,chn[N],chn_t[N],ans_l[N],ans_d[N];
bool vis[N];
struct query{
	int x,y,t,id;
	bool operator < (const query &b) const {
		return t<b.t;
	}
}qry[N];

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

namespace BIT{
	int tr[N];
	inline void mod(int x){
		for(;x<=n;x+=x&-x) ++tr[x];
	}
	inline int ask(int x){
		int ans=0;
		for(;x;x-=x&-x) ans+=tr[x];
		return ans;
	}
	inline int ask_t(const int x,const int y){
		return ask(y)-ask(x-1);
	}
}

namespace G{
	int rt,cnd,cnt,fa[N],sz[N],dfn[N],son[N],dep[N],fir[N],top[N];
	struct edge{
		int to,nx;
	}eg[N];
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void dfs1(const int x){
		sz[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			dep[y]=dep[x]+1;
			dfs1(y);
			if(sz[son[x]]<sz[y]) son[x]=y;
			sz[x]+=sz[y];
		}
	}
	void dfs2(const int x){
		dfn[x]=++cnd;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs2(son[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) dfs2(y);
		}
	}
	inline void get_ans(const int t){
		int x=qry[t].x,y=qry[t].y,ans=0,len=0;
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
			len+=dep[x]-dep[top[x]]+1;
			ans+=BIT::ask_t(dfn[top[x]],dfn[x]);
			x=fa[top[x]];
		}
		if(dep[x]<dep[y]) std::swap(x,y);
		ans_l[qry[t].id]=len+dep[x]-dep[y]+1;
		ans_d[qry[t].id]=ans+BIT::ask_t(dfn[y],dfn[x]);
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		using G::fa;
		fa[i]=nxi();
		if(fa[i]) G::add(fa[i],i);
		else G::rt=i;
	}
	G::dfs1(G::rt);
	G::dfs2(G::rt);
	q=nxi();
	for(int i=1;i<=q;++i){
		const int op=nxi();
		if(op==1){
			const int x=nxi(),y=nxi(),c=nxi();
			++ask_tick;
			qry[ask_tick]=(query){x,y,i-c,ask_tick};
		}
		else{
			chn[++chn_tick]=nxi();
			chn_t[chn_tick]=i;
		}
	}
	std::sort(qry+1,qry+ask_tick+1);
	for(int i=1,j=1;i<=ask_tick;++i){
		for(;j<=chn_tick&&chn_t[j]<qry[i].t;++j){
			if(!vis[chn[j]]){
				BIT::mod(G::dfn[chn[j]]);
				vis[chn[j]]=1;
			}
		}
		G::get_ans(i);
	}
	for(int i=1;i<=ask_tick;++i){
		printf("%d %d\n",ans_l[i],ans_d[i]);
	}
	return 0;
}
