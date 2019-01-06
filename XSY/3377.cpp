#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
const int V=30005;
const int N=1e5+5,S=320;//!!!
int n,q,cnt_rt,val[N],dep[N],rt_mp[N],rt_fa[N];
bool type;
class bits;
std::vector <bits> vt[S];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> T bitcnt(T x){
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}

class bits{
	unsigned len,*n;
	public:
	inline void clear(){
		memset(n,0,((len+31)>>5)*sizeof(unsigned));
	}
	inline void init(unsigned N){
		len=N;
		n=new unsigned[(len+31)>>5];
		clear();
	}
	void operator |= (const bits &b){
		for(int i=((len+31)>>5)-1; i>=0; --i){
			n[i]|=b.n[i];
		}
	}
	friend bits operator | (const bits &a,const bits &b){
		bits c;
		c.init(V);
		for(int i=((c.len+31)>>5)-1; i>=0; --i){
			c.n[i]=a.n[i]|b.n[i];
		}
		return c;
	}
	void set(int x,bool v){
		n[x>>5]&=(~0u)^(1u<<(x&31));
		n[x>>5]|=(unsigned)v<<(x&31);
	}
	void del(){
		delete[] n;
	}
	unsigned get_cnt(){
		unsigned ans=0;
		for(int i=((len+31)>>5)-1; i>=0; --i){
			ans+=bitcnt(n[i]);
		}
		return ans;
	}
	unsigned find_fir(){
		unsigned x=0,pos=0;
		for(; x<<5<len&&n[x]==~0u; ++x);
		for(; n[x]&1<<pos; ++pos);
		return (x<<5)+pos;
	}
};

namespace G{
	int cnt,fir[N],mx_dep[N];
	int fa[N],sz[N],son[N],top[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs1(const int x){
		mx_dep[x]=dep[x];
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!sz[y]){
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs1(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
				if(!rt_mp[y]) apx(mx_dep[x],mx_dep[y]);
			}
		}
		if(mx_dep[x]-dep[x]>=S) rt_mp[x]=++cnt_rt;
	}

	void dfs2(const int x,int rt){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		rt_fa[x]=rt;
		if(rt_mp[x]){
			bits tmp;
			tmp.init(V);
			for(int i=x; i!=rt; i=fa[i]){
				tmp.set(val[i],1);
			}
			const int fa=rt_mp[rt_fa[x]];
			tmp.set(val[rt],1);
			vt[rt_mp[x]].push_back(tmp);
			for(std::vector <bits> ::iterator it=vt[fa].begin(); it!=vt[fa].end(); ++it){
				vt[rt_mp[x]].push_back(tmp|*it);
			}
			rt=x;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs2(y,rt);
		}
	}

	inline int get_lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}
}

inline void get_bits(bits ans,int x,int y){
	for(; dep[x]>=dep[y]&&!rt_mp[x]; x=G::fa[x]){
		ans.set(val[x],1);
	}
	if(dep[x]<dep[y]) return;
	int tp=x,jump=0;
	for(; dep[rt_fa[tp]]>=dep[y]; tp=rt_fa[tp],++jump);
	if(jump) ans|=vt[rt_mp[x]][jump-1];
	for(x=tp; dep[x]>=dep[y]; x=G::fa[x]){
		ans.set(val[x],1);
	}
}

int main(){
	n=nxi(),q=nxi(),type=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	dep[1]=1;
	G::dfs1(1);
	G::dfs2(1,0);
	bits res;
	res.init(V);
	for(int ans=0,i=1; i<=q; ++i){
		res.clear();
		for(int k=nxi(); k; --k){
			const int x=nxi()^ans,y=nxi()^ans;
			const int lca=G::get_lca(x,y);
			get_bits(res,x,lca);
			get_bits(res,y,lca);
		}
		int ans1=res.get_cnt();
		int ans2=res.find_fir();
		if(type) ans=ans1+ans2;
		printf("%d %d\n",ans1,ans2);
	}
	res.del();
	return 0;
}
