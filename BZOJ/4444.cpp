#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=2e5+2;
int n,m,ans[N];
struct sdr{
	int l,r,id;
	bool operator < (const sdr &b) const {
		return l<b.l;
	}
}sr[N<<1];

inline char get_c(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

namespace G{
	int top,fir[N<<1],stk[N<<1];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(int a,int b){
		static int cnt;
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void dfs(int x,int pt){
		stk[++top]=x;
		if(sr[x].id){
			while(pt<top&&sr[stk[pt+1]].r>=sr[x].l+m) ++pt;
			ans[sr[x].id]=top-pt+1;
		}
		for(int i=fir[x];i;i=eg[i].nx){
			dfs(eg[i].to,pt);
		}
		--top;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1,j=0;i<=n;++i){
		sr[++j].l=nxi();
		sr[j].r=nxi();
		if(sr[j].r<sr[j].l) sr[j].r+=m;
		sr[j].id=i;
		++j;
		sr[j].l=sr[j-1].l+m;
		sr[j].r=sr[j-1].r+m;
	}
	std::sort(sr+1,sr+(n<<1)+1);
	for(int i=1,pt=1;i<n<<1;++i){
		while(pt<n<<1&&sr[pt+1].l<=sr[i].r) ++pt;
		G::add(pt,i);
	}
	G::dfs(n<<1,1);
	for(int i=1;i<=n;++i){
		printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
