#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=1e6+5;
int n,m,xval;
struct edge{
	int x,y;
};
std::vector <edge> bukv[(int)1e5];

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

namespace U{
	int fa[N],sz[N];
	inline void init(){
		for(int i=1; i<=n; ++i) sz[i]=1;
	}
	int find_rt(int x){
		while(fa[x]) x=fa[x];
		return x;
	}
	int merge(const int x,const int y){
		if(x==y) return 0;
		assert(x==find_rt(x));
		assert(y==find_rt(y));
		if(sz[x]<sz[y]){
			sz[y]+=sz[x];
			fa[x]=y;
			return x;
		}
		sz[x]+=sz[y];
		fa[y]=x;
		return y;
	}
	void split(const int x){
		assert(fa[x]&&fa[fa[x]]==0);
		sz[fa[x]]-=sz[x];
		fa[x]=0;
	}
}

void add_e(int *stk,int &top,const int v){
	for(std::vector <edge> ::iterator it=bukv[v].begin(); it!=bukv[v].end(); ++it){
		int x=U::find_rt(it->x),y=U::find_rt(it->y);
		if(x!=y) stk[++top]=U::merge(x,y);
	}
}

int solve(const int l,const int r){
	static int stk[N],top;
	if(l==r) return top==n-1?l:-1;
	const int lst_top=top,mid=(l+r)>>1;
	int res=-1;
	for(int i=mid+1; i<=r; ++i){
		add_e(stk,top,i);
	}
	res=solve(l,mid);
	if(~res) return res;
	for(; top>lst_top; --top){
		U::split(stk[top]);
	}
	for(int i=l; i<=mid; ++i){
		add_e(stk,top,i);
	}
	res=solve(mid+1,r);
	if(~res) return res;
	for(; top>lst_top; --top){
		U::split(stk[top]);
	}
	return -1;
}

int main(){
	n=nxi(),m=nxi();
	U::init();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		apx(xval,v);
		bukv[v].push_back((edge){a,b});
	}
	printf("%d\n",solve(0,xval+1));
	return 0;
}
