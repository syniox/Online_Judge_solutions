#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
typedef long long lint;
const int N=1e5+5;
int n,qk,buk1[N];
struct data{
	int l,r;
	bool operator < (const data &b) const {
		return l+r<b.l+b.r;
	}
}dt[N];
struct node{
	int v,f,sz,ssz,c[2];
	lint s;
};

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

struct T{
	int rt,cnt;
	node tr[N<<1];
	inline bool side(const int k){
		return tr[tr[k].f].c[1]==k;
	}
	inline void upd(const int k){
		tr[k].s=(lint)tr[k].v*tr[k].sz+tr[tr[k].c[0]].s+tr[tr[k].c[1]].s;
		tr[k].ssz=tr[tr[k].c[0]].ssz+tr[tr[k].c[1]].ssz+tr[k].sz;
	}
	inline void rot(const int k){
		const int f=tr[k].f,ff=tr[f].f;
		const bool sid=side(k);
		int &p=tr[k].c[sid^1];
		tr[k].f=ff;
		if(ff) tr[ff].c[side(f)]=k;
		tr[f].c[sid]=p;
		tr[p].f=f;
		tr[f].f=k;
		p=f;
		upd(f),upd(k);
	}
	inline void splay(int k){
		while(tr[k].f){
			const int f=tr[k].f;
			if(tr[f].f) rot(side(f)==side(k)?f:k);
			rot(k);
		}
		rt=k;
	}
	inline int find_rk(int rk){
		int k=rt;
		--rk;
		while(tr[k].c[0]||tr[k].c[1]){
			const int tp=tr[tr[k].c[0]].sz;
			if(tp<=rk&&tp+tr[k].sz>rk) break;
			if(tp>rk) k=tr[k].c[0];
			else{
				rk-=tp+tr[k].sz;
				k=tr[k].c[1];
			}
		}
		splay(k);
		return k;
	}
	inline int find_hex(int v){
		int k=rt;
		while(tr[k].v!=v){
			k=tr[k].c[tr[k].v<v];
		}
		splay(k);
		return k;
	}
	//0: pre, 1: next
	inline int pr_nx(const int v,const int f){
		find_hex(v);
		int p=tr[rt].c[f];
		while(tr[p].c[f^1]) p=tr[p].c[f^1];
		return p;
	}
	inline void ins(const int v){
		int k=rt;
		while(k&&tr[k].v!=v&&tr[k].c[tr[k].v<v]){
			k=tr[k].c[tr[k].v<v];
		}
		if(k&&tr[k].v==v) ++tr[k].sz;
		else{
			tr[k].c[tr[k].v<v]=++cnt;
			tr[cnt]=(node){v,k,1,1,{0,0},v};
			k=cnt;
		}
		splay(k);
	}
	inline void del(const int v){
		find_hex(v);
		if(tr[rt].sz>1){
			--tr[rt].sz,--tr[rt].ssz,tr[rt].s-=v;
		}
		else{
			const int ls=tr[rt].c[0],rs=tr[rt].c[1];
			if(!(ls&&rs)){
				rt=ls+rs;
				tr[ls].f=tr[rs].f=0;
				return;
			}
			const int pre=pr_nx(v,0);
			tr[tr[rt].c[0]].f=0;
			tr[rt].c[0]=tr[rt].c[1]=0;
			splay(pre);
			tr[rt].c[1]=rs;
			tr[rs].f=rt;
			upd(rt);
		}
	}
}tr_l,tr_r;

inline lint get_ans(T &tr,const int rk_mid){
	tr.find_rk(rk_mid);
	const int v=tr.tr[tr.rt].v;
	const node &ls=tr.tr[tr.tr[tr.rt].c[0]];
	const node &rs=tr.tr[tr.tr[tr.rt].c[1]];
	return ((lint)v*ls.ssz-ls.s)+(rs.s-(lint)v*rs.ssz);
}

inline lint solve(){
	lint ans=1e14;
	for(int i=1;i<=n;++i){
		tr_r.ins(dt[i].l);
		tr_r.ins(dt[i].r);
	}
//	printf("rt:%d\n",tr_r.rt);
//	for(int i=1;i<=tr_r.cnt;++i){
//		const node &cur=tr_r.tr[i];
//		printf("%d: v=%d f=%d sz=%d ssz=%d",i,cur.v,cur.f,cur.sz,cur.ssz);
//		printf(" c={%d %d} s=%lld\n",cur.c[0],cur.c[1],cur.s);
//	}
	for(int i=1;i<n;++i){
		tr_l.ins(dt[i].l);
		tr_l.ins(dt[i].r);
		tr_r.del(dt[i].l);
		tr_r.del(dt[i].r);
		apn(ans,get_ans(tr_l,i)+get_ans(tr_r,n-i));
	}
	return ans==1e14?0:ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	qk=nxi(),n=nxi();
	lint base=0;
	for(int i=1;i<=n;++i){
		char p,q;
		while((p=getchar())!='A'&&p!='B');
		int x1=nxi();
		while((q=getchar())!='A'&&q!='B');
		int x2=nxi();
		if(x1>x2) std::swap(x1,x2);
		if(p==q){
			base+=x2-x1;
			--i,--n;
		}
		else{
			++base;
			dt[i]=(data){x1,x2};
		}
	}
	if(qk==1){
		for(int i=1;i<=n;++i){
			buk1[(i<<1)-1]=dt[i].l;
			buk1[i<<1]=dt[i].r;
		}
		std::sort(buk1+1,buk1+(n<<1)+1);
		const int mid=buk1[n];
		for(int i=1;i<=n<<1;++i){
			base+=abs(buk1[i]-mid);
		}
		printf("%lld\n",base);
	}
	else{
		std::sort(dt+1,dt+n+1);
		printf("%lld\n",base+solve());
	}
	return 0;
}
