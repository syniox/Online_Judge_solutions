#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
const int N=50005;
const double eps=1e-3;
int n,m,q;

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

namespace S{
	int ans[2];
	double st[2][N],sp[2][N];
	bool vis[2][N];

	inline bool get(const double tick){
		double hx[2]={-1e12};
		for(int i=0; i<2; ++i){
			for(int j=1; j<=n; ++j){
				if(vis[i][j]) continue;
				apx(hx[i],sp[i][j]*(tick-st[i][j]));
			}
		}
		if(hx[0]+hx[1]-m<eps) return 0;
		for(int i=0; i<2; ++i){
			for(int j=1; j<=n; ++j){
				if(fabs(sp[i][j]*(tick-st[i][j])-hx[i])<=eps){
					ans[i]=j;
					break;
				}
			}
		}
		return 1;
	}

	inline void solve(){
		static double last=0;
		double l=last,r=1e9,mid;
		while(r-l>eps){
			mid=(l+r)/2;
			if(get(mid)) r=mid;
			else l=mid;
		}
//		printf("time: %.3lf\n",l);
		last=l;
		vis[0][ans[0]]=vis[1][ans[1]]=1;
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		using namespace S;
		st[0][i]=nxi(),sp[0][i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		using namespace S;
		st[1][i]=nxi(),sp[1][i]=nxi();
	}
	for(int i=1; i<=q; ++i){
		S::solve();
		printf("%d %d\n",S::ans[0],S::ans[1]);
	}
	return 0;
}
