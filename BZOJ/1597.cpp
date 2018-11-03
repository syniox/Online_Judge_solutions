#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=5e4+5;
int n;
lint dp[N];
struct pnt{
	int x,y;
	bool operator < (const pnt &b) const {
		return x==b.x?y<b.y:x<b.x;
	}
}pt[N];

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

inline int uniq(){
	static pnt fp[N];
	memcpy(fp,pt,sizeof(fp));
	int ans=n;
	for(int i=1,j=0;i<=n;++i){
		while(j&&pt[j].y<fp[i].y){
			--j,--ans;
		}
		pt[++j]=fp[i];
	}
	return ans;
}

inline void solve(){
	static int que[N];
	int hd=0,tl=1;
	for(int i=1;i<=n;++i){
		for(int h1=que[hd],h2=que[hd+1];hd+1<tl;++hd,h1=h2,h2=que[hd+1]){
			if((lint)pt[i].x*(pt[h1+1].y-pt[h2+1].y)<dp[h2]-dp[h1]) break;
		}
		dp[i]=dp[que[hd]]+(lint)pt[que[hd]+1].y*pt[i].x;
		if(i==n) break;
		for(int t1,t2;hd+1<tl;--tl){
			t1=que[tl-2],t2=que[tl-1];
			if((dp[t2]-dp[t1])*(pt[t2+1].y-pt[i+1].y)<(dp[i]-dp[t2])*(pt[t1+1].y-pt[t2+1].y)){
				break;
			}
		}
		que[tl++]=i;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		pt[i].x=nxi(),pt[i].y=nxi();
	}
	std::sort(pt+1,pt+n+1);
	n=uniq();
	solve();
	printf("%lld\n",dp[n]);
	return 0;
}
