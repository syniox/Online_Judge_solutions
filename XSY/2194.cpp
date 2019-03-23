#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cassert>
#include <set>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;
const int N=2e5+5;
const double eps=1e-8;
int n,m;
double val[N];
std::set <int> list;

namespace IO{
    char *pt;
    struct _Initializer{
        _Initializer(){
            pt=(char*)mmap(NULL,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);
        }
    }_initializer;
    inline int nxi(){
        int x=0;
        char c;
        while((c=*pt++)>'9'||c<'0');
        while(x=x*10-48+c,(c=*pt++)>='0'&&c<='9');
        return x;
    }
}
using IO::nxi;

namespace B{
	double cur[N],tr[N];
	inline void add_t(int x,const double v){
		for(; x<=n; x+=x&-x) tr[x]+=v;
	}
	inline double ask_t(int x){
		double ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return ans;
	}
	inline double ask(const int x,const int y){
		if(x>y) return 0;
		return ask_t(y)-ask_t(x-1);
	}
	inline void mod(const int x,const double v){
		double delta=v-cur[x];
		cur[x]=v;
		add_t(x,delta);
	}
}

namespace T2{
	int cnt,x,rt[N];
	bool type,rev[N];
	double v;
	class node{
		public:
			int c[2],sz;
			double v;
			inline void reset(){
				v=0;
				c[0]=c[1]=sz=0;
			}
	}tr[N*40];

	inline void upd(const int k){
		tr[k].v=tr[tr[k].c[0]].v+tr[tr[k].c[1]].v;
		tr[k].sz=tr[tr[k].c[0]].sz+tr[tr[k].c[1]].sz;
	}

	void insert_t(int &k,const int l,const int r){
		if(!k) k=++cnt;
		if(l==r){
			tr[k].v=v;
			++tr[k].sz;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) insert_t(tr[k].c[0],l,mid);
		else insert_t(tr[k].c[1],mid+1,r);
		upd(k);
	}

	double askpre_t(const int k,const int l,const int r){
		if(!k||!x) return 0;
		if(tr[k].sz<=x){
			x-=tr[k].sz;
			return tr[k].v;
		}
		if(l==r){
			assert(tr[k].sz>=x);
			return x*log10(l);
		}
		const int son=tr[k].c[type],mid=(l+r)>>1;
		const int sl[2]={l,mid+1},sr[2]={mid,r};
		if(tr[son].sz>=x) return askpre_t(son,sl[type],sr[type]);
		x-=tr[son].sz;
		return tr[son].v+askpre_t(tr[k].c[type^1],sl[type^1],sr[type^1]);
	}

	void split_t(int &r1,int &r2,const int l,const int r){
		if(tr[r1].sz<=x){
			x-=tr[r1].sz;
			r2=r1,r1=0;
			return;
		}
		r2=++cnt;
		if(l==r){
			assert(tr[r1].sz>=x);
			tr[r2].sz=x;
			tr[r2].v=log10(l)*x;
			tr[r1].sz-=x;
			tr[r1].v-=tr[r2].v;
			x=0;
			return;
		}
		const int mid=(l+r)>>1;
		const int sl[2]={l,mid+1},sr[2]={mid,r};
		split_t(tr[r1].c[type],tr[r2].c[type],sl[type],sr[type]);
		if(x) split_t(tr[r1].c[type^1],tr[r2].c[type^1],sl[type^1],sr[type^1]);
		if(r1) upd(r1);
		if(r2) upd(r2);
	}

	void merge_t(int &r1,const int r2,const int l,const int r){
		if(!r1||!r2){
			r1=r1+r2;
			return;
		}
		if(l==r){
			tr[r1].v+=tr[r2].v;
			tr[r1].sz+=tr[r2].sz;
			return;
		}
		const int mid=(l+r)>>1;
		merge_t(tr[r1].c[0],tr[r2].c[0],l,mid);
		merge_t(tr[r1].c[1],tr[r2].c[1],mid+1,r);
		upd(r1);
	}

	inline void insert(const int rt,const int x,const double v){
		T2::x=x,T2::v=v;
		insert_t(T2::rt[rt],1,n);
	}

	inline double askpre(const int rt,const int x,const bool type){
		//type0: pre, type1: nxt
		if(x<=0) return 0;
		T2::x=x,T2::type=type^rev[rt];
		return askpre_t(T2::rt[rt],1,n);
	}

	inline void split(const int rt1,const int rt2,int sz){
		assert(rt[rt1]);
		assert(list.find(rt2)==list.end());
		assert(rt2-rt1==sz);
		rev[rt2]=rev[rt1];
		sz=tr[rt[rt1]].sz-sz;
		T2::x=sz,type=rev[rt1]^1;
		split_t(rt[rt1],rt[rt2],1,n);
		B::mod(rt1,tr[rt[rt1]].v);
		B::mod(rt2,tr[rt[rt2]].v);
		list.insert(rt2);
	}

	inline void merge(const int rt1,const int rt2){
		merge_t(rt[rt1],rt[rt2],1,n);
		rt[rt2]=0;
		B::mod(rt1,tr[rt[rt1]].v);
		B::mod(rt2,0);
		list.erase(rt2);//optimize?
	}
}

inline void merge(const int l,const int r,const bool type){
	std::set <int> ::iterator it1,it2;
	it1=--list.upper_bound(l);
	if(*it1<l){
		T2::split(*it1,l,l-*it1);
		++it1;
	}
	it2=list.upper_bound(r);
	if((it2==list.end()&&r<n)||(it2!=list.end()&&*it2>r+1)){
		--it2;
		T2::split(*it2,r+1,r-*it2+1);
		++it2;
	}
	for(std::set <int> ::iterator it=it1; it!=it2; ){
		if(it==it1&&++it==it2) break;
		assert(it!=it1);
		T2::merge(*it1,*it++);
	}
	T2::rev[*it1]=type^1;
}

inline int ask(const int l,const int r){
	std::set <int> ::iterator pl,pr;
	pl=--list.upper_bound(l);
	pr=--list.upper_bound(r);
	if(pl==pr){
		double minus=l==*pl?0:T2::askpre(*pl,l-*pl,0);
		double ans=T2::askpre(*pr,r-*pr+1,0)-minus;
		return pow(10,ans-floor(ans+eps))+eps;
	}
	double ans=0;
	if(pr!=list.begin()){
		if(*pr-1>=l) ans+=B::ask(l,*pr-1);
	}
	if(!B::cur[l]){
		int end;
		if(pl==list.end()) end=n;
		else end=*++pl-1,--pl;
		ans+=T2::askpre(*pl,end-l+1,1);
	}
	ans+=T2::askpre(*pr,r-*pr+1,0);
	int res=(pow(10,ans-floor(ans+eps))+eps);
	return res;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		const int x=nxi();
		val[i]=log10(x);
		T2::insert(i,x,val[i]);
		list.insert(i);
		B::mod(i,val[i]);
	}
	for(int i=1; i<=m; ++i){
		const int op=nxi(),x=nxi(),y=nxi();
		if(op==1) merge(x,y,nxi());
		else printf("%d\n",ask(x,y));
	}
	return 0;
}
