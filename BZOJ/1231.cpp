#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
typedef long long lint;
const int N=18;
int n,q,hx[N],mess[N][1<<16];
lint dp[1<<16][N];
//0: not messy

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int cbit(int x){
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}

inline int hbit(int x){
	int ans=0;
	for(int i=16;i;i>>=1){
		if(x>>i) x>>=i,ans+=i;
	}
	return ans;
}

inline lint calc(){
	lint ans=0;
	for(int i=1;i<=n;++i){
		ans+=dp[(1<<n)-1][i];
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	for(int i=1;i<=n;++i){
		dp[1<<(i-1)][i]=1;
	}
	for(int i=1;i<1<<n;++i){
		if(cbit(i)==1) continue;
		for(int j=1;j<=n;++j){
			if((i&(1<<(j-1)))==0) continue;
			lint &cur=dp[i][j];
			int last=i^(1<<(j-1));
			for(int k=1;k<=n;++k){
				if((last&(1<<(k-1)))==0) continue;
				if(abs(hx[j]-hx[k])>q) cur+=dp[last][k];
			}
		}
	}
	printf("%lld\n",calc());
	return 0;
}
