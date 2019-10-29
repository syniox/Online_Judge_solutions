#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,m,val[N];
struct objs{
	int w,v;
	friend bool operator < (const objs &a,const objs &b){
		return a.w==b.w?a.v<b.v:a.w<b.w;
	}
}obj[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int main(){
	for(int T=nxi(); T; --T){
		m=nxi();
		for(int i=1; i<=m; ++i){
			obj[i].w=nxi();
			obj[i].v=nxi();
		}
		n=nxi();
		for(int i=1; i<=n; ++i){
			val[i]=nxi();
		}
		std::sort(obj+1,obj+m+1);
		std::sort(val+1,val+n+1);
		int top=0;
		for(int i=m; i>=1; --i){
			static int buk[N];
			int l=1,r=top+1,mid;
			while(l<r){//hack
				mid=(l+r)>>1;
				if(buk[mid]<obj[i].v) r=mid;
				else l=mid+1;
			}
			if(val[n-l+1]>=obj[i].w){
				buk[l]=obj[i].v;
				if(l==top+1) ++top;
			}
		}
		printf("%d\n",top);
	}
	return 0;
}
