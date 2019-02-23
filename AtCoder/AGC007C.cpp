#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
	int n=nxi();
	double d=nxi(),k=nxi(),ans=0;
	for(; n; --n){
		ans+=(d+(d+k*((n<<1)-1)))/2;
		d=(((n+1)<<1)*d+k*5)/(n<<1);
		k=((double)n*2+4)/(n<<1)*k;
	}
	printf("%.9lf\n",ans);
}
