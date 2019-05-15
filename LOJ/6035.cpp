#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
typedef long long lint;
const int N=1e5+5;
const int Q=1e6+5;
int n,m,q;
lint v1[Q],v2[Q];
struct _pair{
	lint x,y;
	friend bool operator < (const _pair &a,const _pair &b){
		return a.y>b.y;
	}
};

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

void get_val(const int l,lint *val){
	std::priority_queue <_pair> pq;
	while(!pq.empty()) pq.pop();
	for(int i=1; i<=l; ++i){
		const int x=nxi();
		pq.push((_pair){x,x});
	}
	for(int i=1; i<=q; ++i){
		_pair cur=pq.top();
		pq.pop();
		val[i]=cur.y;
		pq.push((_pair){cur.x,cur.y+cur.x});
	}
}

int main(){
	q=nxi(),n=nxi(),m=nxi();
	get_val(n,v1);
	get_val(m,v2);
	lint ans=0;
	for(int i=1; i<=q; ++i){
		apx(ans,(lint)v1[i]+v2[q-i+1]);
	}
	printf("%lld\n",ans);
	return 0;
}
