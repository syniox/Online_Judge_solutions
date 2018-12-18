#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n,q,hx[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline lint solve(const int k){
	static int buk[N];
	memset(buk,0,sizeof(buk));
	int pt=0;
	for(int i=1; i<=k; ++i){
		++buk[hx[i]];
		apx(pt,hx[i]);
	}
	lint ans=pt;
	--buk[pt];
	while(pt>0&&!buk[pt]) --pt;
	for(int i=2,j=k+1; i<n; ++i,++j){
		if(j<=n){
			if(hx[j]>pt){
				ans+=i&1?hx[j]:-hx[j];
				continue;
			}
			else ++buk[hx[j]];
		}
		ans+=i&1?pt:-pt;
		--buk[pt];
		while(!buk[pt]) --pt;
	}
	if(k==1) pt=hx[n];
	return ans+(n&1?pt:-pt);
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		hx[i]=nxi();
	}
	while(q--){
		printf("%lld\n",solve(nxi()));
	}
	return 0;
}
