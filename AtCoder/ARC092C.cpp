#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
typedef long long lint;
const int N=105;
int n;
struct pnt{
	int x,y;
	friend bool operator < (const pnt &a,const pnt &b){
		return a.x<b.x;
	}
}pa[N],pb[N];
bool vis[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		pa[i].x=nxi(),pa[i].y=nxi();
	}
	for(int i=1; i<=n; ++i){
		pb[i].x=nxi(),pb[i].y=nxi();
	}
	std::sort(pb+1,pb+n+1);
	int ans=0;
	for(int i=1; i<=n; ++i){
		int res=0;
		for(int j=1; j<=n; ++j){
			if(!vis[j]&&pa[j].x<pb[i].x&&pa[j].y<pb[i].y&&pa[j].y>=pa[res].y){
				res=j;
			}
		}
		if(res) ans+=vis[res]=1;
	}
	printf("%d\n",ans);
	return 0;
}
