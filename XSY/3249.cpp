#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005;
int n,q;
struct pnt{
	int x,y,c;
}pt[N];

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

inline int bel(int x1,int mx,int x2,int y1,int my,int y2,int a,int b){
	//左上 右上 左下 右下
	if(a<=mx&&b<=my) return 0;
	if(a<=mx&&b>my) return 1;
	if(a>mx&&b<=my) return 2;
	if(a>mx&&b>my) return 3;
	return assert(0),0;
}

inline int getnvl(int *c1,int *c2,int *c3){
	int ans=0,tot=0;
	for(int i=0; i<3; ++i){
		tot+=c1[i]+c2[i]+c3[i];
	}
	for(int i=0; i<3; ++i){
		for(int j=0; j<3; ++j){
			if(j==i) continue;
			int res=c1[i]+c2[j]+c3[3-i-j];
			apx(ans,res);
		}
	}
	return tot-ans;
}

int solve(int x1,int x2,int y1,int y2,int k,pnt *v,int len){
	if(len==0) return 0;
	int cnt[4][3],tot[4];
	if(k==0){
		assert(x1==x2&&y1==y2);
		return 0;
	}
	int mx=(x1+x2)>>1,my=(y1+y2)>>1;
	memset(cnt,0,sizeof(cnt));
	memset(tot,0,sizeof(tot));
	for(int i=0; i<len; ++i){
		++cnt[bel(x1,mx,x2,y1,my,y2,v[i].x,v[i].y)][v[i].c];
	}
	pnt *nv[4];
	for(int i=0; i<4; ++i){
		int sum=cnt[i][0]+cnt[i][1]+cnt[i][2];
		if(!sum) nv[i]=0;
		else nv[i]=new pnt[sum];
	}
	for(int i=0; i<len; ++i){
		int b=bel(x1,mx,x2,y1,my,y2,v[i].x,v[i].y);
		nv[b][tot[b]++]=v[i];
	}
	int ans=N;
	apn(ans,solve(x1,mx,y1,my,k-1,nv[0],tot[0])+getnvl(cnt[1],cnt[2],cnt[3]));
	apn(ans,solve(x1,mx,my+1,y2,k-1,nv[1],tot[1])+getnvl(cnt[0],cnt[2],cnt[3]));
	apn(ans,solve(mx+1,x2,y1,my,k-1,nv[2],tot[2])+getnvl(cnt[0],cnt[1],cnt[3]));
	apn(ans,solve(mx+1,x2,my+1,y2,k-1,nv[3],tot[3])+getnvl(cnt[0],cnt[1],cnt[2]));
	for(int i=0; i<4; ++i){
		if(nv[i]!=0) delete[] nv[i];
	}
	return ans;
}

int main(){
	q=nxi(),n=nxi();
	for(int i=0; i<n; ++i){
		pt[i].x=nxi(),pt[i].y=nxi();
		char c;
		while((c=getchar())<'A'||c>'Z');
		switch(c){
			case 'J': pt[i].c=0; break;
			case 'O': pt[i].c=1; break;
			case 'I': pt[i].c=2; break;
		}
	}
	printf("%d\n",solve(1,1<<q,1,1<<q,q,pt,n));
	return 0;
}
