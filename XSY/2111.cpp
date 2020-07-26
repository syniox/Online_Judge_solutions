#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
typedef unsigned long long ull;
using namespace std;
const int N=1e5+5;
const int S=320;
int n,val[N],rngl[N],rngr[N],bel[N];
int rwgt[S][N];
ull rans[S],bsum[S],psum[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

ull qsum(const int l,const int r){
	ull ans=0,prev_l=(bel[l]==bel[l-1]?psum[l-1]:0);
	if(bel[l]==bel[r]) return psum[r]-prev_l;
	ans=bsum[bel[r]-1]-bsum[bel[l]];
	return ans+psum[r]+psum[bel[l]*S]-prev_l;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		bel[i]=(i-1)/S+1;
	}
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		psum[i]=(bel[i]==bel[i-1]?psum[i-1]:0)+val[i];
		if(bel[i]!=bel[i+1]) bsum[bel[i]]=bsum[bel[i]-1]+psum[i];
	}
	for(int i=1; i<=n; ++i){
		rngl[i]=nxi(),rngr[i]=nxi();
		++rwgt[bel[i]][rngl[i]];
		--rwgt[bel[i]][rngr[i]+1];
	}
	for(int i=1; i<=bel[n]; ++i){
		for(int j=1; j<=n; ++j){
			rwgt[i][j]+=rwgt[i][j-1];
			rans[i]+=(ull)val[j]*rwgt[i][j];
		}
	}
	for(int q=nxi(); q--; ){
		const int op=nxi(),x=nxi(),y=nxi();
		if(op==1){
			const int dlt=y-val[x];
			for(int i=1; i<=bel[n]; ++i){
				rans[i]+=(ull)rwgt[i][x]*(y-val[x]);
			}
			for(int i=x; bel[i]==bel[x]; ++i){
				psum[i]+=dlt;
			}
			for(int i=bel[x]; i<=bel[n]; ++i){
				bsum[i]+=dlt;
			}
			val[x]=y;
		}else{
			ull ans=0;
			if(bel[x]==bel[y]){
				for(int i=x; i<=y; ++i){
					ans+=qsum(rngl[i],rngr[i]);
				}
			}else{
				for(int i=x; bel[i]==bel[x]; ++i){
					ans+=qsum(rngl[i],rngr[i]);
				}
				for(int i=y; bel[i]==bel[y]; --i){
					ans+=qsum(rngl[i],rngr[i]);
				}
				for(int i=bel[x]+1; i<bel[y]; ++i){
					ans+=rans[i];
				}
			}
			printf("%llu\n",ans);
		}
	}
	return 0;
}
