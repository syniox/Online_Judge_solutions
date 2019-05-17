#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e4+5;
const double eps=1e-14;
int n;
double q,len[N],wgt[N],spd[N];

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

double getspd(const int x,const double tgt){
	double s=-1.0/tgt;
	double l=std::max(0.0,spd[x]),r=1e4,mid;
	while(r-l>eps){
		mid=(l+r)/2;
		if(wgt[x]*mid*mid*(2*mid-2*spd[x])>s) r=mid;
		else l=mid;
	}
	return l;
}

bool jdg(const double tgt){
	double ans=0;
	for(int i=1; i<=n; ++i){
		double v=getspd(i,tgt);
		v=wgt[i]*(v-spd[i])*(v-spd[i])*len[i];
		if((ans+=v)>q) return 0;
	}
	return 1;
}

double getwgt(){
	double l=-1e2,r=0,mid;
	while(r-l>eps){
		mid=(l+r)/2;
		if(jdg(mid)) l=mid;
		else r=mid;
	}
	return l;
}

int main(){
	n=nxi();
	scanf("%lf",&q);
	for(int i=1; i<=n; ++i){
		scanf("%lf%lf%lf",len+i,wgt+i,spd+i);
	}
	double res=getwgt(),ans=0;
	for(int i=1; i<=n; ++i){
		ans+=len[i]/getspd(i,res);
	}
	printf("%.8lf\n",ans);
	return 0;
}
