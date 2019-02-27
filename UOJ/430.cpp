#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
const int S=320;
int n;
int lf[N],tm[N],val[N];
lint s_val[N],dp[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}
template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline bool st_left(const lint x1,const lint y1,const lint x2,const lint y2){
	//vec 1 on the right side of vec2
	return (__int128)x1*y2-(__int128)y1*x2>=0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace B{
	int tag[S],b_mx[S],pt[S],idx[S][S];
	int bel[N],xtm[N];
	int upd_cnt,upd_que[N];

	inline void init(){
		bel[0]=1;
		for(int i=1; i<=n; ++i){
			bel[i]=i/S+1;
		}
	}

	inline void build_blk(const int p){
		pt[p]=0;
		for(int i=p*S-1,nxt; i>=(p-1)*S; i=nxt){
			int res=i;
			for(int j=nxt=i; j>=(p-1)*S&&xtm[j]==xtm[i]; nxt=--j){
				if(dp[j]<dp[res]) res=j;
			}
			for(; pt[p]>1; --pt[p]){
				int bef=idx[p][pt[p]-1];
				int bbef=idx[p][pt[p]-2];
				const lint bef_x=-xtm[bef]+xtm[bbef];
				const lint bef_y=dp[bef]-dp[bbef];
				const lint cur_x=-xtm[res]+xtm[bbef];
				const lint cur_y=dp[res]-dp[bbef];
				if(!st_left(bef_x,bef_y,cur_x,cur_y)) break;
			}
			if(pt[p]&&xtm[idx[p][pt[p]-1]]<=xtm[res]&&dp[idx[p][pt[p]-1]]<=dp[res]){
				continue;
			}
			idx[p][pt[p]++]=res;
		}
	}

	inline void upd_xtm(const int l,const int r,const int delta){
		if(bel[r]==bel[l]){
			for(int i=l; i<=r; ++i){
				xtm[i]+=delta;
			}
		}
		else{
			for(int i=r; bel[i]==bel[r]; --i){
				xtm[i]+=delta;
			}
			for(int i=bel[l]+1; i<bel[r]; ++i){
				tag[i]+=delta;
			}
			for(int i=l; bel[i]==bel[l]; ++i){
				xtm[i]+=delta;
			}
		}
		upd_que[++upd_cnt]=bel[r];
		upd_que[++upd_cnt]=bel[l];
	}

	inline void upd_blk(int limit){
		for(int i=1; i<=upd_cnt; ++i){
			if(upd_que[i]>limit) continue;
			if(upd_que[i]!=upd_que[i-1]){
				build_blk(upd_que[i]);
			}
		}
	}

	inline lint ask_blk(const int p,const lint v){
		int l=0,r=pt[p]-1,m1,m2;
		int d1,d2;
		while(l<r-1){
			m1=(l+l+r)/3,d1=idx[p][m1];
			m2=(l+r+r)/3,d2=idx[p][m2];
			if(dp[d1]+xtm[d1]*v>dp[d2]+xtm[d2]*v) l=m1+1;
			else r=m2;
		}
		d1=idx[p][l];
		d2=idx[p][r];
		return tag[p]*v+std::min(dp[d1]+xtm[d1]*v,dp[d2]+xtm[d2]*v);
	}

	inline lint ask(const int l,const int r,int mx,const lint v){
		lint ans=2e18;
		if(r-l<=S){
			for(int i=r; i>=l; --i){
				apn(ans,dp[i]+mx*v);
				apx(mx,tm[i]);
			}
			return ans;
		}
		for(int i=r; bel[i]==bel[r]; --i){
			apn(ans,dp[i]+mx*v);
			apx(mx,tm[i]);
		}
		for(int i=bel[r]-1; i>bel[l]; --i){
			apn(ans,ask_blk(i,v));
			apx(mx,b_mx[i]);
		}
		for(int i=bel[l]*S-1; i>=l; --i){
			apn(ans,dp[i]+mx*v);
			apx(mx,tm[i]);
		}
		return ans;
	}
}

inline void solve(){
	static int d_stk[N];//decresing stack for tm[i]
	int top=0;
	for(int i=1; i<=n; ++i){
		B::upd_cnt=0;
		B::upd_xtm(i-1,i-1,tm[i]);
		for(int t=d_stk[top]; top&&tm[t]<tm[i]; t=d_stk[--top]){
			B::upd_xtm(d_stk[top-1],d_stk[top]-1,tm[i]-tm[t]);
		}
		while(top&&tm[d_stk[top]]==tm[i]){
			--top;
		}
		d_stk[++top]=i;
		B::upd_blk(B::bel[i]-1);
		dp[i]=B::ask(lf[i],i-1,tm[i],s_val[i+1]);
		if(i%S==S-1){
			B::build_blk(B::bel[i]);
		}
	}
}

int main(){
	n=nxi();
	B::init();
	for(int i=1; i<=n; ++i){
		lf[i]=nxi();
		tm[i]=nxi();
		apx(B::b_mx[B::bel[i]],tm[i]);
		val[i]=nxi();
	}
	for(int i=n; i; --i){
		s_val[i]=val[i]+s_val[i+1];
	}
	solve();
	printf("%lld\n",dp[n]);
	return 0;
}
