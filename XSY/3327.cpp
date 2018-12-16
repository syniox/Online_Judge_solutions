#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
//BIT维护dp值
const int N=2005;
int n,mp[N][N];
lint ans;

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

struct BIT{
	int tr[N];

	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return ans;
	}

	inline void mod(int x,const int v){
		for(; x<=n; x+=x&-x) tr[x]+=v;
	}

	inline void mod(const int x,const int y,const int v){
		mod(x,v);
		mod(y+1,-v);
	}
}tr[N];

inline void get_dp(){
	static int dp[N];
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			dp[j]=std::max(dp[j-1],dp[j])+mp[i][j];
			ans+=dp[j];
			tr[i].mod(j,j,dp[j]);
		}
	}
}

inline void twk_pt(int x,int &pt,const int v,const int limit,bool f){
	int tp_lf=tr[x].ask(pt-1);
	int tp_up=tr[x-1].ask(pt);
	int cur=tr[x].ask(pt);
	while(pt<limit&&(std::max(tp_lf+v,tp_up)+mp[x][pt]==cur)==f){
		++pt;
		tp_lf=cur;
		tp_up=tr[x-1].ask(pt);
		cur=tr[x].ask(pt);
	}
}

inline void mod(const int x,const int y,const int v){
	int l=y,r=y+1;
	twk_pt(x,r,v,n+1,0);
	mp[x][y]+=v;
	tr[x].mod(l,r-1,v);
	ans+=v*(r-l);
	for(int i=x+1; i<=n; ++i){
		twk_pt(i,l,0,r,1);
		if(l>=r) break;
		twk_pt(i,r,v,n+1,0);
		tr[i].mod(l,r-1,v);
		ans+=v*(r-l);
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			mp[i][j]=nxi();
		}
	}
	get_dp();
	printf("%lld\n",ans);
	for(int i=1; i<=n; ++i){
		char c;
		while((c=get_c())!='U'&&c!='D');
		int x=nxi(),y=nxi();
		mod(x,y,c=='U'?1:-1);
		printf("%lld\n",ans);
	}
	return 0;
}
