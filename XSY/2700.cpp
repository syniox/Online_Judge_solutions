#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1e4+2;
int n,m,qa[6][N],qb[6][N],w_left[6][N],w_down[6][N];
lint ans,dp[2][1<<5];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

inline void read_array(int ar[6][N]){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			ar[i][j]=nxi();
		}
	}
}

inline lint solve(const int t){
	memset(dp,31,sizeof(dp));
	dp[0][0]=0;
	bool pt=1;
	for(int i=1;i<=m;++i){
		for(int j=1;j<=n;++j){
			memset(dp[pt],31,sizeof(dp[pt]));
			for(int k=0;k<(1<<n);++k){
				const bool f=(k>>(j-1))&1;
				const lint b1=dp[pt^1][k],b2=dp[pt^1][k^(1<<(j-1))];
				const lint base1=(f^((qa[j][i]>>t)&1))*(lint)qb[j][i]<<t;
				lint base2=0;
				if(j>1) base2+=(f^((k>>(j-2))&1))*(lint)w_down[j-1][i]<<t;
				if(j==n) base2+=(f^(k&1))*(lint)w_down[n][i]<<t;
				apn(dp[pt][k],b1+base1+base2);
				apn(dp[pt][k],b2+base1+base2+((lint)w_left[j][i]<<t));
			}
			pt^=1;
		}
	}
	lint ans=1e18;
	for(int i=0;i<(1<<n);++i){
		apn(ans,dp[pt^1][i]);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	read_array(qa);
	read_array(qb);
	for(int i=1;i<=n;++i){
		for(int j=2;j<=m;++j){
			w_left[i][j]=nxi();
		}
	}
	read_array(w_down);
	for(int i=19;i>=0;--i){
		ans+=solve(i);
	}
	printf("%lld\n",ans);
	return 0;
}
