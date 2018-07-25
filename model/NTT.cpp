#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long lint;
const int mod=998244353;
const int N=262145;
int l(1),bit,A[N],B[N],rev[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void twk(int &x){
	while(x>=mod) x-=mod;
}

int qpow(lint x,int t){
	int ans(1);
	for(;t;t>>=1,x=x*x%mod){
		if(t&1) ans=1ll*ans*x%mod;
	}
	return ans;
}

inline void NTT(int *a,const int f){
	for(int i=1;i<l;++i){
		if(i<rev[i]) swap(a[i],a[rev[i]]);
	}
	for(int i=1;i<l;i<<=1){
		int t=qpow(3,(mod-1)/(i<<1));
		if(f==-1) t=qpow(t,mod-2);
		for(int j=0;j<l;j+=i<<1){
			int w=1;
			for(int k=0;k<i;w=1ll*w*t%mod,++k){
				int p=1ll*a[j+i+k]*w%mod;
				twk(a[j+i+k]=a[j+k]-p+mod);
				twk(a[j+k]+=p);
			}
		}
	}
	if(f==1) return;
	int w=qpow(l,mod-2);
	for(int i=0;i<l;++i){
		a[i]=1ll*a[i]*w%mod;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("8.in","r",stdin);
#endif
	int n=nxi(),m=nxi();
	while(l<=n+m) l<<=1,++bit;
	for(int i=1;i<N;++i){
		rev[i]=rev[i>>1]>>1|(i&1)<<(bit-1);
	}
	for(int i=0;i<=n;++i) A[i]=nxi();
	for(int i=0;i<=m;++i) B[i]=nxi();
	NTT(A,1);
	NTT(B,1);
	for(int i=0;i<l;++i) A[i]=1ll*A[i]*B[i]%mod;
	NTT(A,-1);
	for(int i=0;i<=n+m;++i){
		printf("%d ",A[i]);
	}
	puts("");
	return 0;
}
