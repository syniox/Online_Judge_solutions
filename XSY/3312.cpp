#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <cstdlib>
typedef long long lint;
const int N=5005;
int n,q,p,val[N],ask_que[N],ask_cnt;
lint dp[N][2];

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N];
	lint tgt;
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x,const int f){
		const lint tval=val[x]*(lint)1e7;
		lint f0=0,f1=-tgt+tval,f2=-5e15;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==f) continue;
			dfs(y,x);
			apx(f2,f2+dp[y][0]);
			apx(f2,f1+dp[y][1]+tgt);
			apx(f1,f1+dp[y][0]);
			apx(f1,f0+dp[y][1]+tval);
			apx(f0,f0+dp[y][0]);
		}
		dp[x][1]=f1;
		dp[x][0]=std::max(f0,std::max(f1,f2));
	}
}

bool jdg(const lint tgt){
	return G::tgt=tgt,G::dfs(1,1),dp[1][0]>=tgt;
}

lint solve(lint lst_ans){
	lint l=lst_ans,r=n*5e11,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(jdg(mid)) l=mid;
		else r=mid-1;
	}
	return r;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	srand(19260817);
	n=nxi(),p=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	q=nxi();
	for(int i=1; i<=n; ++i){
		if(p-1-val[i]<q) ask_que[++ask_cnt]=p-1-val[i];
	}
	ask_que[++ask_cnt]=q;
	std::sort(ask_que+1,ask_que+ask_cnt+1);
	ask_cnt=std::unique(ask_que+1,ask_que+ask_cnt+1)-ask_que-1;
	std::random_shuffle(ask_que+1,ask_que+ask_cnt+1);
	lint ans=0;
	for(int i=1; i<=ask_cnt; ++i){
		for(int j=1; j<=n; ++j) val[j]=(val[j]+ask_que[i])%p;
		if(jdg(ans)) ans=solve(ans);
		for(int j=1; j<=n; ++j) val[j]=(val[j]-ask_que[i]+p)%p;
	}
	printf("%lf\n",(double)ans/1e7);
	return 0;
}
