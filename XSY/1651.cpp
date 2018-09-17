#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long lint;
const int N=1e5+2,K=1048578,SQR=315;
int n,m,q,hx[N],ans,cnt[K];
lint cur,buf[N];
struct data{
	int l,r,id,sr;
	bool operator < (const data &b) const {
		return sr==b.sr?r<b.r:sr<b.sr;
	}
}dt[N];

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

inline void add(const int k){
	cur+=cnt[q^hx[k]];
	++cnt[hx[k]];
}

inline void del(const int k){
	--cnt[hx[k]];
	cur-=cnt[q^hx[k]];
}

inline void solve(){
	int xl=dt[1].l,xr=dt[1].l-1;
	for(int i=1;i<=m;++i){
		while(xl<dt[i].l) del(xl++);
		while(xl>dt[i].l) add(--xl);
		while(xr<dt[i].r) add(++xr);
		while(xr>dt[i].r) del(xr--);
		buf[dt[i].id]=cur;
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=hx[i-1]^nxi();
	}
	for(int i=1;i<=m;++i){
		dt[i].id=i;
		dt[i].l=nxi()-1,dt[i].r=nxi();
		dt[i].sr=dt[i].l/SQR;
	}
	std::sort(dt+1,dt+m+1);
	solve();
	for(int i=1;i<=m;++i){
		printf("%lld\n",buf[i]);
	}
	return 0;
}
