#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2005;
int n,m,val[N],dp[N];
struct vec{
	int x,y;
	friend vec operator - (const vec &a,const vec &b){
		return (vec){a.x-b.x,a.y-b.y};
	}
	friend lint crs(const vec &a,const vec &b){
		return (lint)a.x*b.y-(lint)a.y*b.x;
	}
};

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

inline lint getans(const vec &p,const int x){
	return (lint)p.x*x-p.y;
}

int main(){
	for(int T=nxi(); T; --T){
		static vec que[N];
		n=nxi(),m=nxi();
		memset(dp,0,(n+1)*sizeof(dp[0]));
		for(int i=1; i<=n; ++i){
			val[i]=nxi();
		}
		std::sort(val+1,val+n+1);
		for(int f=1; f<=m; ++f){
			int top=0;
			for(int lst=dp[f-1],i=f; i<=n; ++i){
				vec tmp=(vec){val[i],(i-1)*val[i]-lst};
				for(; top>1&&crs(tmp-que[top-1],que[top]-que[top-1])<=0; --top);
				que[++top]=tmp;
				while(top>1&&getans(que[top],i)>getans(que[top-1],i)){
					--top;
				}
				lst=dp[i];
				dp[i]=(int)getans(que[top],i);
			}
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
