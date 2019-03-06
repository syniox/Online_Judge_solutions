#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1e6+5;
int n,tim[N];
lint val[N],dp[N];

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

inline bool cmp_tim(const int a,const int b){
	return a+tim[a]<b+tim[b];
}

namespace B{
	lint tr[N];
	inline void mod(int x,const lint v){
		for(; x<=n; x+=x&-x) apx(tr[x],v);
	}
	inline lint ask(int x){
		if(x<=0) return 0;
		lint ans=0;
		for(; x; x-=x&-x) apx(ans,tr[x]);
		return ans;
	}
}

int main(){
	static int idx[N];
	n=nxi();
	for(int i=1; i<=n; ++i){
		idx[i]=i;
		tim[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		val[i]=(lint)tim[i]*nxi();
	}
	std::sort(idx+1,idx+n+1,cmp_tim);
	dp[1]=val[1];
	lint ans=val[1];
	for(int i=2,j=1; i<=n; ++i){
		for(; j<i&&idx[j]+tim[idx[j]]<=i; ++j){
			B::mod(idx[j],dp[idx[j]]);
		}
		dp[i]=val[i]+B::ask(i-tim[i]);
		apx(ans,dp[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
