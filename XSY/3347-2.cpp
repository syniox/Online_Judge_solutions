#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
const int N=2e5+5;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	int n,cnt,lst;
	double dp[N<<1];
	bool vis[N<<1];
	struct node{
		int to,lk,c[26],len;
		bool end;
	}tr[N<<1];

	inline void init(){
		memset(tr,0,(cnt+1)*sizeof(node));
		memset(vis,0,(cnt+1)*sizeof(bool));
		cnt=lst=0;
		tr[0].lk=-1;
	}

	inline void ins(int c){
		int p=lst,x=lst=++cnt;
		tr[x].len=tr[p].len+1;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=x;
		}
		if(p==-1) return;
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[x].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk){
				tr[p].c[c]=cnt;
			}
			tr[x].lk=tr[q].lk=cnt;
		}
	}

	inline double dfs(int x){
		if(tr[x].end) return 0;
		if(vis[x]) return dp[x];
		vis[x]=1;
		double buk=0;
		for(int i=0; i<26; ++i){
			if(tr[x].c[i]) buk+=(double)1/(dfs(tr[x].c[i])+1);
		}
		return dp[x]=(double)1/buk;
	}
}

inline double solve(){
	static char ch[N];
	S::init();
	scanf("%s",ch+1);
	S::n=strlen(ch+1);
	for(int i=1; i<=S::n; ++i){
		S::ins(ch[i]-'a');
	}
	for(int p=S::lst; p; p=S::tr[p].lk){
		S::tr[p].end=1;
	}
	return S::dfs(0);
}

int main(){
	for(int T=nxi(); T; --T){
		printf("%.12lf\n",solve());
	}
	return 0;
}
