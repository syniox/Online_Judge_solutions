#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,m,wgt[N],val[N];
lint dp[N][500];
bool ol;

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

lint qry(const lint *d1,const lint *d2,const int l,const int r){
	static lint v1[1000],v2[1000],que[1000];
	memcpy(v1,d1,m*sizeof(v1[0]));
	memcpy(v2,d2,m*sizeof(v2[0]));
	memcpy(v1+m,d1,m*sizeof(v1[0]));
	memcpy(v2+m,d2,m*sizeof(v2[0]));
	int hd=0,tl=0;
	lint ans=-1e15;
	for(int i=r+m; i>=0; --i){
		while(hd<tl&&que[hd]<l+m-i) ++hd;
		while(hd<tl&&v1[que[tl-1]]<v1[r+m-i]) --tl;
		que[tl++]=r+m-i;
		apx(ans,v1[que[hd]]+v2[i]);
	}
	return ans==-1e15?-1:ans;
}

lint qry1(const lint *d,const int l,const int r){
	lint ans=-1e15;
	for(int i=l; i<=r; ++i){
		apx(ans,d[i]);
	}
	return ans==-1e15?-1:ans;
}

inline void init(lint *d){
	memset(d,-10,m*sizeof(d[0]));
	d[0]=0;
}

int main(){
	//[hd,pt),[pt,tl]
	n=nxi(),m=nxi(),ol=nxi();
	init(dp[1]);
	lint ans=0;
	for(int i=1,hd=1,tl=0,pt=1; i<=n; ++i,ans=(ans%((int)1e9+7))*ol){
		static lint fp[500];
		const int op=nxi();
		if(op==1){
			const int w=nxi()^ans,v=nxi()^ans;
			++tl;
			wgt[tl]=w,val[tl]=v;
			for(int j=0; j<m; ++j){
				fp[(j+w)%m]=dp[pt][j]+val[tl];
			}
			for(int j=0; j<m; ++j){
				apx(dp[pt][j],fp[j]);
			}
		}
		else if(++hd>=pt){
			pt=tl+1;
			init(dp[pt]);
			init(dp[tl]);
			dp[tl][wgt[tl]]=val[tl];
			for(int j=tl-1; j>=hd; --j){
				init(dp[j]);
				for(int k=0; k<m; ++k){
					dp[j][k]=std::max(dp[j+1][k],dp[j+1][(k-wgt[j]+m)%m]+val[j]);
				}
			}
		}
		const int l=nxi()^ans,r=nxi()^ans;
		lint res;
		if(hd==pt) printf("%lld\n",res=qry1(dp[pt],l,r));
		else if(pt>tl) printf("%lld\n",res=qry1(dp[hd],l,r));
		else printf("%lld\n",res=qry(dp[hd],dp[pt],l,r));
		if(res!=-1) ans=res;
	}
	return 0;
}
