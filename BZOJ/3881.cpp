#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=1e5+5;
char ch[N*20];
int n,q,dfn[N*20],endp[N*20];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

bool cmp_dfn(const int x,const int y){
	return dfn[x]<dfn[y];
}

namespace BIT{
	int tr[N*20];
	inline void mod(int x,const int v){
		for(;x<N*20;x+=x&-x) tr[x]+=v;
	}
	inline int ask(int x){
		int ans=0;
		for(;x;x-=x&-x) ans+=tr[x];
		return ans;
	}
	inline int ask(const int x,const int y){
		return ask(y)-ask(x-1);
	}
}

namespace T{
	int cnt,cnd,fa[N*20],sz[N*20],top[N*20],son[N*20],fir[N*20],dep[N*20];
	struct edge{
		int to,nx;
	}eg[N*40];
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void dfs1(const int x){
		sz[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa[x]){
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs1(y);
				if(sz[son[x]]<sz[y]) son[x]=y;
				sz[x]+=sz[y];
			}
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
	inline int lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}
}

namespace S{
	int cnt,que[N*20];
	struct node{
		int lk,c[26];
	}tr[N*20];
	inline void add(const int pt){
		const int len=strlen(ch+1);
		int p=0;
		for(int i=1;i<=len;++i){
			const int c=ch[i]-'a';
			if(!tr[p].c[c]) tr[p].c[c]=++cnt;
			p=tr[p].c[c];
		}
		endp[pt]=p;
	}
	inline void build(){
		int hd=0,tl=1;
		while(hd!=tl){
			const int x=que[hd++],lk=tr[x].lk;
			for(int i=0;i<26;++i){
				int &y=tr[x].c[i];
				if(!y) y=tr[lk].c[i];
				else{
					if(x!=lk) tr[y].lk=tr[lk].c[i];
					que[tl++]=y;
					T::add(tr[y].lk+1,y+1);
				}
			}
		}
	}
}

inline void mod(){
	static int stk[N*20];
	using S::tr;
	const int len=strlen(ch+1);
	int p=0,top=0;
	for(int i=1;i<=len;++i){
		const int c=ch[i]-'a';
		p=tr[p].c[c];
		stk[++top]=p+1;
	}
	std::sort(stk+1,stk+top+1,cmp_dfn);
	for(int i=1;i<=top;++i){
		BIT::mod(dfn[stk[i]],1);
		if(i>1) BIT::mod(dfn[T::lca(stk[i-1],stk[i])],-1);
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		scanf("%s",ch+1);
		S::add(i);
	}
	S::build();
	T::dfs1(1);
	T::dfs2(1);
	q=nxi();
	for(int i=1;i<=q;++i){
		const int op=nxi();
		if(op==2){
			const int x=endp[nxi()]+1;
			printf("%d\n",BIT::ask(dfn[x],dfn[x]+T::sz[x]-1));
		}
		else{
			scanf("%s",ch+1);
			mod();
		}
	}
	return 0;
}
