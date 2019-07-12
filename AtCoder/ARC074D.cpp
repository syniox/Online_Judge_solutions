#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
typedef long long lint;
const int N=1e5+5;
int n,val[N*3];
lint psum[N],ssum[N];

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

int main(){
	std::priority_queue <int> pq;
	n=nxi();
	for(int i=1; i<=n*3; ++i){
		val[i]=nxi();
	}
	{
		lint sum=0;
		for(int i=1; i<=n; ++i){
			sum+=val[i];
			pq.push(-val[i]);
		}
		psum[0]=sum;
		for(int i=1; i<=n; ++i){
			pq.push(-val[n+i]);
			sum+=val[n+i]+pq.top();
			pq.pop();
			psum[i]=sum;
		}
	}
	while(!pq.empty()) pq.pop();
	{
		lint sum=0;
		for(int i=1; i<=n; ++i){
			sum+=val[n*2+i];
			pq.push(val[n*2+i]);
		}
		ssum[n+1]=sum;
		for(int i=n; i>=1; --i){
			pq.push(val[n+i]);
			sum+=val[n+i]-pq.top();
			pq.pop();
			ssum[i]=sum;
		}
	}
	lint ans=-1e15;
	for(int i=0; i<=n; ++i){
		apx(ans,psum[i]-ssum[i+1]);
	}
	printf("%lld\n",ans);
	return 0;
}
