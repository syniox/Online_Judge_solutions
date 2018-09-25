#include<iostream>
#include<cstdio>
#include<cstring>
const int N=19;
int n,m,top,oput_stk[N],dis_mid[N][N],dis[N][N],dp[N][1<<18],pre[N][1<<18];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void floyd(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(i==j) continue;
			for(int k=1;k<=n;++k){
				const int v=dis[j][i]+dis[i][k];
				if(dis[j][k]>v){
					dis[j][k]=v;
					dis_mid[j][k]=i;
				}
			}
		}
	}
}

void get_route(int x,int y){
	const int mid=dis_mid[x][y];
	if(!mid){
		if(x!=y) oput_stk[++top]=y;
		oput_stk[++top]=x;
		return;
	}
	if(y!=mid) get_route(mid,y);
	--top;
	if(x!=mid) get_route(x,mid);
}

inline void oput_route(int state){
	int x,cur=1e8;
	for(int i=1;i<=n;++i){
		if(cur>dp[i][state]){
			cur=dp[i][state];
			x=i;
		}
	}
	while(x!=1){
		int f=pre[x][state];
		get_route(f,x);
		--top;
		state^=(1<<(x-1));
		x=f;
	}
	printf("%d ",top);
	printf("1 ");
	for(;top>0;--top){
		printf("%d ",oput_stk[top]);
	}
	puts("");
}

inline void oput(){
	int ax=1,ay=1,ans=1e8;
	for(int i=1;i<(1<<n);++i){
		const int j=((1<<n)-1)^i;
		const int tp=std::max(dp[0][j],dp[0][i]);
		if(tp<ans){
			ax=i,ay=j;
			ans=tp;
		}
	}
	printf("%d\n",ans);
	oput_route(ax);
	oput_route(ay);
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	memset(dis,31,sizeof(dis));
	memset(dp,31,sizeof(dp));
	n=nxi(),m=nxi();
	for(int i=1;i<N;++i) dis[i][i]=0;
	for(int i=1;i<=m;++i){
		const int x=nxi(),y=nxi(),v=nxi();
		apn(dis[x][y],v);
		apn(dis[y][x],v);
	}
	floyd();
	dp[0][0]=0;
	for(int i=1;i<=n;++i){
		dp[i][1<<(i-1)]=dis[1][i];
		pre[i][1<<(i-1)]=1;
	}
	for(int i=1;i<(1<<n);++i){
		for(int j=1;j<=n;++j){
			if(dp[j][i]>5e8) continue;
			if((i&(1<<(j-1)))==0) continue;
			for(int k=1;k<=n;++k){
				if((i&(1<<(k-1)))||dis[j][k]>5e8) continue;
				const int cur=i^(1<<(k-1)),v=dp[j][i]+dis[j][k];
				if(dp[k][cur]>v){
					dp[k][cur]=v;
					pre[k][cur]=j;
				}
			}
			apn(dp[0][i],dp[j][i]);
		}
	}
	oput();
	return 0;
}