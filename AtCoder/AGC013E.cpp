#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int m,n,q;

namespace IO{
	char *ibuf;
	struct _Init{
		_Init(){ibuf=(char*)mmap(0,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);}
	}_init;
	inline int nxi(){
		int x=0;
		char c;
		while((c=*ibuf++)>'9'||c<'0');
		while(x=x*10-48+c,(c=*ibuf++)>='0'&&c<='9');
		return x;
	}
}
using IO::nxi;

struct mtrx{
	int n[3][3];

	friend inline mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		for(int i=0; i<3; ++i){
			for(int j=0; j<3; ++j){
				lint tmp=0;
				for(int k=0; k<3; ++k){
					tmp+=(lint)a.n[i][k]*b.n[k][j];
				}
				c.n[i][j]=tmp%mod;
			}
		}
		return c;
	}
}nxt_0[30],nxt_1;

struct vec{
	int n[3];

	vec operator * (const mtrx &b) const{
		vec c;
		c.n[0]=((lint)n[0]*b.n[0][0]+(lint)n[1]*b.n[1][0]+(lint)n[2]*b.n[2][0])%mod;
		c.n[1]=((lint)n[0]*b.n[0][1]+(lint)n[1]*b.n[1][1]+(lint)n[2]*b.n[2][1])%mod;
		c.n[2]=((lint)n[0]*b.n[0][2]+(lint)n[1]*b.n[1][2]+(lint)n[2]*b.n[2][2])%mod;
		return c;
	}
};

inline int hbit(int x){
	int ans=0;
	for(int i=16; i; i>>=1){
		if(x>>i) x>>=i,ans+=i;
	}
	return ans;
}

void build_mtrx(){
	nxt_0[0].n[0][0]=1,nxt_0[0].n[0][1]=2,nxt_0[0].n[0][2]=1;
	nxt_0[0].n[1][0]=0,nxt_0[0].n[1][1]=1,nxt_0[0].n[1][2]=1;
	nxt_0[0].n[2][0]=1,nxt_0[0].n[2][1]=2,nxt_0[0].n[2][2]=2;
	nxt_1.n[0][0]=1,nxt_1.n[0][1]=2,nxt_1.n[0][2]=1;
	nxt_1.n[1][0]=0,nxt_1.n[1][1]=1,nxt_1.n[1][2]=1;
	nxt_1.n[2][0]=0,nxt_1.n[2][1]=0,nxt_1.n[2][2]=1;
	for(int i=1; i<30; ++i){
		nxt_0[i]=nxt_0[i-1]*nxt_0[i-1];
	}
}

inline void jmp(vec &dp,int len){
	for(int i=hbit(len); ~i; --i){
		if(len>>i&1) dp=dp*nxt_0[i];
	}
}

int main(){
	m=nxi(),n=nxi();
	build_mtrx();
	vec dp=(vec){{1,0,0}};
	for(int lst=-1,i=1; i<=n; ++i){
		int x=nxi();
		jmp(dp,x-lst-1);
		dp=dp*nxt_1;
		if(i==n) jmp(dp,m-x-1);
		lst=x;
	}
	if(!n) jmp(dp,m);
	printf("%d\n",dp.n[2]);
	return 0;
}
