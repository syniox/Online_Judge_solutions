#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
using namespace std;
const int N=20005,M=7;
const double eps=1e-9;
int n,m;
struct vec_s{
	double v[M];
	friend vec_s operator+(const vec_s &a,const vec_s &b);
	friend vec_s operator-(const vec_s &a,const vec_s &b);
	vec_s operator*(const double w);
	double len2();
}pnt[N];

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
			const bool f=(c=='-')&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

vec_s operator+(const vec_s &a,const vec_s &b){
	vec_s c;
	for(int i=0; i<m; ++i){
		c.v[i]=a.v[i]+b.v[i];
	}
	return c;
}
vec_s operator-(const vec_s &a,const vec_s &b){
	vec_s c;
	for(int i=0; i<m; ++i){
		c.v[i]=a.v[i]-b.v[i];
	}
	return c;
}
vec_s vec_s::operator*(const double w){
	vec_s res;
	for(int i=0; i<m; ++i){
		res.v[i]=v[i]*w;
	}
	return res;
}
double vec_s::len2(){
	double ans=0;
	for(int i=0; i<m; ++i){
		ans+=v[i]*v[i];
	}
	return ans;
}

vec_s gauss(double mtx[M][M],const int n){
	for(int i=1; i<=n; ++i){
		int j=i;
		for(; j<=n&&cabs(mtx[j][i])<eps; ++j);
		assert(j<=n);
		if(j!=i){
			for(int k=0; k<=n; ++k)
				swap(mtx[j][k],mtx[i][k]);
		}
		for(int k=i+1; k<=n; ++k){
			double wgt=mtx[k][i]/mtx[j][i];
			if(cabs(wgt)<eps) continue;
			mtx[k][0]-=mtx[j][0]*wgt;
			for(int l=i; l<=n; ++l){
				mtx[k][l]-=mtx[j][l]*wgt;
			}
		}
	}
	vec_s res;
	for(int i=n; i>=1; --i){
		double wgt=mtx[i][0];
		for(int j=i+1; j<=n; ++j)
			wgt+=mtx[i][j]*res.v[j];
		res.v[i]=-wgt/mtx[i][i];
	}
	return res;
}

vec_s getctr(vec_s vc[],const int cvc,double &r2){
	static double mtx[M][M];
	memset(mtx,0,sizeof(mtx));
	for(int i=1; i<cvc; ++i){
		for(int l=1; l<cvc; ++l){
			double w=0;
			for(int j=0; j<m; ++j){
				w+=(vc[i+1].v[j]-vc[i].v[j])*(vc[l].v[j]-vc[cvc].v[j]);
			}
			mtx[i][l]=2*w;
		}
		for(int j=0; j<m; ++j){
			const double b=vc[i+1].v[j],a=vc[i].v[j];
			mtx[i][0]+=2*(b-a)*vc[cvc].v[j];
			mtx[i][0]-=b*b-a*a;
		}
	}
	vec_s wgt=gauss(mtx,cvc-1);
	vec_s res=vc[cvc];
	for(int i=1; i<cvc; ++i){
		res=res+(vc[i]-vc[cvc])*wgt.v[i];
	}
	r2=(res-vc[cvc]).len2();
	return res;
}

vec_s solve(const int n,double &r2,const int creq){
	static vec_s req[M];
	if(n==1&&!creq) return r2=0,pnt[1];
	if(!n) return getctr(req,creq,r2);
	vec_s res=solve(n-1,r2,creq);
	if((pnt[n]-res).len2()-eps<r2) return res;
	assert(creq<=m);
	req[creq+1]=pnt[n];
	return solve(n-1,r2,creq+1);
}

int main(){
	n=ni,m=ni;
	for(int i=1; i<=n; ++i){
		for(int j=0; j<m; ++j){
			scanf("%lf",pnt[i].v+j);
		}
	}
	random_shuffle(pnt+1,pnt+n+1);
	double r;
	vec_s res=solve(n,r,0);
	for(int i=0; i<m; ++i){
		printf("%.6lf ",res.v[i]);
	}
	puts("");
	return 0;
}
