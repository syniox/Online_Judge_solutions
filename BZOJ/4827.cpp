#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const double P=3.14159265359;
const int N=65537;
int n,l(1),bit,sx(0),sy(0),sx2(0),sy2(0),rev[N<<2];
struct cpx{
	double x,y;
	cpx operator + (const cpx &b) const{
		return (cpx){x+b.x,y+b.y};
	}
	cpx operator - (const cpx &b) const{
		return (cpx){x-b.x,y-b.y};
	}
	cpx operator * (const cpx &b) const{
		//x*b.x  -  y*b.y
		return (cpx){x*b.x-y*b.y,x*b.y+y*b.x};
	}
}A[N<<2],B[N<<2];

inline int sq(const int &x){
	return x*x;
}

inline int pre_c(int c){
	return n*c*c+(c<<1)*(sx-sy);
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void fft(cpx *x,int f){
	for(int i=1;i<l;++i){
		if(i<rev[i]) swap(x[i],x[rev[i]]);
	}
	for(int i=1;i<l;i<<=1){//merge(len:i->2i)
		cpx t=(cpx){cos(P/i),f*sin(P/i)};//
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
#ifndef ONLINE_JUDGE
	freopen("8.in","r",stdin);
#endif
	n=nxi();
	nxi();
	while(l<n*3-1) l<<=1,++bit;
	for(int i=1;i<l;++i){
		rev[i]=rev[i>>1]>>1|(i&1)<<(bit-1);
	}
	for(int i=1;i<=n;++i){
		sx+=A[n-i].x=nxi();
		sx2+=sq(A[n-i].x);
	}
	for(int i=0;i<n;++i){
		sy+=B[i].x=B[i+n].x=nxi();
		sy2+=sq(B[i].x);
	}
	int c1=floor((double)(sy-sx)/n),c2=ceil((double)(sy-sx)/n);
	int ans(0),kc=pre_c(c1)<pre_c(c2)?c1:c2;

	fft(A,1);
	fft(B,1);
	for(int i=0;i<l;++i) A[i]=A[i]*B[i];
	fft(A,-1);
	for(int i=n;i<n<<1;++i){
		ans=max(ans,(int)round(A[i].x/l));
	}

	printf("%d\n",pre_c(kc)+sx2+sy2-(ans<<1));
	return 0;
}
