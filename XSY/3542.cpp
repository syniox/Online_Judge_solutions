#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
typedef long long lint;
const int N=2e5+5;
int n,suf[N],pre[N];
lint val[N],ans[N];
bool invld[N];
struct data{
	int id;
	lint v;
	friend bool operator < (const data &a,const data &b){
		return a.v<b.v;
	}
};

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
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

void rm(const int x){
	suf[pre[x]]=suf[x];
	pre[suf[x]]=pre[x];
}

int main(){
	std::priority_queue <data> pq;
	n=nxi();
	for(int i=1; i<=n; ++i){
		pre[i]=i-1;
		suf[i]=i+1;
	}
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		pq.push((data){i,val[i]});
	}
	for(int i=1; i<=(n+1)>>1; ++i){
		while(val[pq.top().id]!=pq.top().v) pq.pop();
		const int p=pq.top().id;
		pq.pop();
		ans[i]=ans[i-1]+val[p];
		val[p]=val[pre[p]]+val[suf[p]]-val[p];
		val[pre[p]]=val[suf[p]]=-1e16;
		if(pre[p]>=1&&suf[p]<=n){
			pq.push((data){p,val[p]});
			rm(pre[p]);
			rm(suf[p]);
		}
		else if(pre[p]>=1) suf[pre[p]]=n+1;
		else if(suf[p]<=n) pre[suf[p]]=0;
	}
	for(int q=nxi(); q; --q){
		printf("%lld\n",ans[nxi()]);
	}
	return 0;
}
