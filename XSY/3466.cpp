#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=3e5+5;
const int S=550;
//const int N=90;
//const int S=10;
int n,ql[N],qr[N];
int hbit[N],maxl[N][19],minr[N][19];
lint dp[N];
struct _vec{
	lint x,y;
	friend _vec operator - (const _vec &a,const _vec &b){
		return (_vec){a.x-b.x,a.y-b.y};
	}
	friend lint crs(const _vec &a,const _vec &b){
		return a.x*b.y-a.y*b.x;
	}
};

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

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

inline void init(){
	for(int i=n; i; --i){
		maxl[i][0]=ql[i];
		minr[i][0]=qr[i];
		for(int j=1; j<19; ++j){
			maxl[i][j]=maxl[i][j-1];
			minr[i][j]=minr[i][j-1];
			if(i+(1<<(j-1))>n) break;
			apx(maxl[i][j],maxl[i+(1<<(j-1))][j-1]);
			apn(minr[i][j],minr[i+(1<<(j-1))][j-1]);
		}
	}
	for(int i=2; i<=n; ++i){
		hbit[i]=hbit[i>>1]+1;
	}
}

inline bool at_able(const int l,const int r){
	int tmp=hbit[r-l+1];
	int tmp_l=std::max(maxl[l][tmp],maxl[r-(1<<tmp)+1][tmp]);
	int tmp_r=std::min(minr[l][tmp],minr[r-(1<<tmp)+1][tmp]);
	return tmp_r>tmp_l;
}

inline lint get_dp(const int fr,const int to){
	return dp[fr]+((lint)(to-fr)*(to-fr-1)>>1);
}

namespace B{
	int bel[N],blk[S][S+5],top[S],pos[S];

	inline void init(){
		for(int i=1; i<=n; ++i) bel[i]=i/S;
	}

	inline void build(const int p,const int l,const int r){
		static _vec pnt[N];
		int top=0,*stk=blk[p];
		for(int i=l; i<=r; ++i){
			_vec cur=(_vec){i,dp[i]+((lint)i*(i+1)>>1)};
			pnt[i]=cur;
			while(top>1&&crs(pnt[stk[top]]-pnt[stk[top-1]],cur-pnt[stk[top]])>=0){
				--top;
			}
			stk[++top]=i;
			assert(top<S+5);
		}
		pos[p]=1;
		B::top[p]=top;
	}

	inline lint ask_b(const int p,const int x){
		while(pos[p]<top[p]&&get_dp(blk[p][pos[p]],x)<=get_dp(blk[p][pos[p]+1],x)){
			++pos[p];
		}
		return get_dp(blk[p][pos[p]],x);
	}

	inline lint ask(const int x,const int l,const int r){
		lint ans=0;
		if(bel[l]==bel[r]){
			for(int i=l; i<=r; ++i){
				apx(ans,get_dp(i,x));
			}
			return ans;
		}
		for(int i=l; bel[i]==bel[l]; ++i){
			apx(ans,get_dp(i,x));
		}
		for(int i=r; bel[i]==bel[r]; --i){
			apx(ans,get_dp(i,x));
		}
		for(int i=bel[l]+1; i<bel[r]; ++i){
			apx(ans,ask_b(i,x));
		}
		return ans;
	}
}

void work(){
	for(int vld_pos=1,i=1; i<=n; ++i){
		if(i%S==0) B::build(i/S-1,i-S,i-1);
		while(vld_pos<=i&&!at_able(vld_pos,i)) ++vld_pos;
		if(vld_pos<=i) dp[i]=B::ask(i,vld_pos-1,i-1);
		else dp[i]=dp[i-1];
		if(vld_pos>0) apx(dp[i],dp[vld_pos-1]);
	}
	/*
	for(int i=1; i<=n; ++i){
		printf("%lld ",dp[i]);
	}
	puts("");
	*/
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("b.in","r",stdin);
	//freopen("d.in","r",stdin);
#endif
	n=nxi();
	for(int i=1; i<=n; ++i){
		ql[i]=nxi(),qr[i]=nxi();
	}
	init();
	B::init();
	work();
	printf("%lld\n",dp[n]);
	return 0;
}
