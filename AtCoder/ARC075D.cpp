#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,qa,qb,val[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
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

bool jdg(const int t){
	lint used=0;
	for(int i=1; used<=t&&i<=n; ++i){
		if(val[i]>(lint)t*qb){
			used+=(val[i]-t*qb+qa-qb-1)/(qa-qb);
		}
	}
	return used<=t;
}

int main(){
	n=nxi(),qa=nxi(),qb=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	{
		int l=1,r=1e9,mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(jdg(mid)) r=mid;
			else l=mid+1;
		}
		printf("%d\n",l);
	}
	return 0;
}
