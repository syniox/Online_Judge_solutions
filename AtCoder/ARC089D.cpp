#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005;
int n,q,mp[N*2][N*2][2];

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

inline int gets(const int x1,const int x2,const int y1,const int y2,const bool c){
	if(x1>x2||y1>y2) return 0;
	return mp[x2][y2][c]-(x1?mp[x1-1][y2][c]:0)-(y1?mp[x2][y1-1][c]:0)+(x1&&y1?mp[x1-1][y1-1][c]:0);
}

inline int split(const int x,const int y,const bool c){
	int m=(q<<1)-1,ans=0;
	ans+=gets(0,x,0,y,c)+gets(0,x,y+1,y+q,c^1)+gets(0,x,y+q+1,m,c);
	ans+=gets(x+1,x+q,0,y,c^1)+gets(x+1,x+q,y+1,y+q,c)+gets(x+1,x+q,y+q+1,m,c^1);
	ans+=gets(x+q+1,m,0,y,c)+gets(x+q+1,m,y+1,y+q,c^1)+gets(x+q+1,m,y+q+1,m,c);
	return ans;
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		const int a=nxi()%(q<<1),b=nxi()%(q<<1);
		char c;
		while((c=getchar())!='W'&&c!='B');
		++mp[a][b][c=='W'];
	}
	for(int i=0; i<q<<1; ++i){
		for(int j=1; j<q<<1; ++j){
			mp[i][j][0]+=mp[i][j-1][0];
			mp[i][j][1]+=mp[i][j-1][1];
		}
	}
	for(int i=1; i<q<<1; ++i){
		for(int j=0; j<q<<1; ++j){
			mp[i][j][0]+=mp[i-1][j][0];
			mp[i][j][1]+=mp[i-1][j][1];
		}
	}
	int ans=0;
	for(int i=-1; i<q; ++i){
		for(int j=-1; j<q; ++j){
			//printf("(%d %d) ",split(i,j,0),split(i,j,1));
			apx(ans,split(i,j,0));
			apx(ans,split(i,j,1));
		}
		//puts("");
	}
	printf("%d\n",ans);
	return 0;
}
