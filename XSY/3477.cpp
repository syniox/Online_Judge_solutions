#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;
const int N=505;
const double eps=1e-8;
int n,cnt_d,xval(-1e9);
lint val[N][N];
int _x1,_x2,_y1,_y2;
struct data{
	int l,r;
}dt[N*N];

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

template <class T> inline T abs(T &x){
	return x<0?-x:x;
}

namespace IO{
	char *ibuf;
	struct _Init{
		_Init(){ibuf=(char*)mmap(0,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);}
	}_init;
	inline int nxi(){
		int x=0;
		char c;
		while(((c=*ibuf++)>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=*ibuf++);
		while(x=x*10-48+c,(c=*ibuf++)>='0'&&c<='9');
		return f?-x:x;
	}
}
using IO::nxi;

bool jdg(const double tgt,const int i,const int j){
	double base=(j-i+1)*2*tgt,psum=0,step=tgt*2;
	double sumr=0;
	for(int k=1; k<=n; ++k){
		sumr+=val[j][k]-val[i-1][k]-step;
		if(sumr-psum>base) return 1;
		psum>sumr?psum=sumr:0;
	}
	return 0;
}

void get_ans(const double tgt,const int i,const int j){
	double base=(j-i+1)*2*tgt,psum=0,step=tgt*2;
	int lpos=0;
	double sumr=0;
	for(int k=1; k<=n; ++k){
		sumr+=val[j][k]-val[i-1][k]-step;
		if(sumr-psum+abs(tgt)*eps>base){
			_y1=lpos+1,_y2=k;
			return;
		}
		if(psum>sumr){
			psum=sumr,lpos=k;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	n=nxi();
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			val[i][j]=nxi();
			apx(xval,(int)val[i][j]);
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			val[i][j]+=val[i-1][j];
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=i; j<=n; ++j){
			dt[++cnt_d]=(data){i,j};
		}
	}
	std::random_shuffle(dt+1,dt+cnt_d+1);
	double ans=(double)xval/4-5;
	for(int t=1; t<=cnt_d; ++t){
		if(!jdg(ans,dt[t].l,dt[t].r)) continue;
		double l=ans,r=xval<0?0:(double)n*xval/4+5,mid; 
		while(r>l&&r-l>std::max(eps,abs(l)*eps)){
			mid=(l+r)/2;
			if(jdg(mid,dt[t].l,dt[t].r)) l=mid;
			else r=mid;
		}
		if(l>ans){
			ans=l;
			get_ans(l,dt[t].l,dt[t].r);
			_x1=dt[t].l,_x2=dt[t].r;
		}
	}
	printf("%.9lf\n",ans);
	printf("%d %d\n%d %d\n",_x1,_y1,_x2,_y2);
	return 0;
}
