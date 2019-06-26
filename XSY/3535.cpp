#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e6+5;
const int K=1005;
int n,q;
lint dp[N];
struct _str{
	static int cp_b;
	int c;
	lint *v;
	friend bool operator < (const _str &a,const _str &b){
		if(a.c<cp_b) return 0;
		if(b.c<cp_b) return 1;
		return a.v[cp_b]<b.v[cp_b];
	}
}str[N];
int _str::cp_b;

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

namespace M{
	lint *v1,*v2,buk[K];
	int r1,l2,r2;

	void solve(const int ql,const int qr,const int sl,const int sr){
		const int mid=(ql+qr)>>1,limr=std::min(sr,mid-l2);
		int dec=-1;
		lint ans=1e15;
		for(int i=std::max(mid-r2,sl); i<=limr; ++i){
			if(v1[i]+v2[mid-i]<ans){
				dec=i;
				ans=v1[i]+v2[mid-i];
			}
		}
		assert(~dec);
		buk[mid]=ans;
		if(ql<mid) solve(ql,mid-1,sl,dec);
		if(qr>mid) solve(mid+1,qr,dec,sr);
	}

	lint* merge(lint *v1,const int r1,lint *v2,const int l2,const int r2){
		M::v1=v1,M::v2=v2;
		M::r1=r1,M::r2=r2;
		const int lim=std::min(q,r1+r2);
		memset(buk,10,l2*sizeof(buk[0]));
		solve(l2,lim,0,r1);
		return buk;
	}
}

int main(){
	memset(dp,10,sizeof(dp));
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		str[i].c=nxi();
		str[i].v=new lint[str[i].c+1];
		for(int j=0; j<=str[i].c; ++j){
			str[i].v[j]=nxi();
		}
		for(int j=1; j<=str[i].c; ++j){
			str[i].v[j]+=str[i].v[j-1];
		}
	}
	dp[0]=0;
	for(int i=1,j=1,s=0; i<=q&&j<=n; ++i){
		const int len=(q+i-1)/i;
		_str::cp_b=i;
		//排序总元素个数为每次商店参与个数之和即m之和,O(mlogn)
		std::sort(str+j,str+n+1);
		while(str[n].c<i) --n;
		const int lim=std::min(j+len-1,n);
		for(int k=j; k<=lim; ++k){
			if(str[k].c<i){
				j=n+1;
				break;
			}
			const lint *res=M::merge(dp,s,str[k].v,i,str[k].c);
			s=std::min(q,s+str[k].c);
			for(int l=1; l<=s; ++l){
				apn(dp[l],res[l]);
			}
		}
		j=lim+1;
	}
	for(int i=1; i<=q; ++i){
		printf("%lld ",dp[i]);
	}
	puts("");
	return 0;
}
