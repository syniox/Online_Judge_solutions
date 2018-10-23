#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long lint;
const int N=1e5+5;
int n,m,cnd;
struct data{
	int l,r;
	bool operator < (const data &b) const {
		return r<b.r;
	}
}dt[N*3];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

struct BIT{
	lint tr[N*3];
	inline void mod(int x,int v){
		for(;x<=m*3;x+=x&-x) tr[x]+=v;
	}
	inline lint ask(int x){
		lint ans=0;
		for(;x;x-=x&-x) ans+=tr[x];
		return ans;
	}
	inline lint ask(const int x,const int y){
		return ask(y)-ask(x-1);
	}
}tr_s,tr_sz;

inline lint solve(){
	lint ans=0;
	for(int i=m*3,j=cnd;i;--i){
		for(;j&&dt[j].r>=i;--j){
			tr_sz.mod(dt[j].l,1);
			tr_s.mod(dt[j].l,dt[j].l);
		}
		const lint s=tr_s.ask(1,i-1);
		const int sz=tr_sz.ask(1,i-1);
		apx(ans,(lint)i*sz-s-sz);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	int lst=nxi();
	lint ans=0;
	for(int i=2;i<=n;++i){
		const int x=nxi();
		if(x>=lst){
			dt[++cnd]=(data){lst,x};
			dt[++cnd]=(data){lst+m,x+m};
			dt[++cnd]=(data){lst+(m<<1),x+(m<<1)};
			ans+=x-lst;
		}
		else{
			dt[++cnd]=(data){lst,x+m};
			dt[++cnd]=(data){lst+m,x+(m<<1)};
			ans+=x+m-lst;
		}
		lst=x;
	}
	std::sort(dt+1,dt+cnd+1);
	printf("%lld\n",ans-solve());
	return 0;
}
