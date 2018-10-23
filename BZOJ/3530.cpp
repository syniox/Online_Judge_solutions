#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1205;
const int mod=1e9+7;
int n,dp[N][1505];
char ch[N],qn[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	int cnt,que[1505];
	struct node{
		int lk,c[10];
		bool end;
	}tr[1505];
	inline void add(){
		const int len=strlen(ch+1);
		int p=0;
		for(int i=1;i<=len;++i){
			const int c=ch[i]-'0';
			if(!tr[p].c[c]) tr[p].c[c]=++cnt;
			p=tr[p].c[c];
		}
		tr[p].end=1;
	}
	inline void build(){
		int hd=0,tl=1;
		que[0]=0;
		while(hd!=tl){
			const int x=que[hd++],lk=tr[x].lk;
			tr[x].end|=tr[lk].end;
			for(int i=0;i<10;++i){
				int &y=tr[x].c[i];
				if(!y) y=tr[lk].c[i];
				else {
					if(x!=lk) tr[y].lk=tr[tr[x].lk].c[i];
					tr[y].end|=tr[x].end;
					que[tl++]=y;
				}
			}
		}
	}
}

int dfs(const int t,const int x,const bool top,const bool zero){
	using S::tr;
	if(dp[t][x]&&!top&&!zero) return dp[t][x];
	if(t==n) return 1;
	const int limit=top?qn[t+1]:9;
	int ans=0;
	for(int i=0;i<=limit;++i){
		if(!tr[tr[x].c[i]].end){
			const bool tpz=zero&&i==0;
			ans+=dfs(t+1,tpz?0:tr[x].c[i],top&&(i==limit),tpz);
		}
		if(ans>=mod) ans-=mod;
	}
	if(!top&&!zero) dp[t][x]=ans;
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	scanf("%s",qn+1);
	n=strlen(qn+1);
	for(int i=1;i<=n;++i){
		qn[i]-='0';
	}
	const int m=nxi();
	for(int i=1;i<=m;++i){
		scanf("%s",ch+1);
		S::add();
	}
	S::build();
	printf("%d\n",dfs(0,0,1,1)-1);
	return 0;
}
