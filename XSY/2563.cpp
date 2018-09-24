#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=502;
int n,ans,hx[N];

template <class T> inline void apx(T &x,T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

inline int kick_zero(){
	int pt=0;
	while(pt<n&&hx[pt+1]==0) ++pt;
	if(pt<=1) return 0;
	for(int i=pt;i<=n;++i){
		hx[i-pt+1]=hx[i];
	}
	n=n-pt+1;
	return pt;
}

inline int solve(int a,int b){
	int x=hx[a],y=hx[b],cnt=2;
	for(int i=b+1;i<=n;++i){
		if(hx[i]==x+y){
			x=y,y=hx[i];
			++cnt;
		}
	}
	return cnt;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	std::sort(hx+1,hx+n+1);
	ans=kick_zero();
	for(int i=1;i<n;++i){
		for(int j=i+1;j<=n;++j){
			apx(ans,solve(i,j));
		}
	}
	printf("%d\n",ans);
	return 0;
}
