#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cassert>
const int L=3e5+2;
const int N=524289;
const double P=acos(-1.0);
double mp[26];
int len,bit,rev[N];
struct cpx{
	double x,y;
	cpx operator + (const cpx &b) const {
		return (cpx){x+b.x,y+b.y};
	}
	cpx operator - (const cpx &b) const {
		return (cpx){x-b.x,y-b.y};
	}
	cpx operator * (const cpx &b) const {
		return (cpx){x*b.x-y*b.y,x*b.y+y*b.x};
	}
}A[N],B[N],fw[N],wf[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int highbit(int x){
	int ans=0;
	if(x>>16) ans+=16,x>>=16;
	if(x>>8) ans+=8,x>>=8;
	if(x>>4) ans+=4,x>>=4;
	if(x>>2) ans+=2,x>>=2;
	if(x>>1) ans+=1;
	return ans;
}

inline void init(){
	for(int i=0;i<26;++i){
		mp[i]=1.0/('a'+i);
	}
	for(int i=1;i<len;++i){
		rev[i]=rev[i>>1]>>1|(i&1)<<(bit-1);
	}
	fw[0]=(cpx){1,0};
	for(int i=1;i<len;++i){
		fw[i]=(cpx){cos(P*i/len),sin(P*i/len)};
	}
}

inline void fft(cpx *x,int f){
	for(int i=1;i<len;++i){
		if(i<rev[i]) std::swap(x[i],x[rev[i]]);
	}
	for(int i=1;i<len;i<<=1){
		int dw=len/i;
		for(int j=0;j<len;j+=i<<1){
			for(int k=0;k<i;++k){
				cpx tp=fw[k*dw];
				if(f==-1) tp.y=-tp.y;
				cpx p=x[i+j+k]*tp;
				x[i+j+k]=x[j+k]-p;
				x[j+k]=x[j+k]+p;
			}
		}
	}
	if(f==-1){
		for(int i=0;i<len;++i) x[i].x/=len;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("1.in","r",stdin);
#endif
	static char s[N];
	int l1=nxi(),l2=nxi();
	bit=highbit(l1+l2-1)+1;
	len=1<<bit;
	init();

	scanf("%s",s+1);
	for(int i=1;i<=l1;++i){
		if(s[i]!='*') A[l1-i].x=mp[s[i]-'a'];
	}
	scanf("%s",s+1);
	for(int i=1;i<=l2;++i){
		if(s[i]!='*') B[i-1].x=s[i];
	}
	fft(A,1);
	fft(B,1);
	for(int i=0;i<len;++i) B[i]=A[i]*B[i];
	fft(B,-1);

	static int ans[N];
	int cnt=0;
	for(int i=l1-1;i<l2;++i){
		if(fabs(round(B[i].x)-B[i].x)<1e-5) ans[++cnt]=i-l1+2;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;++i){
		printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
