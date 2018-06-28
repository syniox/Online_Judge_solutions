#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int N=12;
int n,m,q,map[N][N],dp[N][N][1<<10],pre[N][N][1<<10];
bool vis[N][N];
struct node{
	int x,y;
	node operator + (const node b) const {
		return (node){x+b.x,y+b.y};
	}
};
queue <node> que;
node cg[]={{0,1},{1,0},{0,-1},{-1,0}};
inline void apn(int &a,int b){
	if(a>b) a=b;
}
inline bool jdg(node x){
	return x.x&&x.x<=n&&x.y&&x.y<=m;
}
inline int pk(int x,int y,int t){
	return t<<8|x<<4|y;
}
inline void upk(int &x,int &y,int &t,int p){
	x=(p>>4)&15,y=p&15,t=p>>8;
}
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-48;
	return x;
}
inline void init(int lt){
	memset(vis,1,sizeof(vis));
	while(!que.empty()) que.pop();
	int cnt=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(!map[i][j]){
				if((1<<cnt)&lt){
					int q=lt^(1<<cnt);
					if(dp[i][j][lt]>dp[i][j][q]){
						dp[i][j][lt]=dp[i][j][q];
						pre[i][j][lt]=pk(i,j,q);
					}
				}
				++cnt;
			}
			que.push((node){i,j});
		}
	}
}
void spfa(int lt){
	init(lt);
	while(!que.empty()){
		node tp,x=que.front();
		que.pop();
		int v=dp[x.x][x.y][lt];
		vis[x.x][x.y]=0;
		for(int i=0;i<4;++i){
			if(jdg(tp=x+cg[i])){
				int &p=dp[tp.x][tp.y][lt];
				if(p>v+map[tp.x][tp.y]){
					p=v+map[tp.x][tp.y];
					pre[tp.x][tp.y][lt]=pk(x.x,x.y,lt);
					if(!vis[tp.x][tp.y]){
						que.push(tp);
						vis[tp.x][tp.y]=1;
					}
				}
			}
		}
	}
}
void cal(){
	memset(dp,15,sizeof(dp));
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j) dp[i][j][0]=0;
	}
	for(int i=1;i<q;++i){
		for(int j=1;j<=n;++j){
			for(int k=1;k<=m;++k){
				for(int l=(i-1)&i;l;l=(l-1)&i){
					int p=dp[j][k][l]+dp[j][k][i^l]-map[j][k];
					if(dp[j][k][i]>p){
						dp[j][k][i]=p;
						pre[j][k][i]=pk(j,k,l);
					}
				}
			}
		}
		spfa(i);
	}
}
void dfs(int x,int y,int t){
	vis[x][y]=1;
	if(!pre[x][y][t]) return;
	int tx,ty,tt;
	upk(tx,ty,tt,pre[x][y][t]);
	dfs(tx,ty,tt);
	if(x==tx&&y==ty&&tt&&tt!=t) dfs(x,y,t^tt);
}
void pt(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(!map[i][j]) putchar('x');
			else if(vis[i][j]) putchar('o');
			else putchar('_');
		}
		puts("");
	}
}

//---------------main---------------//

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			map[i][j]=nxi();
			q+=map[i][j]==0;
		}
	}
	q=1<<q;
	cal();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(!map[i][j]){
				printf("%d\n",dp[i][j][q-1]);
				dfs(i,j,q-1);
				pt();
				return 0;
			}
		}
	}
	return 0;
}
