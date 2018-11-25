#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
const int N=5e5+5;
int n,q,pos[N],ans[N],to_s[N],to_b[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

bool cmp_pos(const int a,const int b){
	return pos[a]<pos[b];
}

struct cmp_pos_greater{
	bool operator () (const int a,const int b){
		return pos[a]>pos[b];
	}
};

namespace G{
	int cnt,fir[N],in[N],buk[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		++in[b];
	}

	inline void init(){
		for(int i=1;i<=n;++i){
			if(to_s[i]<=n) add(i,to_s[i]);
			if(to_b[i]<=n) add(i,to_b[i]);
		}
	}

	inline void topo(){
		std::priority_queue <int,std::vector <int>,cmp_pos_greater> pq;
		int top=0;
		for(int i=1;i<=n;++i){
			if(!in[i]) pq.push(i);
		}
		while(!pq.empty()){
			const int x=pq.top();
			pq.pop();
			buk[++top]=x;
			for(int i=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to;
				if(!--in[y]) pq.push(y);
			}
		}
	}
}

namespace T{
	int x,y,v,tr[N<<1],buk[N];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)]=tr[idx(l,mid)]+tr[idx(mid+1,r)];
	}

	void mod_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]+=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		else mod_t(mid+1,r);
		upd(l,r);
	}

	int ask_l_t(const int l,const int r){
		if(!tr[idx(l,r)]) return n+1;
		if(l==r) return l;
		int tp,mid=(l+r)>>1;
		if(x<=mid&&(tp=ask_l_t(l,mid))<=n) return tp;
		return ask_l_t(mid+1,r);
	}

	inline void mod(const int x,const int v){
		T::x=x,T::v=v;
		mod_t(1,n);
	}

	inline int ask_l(const int x,const int y){
		if(x>y) return n+1;
		T::x=x,T::y=y;
		return ask_l_t(1,n);
	}

	inline void init(){
		for(int i=1;i<=n;++i){
			buk[pos[i]]=i;
		}
		std::sort(buk+1,buk+n+1,cmp_pos);
	}

	inline void solve1(){
		for(int i=1;i<=n;++i){
			if(i-q>0) mod(buk[i-q],-1);
			apn(to_s[buk[i]],ask_l(buk[i]+1,n));
			mod(buk[i],1);
		}
	}

	inline void solve2(){
		for(int i=n;i;--i){
			if(i+q<=n) mod(buk[i+q],-1);
			apn(to_b[buk[i]],ask_l(buk[i]+1,n));
			mod(buk[i],1);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("f.in","r",stdin);
#endif
	memset(to_s,1,sizeof(to_s));
	memset(to_b,1,sizeof(to_b));
	n=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		pos[nxi()]=i;
	}
	T::init();
	T::solve1();
	memset(T::tr,0,sizeof(T::tr));
	T::solve2();
//	for(int i=1;i<=n;++i){
//		printf("%d %d\n",to_l[i],to_r[i]);
//	}
	G::init();
	G::topo();
	for(int i=1;i<=n;++i){
		ans[pos[G::buk[i]]]=i;
	}
	for(int i=1;i<=n;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
