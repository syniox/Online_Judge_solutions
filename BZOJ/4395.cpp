#include <iostream>
#include <cstdio>
#include <cstring>
const int N=102;
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int hd,tl,cnt,fir[N*N],que[N*N];
	bool walk[N*N],light[N*N];
	struct edge{
		int to,nx;
	}eg[(int)2e5+5];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline void check_w(const int x){
		if(!walk[x]&&light[x]) que[tl++]=x;
		walk[x]=1;
	}

	inline void check_l(const int x){
		if(!light[x]&&walk[x]) que[tl++]=x;
		light[x]=1;
	}

	inline int bfs(){
		hd=0,tl=1;
		int ans=0;
		walk[0]=light[0]=1;
		que[0]=0;
		while(hd!=tl){
			const int x=que[hd++];
			if(x%n) check_w(x-1);
			if(x/n) check_w(x-n);
			if(x%n<n-1) check_w(x+1);
			if(x/n<n-1) check_w(x+n);
			for(int i=fir[x];i;i=eg[i].nx){
				check_l(eg[i].to);
			}
		}
		for(int i=n*n-1;i>=0;--i){
			ans+=light[i];
		}
		return ans;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int a=nxi()-1,b=nxi()-1,x=nxi()-1,y=nxi()-1;
		const int fr=a*n+b,to=x*n+y;
		G::add(fr,to);
	}
	printf("%d\n",G::bfs());
	return 0;
}
