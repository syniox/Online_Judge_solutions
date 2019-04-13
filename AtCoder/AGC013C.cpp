#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;
const int N=1e5+5;
int n,len,q,pos[N];
int turn_0,turn_1,cnt_0,cnt_1,buk_0[N],buk_1[N];

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

int main(){
	n=nxi(),len=nxi(),q=nxi();
	int cyc=q/len,rest=q-cyc*len;
	lint dlt=0;
	for(int i=1; i<=n; ++i){
		int pos=nxi();
		if(nxi()==1){
			dlt+=cyc;
			int tgt=pos+rest;
			if(tgt>=len) ++dlt,tgt-=len;
			else turn_0=cnt_0+1;
			buk_0[++cnt_0]=tgt;
		}
		else{
			dlt-=cyc;
			int tgt=pos-rest;
			if(tgt<0){
				--dlt,tgt+=len;
				turn_1=cnt_1+1;
			}
			buk_1[++cnt_1]=tgt;
		}
	}
	for(int c=1,i=1,j=turn_0+1,k=1,l=turn_1+1; c<=n; ++c){
		int type=0,nval=1e9;
		if(i<=turn_0&&buk_0[i]<nval)
			nval=buk_0[i],type=1;
		if(j<=cnt_0&&buk_0[j]<nval)
			nval=buk_0[j],type=2;
		if(k<=turn_1&&buk_1[k]<nval)
			nval=buk_1[k],type=3;
		if(l<=cnt_1&&buk_1[l]<nval)
			nval=buk_1[l],type=4;
		pos[c]=nval;
		switch(type){
			case 1: ++i; break;
			case 2: ++j; break;
			case 3: ++k; break;
			case 4: ++l; break;
		}
	}
	dlt%=n;
	if(dlt<0) dlt+=n;
	for(int i=dlt+1; i<=n; ++i){
		printf("%d\n",pos[i]);
	}
	for(int i=1; i<=dlt; ++i){
		printf("%d\n",pos[i]);
	}
	return 0;
}
