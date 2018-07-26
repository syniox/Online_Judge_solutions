#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstring>
#include<cmath>
using namespace std;
const int L=131072;
const double P=3.14159265359;
int n,bit,rev[L],ans[L],org[40000];
struct cpx{
	double x,y;
	cpx operator + (const cpx &b) const{
		return (cpx){x+b.x,y+b.y};
	}
	cpx operator - (const cpx &b) const{
		return (cpx){x-b.x,y-b.y};
	}
	cpx operator * (const cpx &b) const{
		return (cpx){x*b.x-y*b.y,x*b.y+y*b.x};
	}
}A[L],B[L];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	bit=17;
	for(int i=1;i<L;++i){
		rev[i]=rev[i>>1]>>1|(i&1)<<(bit-1);
	}
}

inline void fft(cpx *x,int f){
	for(int i=1;i<L;++i){
		if(i<rev[i]) swap(x[i],x[rev[i]]);
	}
	for(int i=1;i<L;i<<=1){
		const cpx t=(cpx){cos(P/i),f*sin(P/i)};
		for(int j=0;j<L;j+=i<<1){
			cpx w=(cpx){1,0};
			for(int k=0;k<i;w=w*t,++k){
				const cpx p=x[i+j+k]*w;
				x[i+j+k]=x[j+k]-p;
				x[j+k]=x[j+k]+p;
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("1728.in","r",stdin);
#endif
	init();
	n=nxi();
	for(int i=1;i<=n;++i){
		org[i]=nxi();
		++A[org[i]].x;
	}
	A[0].x=1;
	fft(A,1);
	memcpy(B,A,sizeof(B));
	for(int i=0;i<L;++i) A[i]=A[i]*A[i]*A[i];
	fft(A,-1);
	for(int i=1;i<L;++i){
		ans[i]=(int)(A[i].x/L+0.5);
	}
	for(int i=1;i<=n;++i){
		++A[org[i]<<1].x;
	}
	A[0].x=1;
	fft(A,1);
	for(int i=0;i<L;++i) A[i]=A[i]*B[i];
	fft(A,-1);
	for(int i=1;i<L;++i){
		ans[i]-=(int)(A[i].x/L+0.5);
	}
	for(int i=1;i<L;++i){
		if(ans[i]) printf("%d %d\n",i,ans[i]);
	}
	return 0;
}
