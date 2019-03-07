#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>
typedef long long lint;
const int N=1005;
const int Q=5e5+5;
const int mod=1e9+7;
int n,m,q;
std::set <int> vld[N];

class mod_seq{
	public:
		int x,y;
}mseq[Q];

class pair{
	public:
		int x,y;
		friend bool operator < (const pair &a,const pair &b){
			return a.y==b.y?a.x>b.x:a.y<b.y;
		}
};
std::set <pair> bit_st[Q];

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

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace D{
	int val[Q],*pt=val;
	inline void insert(int v){
		*pt++=v;
	}
	inline void build(){
		std::sort(val,pt);
		pt=std::unique(val,pt);
	}
	inline int ask(const int v){
		return std::lower_bound(val,pt,v)-val+1;
	}
}

inline void flip(int bel,int pos){
	std::set <pair> ::iterator it,it2;
	int dpos=D::ask(pos);

	if(vld[bel].count(pos)){
		vld[bel].erase(pos);
		it=bit_st[dpos].lower_bound((pair){bel,bel});
		if(it->x<bel) bit_st[dpos].insert((pair){it->x,bel-1});
		if(it->y>bel) bit_st[dpos].insert((pair){bel+1,it->y});
		bit_st[dpos].erase(it);
	}
	else{
		vld[bel].insert(pos);
		it=bit_st[dpos].lower_bound((pair){bel,bel});
		int ins_l=bel,ins_r=bel;
		if(it!=bit_st[dpos].begin()){
			it2=it;
			if((--it2)->y==bel-1){
				ins_l=it2->x;
				bit_st[dpos].erase(it2);
			}
		}
		if(it!=bit_st[dpos].end()){
			if(it->x==bel+1){
				ins_r=it->y;
				bit_st[dpos].erase(it);
			}
		}
		bit_st[dpos].insert((pair){ins_l,ins_r});
	}
}

inline bool exist(int *buk,int len,int v){
	//buk is decresing
	int l=1,r=len,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(buk[mid]>v) l=mid+1;
		else r=mid;
	}
	return buk[l]==v;
}

inline void remove_pt(int bel,int pos,int &res,int *rm_buk){
	res=(res-fpow(2,pos)+mod)%mod;
	int dpos=D::ask(pos);
	std::set <pair> ::iterator it=bit_st[dpos].lower_bound((pair){bel,bel});
	if(it==bit_st[dpos].end()||it->x>bel) return;
	assert(it->x<=bel&&it->y+1>=bel);
	if(rm_buk[it->y+1]==pos){
		rm_buk[it->y+1]=-1;
	}
}

inline int solve(){
	static int rm_buk[N];
	memset(rm_buk+1,-1,n*sizeof(int));
	static int stk[N];
	std::set <pair> ::iterator it;
	int top=0,ans=0,res=0;
	//res: result of current line
	for(int i=1; i<=n; ++i){
		int lbound=rm_buk[i];
		for(; top&&stk[top]<=lbound; --top){
			remove_pt(i,stk[top],res,rm_buk);
		}
		std::set <int> ::iterator it=vld[i].upper_bound(lbound);
		for(; it!=vld[i].end()&&top&&exist(stk,top,*it); ++it){
			for(; top&&stk[top]<=*it; --top){
				remove_pt(i,stk[top],res,rm_buk);
			}
		}
		if(it==vld[i].end()) return -1;
		for(; top&&stk[top]<=*it; --top){
			remove_pt(i,stk[top],res,rm_buk);
		}
		std::set <pair> ::iterator it_p=bit_st[D::ask(*it)].lower_bound((pair){i,i});
		apx(rm_buk[it_p->y+1],*it);
		stk[++top]=*it;
		res=(res+fpow(2,*it))%mod;
		ans=(ans+res)%mod;
	}
	return ans;
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=q; ++i){
		int op=nxi();
		if(op==1){
			int x=nxi(),y=nxi();
			mseq[i]=(mod_seq){x,m-y};
			D::insert(m-y);
		}
	}
	D::build();
	for(int i=1; i<=q; ++i){
		if(mseq[i].x) flip(mseq[i].x,mseq[i].y);
		else printf("%d\n",solve());
	}
	return 0;
}
