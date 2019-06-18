#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e6+5;
int n;
bool invld[N];
struct _pair{
	int x,y;
	friend bool operator < (const _pair &a,const _pair &b){
		return a.x<b.x;
	}
};

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void solve(){
	static _pair cur[N],nxt1[N],nxt2[N],nxt[N];
	int ccur=0,cnxt1=0,cnxt2=0;
	cur[++ccur]=(_pair){1,n};
	for(int i=n-1; i; --i){
		cnxt1=cnxt2=0;
		for(int j=1; j<=ccur; ++j){
			int l1=std::max(1,cur[j].x-i),r1=std::max(0,cur[j].y-i);
			if(l1<=r1) nxt1[++cnxt1]=(_pair){l1,r1};
			int l2=std::min(n+1,cur[j].x+i),r2=std::min(n,cur[j].y+i);
			if(l2<=r2) nxt2[++cnxt2]=(_pair){l2,r2};
		}
		std::merge(nxt1+1,nxt1+cnxt1+1,nxt2+1,nxt2+cnxt2+1,nxt+1);
		int cnt=1;
		for(int i=2; i<=cnxt1+cnxt2; ++i){
			if(nxt[i].x<=nxt[cnt].y) apx(nxt[cnt].y,nxt[i].y);
			else nxt[++cnt]=nxt[i];
		}
		nxt[0]=(_pair){0,0};
		nxt[cnt+1]=(_pair){n+1,n+1};
		ccur=0;
		for(int j=1; j<=cnt+1; ++j){
			if(nxt[j].x==nxt[j-1].y+1) continue;
			cur[++ccur]=(_pair){nxt[j-1].y+1,nxt[j].x-1};
		}
	}
	for(int i=1; i<=ccur; ++i){
		for(int j=cur[i].x; j<=cur[i].y; ++j){
			invld[j]=1;
		}
	}
}

int main(){
	n=nxi();
	solve();
	for(int q=nxi(); q; --q){
		putchar('0'+(invld[nxi()]^1));
	}
	puts("");
	return 0;
}
