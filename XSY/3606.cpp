#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <queue>
typedef long long lint;
const int N=1e5+5;
int n,qa,qb,qc;
lint ansx[N],ansy[N];
struct data{
	int x,y,z;
}dt[N];

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

bool cmp_xy(const data &a,const data &b){
	return (a.y-a.x)<(b.y-b.x);
}

void solve(){
	static std::priority_queue <int> pq;
	lint sum=0;
	for(int i=1; i<=qa; ++i){
		sum+=dt[i].x;
		pq.push(dt[i].z-dt[i].x);
	}
	ansx[qa]=sum;
	for(int i=qa+1; i<=n-qb; ++i){
		sum+=dt[i].x;
		pq.push(dt[i].z-dt[i].x);
		sum+=pq.top();
		pq.pop();
		ansx[i]=sum;
	}
	while(!pq.empty()) pq.pop();
	sum=0;
	for(int i=n; i>n-qb; --i){
		sum+=dt[i].y;
		pq.push(dt[i].z-dt[i].y);
	}
	ansy[n-qb+1]=sum;
	for(int i=n-qb; i>qa; --i){
		sum+=dt[i].y;
		pq.push(dt[i].z-dt[i].y);
		sum+=pq.top();
		pq.pop();
		ansy[i]=sum;
	}
}

int main(){
	qa=nxi(),qb=nxi(),qc=nxi();
	n=qa+qb+qc;
	for(int i=1; i<=n; ++i){
		dt[i].x=nxi(),dt[i].y=nxi(),dt[i].z=nxi();
	}
	std::sort(dt+1,dt+n+1,cmp_xy);
	solve();
	lint ans=0;
	for(int i=qa; i<=n-qb; ++i){
		apx(ans,ansx[i]+ansy[i+1]);
	}
	printf("%lld\n",ans);
	return 0;
}
