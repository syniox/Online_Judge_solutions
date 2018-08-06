#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=102;
int n,a[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool jdg(){
	int dis=a[n],tp=dis&1;
	if(a[1]!=(dis+1)>>1) return 0;
	if(a[n-1]!=dis||(a[1]==a[2])^tp){
		return 0;
	}
	tp+=1;
	if(a[tp+1]==a[1]) return 0;
	int ts=2;
	for(int i=tp+1;i<=n;++i){
		if(a[i]!=a[i-1]){
			if(ts<2||a[i]-a[i-1]>1) return 0;
			ts=0;
		}
		++ts;
	}
	return 1;

}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		a[i]=nxi();
	}
	std::sort(a+1,a+n+1);
	puts(jdg()?"Possible":"Impossible");
	return 0;
}
