#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1002;

inline void apn(int &a,int b){
	if(a>b)a=b;
}

inline char get_c(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10+c-48,(c=get_c())>='0'&&c<='9');
	return x;
}

int main(){
	static int fa[N],hx[N],dp[N][5002];
	int n=nxi();
	for(int i=2;i<=n;++i) fa[i]=nxi();
	for(int i=1;i<=n;++i) hx[i]=nxi();

	for(int x=n;x;--x){
		int y=fa[x];
		for(int i=hx[y];i>=0;--i){
			int p=dp[y][i];
			dp[y][i]=1e5;
			if(hx[x]<=i){
				dp[y][i]=(hx[x]?dp[y][i-hx[x]]:p)+dp[x][hx[x]];
			}
			if(dp[x][hx[x]]<=i){
				apn(dp[y][i],(dp[x][hx[x]]?dp[y][i-dp[x][hx[x]]]:p)+hx[x]);
			}
		}
	}
	puts(dp[1][hx[1]]>=1e5?"IMPOSSIBLE":"POSSIBLE");
	return 0;
}
