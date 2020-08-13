#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
const int N=1005,Q=1e5+5;
int n,m,q,pvld[N][N];//n行m列
bool vld[N*N],ans[Q];
struct qry_s{
	int x1,y1,x2,y2,id;
};
vector<int> vldbuk[N];
vector<qry_s> qbuk[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

namespace U{
	int fa[N*N];
	int qrt(const int x){
		return fa[x]?fa[x]=qrt(fa[x]):x;
	}
	void lnk(int x,int y){
		x=qrt(x),y=qrt(y);
		if(x!=y) fa[x]=y;
	}
}

inline int id(const int x,const int y){
	return (x-1)*m+y;
}
inline int qvld(const int x1,const int y1,const int x2,const int y2){
	assert(x1<=x2&&y1<=y2);
	assert(x1<=n&&x2<=n&&y1<=m&&y2<=m);
	assert(x1>0&&x2>0&&y1>0&&y2>0);
	return pvld[x2][y2]-pvld[x2][y1-1]-pvld[x1-1][y2]+pvld[x1-1][y1-1];
}

int main(){
	n=ni,m=ni,q=ni;
	for(int i=1; i<=n; ++i){
		static char str[N];
		scanf("%s",str+1);
		for(int j=1; j<=m; ++j){
			assert(i>=1&&j>=1&&i<=n&&j<=m);
			pvld[i][j]=pvld[i-1][j]+pvld[i][j-1]+(str[j]=='1')-pvld[i-1][j-1];
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			int l=0,r=min(n-i+1,m-j+1),mid;
			while(l!=r){
				mid=(l+r+1)>>1;
				if(qvld(i,j,i+mid-1,j+mid-1)) r=mid-1;
				else l=mid;
			}
			if(l) vldbuk[l].push_back(id(i,j));
			//eprintf("%d ",l);
		}
		//eprintf("\n");
	}
	for(int i=1; i<=q; ++i){
		int x1=ni,y1=ni,x2=ni,y2=ni,w=ni;
		if(x1<w||x2<w||y1<w||y2<w) continue;
		if(x1>n||x2>n||y1>m||y2>m) continue;
		qbuk[w].push_back((qry_s){x1-w+1,y1-w+1,x2-w+1,y2-w+1,i});
	}
	for(int i=min(n,m); i; --i){
		for(vector<int>::iterator it=vldbuk[i].begin(); it!=vldbuk[i].end(); ++it){
			int x=*it;
			vld[x]=1;
			//udlr
			if(x>m&&vld[x-m]) U::lnk(x,x-m);
			if(x+m<=n*m&&vld[x+m]) U::lnk(x,x+m);
			if(x%m!=1&&vld[x-1]) U::lnk(x,x-1);
			if(x%m&&vld[x+1]) U::lnk(x,x+1);
		}
		for(vector<qry_s>::iterator it=qbuk[i].begin(); it!=qbuk[i].end(); ++it){
			assert(it->x1>0&&it->y1>0&&it->x1<=n&&it->y1<=m);
			if(!vld[id(it->x1,it->y1)]) continue;
			ans[it->id]=U::qrt(id(it->x1,it->y1))==U::qrt(id(it->x2,it->y2));
		}
		//*/
	}
	for(int i=1; i<=q; ++i){
		puts(ans[i]?"Yes":"No");
	}
	return 0;
}
