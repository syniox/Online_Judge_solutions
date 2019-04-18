#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <emmintrin.h>
const int N=108;
const double eps=1e-12;
int n,m,qx,qy;
double mat[2][N][N],res[N][N];
//ans(i,j)=\sum(k<m) mat[i][j][k]*(0,k)+mat[i][j][m],滚动i

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline T abs(T x){
	return x<0?-x:x;
}

inline void m128d_mul(double *a,int len,double wgt){
	assert((len&1)==0);
	__m128d *ptr=(__m128d*)a;
	__m128d mwgt(_mm_set1_pd(wgt));
	for(int i=0; i<len; ++ptr,i+=2,a+=2){
		_mm_store_pd(a,_mm_mul_pd(*ptr,mwgt));
	}
}

inline void m128d_sub(double *a,double *b,int len){
	assert((len&1)==0);
	__m128d *pa=(__m128d*)a;
	__m128d *pb=(__m128d*)b;
	for(int i=0; i<len; ++pa,++pb,a+=2,b+=2,i+=2){
		_mm_store_pd(a,_mm_sub_pd(*pa,*pb));
	}
}

inline void m128d_mul_to(double *a,double wgt,double *b,int len){
	assert((len&1)==0);
	__m128d *pa=(__m128d*)a;
	__m128d *pb=(__m128d*)b;
	__m128d mwgt(_mm_set1_pd(wgt));
	for(int i=0; i<len; ++pa,++pb,b+=2,i+=2){
		_mm_store_pd(b,_mm_add_pd(*pb,_mm_mul_pd(*pa,mwgt)));
	}
}

inline void m128d_add_mul_to(double *a,double *b,double wgt,double *c,int len){
	assert((len&1)==0);
	__m128d *pa=(__m128d*)a;
	__m128d *pb=(__m128d*)b;
	__m128d mwgt(_mm_set1_pd(wgt));
	for(int i=0; i<len; ++pa,++pb,i+=2,c+=2){
		_mm_store_pd(c,_mm_mul_pd(_mm_add_pd(*pa,*pb),mwgt));
	}
}

double gauss(double mtx[N][N],int n){
	static double tmp[N],res[N];
	const int end=(n+1)+((n+1)&1);
	for(int i=0; i<n; ++i){
		int j=i;
		while(j<n&&abs(mtx[j][i])<eps) ++j;
		if(j==n) return 0;
		if(i!=j){
			for(int k=0; k<=n; ++k){
				std::swap(mtx[j][k],mtx[i][k]);
			}
		}
		int spos=i-(i&1),len=end-spos;
		assert((len&1)==0);
		for(int j=i+1; j<n; ++j){
			if(abs(mtx[j][i])<eps) continue;
			memcpy(tmp,mtx[i]+spos,len*sizeof(double));
			double wgt=mtx[j][i]/mtx[i][i];
			m128d_mul(tmp,len,wgt);
			m128d_sub(mtx[j]+spos,tmp,len);
		}
	}
	for(int i=n-1; ~i; --i){
		if(!mtx[i][i]) continue;
		double w=mtx[i][n];
		for(int j=i+1; j<n; ++j){
			w+=mtx[i][j]*res[j];
		}
		res[i]=w/-mtx[i][i];
	}
	return res[0];
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	n=nxi(),m=nxi(),qx=nxi(),qy=nxi();
	for(int i=0; i<m; ++i){
		mat[n&1][i][i]=1;
	}
	for(int i=n-1; ~i; --i){
		int p=i&1,len=(m+1)+((m+1)&1);
		memset(mat[p],0,sizeof(mat[p]));
		if(i!=qx){
			double d=0.5;
			for(int j=0; j<m; ++j,d*=0.5){
				m128d_mul_to(mat[p^1][j],d,mat[p][0],len);
			}
			d*=2;
			double w=1.0/(1.0-d);
			mat[p][0][m]+=2.0-d*2;
			for(int k=0; k<=m; ++k){
				mat[p][0][k]*=w;
			}
			memcpy(mat[p][m],mat[p][0],(m+1)*sizeof(double));
			for(int j=m-1; j; --j){
				m128d_add_mul_to(mat[p][j+1],mat[p^1][j],0.5,mat[p][j],len);
				mat[p][j][m]+=1.0;
			}
		}
		else{
			for(int j=qy-1; ~j; --j){
				m128d_add_mul_to(mat[p][j+1],mat[p^1][j],0.5,mat[p][j],len);
				mat[p][j][m]+=1.0;
			}
			memcpy(mat[p][m],mat[p][0],(m+1)*sizeof(double));
			for(int j=m-1; j>qy; --j){
				m128d_add_mul_to(mat[p][j+1],mat[p^1][j],0.5,mat[p][j],len);
				mat[p][j][m]+=1.0;
			}
		}
	}
	memcpy(res,mat[0],sizeof(res));
	for(int i=0; i<m; ++i){
		res[i][i]-=1.0;
	}
	printf("%.6lf\n",gauss(res,m));
	return 0;
}
