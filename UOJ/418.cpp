#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
int n,val[N];
int seq[N],pos[N];
lint ans[N];

class data{
	public:
		int id;
		lint sum,max;
		friend bool operator < (const data &a,const data &b);
		friend data merge(const data &a,const data &b,bool a_as_id);
		friend bool operator == (const data &a,const data &b);
}dt[N];

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

bool operator < (const data &a,const data &b){
	if(a.sum<0&&b.sum<0) return a.max<b.max;
	if(a.sum<0||b.sum<0) return a.sum<b.sum;
	return a.max-a.sum>b.max-b.sum;
}
bool operator == (const data &a,const data &b){
	return a.id==b.id&&a.sum==b.sum&&a.max==b.max;
}

inline data merge(const data &a,const data &b,bool a_as_id){
	return (data){a_as_id?a.id:b.id,a.sum+b.sum,std::max(a.max,a.sum+b.max)};
}

namespace U{
	int fa[N];

	inline int get_fa(const int x){
		return fa[x]?fa[x]=get_fa(fa[x]):x;
	}
	inline void link(const int x,const int y){
		fa[x]=y;
	}
}

namespace L{
	int hd[N],nxt[N],tl[N];

	inline void init(){
		for(int i=1; i<=n; ++i) hd[i]=tl[i]=i;
	}
	inline void link(const int x,const int y){
		assert(hd[x]);
		assert(tl[x]);
		nxt[tl[y]]=hd[x];
		tl[y]=tl[x];
		hd[x]=tl[x]=0;
	}
}

namespace T{
	int pos,cnt,rt[N];
	data v;
	class node{
		public:
			data s;
			int l,r;
	}tr[N*20];

	inline void build_t(const int k,const int l,const int r){
		if(l==r){
			tr[k].s=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(pos<=mid) build_t(tr[k].l=++cnt,l,mid);
		else build_t(tr[k].r=++cnt,mid+1,r);
		tr[k].s=merge(tr[tr[k].l].s,tr[tr[k].r].s,0);
	}

	inline int merge(const int k1,const int k2){
		if(!k1||!k2) return k1+k2;
		tr[k1].l=merge(tr[k1].l,tr[k2].l);
		tr[k1].r=merge(tr[k1].r,tr[k2].r);
		tr[k1].s=merge(tr[tr[k1].l].s,tr[tr[k1].r].s,0);
		return k1;
	}

	inline void build_x(const int x,const int pos,const data &d){
		v=d,T::pos=pos;
		build_t(rt[x]=++cnt,1,n);
	}
}

namespace G{
	int cnt,fa[N],fir[N];
	struct edge{
		int to,nx;
	}eg[N];

	inline void add(const int a,const int b){
		//printf("add: %d -> %d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_ans(const int x){
		T::build_x(x,pos[x],dt[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			dfs_ans(y);
			T::rt[x]=T::merge(T::rt[x],T::rt[y]);
		}
		ans[x]=T::tr[T::rt[x]].s.max;
	}
}

inline void unlock(bool *unlocked,int x){
	for(int i=G::fir[x]; i; i=G::eg[i].nx){
		unlocked[G::eg[i].to]=1;
	}
}

inline void get_seq(){
	static bool vis[N],unlocked[N];
	//static bool unlocked[N];
	static data cur_dt[N];
	static data buk[N];
	std::priority_queue <data> pq;

	memcpy(cur_dt,dt,(n+1)*sizeof(data));
	memcpy(buk+1,dt+1,n*sizeof(data));
	std::sort(buk+1,buk+n+1);
	int cnt_seq=n;
	for(int i=1; i<=n; ++i){
		pq.push(dt[i]);
	}
	unlocked[1]=1;
	while(!pq.empty()){
		data x=pq.top();
		pq.pop();
		if(!(x==cur_dt[x.id])||vis[x.id]) continue;
		//assert(vis[x.id]==0);
		//所有儿子并入后的父亲不总是最先出现
		vis[x.id]=1;
		if(!unlocked[x.id]){
			U::link(x.id,G::fa[x.id]);
			int fa=U::get_fa(x.id);
			L::link(x.id,fa);
			cur_dt[fa]=merge(x,cur_dt[fa],0);
			pq.push(cur_dt[fa]);
		}
		else{
			for(int i=L::hd[x.id]; i; i=L::nxt[i]){
				seq[cnt_seq]=i;
				pos[i]=cnt_seq--;
				unlock(unlocked,i);
			}
		}
	}
}

int main(){
	nxi(),n=nxi();
	L::init();
	for(int i=2; i<=n; ++i){
		G::fa[i]=nxi();
		G::add(G::fa[i],i);
	}
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		dt[i].id=i;
		dt[i].max=dt[i].sum=val[i];
		for(int j=G::fir[i]; j; j=G::eg[j].nx){
			dt[i].sum-=val[G::eg[j].to];
		}
	}
	get_seq();
	/*
	fprintf(stderr,"seq:");
	for(int i=1; i<=n; ++i){
		fprintf(stderr,"%d ",seq[i]);
	}
	fprintf(stderr,"\n");
	*/
	/*
	data res=(data){0,0,0};
	for(int i=1; i<=n; ++i){
		res=merge(res,dt[seq[i]],0);
	}
	printf("sum%lld, max%lld\n",res.sum,res.max);
	*/
	G::dfs_ans(1);
	for(int i=1; i<=n; ++i){
		printf("%lld ",ans[i]);
	}
	puts("");
	return 0;
}
