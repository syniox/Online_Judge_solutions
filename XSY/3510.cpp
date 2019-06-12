#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,m,posa,posb,va[N],vb[N];

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

bool jdg(const int t){
	//返回先手是否必胜（答案是否<t）
	static int cw[N],rw[N];
	lint sum=0,ans1=0,ans2=0;
	rw[0]=m,cw[0]=n;
	for(int i=1; i<=n; ++i){
		rw[i]=rw[i-1];
		while(rw[i]&&va[i]+vb[rw[i]]>=t) --rw[i];
		sum+=m-rw[i];
	}
	for(int i=1; i<=m; ++i){
		cw[i]=cw[i-1];
		while(cw[i]&&va[cw[i]]+vb[i]>=t) --cw[i];
	}
	for(int i=0,j=0; i<=n; ++i){
		sum+=std::min(j,rw[i]);
		sum-=std::min(m-rw[i],m-j);
		for(; j<m&&cw[j+1]>=n-i; ++j){
			sum+=std::min(i,cw[j+1]);
			sum-=std::min(n-i,n-cw[j+1]);
		}
		apx(ans1,sum);
		apx(ans2,sum-(i<posa&&j<posb));
	}
	return ans1==ans2;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		va[i]=nxi();
	}
	for(int i=1; i<=m; ++i){
		vb[i]=nxi();
	}
	const int sa=va[1],sb=vb[1];
	std::sort(va+1,va+n+1);
	std::sort(vb+1,vb+m+1);
	posa=std::lower_bound(va+1,va+n+1,sa)-va;
	posb=std::lower_bound(vb+1,vb+m+1,sb)-vb;
	int l=2,r=sa+sb,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(jdg(mid)) r=mid-1;
		else l=mid;
	}
	printf("%d\n",l);
	return 0;
}
