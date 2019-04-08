/*
first pos with 1 after different:
  >l's first 1: *
  =l's first 1: >=l||<=r
  <l's first 1: none
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;

namespace IO{
	char *ibuf;
	struct _Init{
		_Init(){ibuf=(char*)mmap(0,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);}
	}_init;
	template <class T> inline T nxi(){
		T x=0;
		char c;
		while((c=*ibuf++)>'9'||c<'0');
		while(x=x*10-48+c,(c=*ibuf++)>='0'&&c<='9');
		return x;
	}
}
using IO::nxi;

template <class T> inline int hbit(T x){
	int ans=0;
	for(int i=32; i; --i){
		if(x>>i) x>>=i,ans+=i;
	}
	return ans;
}

inline lint solve(lint l,lint r){
	int dpos=hbit(l^r);//first different pos
	l&=(1ll<<(dpos+1))-1;
	r&=(1ll<<(dpos+1))-1;
	if(r!=1ll<<dpos) r|=(1ll<<hbit(r^1ll<<dpos))-1;
	return (((1ll<<dpos)-l)<<1)+(std::min((l^1ll<<dpos)-1,r)+1-(1ll<<dpos));
}

int main(){
	for(int T=nxi<int>(); T; --T){
		int n=nxi<int>();
		const lint l=nxi<lint>(),r=nxi<lint>();
		if(n==1||r==l) printf("%lld\n",r-l+1);
		else printf("%lld\n",solve(l,r));
	}
	return 0;
}
