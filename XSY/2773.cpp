#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include <queue>
typedef long long lint;
using namespace std;
const int N=8e4+5,logN=17;
int n,m,val[N],fa[N],len[N];
char ch[N];

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

namespace T{
	queue<int> rm_ls;
	int rt[N];
	struct node{//小根堆
		int wgt,ls,rs,v;
		int sz;
	}tr[(int)(N*logN*1.5)];

	inline void upd(const int k){
		tr[k].sz=tr[tr[k].ls].sz+tr[tr[k].rs].sz+1;
	}

	inline int newnode(const int v){
		static int cnode;
		int res;
		if(!rm_ls.empty()){
			res=rm_ls.front();
			rm_ls.pop();
		}else{
			res=++cnode;
		}
		tr[res]=(node){rand(),0,0,v,1};
		return res;
	}

	void split(const int k,int &h1,int &h2,const int v){
		if(!k) return h1=h2=0,void();
		assert(tr[k].ls!=k&&tr[k].rs!=k);
		if(tr[k].v<=v){
			h1=k;
			split(tr[k].rs,tr[k].rs,h2,v);
		}else{
			h2=k;
			split(tr[k].ls,h1,tr[k].ls,v);
		}
		upd(k);
	}
	void merge(int &k,const int h1,const int h2){
		if(!h1||!h2) return k=h1|h2,void();
		if(tr[h1].wgt<tr[h2].wgt){
			k=h1;
			merge(tr[k].rs,tr[k].rs,h2);
		}else{
			k=h2;
			merge(tr[k].ls,h1,tr[k].ls);
		}
		upd(k);
	}

	void dfs_rem(const int k){
		if(tr[k].ls) dfs_rem(tr[k].ls);
		if(tr[k].rs) dfs_rem(tr[k].rs);
		if(k) rm_ls.push(k);
	}

	void insert(int &rt,const int v){
		int r1,r2;
		split(rt,r1,r2,v);
		merge(r1,r1,newnode(v));
		merge(rt,r1,r2);
	}
	int qsum(int &rt,const int v){
		int r1,r2;
		split(rt,r1,r2,v);
		int res=tr[r1].sz;
		merge(rt,r1,r2);
		return res;
	}

	void rebuild(int &k,const int *v,const int len){
		static int stk[N];
		dfs_rem(k);
		int top=0;
		for(int i=1; i<=len; ++i){//stk[0]=0 极限
			int p=newnode(v[i]);
			if(top&&tr[stk[top]].wgt>tr[p].wgt){
				while(top>1&&tr[stk[top-1]].wgt>tr[p].wgt){
					upd(stk[top--]);
				}
				upd(stk[top]);
				tr[p].ls=stk[top--];
			}
			if(top){
				tr[stk[top]].rs=p;
			}
			stk[++top]=p;
		}
		while(top) upd(stk[top--]);
		k=stk[1];
	}
}

namespace S{
	const double alpha=0.68;
	int *rnd,rbuk[N],vbuk[N],rcnt;
	int rt;
	double rvd,rvu;
	int q,ql,qr,ans;
	struct node{
		int hgt,fa,ls,rs;
		double rk;

		int sz,nhgt;
		double nrk,xrk;
	}tr[N];

	void upd(const int k){
		const int ls=tr[k].ls,rs=tr[k].rs;
		tr[k].nhgt=tr[k].hgt;
		tr[k].nrk=tr[k].xrk=tr[k].rk;
		tr[k].sz=1;
		if(ls){
			tr[k].nrk=tr[ls].nrk;
			apn(tr[k].nhgt,tr[ls].nhgt);
			tr[k].sz+=tr[ls].sz;
		}
		if(rs){
			tr[k].xrk=tr[rs].xrk;
			apn(tr[k].nhgt,tr[rs].nhgt);
			tr[k].sz+=tr[rs].sz;
		}
	}
	inline void touch(const int x){
		for(int i=x; i; i=tr[i].fa) upd(i);
	}

	inline bool cmpstr(const int a,const int b){
		if(ch[a]!=ch[b]) return ch[a]<ch[b];
		return tr[fa[a]].rk<tr[fa[b]].rk;
	}

	void dfs_nd(const int x){
		if(tr[x].ls) dfs_nd(tr[x].ls);
		rbuk[++rcnt]=x;
		if(tr[x].rs) dfs_nd(tr[x].rs);
	}
	int build_rbuk(const int f,const int l,const int r){
		if(l>r) return 0;
		const int mid=(l+r)>>1,k=rbuk[mid];
		tr[k].fa=f;
		tr[k].ls=build_rbuk(k,l,mid-1);
		tr[k].rs=build_rbuk(k,mid+1,r);
		inplace_merge(vbuk+l,vbuk+mid,vbuk+mid+1);
		inplace_merge(vbuk+l,vbuk+mid+1,vbuk+r+1);
		T::rebuild(T::rt[k],vbuk+l-1,r-l+1);
		upd(k);
		return k;
	}
	void rebuild(int *x){
		rcnt=0;
		const int f=tr[*x].fa;
		dfs_nd(*x);
		for(int i=1; i<=rcnt; ++i){
			tr[rbuk[i]].rk=(rvu*i+rvd*(rcnt-i+1))/(rcnt+1);
			vbuk[i]=val[rbuk[i]];
		}
		*x=build_rbuk(f,1,rcnt);
		touch(f);
	}

	int qprev(const int x){
		int k=rt,res=0;
		while(k){
			if(!cmpstr(k,x)) k=tr[k].ls;
			else res=k,k=tr[k].rs;
		}
		return res;
	}
	int qnext(const int x){
		int k=rt,res=0;
		while(k){
			if(cmpstr(k,x)) k=tr[k].rs;
			else res=k,k=tr[k].ls;
		}
		return res;
	}

	void insert_t(int &k,int f,int x,double vd,double vu){
		if(!k){
			k=x;
			tr[x].fa=f;
			tr[x].rk=(vu+vd)/2;
			upd(x);
			T::insert(T::rt[x],val[x]);
			return;
		}
		T::insert(T::rt[k],val[x]);
		if(cmpstr(x,k)){
			insert_t(tr[k].ls,k,x,vd,tr[k].rk);
		}else{
			insert_t(tr[k].rs,k,x,tr[k].rk,vu);
		}
		upd(k);
		const int lim=tr[k].sz*alpha;
		if(tr[k].sz>2&&(tr[tr[k].ls].sz>lim||tr[tr[k].rs].sz>lim)){
			rnd=&k,rvu=vu,rvd=vd;
		}
	}

	int qans(const int k){//1: 能否到左边 2: 能否到右边
		if(!k||tr[k].nhgt>=ql){
			if(k) ans+=T::qsum(T::rt[k],qr);
			return 3;
		}
		int res=0;
		if(k==q){
			ans+=val[q]<=qr;
			if(tr[k].hgt>=ql) res|=qans(tr[k].ls)&1;
			res|=qans(tr[k].rs)&2;
		}else if(tr[q].rk<tr[k].rk){
			int tmp=qans(tr[k].ls);
			if((tmp&2)&&tr[k].hgt>=ql){
				ans+=val[k]<=qr;
				tmp=(tmp&1)|(qans(tr[k].rs)&2);
			}else tmp&=1;
			res=tmp;
		}else{//tr[q].rk>tr[k].rk
			int tmp=qans(tr[k].rs);
			if(tmp&1){
				ans+=val[k]<=qr;
				if(tr[k].hgt>=ql){
					tmp=(tmp&2)|(qans(tr[k].ls)&1);
				}else tmp^=1;
			}
			res=tmp;
		}
		return res;
	}

	int qlcp(const int k,const int a,const int b){//不计算a的height
		if(tr[k].nrk>tr[a].rk&&tr[k].xrk<=tr[b].rk) return tr[k].nhgt;
		int res=1e9,ls=tr[k].ls,rs=tr[k].rs;
		if(ls&&tr[a].rk<tr[ls].xrk) apn(res,qlcp(ls,a,b));
		if(tr[a].rk<tr[k].rk&&tr[k].rk<=tr[b].rk) apn(res,tr[k].hgt);
		if(rs&&tr[rs].nrk<=tr[b].rk) apn(res,qlcp(rs,a,b));
		return res;
	}

	void insert(const int x){
		rnd=0;
		int pv=qprev(x),nx=qnext(x);
		int hgt_pv=pv&&ch[x]==ch[pv]?qlcp(rt,fa[pv],fa[x])+1:0;
		int hgt_nx=nx&&ch[x]==ch[nx]?qlcp(rt,fa[x],fa[nx])+1:0;
		tr[x].hgt=hgt_pv;
		if(nx){
			tr[nx].hgt=hgt_nx;
			touch(nx);
		}
		insert_t(rt,0,x,0,1e9);
		if(rnd) rebuild(rnd);
	}

	int ask(const int q,const int l,const int r){
		S::q=q,ql=l,qr=r,ans=0;
		qans(rt);
		return ans;
	}
}

void build_S(){
	static const int N=4e4+5;
	static vector <int> son[N];
	static int que[N];
	using S::tr;
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		fa[b]=a;
		while((ch[b]=getchar())>'Z'||ch[b]<'A');
		son[a].push_back(b);
	}
	int hd=0,tl=1;
	que[0]=1;
	while(hd!=tl){
		const int x=que[hd++];
		for(vector<int>::iterator it=son[x].begin(); it!=son[x].end(); ++it){
			len[*it]=len[x]+1;
			que[tl++]=*it;
			S::insert(*it);
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	build_S();
	for(int ans=1; m--; ){
		if(nxi()==0){
			int u=nxi()^ans,l=nxi(),r=nxi();
			if(l>len[u]) puts("0");
			else{
				int res=S::ask(u,l,r)+(l==0&&val[1]<=r);//node 1
				if(res) ans=res;
				printf("%d\n",res);
			}
		}else{
			fa[++n]=nxi()^ans;
			val[n]=nxi();
			len[n]=len[fa[n]]+1;
			while((ch[n]=getchar())>'Z'||ch[n]<'A');
			S::insert(n);
		}
	}
	return 0;
}
