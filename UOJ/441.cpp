#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
const lint INF=1e12;
int n,q,val[N];

class mtrx{
	public:
		lint n[2][2];
		inline void clear(){
			memset(n,0,sizeof(n));
		}
		friend mtrx operator * (const mtrx &a,const mtrx &b);
};

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

mtrx operator * (const mtrx &a,const mtrx &b){
	mtrx c;
	c.n[0][0]=std::min(a.n[0][0]+b.n[0][0],a.n[0][1]+b.n[1][0]);
	c.n[0][1]=std::min(a.n[0][0]+b.n[0][1],a.n[0][1]+b.n[1][1]);
	c.n[1][0]=std::min(a.n[1][0]+b.n[0][0],a.n[1][1]+b.n[1][0]);
	c.n[1][1]=std::min(a.n[1][0]+b.n[0][1],a.n[1][1]+b.n[1][1]);
	return c;
}

inline mtrx build_mtrx(const lint cos_0,const lint cos_1){
	return (mtrx){INF,cos_1,cos_0,cos_1};
}

namespace T{
	mtrx tr[N<<1];
	//start from right!
	int x,y;
	mtrx v;

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)]=tr[idx(mid+1,r)]*tr[idx(l,mid)];
	}

	mtrx ask_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)];
		const int mid=(l+r)>>1;
		if(y<=mid) return ask_t(l,mid);
		if(x>mid) return ask_t(mid+1,r);
		return ask_t(mid+1,r)*ask_t(l,mid);
	}

	void mod_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		else mod_t(mid+1,r);
		upd(l,r);
	}

	inline mtrx ask(const int l,const int r){
		T::x=l,T::y=r;
		return ask_t(1,n);
	}

	inline void mod(const int x,const mtrx &v){
		T::x=x,T::v=v;
		mod_t(1,n);
	}
}

namespace G{
	int cnt,fir[N],dep[N],fa[N];
	int sz[N],dfn[N],son[N],top[N],bot[N];
	lint cos_0[N],cos_1[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!sz[y]){
				dep[y]=dep[x]+1;
				fa[y]=x;
				dfs_son(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}

	void dfs_top(const int x){
		static int cnd;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		bot[top[x]]=x;
		dfn[x]=++cnd;
		if(son[x]) dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs_top(y);
		}
	}

	void dfs_cos(const int x){
		static int tmp_0,tmp_1;
		int ccos_0=0,ccos_1=val[x];
		bot[x]=bot[top[x]];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==son[x]||y==fa[x]) continue;
			dfs_cos(y);
			ccos_1+=std::min(tmp_0,tmp_1);
			ccos_0+=tmp_1;
		}
		cos_0[x]=ccos_0;
		cos_1[x]=ccos_1;
		if(son[x]) dfs_cos(son[x]);
		else tmp_0=tmp_1=0;
		ccos_0+=tmp_1;
		ccos_1+=std::min(tmp_0,tmp_1);
		tmp_0=ccos_0;
		tmp_1=ccos_1;
	}

	inline void mod(int x,mtrx tp){
		//didn't change cos[x], but it doesn't matter
		mtrx org;
		lint org_0,org_1;
		lint cur_0,cur_1;
		for(int nxt=fa[top[x]]; x; x=nxt,nxt=fa[top[x]]){
			org=T::ask(dfn[top[x]],dfn[bot[x]]);
			T::mod(dfn[x],tp);
			if(!nxt) break;

			org_0=std::min(org.n[0][0],org.n[1][0]);
			org_1=std::min(org.n[0][1],org.n[1][1]);

			tp=T::ask(dfn[top[x]],dfn[bot[x]]);

			cur_0=std::min(tp.n[0][0],tp.n[1][0]);
			cur_1=std::min(tp.n[0][1],tp.n[1][1]);

			cos_0[nxt]+=cur_1-org_1;
			cos_1[nxt]+=std::min(cur_0,cur_1)-std::min(org_0,org_1);

			tp=build_mtrx(cos_0[nxt],cos_1[nxt]);
		}
	}
}

inline void solve(int a,int x,int b,int y){
	using G::dfn;
	if(G::dep[a]<G::dep[b]){
		std::swap(a,b);
		std::swap(x,y);
	}

	const mtrx org_a=T::ask(dfn[a],dfn[a]);
	mtrx mod_a=org_a;
	mod_a.n[0][x^1]=INF,mod_a.n[1][x^1]=INF;
	G::mod(a,mod_a);

	const mtrx org_b=T::ask(dfn[b],dfn[b]);
	mtrx mod_b=org_b;
	mod_b.n[0][y^1]=INF,mod_b.n[1][y^1]=INF;
	G::mod(b,mod_b);

	mtrx ans=T::ask(1,dfn[G::bot[1]]);
	lint ans_0=std::min(ans.n[0][0],ans.n[1][0]);
	lint ans_1=std::min(ans.n[0][1],ans.n[1][1]);
	printf("%lld\n",std::min(ans_0,ans_1));
	G::mod(b,org_b);
	G::mod(a,org_a);
}

int main(){
	n=nxi(),q=nxi(),nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	G::dfs_son(1);
	G::dfs_top(1);
	G::dfs_cos(1);
	for(int i=1; i<=n; ++i){
		T::mod(G::dfn[i],build_mtrx(G::cos_0[i],G::cos_1[i]));
	}
	while(q--){
		const int a=nxi(),x=nxi(),b=nxi(),y=nxi();
		if(!x&&!y&&(G::fa[a]==b||G::fa[b]==a)) puts("-1");
		else solve(a,x,b,y);
	}
	return 0;
}
