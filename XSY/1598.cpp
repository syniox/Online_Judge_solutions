#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e6+2;
int n,ans,lc[N],rc[N],prs[N];
char ch[N];

inline void apx(int &x,const int y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void get_string(){
	char c;
	while((c=getchar())!='j'&&c!='p');
	fread(ch+2,1,n-1,stdin);
	ch[1]=c;
}

inline void get(int cc[N],const bool fx){
	static int stk[N];
	int st=1,ed=n,sp=fx?-1:1;
	if(fx) std::swap(st,ed);
	int top=0;
	ed+=sp;
	for(int i=st;i!=ed;i+=sp){
		if(ch[i]>0) stk[++top]=i;
		else{
			while(top&&(prs[i+sp*fx]-prs[stk[top]-(fx^1)])*sp<0){
				cc[stk[top--]]=i-sp;
			}
		}
	}
	ed-=sp;
	for(;top;--top) cc[stk[top]]=ed;
}

int dfs(const int x,const int y){
	if(lc[x]>=y&&rc[y]<=x) return y-x+1;
	if(rc[y]>x){
		int tx=rc[y]+1,ty=rc[y]-1,ans=0;
		for(;ty>=x&&ch[ty]<0;--ty);
		if(ty>=x) apx(ans,dfs(x,ty));
		for(;tx<=y&&ch[tx]<0;++tx);
		if(tx<=y) apx(ans,dfs(tx,y));
		return ans;
	}
	int tx=lc[x]+1,ty=lc[x]-1,ans=0;
	for(;ty>=x&&ch[ty]<0;--ty);
	if(ty>=x) apx(ans,dfs(x,ty));
	for(;tx<=y&&ch[tx]<0;++tx);
	if(tx<=y) apx(ans,dfs(tx,y));
	return ans;
}

inline void solve(){
	int s,i,cur=0;
	for(s=1,i=1;i<=n;++i){
		if((cur+=ch[i])<0){
			if(s!=i){
				int k=i-1;
				for(;k>=s&&ch[k]<0;--k);
				if(k>=s) apx(ans,dfs(s,k));
			}
			cur=0;
			s=i+1;
		}
	}
	if(s!=i){
		int k=i-1;
		for(;k>=s&&ch[k]<0;--k);
		if(k>=s) apx(ans,dfs(s,k));
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	get_string();
	for(int i=1;i<=n;++i){
		prs[i]=prs[i-1]+(ch[i]=(ch[i]=='p'?1:-1));
	}
	get(lc,0);
	get(rc,1);
	solve();
	printf("%d\n",ans);
	return 0;
}
