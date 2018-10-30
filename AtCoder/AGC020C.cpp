#include <iostream>
#include <cstdio>
#include <cstring>
#include <bitset>
int n,sum;
std::bitset<2000005> bt;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int solve(){
	for(int i=(sum+1)>>1;i<sum;++i){
		if(bt[i]) return i;
	}
	return -1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	bt[0]=1;
	for(int i=1;i<=n;++i){
		const int x=nxi();
		sum+=x;
		bt|=bt<<x;
	}
	printf("%d\n",solve());
}
