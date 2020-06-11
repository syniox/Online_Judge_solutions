#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <stack>
typedef long long lint;
const int N=5e5+5;
const int V=1e6;
int n,m,vbuk[N+V+1],qbuk[N];
lint ans;
struct node{
	int v,sz;
};

namespace utils{
#define eprintf(fmt,...) fprintf(stderr,fmt,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void add(lint &sum,int &sz,const int v,const int cnt){
	sz+=cnt,sum+=(lint)v*cnt;
}

void solve(const int q){
	//每次最多从栈中吐出一个元素
	static node stk[N];
	static int sz,top,tag,cpt(V);
	//tag: 栈中元素偏移 cpt: 当前未进队最高位
	static lint sum;
	for(; sz<q;){
		for(; N+cpt>=0&&!vbuk[N+cpt]; --cpt);//复杂度？
		assert(N+cpt>=0);
		int use=std::min(vbuk[N+cpt],q-sz);
		vbuk[N+cpt]-=use;
		if(top&&stk[top].v==cpt+tag){
			stk[top].sz+=use;
		}else{
			stk[++top]=(node){cpt+tag,use};
		}
		add(sum,sz,cpt,use);
	}
	++tag;
	ans+=sum,sum-=sz;
	node p=stk[top--];
	apx(cpt,p.v-tag);
	add(sum,sz,p.v-tag,-p.sz);
	vbuk[N+p.v-tag]+=p.sz;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		++vbuk[N+nxi()];
	}
	m=nxi();
	for(int i=1; i<=m; ++i){
		++qbuk[nxi()];
	}
	for(int i=1; i<=n; ++i){
		while(qbuk[i]--) solve(i);
	}
	printf("%lld\n",ans);
	return 0;
}
