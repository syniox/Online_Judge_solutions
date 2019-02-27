#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e2+5;
const int S=10;
int n,lf[N],val[N],cos[N];
lint dp[N],s_cos[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}
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

namespace B{
	int bel[N],xnx[N],b_mx[S];
	int tl[S],hd[S];
	lint n_dp[N];
	class _vec{
		public:
			lint x,y;//x->xnx,y->dp
			friend _vec operator - (const _vec &a,const _vec &b){
				return (_vec){a.x-b.x,a.y-b.y};
			}
	}idx[S][S+5];
	//xnx[i]: current max after i (not all are satisfied)

	inline void init(){
		for(int i=0; i<=n; ++i){
			bel[i]=i/S+1;
		}
	}

	inline bool st_left(const _vec &a,const _vec &b){
		return (__int128)a.x*b.y-(__int128)a.y*b.x>0;
	}

	inline void build_g(const int p){
		for(int i=p*S-1,mx=0; i>=(p-1)*S; --i){
			if(i==p*S-1) n_dp[i]=dp[i];
			else n_dp[i]=std::min(dp[i],n_dp[i+1]);
			xnx[i]=mx;
			_vec cur=(_vec){-xnx[i],dp[i]};
			for(_vec bef=idx[p][tl[p]]; tl[p]>1; bef=idx[p][--tl[p]]){
				_vec bbef=idx[p][tl[p]-1];
				if(st_left(cur-bef,bef-bbef)) break;
			}
			apx(mx,val[i]);
			b_mx[p]=mx;
			if(tl[p]&&-idx[p][tl[p]].x<=xnx[i]&&idx[p][tl[p]].y<=dp[i]){
				continue;
			}
			idx[p][++tl[p]]=cur;
		}
		hd[p]=1;
	}

	inline void ap_max(const int p,const int v){
		if(-idx[p][hd[p]].x>v) return;
		while(hd[p]<tl[p]&&-idx[p][hd[p]].x<=v) ++hd[p];
		int l=(p-1)*S,r=p*S-1,mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(xnx[mid]<=v) r=mid;
			else l=mid+1;
		}
		idx[p][--hd[p]]=(_vec){-v,n_dp[l]};
	}

	inline lint qry_blk(const int p,const lint v){
		static int lst_pos[N];
		apx(lst_pos[p],hd[p]);
		int dec=lst_pos[p];
		for(_vec tp1,tp2; dec<tl[p]; ++dec){
			tp1=idx[p][dec];
			tp2=idx[p][dec+1];
			if(tp1.y-tp1.x*v<tp2.y-tp2.x*v) break;
		}
		lst_pos[p]=dec;
		return idx[p][dec].y-idx[p][dec].x*v;
	}

	inline void solve(){
		init();
		for(int i=1; i<=n; ++i){

			for(int j=1; j<bel[i]; ++j){
				ap_max(j,val[i]);
			}
			dp[i]=2e18;
			if(i-lf[i]<=S){
				for(int mx=val[i],j=i-1; j>=lf[i]; --j){
					apx(mx,val[j+1]);
					apn(dp[i],dp[j]+(lint)mx*s_cos[i+1]);
				}
			}
			else{
				int mx=val[i];
				for(int j=i-1; bel[j]==bel[i]; --j){
					apx(mx,val[j+1]);
					apn(dp[i],dp[j]+(lint)mx*s_cos[i+1]);
				}
				apx(mx,val[(bel[i]-1)*S]);
				for(int j=bel[i]-1; j>bel[lf[i]]; --j){
					apx(mx,b_mx[j]);
					apn(dp[i],qry_blk(j,s_cos[i+1]));
				}
				for(int j=bel[lf[i]]*S; j>=lf[i]; --j){
					apx(mx,val[j+1]);
					apn(dp[i],dp[j]+(lint)mx*s_cos[i+1]);
				}
			}
			printf("%lld ",dp[i]);
			//fprintf(stderr,"%lld ",dp[i]);
			if(i%S==S-1) build_g(bel[i]);
		}
		//we don't need to build bel[n] at this case
		/*
		dp[n]=2e18;
		for(int i=n-1; i>=0&&i>=lf[n]; --i){
			apn(dp[n],dp[i]);
		}
		*/
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		lf[i]=nxi(),val[i]=nxi(),cos[i]=nxi();
	}
	for(int i=n; i; --i){
		s_cos[i]=s_cos[i+1]+cos[i];
	}
	B::solve();
	printf("%lld\n",dp[n]);
	return 0;
}
