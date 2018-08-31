#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
const int N=302;
const long double eps=1e-12;
int n,m;
char ch[N][N];
long double mp[N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void get_mp(int t){
	static int nx[N];
	for(int j=0,i=2;i<=m;++i){
		while(j&&ch[t][i]!=ch[t][j+1]) j=nx[j];
		if(ch[t][i]==ch[t][j+1]) ++j;
		nx[i]=j;
	}
	mp[t][t]=-1;
	for(int i=1;i<=n;++i){
		int j=1,k=0;
		for(;j<=m;++j){
			while(k&&ch[i][j]!=ch[t][k+1]) k=nx[k];
			if(ch[i][j]==ch[t][k+1]) ++k;
		}
		if(k==m) k=nx[k];
		for(;k;k=nx[k]){
			if(m-k>63) break;
			mp[t][i]-=1.0/(1ull<<(m-k));
		}
	}
}

inline void gauss(){
	for(int i=1;i<=n+1;++i){
		int j=i;
		while(j<=n+1&&fabs(mp[j][i])<eps) ++j;
		if(j>n+1) return;
		std::swap(mp[i],mp[j]);
		for(int k=1;k<=n+1;++k){
			if(k==i) continue;
			const long double p=mp[k][i]/mp[i][i];
			for(int l=0;l<=n+1;++l){
				mp[k][l]-=mp[i][l]*p;
			}
		}
	}
	for(int i=1;i<=n+1;++i){
		if(fabs(mp[i][0])>eps) mp[i][i]=mp[i][0]/mp[i][i];
		else mp[i][i]=0;
	}
}

inline void gauss_init(){
	for(int i=1;i<=n;++i){
		mp[n+1][i]=1;
		get_mp(i);
		mp[i][n+1]=1;
		//we don't need to know men.
		//1/(2^m)*men instead of men is also ok.
	}
	mp[n+1][0]=1;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		scanf("%s",ch[i]+1);
	}
	gauss_init();
	gauss();
	for(int i=1;i<=n;++i){
		printf("%.10lf\n",(double)mp[i][i]);
	}
	return 0;
}
