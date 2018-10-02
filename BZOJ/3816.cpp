#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=202;
int n,m,pt[N],ans[N],mp[N][N<<1];
bool match[N];
//is color matched?
//ans[i]: which color i line is
struct node{
	int pos,line;
	bool operator < (const node &b) const {
		return pos<b.pos;
	}
}nd[N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool done(){
	for(int i=1;i<=n;++i){
		if(!ans[i]) return 0;
	}
	return 1;
}

inline void solve(){
	for(int i=1;i<=n;++i){
		if(!match[i]){
			const node cur=nd[i][pt[i]];
			const int bef=ans[cur.line];
			if(nd[bef][pt[bef]].pos>cur.pos){
				match[bef]=0;
				match[i]=1;
				ans[cur.line]=i;
			}
			else --pt[i];
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	int T=nxi();
	nd[0][0]=(node){(int)1e8,(int)1e8};
	while(T--){
		memset(ans,0,sizeof(ans));
		memset(match,0,sizeof(match));
		memset(pt,0,sizeof(pt));
		n=nxi(),m=nxi();
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				mp[i][j]=nxi();
				if(mp[i][j]){
					const int cur=mp[i][j];
					nd[cur][++pt[cur]]=(node){j,i};
				}
			}
		}
		for(int i=1;i<=n;++i){
			std::sort(nd[i]+1,nd[i]+n+1);
		}
		while(!done()) solve();
		for(int i=1;i<=n;++i){
			printf("%d ",ans[i]);
		}
		puts("");
	}
	return 0;
}
