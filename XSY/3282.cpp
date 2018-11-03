#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n,hx[N];
struct data{
	int id,v;
	bool operator < (const data &b) const {
		return v==b.v?id<b.id:v<b.v;
	}
};

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	lint tr[N];

	inline void init(){
		memset(tr,0,sizeof(tr));
	}

	inline void mod(int x,const int v){
		for(++x;x<=n+1;x+=x&-x) tr[x]+=v;
	}
	inline lint ask(int x){
		lint ans=0;
		for(++x;x;x-=x&-x) ans+=tr[x];
		return ans;
	}
	inline lint ask(const int x,const int y){
		if(x>y) return 0;
		return ask(y)-ask(x-1);
	}
}

inline lint solve(const int mid,const int nl,const int xl){
	static int val[N];
	static data dt[N];
	lint ans=0;
	T::init();
	dt[0]=(data){0,0};
	for(int i=1;i<=n;++i){
		val[i]=val[i-1]+(hx[i]<=mid?1:-1);
		dt[i]=(data){i,val[i]};
	}
	std::sort(dt,dt+n+1);
	for(int i=0;i<=n;++i){
		if(dt[i].id>=nl){
			ans+=T::ask(std::max(dt[i].id-xl,0),dt[i].id-nl);
		}
		T::mod(dt[i].id,1);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	for(int i=nxi();i;--i){
		const int l1=nxi(),r1=nxi(),l2=nxi(),r2=nxi();
		printf("%lld\n",solve(r1,l2,r2)-solve(l1-1,l2,r2));
	}
	return 0;
}
