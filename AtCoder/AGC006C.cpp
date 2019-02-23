#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n,m,val[N],nxt[N],ans[N];
lint q;
bool vis[N];

template <class T> inline T nxi(){
	T x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

inline void solve(const int st){
	static int cyc[N];
	int pt=0;
	for(int x=st; !vis[x]; x=nxt[x]){
		vis[x]=1;
		cyc[++pt]=x;
	}
	for(int i=1; i<=pt; ++i){
		ans[cyc[i]]=val[cyc[(i+q%pt-1)%pt+1]];
	}
}

int main(){
	n=nxi<int>();
	for(int lst=0,x,i=1; i<=n; lst=x,++i){
		nxt[i]=i;
		x=nxi<int>();
		val[i]=x-lst;
	}
	m=nxi<int>(),q=nxi<lint>();
	for(int i=1; i<=m; ++i){
		const int x=nxi<int>();
		std::swap(nxt[x],nxt[x+1]);
	}
	for(int i=1; i<=n; ++i){
		if(!vis[i]) solve(i);
	}
	lint sum=0;
	for(int i=1; i<=n; ++i){
		printf("%lld\n",sum+=ans[i]);
	}
	return 0;
}
