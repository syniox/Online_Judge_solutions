#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=1e5+5;
int n,m;
bool type;
pair<int,int> mz[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

namespace U{
	int fa[N],ecnt[N],sz[N];
	int lp[N],top;
	inline int qrt(int x){
		for(; fa[x]; x=fa[x]);
		return x;
	}
	inline int qans(int x){
		return sz[x]-(ecnt[x]<sz[x]);
	}
	inline void reset(){
		for(int i=1; i<=n; ++i){
			sz[i]=1,fa[i]=ecnt[i]=0;
		}
	}
	inline int merge(pair<int,int> st){
		int x=qrt(st.first),y=qrt(st.second);
		int oldans;
		if(x==y){
			oldans=qans(x);
			lp[++top]=-x;
			++ecnt[x];
		}
		else{
			oldans=qans(x)+qans(y);
			if(sz[x]<sz[y]) swap(x,y);
			lp[++top]=y;
			fa[y]=x;
			ecnt[x]+=ecnt[y]+1;
			sz[x]+=sz[y];
		}
		return qans(x)-oldans;
	}
	inline void pullback(){
		for(; top; --top){
			if(lp[top]<0) --ecnt[-lp[top]];
			else{
				int y=lp[top],x=fa[y];
				assert(qrt(x)==x);
				fa[y]=0;
				ecnt[x]-=ecnt[y]+1;
				sz[x]-=sz[y];
			}
		}
	}
}

int main(){
	n=nxi(),m=nxi(),type=nxi();
	U::reset();
	for(int p1=1,p2=1,p3=1,ans=0,ap2=0; m--; ){
		int op=nxi();
		if(type) op=(op+ans)&1;
		if(op==1){
			int a=nxi(),b=nxi();
			if(type) a=(a+ans)%n+1,b=(b+ans)%n+1;
			mz[p3++]=make_pair(a,b);
			ap2+=U::merge(mz[p3-1]);
		}else{
			if(p1==p2){
				p2=std::min(p2+300,p3);
				U::reset();
				ap2=0;
				for(int i=p2; i<p3; ++i){
					ap2+=U::merge(mz[i]);
				}
			}
			++p1;
		}
		ans=ap2;
		U::top=0;
		for(int i=p1; i<p2; ++i){
			ans+=U::merge(mz[i]);
		}
		U::pullback();
		printf("%d\n",ans);
	}
	return 0;
}
