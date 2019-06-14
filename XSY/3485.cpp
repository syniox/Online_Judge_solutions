//Treap index比SAM多1

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <map>
typedef long long lint;
const int N=1e5+5;
int n,m,q,str[N],up_st[N],ans[N*5];
struct _qry{
	int dlt,kth,id;
	friend bool operator < (const _qry &a,const _qry &b){
		return a.dlt<b.dlt;
	}
}qry[N*5];
struct _pair{
	int x,y;
}mov[N*5];

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

inline bool cmp_y(const _pair &a,const _pair &b){
	return a.y>b.y;
}

namespace T{
	//小根堆
	int rt;
	const int *idx;
	const bool *vld;
	struct node{
		//fa只保证merge之后正确
		int ls,rs,w,fa,sz,sz_t;
		bool vld;
	}tr[N<<1];

	inline void upd(const int k){
		const int ls=tr[k].ls,rs=tr[k].rs;
		tr[k].sz=tr[ls].sz+tr[rs].sz+vld[k];
		tr[k].sz_t=tr[ls].sz_t+tr[rs].sz_t+1;
		if(ls) tr[ls].fa=k;
		if(rs) tr[rs].fa=k;
	}

	int build_t(const int l,const int r){
		int rt=l;
		for(int i=l+1; i<=r; ++i){
			if(tr[idx[i]].w<tr[idx[rt]].w) rt=i;
		}
		if(l<rt) tr[idx[rt]].ls=build_t(l,rt-1);
		if(r>rt) tr[idx[rt]].rs=build_t(rt+1,r);
		upd(idx[rt]);
		return idx[rt];
	}

	void build(const int *idx,const bool *vld,const int len){
		T::idx=idx;
		T::vld=vld;
		for(int i=1; i<=len; ++i){
			tr[i].w=rand();
		}
		rt=build_t(1,len);
	}

	void split(const int k,int &r1,int &r2,const int v){
		if(!k){
			r1=r2=0;
			return;
		}
		const int sz_l=tr[tr[k].ls].sz_t;
		if(sz_l>=v){
			r2=k;
			split(tr[k].ls,r1,tr[k].ls,v);
		}
		else{
			r1=k;
			split(tr[k].rs,tr[k].rs,r2,v-sz_l-1);
		}
		if(r1) upd(r1);
		if(r2) upd(r2);
	}

	void merge(int &k,const int r1,const int r2){
		if(!r1||!r2){
			k=r1+r2;
			tr[k].fa=0;
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
		tr[k].fa=0;
	}

	int kth(const int k,const int v){
		assert(k&&v>0);
		const int sz_l=tr[tr[k].ls].sz;
		if(sz_l>=v) return kth(tr[k].ls,v);
		if(vld[k]&&sz_l+vld[k]==v) return k;
		return kth(tr[k].rs,v-sz_l-vld[k]);
	}

	inline int rnk_t(int q){
		int ans=tr[tr[q].ls].sz_t+1;;
		for(int f=tr[q].fa; f; q=f,f=tr[q].fa){
			if(tr[f].rs==q) ans+=tr[tr[f].ls].sz_t+1;
		}
		return ans;
	}

	void shift(const int l,const int r,const int p){
		//[l,r]移到原来的p之后(l>p)
		assert(l>p);
		if(l==p+1) return;
		int r1,r2,r3;
		split(rt,rt,r3,r);
		split(rt,rt,r2,l-1);
		split(rt,rt,r1,p);
		merge(rt,rt,r2);
		merge(rt,rt,r1);
		merge(rt,rt,r3);
	}
}

namespace S{
	int cnt,lst,id[N],idfn[N<<1],cnd;
	bool vld[N<<1];
	std::map <int,int> nxt[N<<1];
	struct node{
		int lk,sz,pos,len;
		std::map <int,int> c;
	}tr[N<<1];
	struct _init{
		_init(){tr[0].lk=-1;}
	}init;

	void insert(const int c,const int pos){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		tr[k].sz=vld[k]=1;
		tr[k].pos=pos;
		id[pos]=k;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
		}
		if(p==-1) return;
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[k].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			tr[cnt].sz=0;
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk){
				tr[p].c[c]=cnt;
			}
			tr[k].lk=tr[q].lk=cnt;
		}
	}

	void dfs_sz(const int x){
		idfn[++cnd]=x+1;
		tr[x].sz=1;
		for(std::map <int,int> ::iterator it=nxt[x].begin(); it!=nxt[x].end(); ++it){
			dfs_sz(it->second);
			tr[x].sz+=tr[it->second].sz;
		}
	}

	void build(){
		for(int i=1; i<=cnt; ++i){
			const int f=tr[i].lk,p=tr[i].pos+tr[f].len;
			mov[i]=(_pair){i,str[p]};
			assert(nxt[f].find(str[p])==nxt[f].end());
			nxt[f][str[p]]=i;
		}
		std::sort(mov+1,mov+cnt+1,cmp_y);
		dfs_sz(0);
		T::build(idfn,vld-1,cnt+1);
	}
}

int main(){
	srand(19491001);
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		str[i]=nxi();
	}
	for(int i=1; i<=q; ++i){
		qry[i].dlt=nxi();
		qry[i].kth=nxi();
		qry[i].id=i;
	}
	std::sort(qry+1,qry+q+1);
	for(int i=n; i>=1; --i){
		S::insert(str[i],i);
	}
	S::build();
	for(int i=1,j=1; i<=q; ++i){
		for(; j<=S::cnt&&mov[j].y+qry[i].dlt>=m; ++j){
			const int x=mov[j].x,sf=S::tr[x].lk;
			int p=T::rnk_t(x+1),sz=S::tr[x].sz;
			T::shift(p,p+sz-1,p+sz-S::tr[sf].sz);
		}
		ans[qry[i].id]=S::tr[T::kth(T::rt,qry[i].kth)-1].pos;
	}
	for(int i=1; i<=q; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
