#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n;

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace B{
	lint tick,tm[N],tr[N];
	inline void upd(const int x){
		if(tm[x]<tick) tm[x]=tick,tr[x]=0;
	}
	inline void mod(int x,const int v){
		for(;x<=n;x+=x&-x) upd(x),tr[x]+=v;
	}
	inline lint ask(int x){
		int ans=0;
		for(;x;x-=x&-x) upd(x),ans+=tr[x];
		return ans;
	}
}

inline lint solve(const int qa[],const int qb[]){
	static int buk[N],que[N];
	++B::tick;
	lint ans=0,cnt;
	for(int i=1;i<=n;++i) buk[qa[i]]=i;
	for(int i=1;i<=n;++i) que[i]=buk[qb[i]];
	for(int i=1;i<=n;++i){
		ans+=B::ask(n)-B::ask(que[i]);
		B::mod(que[i],1);
	}
	cnt=ans;
	for(int i=n;i>1;--i){
		apn(ans,cnt+=que[i]-1-(n-que[i]));
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	static int qa[N],qb[N];
	n=nxi();
	for(int i=1;i<=n;++i) qa[i]=nxi();
	for(int i=1;i<=n;++i) qb[i]=nxi();
	printf("%lld\n",std::min(solve(qa,qb),solve(qb,qa)));
	return 0;
}
