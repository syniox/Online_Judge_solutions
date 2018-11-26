#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int N=1e5+5;
int n,m,fa[N],dep[N],ch_tick[N];
struct data{
	int t,s;
	bool operator < (const data &b) const {
		return t<b.t;
	}
};
std::vector <data> sz[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int find_rt(int x,const int t){
	while(fa[x]&&ch_tick[x]<=t) x=fa[x];
	return x;
}

inline void merge(int x,int y,const int t){
	x=find_rt(x,t),y=find_rt(y,t);
	if(x==y) return;
	if(dep[x]<dep[y]){
		ch_tick[x]=t;
		fa[x]=y;
		sz[y].push_back((data){t,sz[x].back().s+sz[y].back().s});
	}
	else{
		ch_tick[y]=t;
		fa[y]=x;
		sz[x].push_back((data){t,sz[y].back().s+sz[x].back().s});
		if(dep[x]==dep[y]) ++dep[x];
	}
}

inline int calc(int x,int y,const int t){
	x=find_rt(x,t),y=find_rt(y,t);
	int sz1=(--std::upper_bound(sz[x].begin(),sz[x].end(),(data){t,0}))->s;
	if(x==y) return sz1;
	int sz2=(--std::upper_bound(sz[y].begin(),sz[y].end(),(data){t,0}))->s;
	return sz1+sz2;
}

inline int solve(const int x,const int y){
	int l=1,r=m,mid,aim=nxi();
	while(l!=r){
		mid=(l+r)>>1;
		if(calc(x,y,mid)>=aim) r=mid;
		else l=mid+1;
	}
	return l;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		sz[i].push_back((data){0,1});
	}
	for(int i=1;i<=m;++i){
		merge(nxi(),nxi(),i);
	}
	for(int q=nxi();q;--q){
		printf("%d\n",solve(nxi(),nxi()));
	}
	return 0;
}
