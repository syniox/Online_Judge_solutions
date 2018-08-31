#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=10,P=1e3,mod=1e9;
int n,m,cn,zf,dg[N*N],tp[N][N],mp[N*N][N*N];
char ch[N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool vld(int x,int y){
	return x>0&&y>0&&x<=n&&y<=m&&ch[x][y]=='.';
}

inline void get_mtx(){
	for(int i=1;i<=n;++i){
		const int cx[]={0,1,0,-1},cy[]={1,0,-1,0};
		for(int j=1;j<=m;++j){
			const int cur=tp[i][j];
			for(int k=0;k<4;++k){
				const int tx=i+cx[k],ty=j+cy[k];
				if(vld(tx,ty)){
					const int p=tp[tx][ty];
					++dg[cur];
					mp[cur][p]=mp[p][cur]=mod-1;
				}
			}
			mp[cur][cur]=dg[cur];
		}
	}
}

inline void gauss_eli(const int qa,const int qb,const int t){
	int a=qa,b=qb;
	while(mp[a][t]&&mp[b][t]){
		if(mp[a][t]>mp[b][t]) std::swap(a,b);
		int p=mp[b][t]/mp[a][t];
		if(p==0) return;
		for(int i=1;i<=cn;++i){
			mp[b][i]-=(lint)mp[a][i]*p%mod;
			if(mp[b][i]<0) mp[b][i]+=mod;
		}
	}
	if(mp[qb][t]){
		std::swap(mp[a],mp[b]);
		zf*=-1;
	}
}

inline bool gauss(){
	--cn;
	for(int i=1;i<=cn;++i){
		int j=i;
		while(j<=cn&&!mp[j][i]) ++j;
		if(j>cn) return 0;
		std::swap(mp[i],mp[j]);
		if(i!=j) zf*=-1;
		for(int k=i+1;k<=cn;++k){
			gauss_eli(i,k,i);
		}
	}
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	lint ans=zf=1;
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		scanf("%s",ch[i]+1);
		for(int j=1;j<=m;++j){
			if(ch[i][j]=='.') tp[i][j]=++cn;
		}
	}
	get_mtx();
	if(!gauss()){
		puts("0");
		return 0;
	}
	for(int i=1;i<=cn;++i){
		ans=ans*mp[i][i]%mod;
	}
	printf("%lld\n",(ans*zf%mod+mod)%mod);
	return 0;
}
