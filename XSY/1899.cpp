#include<iostream>
#include<cstdio>
#include<cstring>
const int N=12,M=81;
int n,num[N];
double alv[N];
double killed[N][M];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline double qpow(double x,int t){
	double ans=1;
	for(;t;t>>=1,x*=x){
		if(t&1) ans*=x;
	}
	return ans;
}

inline double solve(const int x){
	double ans=0;
	for(int t=1;t<M-1;++t){
		double cnt=1;
		for(int i=1;i<=n;++i){
			if(i==x) continue;
			cnt*=killed[i][t];
		}
		ans+=(1-killed[x][t]-(1-killed[x][t+1]))*cnt;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	int T=nxi();
	while(T--){
		n=nxi();
		for(int i=1;i<=n;++i){
			num[i]=nxi();
			scanf("%lf",alv+i);
			double cur=alv[i];
			for(int j=1;j<M;cur*=alv[i],++j){
				killed[i][j]=qpow(1.0-cur,num[i]);
			}
		}
		for(int i=1;i<=n;++i){
			printf("%lf ",solve(i));
		}
		puts("");
	}
	return 0;
}
