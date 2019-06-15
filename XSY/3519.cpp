#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n;
lint ans[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

template <class T,size_t S>
class _disc{
	public:
		T v[S],*tl;
		int tot;
		_disc(){tl=v;}
		inline void insert(const T &x){
			*++tl=x;
		}
		inline void build(){
			std::sort(v+1,tl+1);
			tl=std::unique(v+1,tl+1)-1;
			tot=tl-v;
		}
		inline int ask(const T &x){
			return std::lower_bound(v+1,tl+1,x)-v;
		}
};
_disc <int,N> D;

class mset{
	protected:
		int rt;
		struct node{
			int ls,rs,sz,v,w;
			node(){w=rand();}
		};
		static node tr[(int)3e6];
		static int cnt;

		inline void upd(const int k){
			tr[k].sz=tr[tr[k].ls].sz+tr[tr[k].rs].sz+1;
		}

		void split(const int k,int &r1,int &r2,const int v){
			if(!k){
				r1=r2=0;
				return;
			}
			if(tr[k].v>v){
				r2=k;
				split(tr[k].ls,r1,tr[k].ls,v);
			}
			else{
				r1=k;
				split(tr[k].rs,tr[k].rs,r2,v);
			}
			if(r1) upd(r1);
			if(r2) upd(r2);
		}

		void merge(int &k,const int r1,const int r2){
			if(!r1||!r2){
				k=r1+r2;
				return;
			}
			if(tr[r1].w<tr[r2].w){
				k=r1;
				merge(tr[k].rs,tr[k].rs,r2);
			}
			else{
				k=r2;
				merge(tr[k].ls,r1,tr[k].ls);
			}
			upd(k);
		}

		int rnk_t(const int k,const int v){
			if(!k) return 0;
			if(tr[k].v>v) return rnk_t(tr[k].ls,v);
			return tr[tr[k].ls].sz+1+rnk_t(tr[k].rs,v);
		}
	public:
		inline void insert(const int v){
			int r1,r2;
			split(rt,r1,r2,v);
			tr[++cnt].v=v;
			tr[cnt].sz=1;
			merge(r1,r1,cnt);
			merge(rt,r1,r2);
		}

		inline void erase(const int v){
			int r1,r2,q;
			split(rt,r1,r2,v);
			assert(r1);
			if(!tr[r1].rs) r1=tr[r1].ls;
			else{
				for(q=r1; tr[tr[q].rs].rs; q=tr[q].rs){
					--tr[q].sz;
				}
				--tr[q].sz;
				assert(tr[tr[q].rs].v==v);
				tr[q].rs=tr[tr[q].rs].ls;
			}
			merge(rt,r1,r2);
		}

		inline int rank(const int v){
			return rnk_t(rt,v);
		}
};
int mset::cnt;
mset::node mset::tr[(int)3e6];

namespace B{
	mset tr[N];
	inline void add(int x,const int v){
		for(; x<=D.tot; x+=x&-x) tr[x].insert(v);
	}
	inline void rem(int x,const int v){
		for(; x<=D.tot; x+=x&-x) tr[x].erase(v);
	}
	inline int ask(int x,const int v){
		int ans=0;
		for(; x; x-=x&-x) ans+=tr[x].rank(v);
		return ans;
	}
}

int calc(const int w){
	const int tot=B::ask(w-1,2e9);
	if(!tot) return -1;
	int l=-1,r=2e9,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(B::ask(w-1,mid)<(tot+1)>>1) l=mid+1;
		else r=mid;
	}
	return l;
}

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,wi,cs,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int w,const int c){
		eg[++cnt]=(edge){b,w,c,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x,const int f){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==f) continue;
			int res=calc(eg[i].wi);
			res=res==-1?eg[i].cs:res+1;
			ans[y]=ans[x]+res;
			B::add(eg[i].wi,res);
			dfs(y,x);
			B::rem(eg[i].wi,res);
		}
	}
}

int main(){
	srand(19491001);
	n=nxi()+1;
	for(int i=1; i<n; ++i){
		const int a=nxi()+1,b=nxi()+1,w=nxi(),c=nxi();
		G::add(a,b,w,c);
		G::add(b,a,w,c);
		D.insert(w);
	}
	D.build();
	for(int i=1; i<G::cnt; i+=2){
		using G::eg;
		eg[i].wi=eg[i+1].wi=D.ask(eg[i].wi);
	}
	G::dfs(1,1);
	for(int i=2; i<=n; ++i){
		printf("%lld ",ans[i]);
	}
	puts("");
	return 0;
}
