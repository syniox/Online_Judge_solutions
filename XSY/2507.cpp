#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2e5+5;
int n,pa[N],pb[N],pc[N];
lint sum;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool solve(){
	static int cnt[32];
	if(sum%(n*2)||(n==1&&pb[1]!=pc[1])) return 0;
	sum/=(n*2);
	for(int i=1; i<=n; ++i){
		if((pb[i]+pc[i]-sum)%n) return 0;
		pa[i]=(pb[i]+pc[i]-sum)/n;
		for(int j=31; ~j; --j) cnt[j]+=(pa[i]>>j)&1;
	}
	for(int i=1; i<=n; ++i){
		lint sumb=0,sumc=0;
		for(int j=31; ~j; --j){
			sumb+=(1ll<<j)*((pa[i]>>j)&1?cnt[j]:0);
			sumc+=(1ll<<j)*((pa[i]>>j)&1?n:cnt[j]);
			if(sumb>pb[i]||sumc>pc[i]) break;
		}
		if(sumb!=pb[i]||sumc!=pc[i]) return 0;
	}
	for(int i=1; i<=n; ++i){
		printf("%d ",pa[i]);
	}
	puts("");
	return 1;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i) sum+=(pb[i]=nxi());
	for(int i=1; i<=n; ++i) sum+=(pc[i]=nxi());
	if(!solve()) puts("-1");
	return 0;
}
