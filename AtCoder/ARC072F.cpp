#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=5e5+5;
int n,q;
struct data{
	int w;
	double t;
};

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}

	template <class T>
		inline void apx(T &x,const T y){
			x<y?x=y:0;
		}

	template <class T>
		inline void apn(T &x,const T y){
			x>y?x=y:0;
		}
}
using namespace utils;

int main(){
	static data dq[N];
	double sumt=0;
	int hd=0,tl=0,sumw=0;
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		int t=nxi(),w=nxi();
		dq[tl++]=(data){w,(double)t};
		sumw+=w;
		sumt+=(lint)t*w;
		for(; tl-1>hd&&dq[tl-1].t<dq[tl-2].t; --tl){
			int oflow=std::max(0,dq[tl-2].w+dq[tl-1].w-q);
			sumw-=oflow;
			sumt-=dq[tl-2].t*oflow;
			assert(oflow<=dq[tl-2].w);
			int w0=dq[tl-2].w-oflow,w1=dq[tl-1].w;
			dq[tl-2].t=(dq[tl-2].t*w0+dq[tl-1].t*w1)/(w0+w1);
			dq[tl-2].w+=dq[tl-1].w-oflow;
		}
		for(; sumw>q&&hd<tl; ++hd){
			int wgt=std::min(sumw-q,dq[hd].w);
			dq[hd].w-=wgt;
			sumw-=wgt;
			sumt-=wgt*dq[hd].t;
			if(sumw==q) break;
		}
		assert(hd<tl);
		printf("%.8lf\n",sumt/sumw);
	}
	return 0;
}
