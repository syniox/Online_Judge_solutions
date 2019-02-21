#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=1e5+5;
int n,val[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> bool gcmp(const T a,const T b){
	return a>b;
}

inline bool jdg(){
	int x=1,y=1,lim_x;
	for(; x<n&&y+1<=val[x+1]; ++x,++y);
	if((val[x]-y)&1) return 1;
	for(lim_x=x; val[lim_x+1]>=y; ++lim_x);
	return (lim_x-x)&1;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	std::sort(val+1,val+n+1,gcmp<int>);
	puts(jdg()?"First":"Second");
	return 0;
}
