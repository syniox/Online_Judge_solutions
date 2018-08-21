#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=1e5+2;
int n,m;
struct data{
	int l,r;
	bool operator < (const data &b) const {
		return r-l<b.r-b.l;
	}
}dt[N*3];

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
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int tr[N];
	inline void mod(int x,const int v){
		for(;x<=m;x+=x&-x){
			tr[x]+=v;
		}
	}
	inline int ask(int x){
		int ans=0;
		for(;x;x-=x&-x){
			ans+=tr[x];
		}
		return ans;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		dt[i].l=nxi(),dt[i].r=nxi();
	}
	std::sort(dt+1,dt+n+1);
	for(int i=1,pt=1;i<=m;++i){
		int ans=0;
		for(int j=i;j<=m;j+=i){
			ans+=T::ask(j);
		}
		printf("%d\n",ans+n-pt+1);
		while(pt<=n&&dt[pt].r-dt[pt].l<=i){
			T::mod(dt[pt].l,1);
			T::mod(dt[pt].r+1,-1);
			++pt;
		}
	}
	return 0;
}
