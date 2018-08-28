#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cassert>
using namespace std;
int dg;
double og[8],ans[6],xx[8][6];
//[base][time]
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	for(int i=0;i<8;++i) xx[i][0]=1;
	for(int i=1;i<8;++i){
		for(int j=1;j<6;++j){
			xx[i][j]=xx[i][j-1]*i;
		}
	}
}

inline void gauss(int p1,int p2){
	static double mg[8],xs[8][6];
	static int get[6];
	static bool vis[8];
	memcpy(xs,xx,sizeof(xs));
	memcpy(mg,og,sizeof(mg));
	memset(vis,0,sizeof(vis));
	vis[p1]=vis[p2]=1;

	for(int i=dg,j=1;i;--i,++j){
		while(vis[j]) ++j;
		vis[j]=1;
		get[i]=j;
		double p=xs[j][i];
		for(int k=0;k<dg+3;++k){
			if(vis[k]) continue;
			double t=xs[k][i]/p;
			mg[k]-=mg[j]*t;
			for(int l=i;l>=0;--l){
				xs[k][l]-=xs[j][l]*t;
			}
		}
	}

	get[0]=!p1||!p2?get[1]+1:0;
	while(vis[get[0]]) ++get[0];
	ans[0]=mg[get[0]];
	for(int i=1;i<=dg;++i){
		double tp(0);
		for(int j=0;j<i;++j){
			tp+=xs[get[i]][j]*ans[j];
		}
		ans[i]=(mg[get[i]]-tp)/xs[get[i]][i];
	}
}

inline bool jdg(int k){
	double tp=0;
	for(int i=dg;~i;--i){
		tp+=ans[i]*xx[k][i];
	}
	return fabs(tp-og[k])<1e-4;
}


inline int solve(){
	for(int i=0;i<dg+3;++i){
		for(int j=i+1;j<dg+3;++j){
			gauss(i,j);
			if(jdg(i)) return j;
			if(jdg(j)) return i;
		}
	}
	return 0;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	init();
	while((dg=nxi())){
		for(int i=0;i<dg+3;++i) scanf("%lf",og+i);
		printf("%d\n",solve());
	}
	return 0;
}
