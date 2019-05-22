#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
int pow10[]={(int)1e0,(int)1e1,(int)1e2,(int)1e3,(int)1e4,
	(int)1e5,(int)1e6,(int)1e7,(int)1e8,(int)1e9};

inline char getres(lint x){
	printf("? %lld\n",x);
	fflush(stdout);
	char c;
	while((c=getchar())!='Y'&&c!='N');
	return c;
}

int main(){
	if(getres(1e10)=='Y'){
		int l=0,r=9,mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(getres(2*pow10[mid])=='Y') r=mid;
			else l=mid+1;
		}
		printf("! ");
		putchar('1');
		while(l--) putchar('0');
		puts("");
		fflush(stdout);
	}
	else{
		int len;
		{
			int l=0,r=9,mid;
			while(l!=r){
				mid=(l+r+1)>>1;
				if(getres(pow10[mid])=='N') r=mid-1;
				else l=mid;
			}
			len=l;
		}
		if(len==9){
			printf("! %d\n",(int)1e9);
			fflush(stdout);
			return 0;
		}
		int l=pow10[len],r=pow10[len+1]-1,mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(getres(mid*10ll)=='Y') r=mid;
			else l=mid+1;
		}
		printf("! %d\n",l);
		fflush(stdout);
	}
	return 0;
}
