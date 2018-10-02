#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
const int N=1002,M=7;
int n,m,bar,dp[N][M][200],fdp[N][M][200];
//0: none, 1: left, 2: right
int cni,idx[N];
bool mp[N][M];
std::map <int,int> stt;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_mp(const int st){
	if(!stt.find(st)){
		stt[to]=++cni;
		inx[cni]=st;
	}
	return stt[st];
}

inline void get_dp(){
	dp[1][0][0]=1;
	stt[0]=1;
	idx[++cni]=0;
	for(int i=1;i<n;++i){
		for(int j=1;j<=cni;++j){
			const int fr=stt[idx[j]<<1];
			dp[i][0][j]=dp[i-1][m][fr];
		}
		for(int j=0;j<m;++j){
			for(int k=1;i<=cni;++k){
				if(!dp[i][j][k]) continue;
				const int cur=stt[k],base=dp[i][j][k];
				const int p1=cur>>(j<<1)&3,p2=cur>>((j+1)<<1)&3;
				if(!p1&&!p2){
					const int to=cur|(1<<(j<<1))|(2<<((j+1)<<1));
					dp[i][j+1][get_stt(to)]+=base;
				}
				else if((p1>0)^(p2>0)){
					dp[i][j+1][k]+=base;
					const int removed=cur^(p1<<(j<<1))^(p2<<(j+1)<<1);
					const int to=removed|(p1<<((j+1)<<1))|(p2<<(j<<1));
					dp[i][j+1][get_stt(to)]+=base;
				}
			}
		}
	}
}

inline void get_fdp(){

}

int main(){
	n=nxi(),m=nxi(),bar=nxi();
	for(int i=1;i<=bar;++i){
		const int x=nxi(),y=nxi();
		mp[x][y]=nxi();
	}
	get_dp();
	get_fdp();
	int q=nxi();
	while(q--){
		const int x=nxi(),y=nxi();
	}
	return 0;
}
