#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=2e5+2;
int n,m,q,ans[N];
struct edge{
	int x,y;
}eg[N];
struct query{
	int l,r,id;
	bool operator < (const query &b) const {
		return l<b.l;
	}
}qry[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	struct node{
		int f,v,xv,c[2];
		bool rev;
		inline void putrev(){
			rev^=1;
			std::swap(c[0],c[1]);
		}
	}tr[N<<1];
	inline bool side(const int k){
		return tr[tr[k].f].c[1]==k;
	}
	inline bool isrt(const int k){
		return tr[tr[k].f].c[0]!=k&&tr[tr[k].f].c[1]!=k;
	}
	inline void upd(const int k){
		tr[k].xv=tr[k].v;
		apx(tr[k].xv,tr[tr[k].c[0]].xv);
		apx(tr[k].xv,tr[tr[k].c[1]].xv);
	}
	void get_rev(const int k){
		if(!isrt(k)) get_rev(tr[k].f);
		if(tr[k].rev){
			tr[tr[k].c[0]].putrev();
			tr[tr[k].c[1]].putrev();
			tr[k].rev=0;
		}
	}
	inline void rot(const int k){
		const int f=tr[k].f,ff=tr[f].f;
		const bool sid=side(k);
		int &p=tr[k].c[sid^1];
		tr[k].f=ff;
		if(!isrt(f)) tr[ff].c[side(f)]=k;
		tr[f].f=k;
		tr[f].c[sid]=p;
		if(p) tr[p].f=f;
		p=f;
		upd(f);
		upd(k);
	}
	inline void splay(int x){
		get_rev(x);
		while(!isrt(x)){
			const int f=tr[x].f;
			if(!isrt(f)){
				rot(side(f)==side(x)?f:x);
			}
			rot(x);
		}
	}
	inline void acs(int k){
		for(int p=0;k;p=k,k=tr[k].f){
			splay(k);
			tr[k].c[1]=p;
			upd(k);
		}
	}
	inline void mrt(const int k){
		acs(k);
		splay(k);
		tr[k].putrev();
	}
	inline void link(const int x,const int y){
		mrt(x);
		tr[x].f=y;
	}
	inline void split(const int x,const int y){
		mrt(x);
		acs(y);
		splay(y);
	}
	inline void cut(const int x,const int y){
		split(x,y);
		tr[y].c[0]=tr[x].f=0;
		upd(y);
	}
	inline bool same_rt(const int x,const int y){
		split(x,y);
		return tr[x].f!=0;
	}
}

namespace B{
	int tr[N];
	inline void mod(int x,const int v){
		for(;x<=m;x+=x&-x){
			tr[x]+=v;
		}
	}
	inline int ask(int x){
		int ans=0;
		for(;x;x-=x&-x){
			ans+=tr[x];
		}
		return ans;
	}
	inline int ask(const int x,const int y){
		return ask(y)-ask(x-1);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	int Tick=nxi();
	while(Tick--){
		memset(T::tr,0,sizeof(T::tr));
		memset(B::tr,0,sizeof(B::tr));
		n=nxi(),m=nxi(),q=nxi();
		for(int i=1;i<=m;++i){
			eg[i].x=nxi(),eg[i].y=nxi();
			T::tr[i+N].v=T::tr[i+N].xv=i;
		}
		for(int i=1;i<=q;++i){
			qry[i].id=i;
			qry[i].l=nxi(),qry[i].r=nxi();
		}
		std::sort(qry+1,qry+q+1);
		for(int i=m,j=q;i&&j;--i){
			const int x=eg[i].x,y=eg[i].y;
			if(x!=y){
				if(T::same_rt(x,y)){
					const int lst=T::tr[y].xv;
					T::cut(eg[lst].x,lst+N);
					T::cut(lst+N,eg[lst].y);
					B::mod(lst,-1);
				}
				T::link(x,i+N);
				T::link(i+N,y);
				B::mod(i,1);
			}
			for(;qry[j].l==i;--j){
				ans[qry[j].id]=n-B::ask(qry[j].l,qry[j].r);
			}
		}
		for(int i=1;i<=q;++i){
			printf("%d\n",ans[i]);
		}
	}
	return 0;
}
