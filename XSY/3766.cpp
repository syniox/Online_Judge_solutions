#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=1e6+5;
int n,ql,qr,val[N],sum[N],rk[N],stot[N<<1];
int dp[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	inline char getc(){
		static char buf[20000],*h,*t;
		if(h==t){
			t=(h=buf)+fread(buf,1,20000,stdin);
			if(h==t) return EOF;
		}
		return *h++;
	}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getc())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getc());
			while(x=x*10-48+c,(c=getc())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

void getrk(){
	static int tmp[N<<1];
	for(int i=0; i<=n; ++i){
		++stot[sum[i]+N];
	}
	for(int i=N-n; i<=N+n; ++i){
		stot[i]+=stot[i-1];
	}
	memcpy(tmp,stot,sizeof(tmp));
	for(int i=n; i>=0; --i){
		rk[i]=tmp[sum[i]+N]--;
	}
}

namespace T{
#define mid ((l+r)>>1)
	int x,y,v,tr[N<<1];
	struct _init{
		_init(){ memset(tr,-10,sizeof(tr)); }
	}_init_;

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}
	inline void upd(const int l,const int r){
		tr[idx(l,r)]=max(tr[idx(l,mid)],tr[idx(mid+1,r)]);
	}

	int qans_t(const int l,const int r){
		if(r<=x) return tr[idx(l,r)]+1;
		if(l>x&&r<=y) return tr[idx(l,r)];
		if(l>y) return tr[idx(l,r)]-1;
		return max(qans_t(l,mid),qans_t(mid+1,r));
	}
	void set_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=v;
			return;
		}
		if(x<=mid) set_t(l,mid);
		else set_t(mid+1,r);
		upd(l,r);
	}

	inline void set(const int x,const int v){
		T::x=x,T::v=v;
		set_t(1,n+1);
	}
	inline int qans(const int x,const int y){
		T::x=x,T::y=y;
		return qans_t(1,n+1);
	}
#undef mid
}

int main(){
	memset(dp,-10,sizeof(dp));
	n=ni,ql=ni,qr=ni;
	for(int i=1; i<=n; ++i){
		val[i]=ni;
		sum[i]=sum[i-1]+val[i];
	}
	getrk();
	dp[0]=0;
	for(int i=1; i<=n; ++i){
		if(i>=ql) T::set(rk[i-ql],dp[i-ql]);
		if(i>qr) T::set(rk[i-qr-1],-1e9);
		dp[i]=T::qans(stot[sum[i]+N-1],stot[sum[i]+N]);
	}
	if(dp[n]<-n) puts("Impossible");
	else printf("%d\n",dp[n]);
	return 0;
}
