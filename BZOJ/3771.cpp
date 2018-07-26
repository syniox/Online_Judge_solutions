#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long lint;
const int L=131072;
const double P=acos(-1);
int n,rev[L],org[40001];
lint ans[L];
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
	const int bit=17;
	for(int i=1;i<L;++i){
		rev[i]=rev[i>>1]>>1|(i&1)<<(bit-1);
	}
}

inline void fft(cpx *x,const int f){
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
//	freopen("1728.out","w",stdout);
#endif
	init();
	n=nxi();
	for(int i=1;i<=n;++i){
		org[i]=nxi();
		++A[org[i]].x;
	}
//3
	fft(A,1);
	memcpy(B,A,sizeof(B));
	for(int i=0;i<L;++i) A[i]=A[i]*A[i]*A[i];
	fft(A,-1);
	for(int i=1;i<L;++i){
		ans[i]=(lint)(A[i].x/L+0.5);
	}
	memset(A,0,sizeof(A));
	for(int i=1;i<=n;++i){
		++A[org[i]<<1].x;
	}
	fft(A,1);
	for(int i=0;i<L;++i) A[i]=A[i]*B[i];
	fft(A,-1);
	for(int i=1;i<L;++i){
		ans[i]-=(lint)(A[i].x/L+0.5)*3;
	}
	for(int i=1;i<=n;++i) ans[org[i]*3]+=2;
	for(int i=0;i<L;++i) ans[i]/=6;

	//2
	for(int i=0;i<L;++i) B[i]=B[i]*B[i];
	fft(B,-1);
	for(int i=1;i<=n;++i) B[org[i]<<1].x-=L;
	for(int i=1;i<L;++i){
		ans[i]+=(lint)(B[i].x/L+0.5)>>1;
	}


	for(int i=1;i<=n;++i){
		++ans[org[i]];
	}
	for(int i=1;i<L;++i){
		if(ans[i]) printf("%d %lld\n",i,ans[i]);
	}
	return 0;
}
