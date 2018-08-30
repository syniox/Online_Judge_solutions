#include<iostream>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<fstream>
const int N=602,mod=123456789;
int n,m;
std::bitset<N*3> rc[N][N];
const int cx[]={1,2,2,1,-1,-2,-2,-1};
const int cy[]={2,1,-1,-2,-2,-1,1,2};

inline bool vld(int x,int y){
	return x>0&&y>0&&x<=n&&y<=m;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int gauss(){
	int cnt=0,ans=0;
	std::bitset<N*3>mp[N*3];
	for(int i=1;i<=n;++i){
		mp[++cnt]=rc[i][m];
		for(int j=0;j<8;++j){
			int tx=i+cx[j],ty=m+cy[j];
			if(vld(tx,ty)){
				mp[cnt]^=rc[tx][ty];
			}
		}
	}
	for(int i=std::max(1,n-1);i<=n;++i){
		for(int j=1;j<m;++j){
			mp[++cnt]=rc[i][j];
			for(int k=0;k<8;++k){
				int tx=i+cx[k],ty=j+cy[k];
				if(vld(tx,ty)){
					mp[cnt]^=rc[tx][ty];
				}
			}
		}
	}
	for(int i=1;i<=cnt;++i){
		for(int j=1;j<=cnt;++j){
		}
	}
	for(int i=1;i<=cnt;++i){
		int j=i;
		while(j<=cnt&&!mp[j][i]) ++j;
		if(j>cnt) ++ans;
		else{
			swap(mp[i],mp[j]);
			for(int k=i+1;k<=cnt;++k){
				if(mp[k][i]) mp[k]^=mp[i];
			}
		}
	}
	int cns=1;
	for(int i=1;i<=ans;++i){
		cns=cns<<1;
		if(cns>mod) cns-=mod;
	}
	return cns;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=2;++i){
		for(int j=1;j<=m;++j){
			rc[i][j][(i-1)*m+j]=1;
		}
	}
	for(int i=3;i<=n;++i){
		rc[i][1][(m<<1)+i-2]=1;
	}
	for(int i=3;i<=n;++i){
		for(int j=2;j<=m;++j){
			const int a=i-2,b=j-1;
			rc[i][j]=rc[a][b];
			for(int k=0;k<8;++k){
				const int ta=a+cx[k],tb=b+cy[k];
				if((ta!=i||tb!=j)&&vld(ta,tb)){
					rc[i][j]^=rc[ta][tb];
				}
			}
		}
	}
	printf("%d\n",gauss());
	return 0;
}
