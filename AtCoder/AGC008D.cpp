#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=502;
int n,xl[N*N];
bool vis[N*N];
struct reqst{
	int id,pos;
	bool operator < (const reqst &b) const {
		return pos<b.pos;
	}
}req[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool jdg(){
	int pt=1;
	for(int i=1;i<=n;++i){
		int need=req[i].id-1;
		for(;need;++pt){
			if(!vis[pt]){
				xl[pt]=req[i].id;
				--need;
			}
		}
		if(pt>req[i].pos) return 0;
	}
	pt=n*n;
	for(int i=n;i>=1;--i){
		int need=n-req[i].id;
		for(;need;--pt){
			if(!vis[pt]){
				xl[pt]=req[i].id;
				--need;
			}
		}
		if(pt<req[i].pos) return 0;
	}
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		req[i]=(reqst){i,nxi()};
		vis[req[i].pos]=1;
		xl[req[i].pos]=i;
	}
	std::sort(req+1,req+n+1);
	if(!jdg()) puts("No");
	else{
		puts("Yes");
		const int n2=n*n;
		for(int i=1;i<=n2;++i){
			printf("%d ",xl[i]);
		}
	}
	return 0;
}
