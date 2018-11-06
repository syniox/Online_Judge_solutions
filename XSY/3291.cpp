#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=5e5+5;
int n,m,fa[N];
bool loop[N];
struct edge{
	int x,y,v;
	bool operator < (const edge &b) const {
		return v<b.v;
	}
}eg[N];

int find_rt(const int x){
	return fa[x]?fa[x]=find_rt(fa[x]):x;
}

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

inline bool jdg(){
	for(int i=1;i<=n;++i){
		if(find_rt(i)==i&&!loop[i]) return 0;
	}
	return 1;
}

inline void solve(){
	lint ans=0;
	for(int i=1;i<=m;++i){
		const int x=find_rt(eg[i].x),y=find_rt(eg[i].y);
		if(x==y){
			if(!loop[x]){
				loop[x]=1;
				ans+=eg[i].v;
			}
		}
		else if(!(loop[x]&&loop[y])){
			fa[x]=y;
			ans+=eg[i].v;
			loop[y]|=loop[x];
		}
	}
	if(!jdg()){
		puts("No");
		return;
	}
	printf("%lld\n",ans);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		eg[i].x=nxi(),eg[i].y=nxi(),eg[i].v=nxi();
	}
	std::sort(eg+1,eg+m+1);
	solve();
	return 0;
}
