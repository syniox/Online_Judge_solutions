#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=50005;
const int C=305;
int n,q,slen;
lint dp[N],sum[(int)1e6];
std::vector <int> buk[C];

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}

	template <class T>
		inline void apx(T &x,const T y){
			x<y?x=y:0;
		}

	template <class T>
		inline void apn(T &x,const T y){
			x>y?x=y:0;
		}
}
using namespace utils;

void solve(const lint *org,lint *res,const int l,const int r,
		const int ql,const int qr){
	const int mid=(l+r)>>1;
	assert(mid>0);
	int lim_l=std::max(mid-slen,ql),lim_r=std::min(mid,qr);
	int pnt=lim_l;
	for(int i=lim_l+1; i<=lim_r; ++i){
		if(org[i]+sum[mid-i]>org[pnt]+sum[mid-pnt]) pnt=i;
	}
	res[mid]=org[pnt]+sum[mid-pnt];
	if(l<mid) solve(org,res,l,mid-1,ql,pnt);
	if(r>mid) solve(org,res,mid+1,r,pnt,qr);
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		int c=nxi(),v=nxi();
		buk[c].push_back(v);
	}
	for(int i=1; i<std::min(q+1,C); ++i){
		static lint org[N],res[N];
		if(buk[i].empty()) continue;
		std::sort(buk[i].begin(),buk[i].end());
		slen=buk[i].size();
		for(int j=1; j<=slen; ++j){
			sum[j]=sum[j-1]+buk[i][slen-j];
		}
		for(int j=0; j<i; ++j){
			int lim=(q-j)/i+1;
			for(int k=1; k<=lim; ++k){
				org[k]=dp[j+i*(k-1)];
			}
			solve(org,res,1,lim,1,lim);
			for(int k=1; k<=lim; ++k){
				dp[j+i*(k-1)]=res[k];
			}
		}
	}
	for(int i=1; i<=q; ++i){
		printf("%lld ",dp[i]);
	}
	puts("");
	return 0;
}
