#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
int n;
bool hx[N];

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

inline int solve(){
	int ans=0,sum=0;
	for(int i=1;i<=n<<1;++i){
		apn(ans,sum+=(hx[i])?1:-1);
	}
	return n+ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[nxi()]=1;
	}
	printf("%d\n",solve());
	return 0;
}
