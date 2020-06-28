#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2005;
int n,m,q,val[N],dv[N],dcnt,dlim;

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

int getans(){
	static int buk[N];
	int cnt=0;
	for(int j,i=1; i<=n; i=j+1){
		for(j=i; val[j]>=dlim; ++j);
		if(j-i<m) continue;
		std::nth_element(val+i,val+j-m,val+j);
		for(int k=i; k+m<=j; ++k){
			buk[++cnt]=val[k];
		}
	}
	std::sort(buk+1,buk+cnt+1);
	return cnt<q?1e9:buk[q]-buk[1];
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		dv[i]=val[i]=nxi();
	}
	std::sort(dv+1,dv+n+1);
	dcnt=std::unique(dv+1,dv+n+1)-dv-1;
	int ans=1e9;
	for(int i=dcnt; i>=1; --i){
		dlim=dv[i];
		apn(ans,getans());
	}
	printf("%d\n",ans);
	return 0;
}
