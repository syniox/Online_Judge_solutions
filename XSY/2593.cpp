#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
int n,m,fir[N],dgr[N];
bool isr[N];
struct edge{
	int to,nx;
}eg[N<<1];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline void add(const int a,const int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

void dfs(const int x,const int fa){
	static int cnd,top,stk[N],dfn[N],low[N];
	static bool inq[N];
	dfn[x]=low[x]=++cnd;
	inq[x]=1;
	stk[++top]=x;
	int cnt=0;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y==fa) continue;
		if(!dfn[y]){
			dfs(y,x);
			if(low[y]>=dfn[x]){
				++cnt;
				for(;stk[top]!=x;--top);
			}
			apn(low[x],low[y]);
		}
		else{
			if(inq[y]) apn(low[x],dfn[y]);
		}
	}
	isr[x]=(cnt+(fa>0))>1;
}

inline void oput(){
	static int ans=0,buf[N];
	if(m-2==n){
		for(int i=1;i<=n;++i){
			if(!fir[i]){
				printf("1\n%d\n",i);
				return;
			}
		}
	}
	for(int i=1;i<=n;++i){
		if(dgr[i]==m-(n-2)&&!isr[i]){
			buf[++ans]=i;
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;++i){
		printf("%d ",buf[i]);
	}
	puts("");
}

int main(){
#ifndef ONLNE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int x=nxi(),y=nxi();
		++dgr[x];
		++dgr[y];
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	oput();
	return 0;
}
