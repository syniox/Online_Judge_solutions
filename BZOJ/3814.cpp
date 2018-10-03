#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<cassert>
typedef long long lint;
const int N=1002,M=7;
const int mod=1e9+7;
int n,m,bar,dp[N][M][200],fdp[N][M][200];
//0: none, 1: left, 2: right
int cni,idx[200],lk[200][8];
bool mp[N][M];
std::map <int,int> stt;

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline bool vld(const int k){
	return !(idx[k]>>(m<<1)&3);
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_stt(const int st){
	if(stt.find(st)==stt.end()){
		stt[st]=++cni;
		idx[cni]=st;
	}
	return stt[st];
}

inline void get_dp(int dp[N][M][200],const int step_i){
	dp[1][0][get_stt(0)]=1;
	dp[n][0][get_stt(0)]=1;
	const int st_i=step_i>0?1:n;
	const int ed_i=step_i>0?n:1;
	for(int i=st_i;i!=ed_i;i+=step_i){
		for(int j=1;j<=cni;++j){
			if((idx[j])>>(m<<1)&3) continue;
			const int to=get_stt(idx[j]<<2);
			twk(dp[i][0][to]+=dp[i-step_i][m][j]);
		}
		for(int j=0;j<m;++j){
			for(int k=1;k<=cni;++k){
				if(!dp[i][j][k]) continue;
				const int cur=idx[k],base=dp[i][j][k];
				const int p1=cur>>(j<<1)&3,p2=cur>>((j+1)<<1)&3;
				if((p1||p2)&&mp[i][j+1]) continue;
				if(!p1&&!p2){
					twk(dp[i][j+1][k]+=base);
					if(mp[i][j+1]) continue;
					const int to=cur|(1<<(j<<1))|(2<<((j+1)<<1));
					twk(dp[i][j+1][get_stt(to)]+=base);
				}
				else if((p1>0)^(p2>0)){
					twk(dp[i][j+1][k]+=base);
					const int removed=cur^(p1<<(j<<1))^(p2<<((j+1)<<1));
					const int to=removed|(p1<<((j+1)<<1))|(p2<<(j<<1));
					twk(dp[i][j+1][get_stt(to)]+=base);
				}
				else if(p1==p2){
					const int step=p1==1?1:-1,end=p1==1?m+1:0;
					int l,cnt=-(p1!=1);
					for(l=j+step;l!=end;l+=step){
						const int now=(cur>>(l<<1))&3;
						if(now==p1) --cnt;
						if(now&&now!=p1&&++cnt>=0) break;
					}
					const int to=cur^(p1<<(j<<1))^(p2<<((j+1)<<1))^(3<<(l<<1));
					twk(dp[i][j+1][get_stt(to)]+=base);
				}
				else if(p2==1){
					const int to=cur^(p1<<(j<<1))^(p2<<((j+1)<<1));
					twk(dp[i][j+1][get_stt(to)]+=base);
				}
			}
		}
	}
}

inline void prt_bin(const int x){
	if(x==1) printf("01 ");
	if(x==2) printf("10 ");
	if(x==0) printf("00 ");
}

void prt_st(const int st){
	for(int i=0;i<=m;++i){
		prt_bin((st>>(i<<1))&3);
	}
	puts("");
}

inline void get_lk(){
	memset(lk,-1,sizeof(lk));
	static int stk[8];
	for(int i=1;i<=cni;++i){
		const int cur=idx[i];
		if(cur>>(m<<1)&3) continue;
		int tp,top=0;
		for(int j=0;j<=m;++j){
			if((tp=(cur>>(j<<1)&3))){
				if(tp==1) stk[++top]=j;
				else{
					lk[i][j]=stk[top];
					lk[i][stk[top--]]=j;
				}
			}
		}
	}
}


inline int jdg(const int x,const int y){
	static bool vis[8];
	memset(vis,0,sizeof(vis));
	int st=0;
	for(;lk[x][st]==-1;++st);
	while(~st&&!vis[st]){
		vis[st]=1;
		st=lk[y][st];
		if(st==-1) return 0;
		vis[st]=1;
		st=lk[x][st];
	}
	for(int i=0;i<=m;++i){
		if(!vis[i]){
			if(~lk[x][i]||~lk[y][i]) return 0;
		}
	}
	return 1;
}

inline int get_ans(const int x,const int y){
	int ans=0;
	for(int i=1;i<=cni;++i){
		if(!dp[x][m][i]||!vld(i)||!(idx[i]>>((y-1)<<1)&3)) continue;
		for(int j=1;j<=cni;++j){
			if(!fdp[x+1][m][j]||!vld(j)||!(idx[i]>>((y-1)<<1)&3)) continue;
			if(jdg(i,j)){
				ans=(ans+(lint)dp[x][m][i]*fdp[x+1][m][j])%mod;
			}
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi(),bar=nxi();
	for(int i=1;i<=bar;++i){
		const int x=nxi(),y=nxi();
		mp[x][y]=1;
	}
	get_dp(dp,1);
	get_dp(fdp,-1);
	get_lk();
	int q=nxi();
	while(q--){
		const int x=nxi(),y=nxi();
		printf("%d\n",get_ans(x,y));
	}
	return 0;
}
