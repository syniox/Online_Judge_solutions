#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=1e5+5;
int n,q,mu[N],val[N],pos[N],spr[N];
lint ans[N];
struct qry{
	int id,x;
};
std::vector <qry> qbuk[N];

namespace utils{
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

namespace B{
	lint tr[N];
	inline void add(int x,const lint v){
		for(; x<=n; x+=x&-x) tr[x]+=v;
	}
	inline lint ask(int x){
		lint ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return ans;
	}
}

void init(){
	static bool npr[N];
	static int prm[N];
	int cnp=0;
	mu[1]=1;
	for(int i=2; i<N; ++i){
		if(!npr[i]){
			prm[++cnp]=spr[i]=i;
			mu[i]=-1;
		}
		for(int j=1; j<=cnp&&i*prm[j]<N; ++j){
			npr[i*prm[j]]=1;
			spr[i*prm[j]]=prm[j];
			if(i%prm[j]==0) break;
			mu[i*prm[j]]=-mu[i];
		}
	}
}

int main(){
	n=nxi(),q=nxi();
	init();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		pos[val[i]]=i;
	}
	for(int i=1; i<=q; ++i){
		const int x=nxi(),y=nxi();
		qbuk[y].push_back((qry){i,x});
	}
	for(int i=3; i<=n; ++i){
		static int ls[N],buk[N],cc[N],used[N*15];
		static bool vis[N];
		int tot=0,cntu=0;
		for(int j=val[i]*2; j<=n; j+=val[i]){
			if(pos[j]<i) ls[++tot]=pos[j];
		}
		std::sort(ls+1,ls+tot+1);
		for(int j=tot; j; --j){
			int cnt=1,res=cc[1];
			buk[1]=vis[1]=1;
			for(int k=val[ls[j]]/val[i]; k>1; k/=spr[k]){
				for(int l=cnt; l; --l){
					int tmp=buk[l]*spr[k];
					if(vis[tmp]) continue;
					vis[tmp]=1;
					buk[++cnt]=used[++cntu]=tmp;
					res+=cc[tmp]*mu[tmp];
					++cc[tmp];
				}
			}
			++cc[1];
			for(int k=1; k<=cnt; ++k){
				vis[buk[k]]=0;
			}
			assert(res>=0);
			B::add(n-ls[j]+1,(lint)res*val[i]);
		}
		cc[1]=0;
		for(; cntu; --cntu){
			cc[used[cntu]]=0;
		}
		for(std::vector <qry> ::iterator it=qbuk[i].begin(); it!=qbuk[i].end(); ++it){
			ans[it->id]=B::ask(n-(it->x)+1);
		}
	}
	for(int i=1; i<=q; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
