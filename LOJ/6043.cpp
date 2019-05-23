#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=105;
int n,nxt[N],ccir,pos[N];
bool vis[N],ans[N];
//0左1右

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

bool dfs(const int t,int psum){
	int cur=t>ccir?n:pos[t]-1;
	for(int i=t==1?1:pos[t-1]; i<=cur; ++i){
		if((psum+=ans[i]?-1:1)<0) return 0;
	}
	if(t>ccir){
		for(int i=1; i<=n; ++i){
			putchar(ans[i]?')':'(');
		}
		putchar('\n');
		return 1;
	}
	bool p=0;
	for(int i=pos[t]; ; p^=1,i=nxt[i]){
		ans[i]=p;
		if(nxt[i]==pos[t]) break;
	}
	if(dfs(t+1,psum)) return 1;
	p=1;
	for(int i=pos[t]; ; p^=1,i=nxt[i]){
		ans[i]=p;
		if(nxt[i]==pos[t]) break;
	}
	return dfs(t+1,psum);
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		nxt[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		if(vis[i]) continue;
		int sz=0;
		for(int j=i; !vis[j]; j=nxt[j]){
			++sz;
			vis[j]=1;
		}
		if(sz>2) pos[++ccir]=i;
		else{
			ans[i]=0;
			ans[nxt[i]]=1;
		}
	}
	dfs(1,0);
	return 0;
}
