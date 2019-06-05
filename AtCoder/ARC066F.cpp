#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=3e5+5;
int n,val[N];
lint predp[N],sufdp[N],req[N],pres[N],sufs[N];//suf反向编号
struct vec{
	lint x,y;
	friend vec operator - (const vec &a,const vec &b){
		return (vec){a.x-b.x,a.y-b.y};
	}
};

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
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

inline lint crs(const vec &a,const vec &b){
	return a.x*b.y-a.y*b.x;
}

inline lint qans(lint *dp,lint *sum,int fr,int tgt){
	return dp[fr]+((lint)(tgt-fr)*(tgt-fr+1)>>1)-(sum[tgt]-sum[fr]);
}

int get_dp(lint *dp){
	static vec stk[N];
	static lint sum[N];
	int top=0;
	for(int i=1; i<=n; ++i){
		sum[i]=sum[i-1]+val[i];
	}
	dp[0]=0;
	stk[++top]=(vec){0,0};
	for(int i=1; i<=n; ++i){
		while(top>1&&qans(dp,sum,stk[top].x,i)<=qans(dp,sum,stk[top-1].x,i)){
			--top;
		}
		dp[i]=std::max(dp[i-1],qans(dp,sum,stk[top].x,i));
		vec cur=(vec){i,dp[i]+(((lint)i*i-i)>>1)+sum[i]};
		while(top>1&&crs(stk[top]-stk[top-1],cur-stk[top-1])>=0){
			--top;
		}
		stk[++top]=cur;
	}
	return dp[n];
}

void get_req(lint *dp,lint *sum,lint *res,int l,int mid,int r){
	static vec stk[N];
	int top=0;
	for(int i=l-1; i<mid; ++i){
		vec cur=(vec){i,dp[i]+(((lint)i*i-i)>>1)+sum[i]};
		while(top>1&&crs(stk[top]-stk[top-1],cur-stk[top-1])>=0){
			--top;
		}
		stk[++top]=cur;
	}
	for(int i=mid+1; i<=r; ++i){
		while(top>1&&qans(dp,sum,stk[top].x,i)<=qans(dp,sum,stk[top-1].x,i)){
			--top;
		}
		res[i-mid]=qans(dp,sum,stk[top].x,i);
	}
}

void div_req(const int l,const int r){
	static lint res[N];
	const int mid=(l+r)>>1;
	if(l==r){
		apx(req[l],predp[l-1]+sufdp[n-l]+1-val[l]);
		return;
	}
	get_req(predp,pres,res,l,mid,r);
	lint suf=-1e15;
	for(int i=r; i>mid; --i){
		apx(suf,res[i-mid]+sufdp[n-i]);
		apx(req[i],suf);
	}
	get_req(sufdp,sufs,res,n-r+1,n-(mid+1)+1,n-l+1);
	lint pre=-1e15;
	for(int i=l; i<=mid; ++i){
		apx(pre,res[mid-i+1]+predp[i-1]);
		apx(req[i],pre);
	}
	div_req(l,mid);
	div_req(mid+1,r);
}

int main(){
	memset(req,-10,sizeof(req));
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		pres[i]=pres[i-1]+val[i];
	}
	for(int i=n; i>=1; --i){
		sufs[i]=sufs[i+1]+val[i];
	}
	std::reverse(sufs+1,sufs+n+1);
	get_dp(predp);
	std::reverse(val+1,val+n+1);
	get_dp(sufdp);
	std::reverse(val+1,val+n+1);
	div_req(1,n);
	for(int q=nxi(); q; --q){
		int pos=nxi(),v=nxi();
		lint res=std::max(req[pos]+val[pos]-v,predp[pos-1]+sufdp[n-pos]);
		printf("%lld\n",res);
	}
	return 0;
}
