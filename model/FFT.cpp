#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
const double P=3.14159265359*2;
const int N=262150;
int n,m,l=1,bit,rev[N];
struct cpx{
	double x,y;
	cpx operator + (cpx b){
		return (cpx){x+b.x,y+b.y};
	}
	cpx operator - (cpx b){
		return (cpx){x-b.x,y-b.y};
	}
	cpx operator * (cpx b){
		return (cpx){x*b.x-y*b.y,x*b.y+y*b.x};
	}
};
cpx a[N],b[N];
inline void fft(cpx *x,int f){
	for(int i=1;i<l;++i){
		if(i<rev[i]) swap(x[i],x[rev[i]]);//modify order
	}
	for(int i=1;i<l;i<<=1){//ith merge(len:2i)
		cpx t=(cpx){cos(P/(i<<1)),f*sin(P/(i<<1))};//
		for(int j=0;j<l;j+=i<<1){
			cpx w=(cpx){1,0};
			for(int k=0;k<i;w=w*t,++k){
				cpx p=x[j+k+i]*w;//
				x[j+k+i]=x[j+k]-p;
				x[j+k]=x[j+k]+p;
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;++i) scanf("%lf",&a[i].x);
	for(int i=0;i<=m;++i) scanf("%lf",&b[i].x);
	while(l<=m+n) l<<=1,++bit;
	for(int i=1;i<l;++i){
		rev[i]=rev[i>>1]>>1|(i&1)<<bit-1;//dp;
	}
	fft(a,1);
	fft(b,1);
	for(int i=0;i<l;++i) a[i]=a[i]*b[i];
	fft(a,-1);
	for(int i=0;i<=n+m;++i){
		a[i].x=a[i].x/l+0.5;//
		printf("%d ",(int)a[i].x);
	}
	return 0;
}
