#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
typedef long long lint;
using namespace std;
const int N=1e5+5,logN=18,M=5e5+5;
int n,m,ans[M];
struct rng{
	int l,r;
	friend bool operator<(const rng &a,const rng &b){
		return a.l==b.l?a.r>b.r:a.l<b.l;
	}
};
vector <rng> rbuk[N];
struct mdf_s{
	int r,v;
};
vector <mdf_s> mbuk[N];
struct qry_s{
	int r,id;
};
vector <qry_s> qbuk[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace D{
	lint v[N];
	int cnt;
	inline void add(const lint x){
		v[++cnt]=x;
	}
	inline void build(){
		sort(v+1,v+cnt+1);
		cnt=unique(v+1,v+cnt+1)-v-1;
	}
	inline int ask(const lint x){
		return lower_bound(v+1,v+cnt+1,x)-v;
	}
}

void ins_v(set<int> &st,const int x,const int v){
	set<int>::iterator it=st.lower_bound(x);
	assert(*it!=x);
	if(it!=st.end()){
		rbuk[v].push_back((rng){x,*it});
	}
	if(it!=st.begin()){
		rbuk[v].push_back((rng){*--it,x});
	}
}
void ins_mdf(const int l,const int r,const int v){
	mbuk[l].push_back((mdf_s){r,v});
}

namespace B{
	int tr[N];
	inline void add(int x,const int v){
		for(; x<=n; x+=x&-x) tr[x]+=v;
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return ans;
	}
}

namespace G{
	int cnt,fir[N],sz[N],son[N];
	lint dis[N];
	set<int> qst[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs_dis(const int x){
		D::add(dis[x]);
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(sz[y]) continue;
			dis[y]=dis[x]+eg[i].wi;
			dfs_dis(y);
			if(sz[son[x]]<sz[y]) son[x]=y;
			sz[x]+=sz[y];
		}
	}
	void dfs_rng(const int x){
		rbuk[dis[x]].push_back((rng){x,x});
		if(!son[x]){
			qst[x].insert(x);
			return;
		}else{
			dfs_rng(son[x]);
			swap(qst[x],qst[son[x]]);
			ins_v(qst[x],x,dis[x]);
			qst[x].insert(x);
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(sz[y]>sz[x]||y==son[x]) continue;
			dfs_rng(y);
			for(set<int>::iterator it=qst[y].begin(); it!=qst[y].end(); ++it){
				ins_v(qst[x],*it,dis[x]);
			}
			for(set<int>::iterator it=qst[y].begin(); it!=qst[y].end(); ++it){
				qst[x].insert(*it);
			}
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v),G::add(b,a,v);
	}
	G::dfs_dis(1);
	D::build();
	for(int i=1; i<=n; ++i){
		//eprintf("dep%d: %lld\n",i,D::v[i]);
	}
	for(int i=1; i<=n; ++i){
		G::dis[i]=D::ask(G::dis[i]);
	}
	G::dfs_rng(1);
	for(int i=1; i<=D::cnt; ++i){
		static int stk[N*20];
		assert(!rbuk[i].empty());
		sort(rbuk[i].begin(),rbuk[i].end());
		int top=0;
		for(int j=0; j<(int)rbuk[i].size(); ++j){
			while(top&&rbuk[i][stk[top]].r>=rbuk[i][j].r) --top;
			stk[++top]=j;
		}
		for(int lst=0,j=1; j<=top; ++j){
			ins_mdf(lst+1,rbuk[i][stk[j]].r,1);
			ins_mdf(rbuk[i][stk[j]].l+1,rbuk[i][stk[j]].r,-1);
			lst=rbuk[i][stk[j]].l;
		}
	}
	for(int i=1; i<=m; ++i){
		const int l=nxi(),r=nxi();
		qbuk[l].push_back((qry_s){r,i});
	}
	for(int i=1; i<=n; ++i){
		for(vector<mdf_s>::iterator it=mbuk[i].begin(); it!=mbuk[i].end(); ++it){
			B::add(it->r,it->v);
		}
		for(vector<qry_s>::iterator it=qbuk[i].begin(); it!=qbuk[i].end(); ++it){
			ans[it->id]=B::ask(it->r);
		}
	}
	for(int i=1; i<=m; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
