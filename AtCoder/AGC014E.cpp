#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
#include <set>
typedef long long lint;
const int N=1e5+5;
int n,sz[N];
std::set <int> tr[N];
std::set <lint> exi;
std::queue <lint> que;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace U{
	int fa[N],sz[N];
	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
}

inline lint get_id(const int x,const int y){
	return (lint)x*n+y-1;
}

void ins(int x,int y){
	if(x>y) std::swap(x,y);
	std::set <lint> ::iterator it=exi.find(get_id(x,y));
	if(it!=exi.end()){
		que.push(get_id(x,y));
		tr[x].erase(y);
		tr[y].erase(x);
		exi.erase(*it);
	}
	else{
		exi.insert(get_id(x,y));
		tr[x].insert(y);
		tr[y].insert(x);
	}
}

bool solve(){
	for(int i=1; i<n; ++i){
		if(que.empty()) return 0;
		lint tmp=que.front();
		que.pop();
		int x=tmp/n,y=tmp-(lint)n*x+1;
		x=U::find_rt(x);
		y=U::find_rt(y);
		assert(x!=y);
		if(sz[x]>sz[y]) std::swap(x,y);
		sz[y]+=sz[x];
		U::fa[x]=y;
		for(std::set <int> ::iterator it=tr[x].begin(); it!=tr[x].end(); ++it){
			if(*it==y) continue;
			assert(U::find_rt(*it)==*it);
			tr[*it].erase(x);
			ins(y,*it);
		}
		tr[x].clear();
	}
	return 1;
}

int main(){
#ifdef LOCAL
	freopen("d.in","r",stdin);
#endif
	n=nxi();
	for(int i=1; i<=n; ++i) sz[i]=1;
	for(int i=1; i<n; ++i) ins(nxi(),nxi());
	for(int i=1; i<n; ++i) ins(nxi(),nxi());
	puts(solve()?"YES":"NO");
	return 0;
}
