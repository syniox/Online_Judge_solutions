#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1e6+5;
const int P=78600;
int cnp,prm[P],id_pr[N],mn_pr[N],lg2[N];
lint m,mi[P][63];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

inline void split_pr(const int x,int *used,int *buk,int &cuse){
	for(int y=x; y>1; y/=mn_pr[y]){
		used[++cuse]=id_pr[mn_pr[y]];
		++buk[used[cuse]];
	}
}

class _Prbuk{
	public:
		int a,b,c,buk[P],cuse,used[N];

		inline void init(bool type){
			split_pr(a,used,buk,cuse);
			split_pr(b,used,buk,cuse);
			split_pr(c,used,buk,cuse);
			if(type) ++buk[1],used[++cuse]=1;
		}
		inline void sanitize(){
			std::sort(used+1,used+cuse+1);
			cuse=std::unique(used+1,used+cuse+1)-used-1;
		}

		inline void clear(){
			for(int i=1; i<=cuse; ++i){
				buk[used[i]]=0;
			}
			cuse=a=b=c=0;
		}
}n,s;

inline void init(){
	static bool npr[N];
	for(int i=0; i<=15; ++i) lg2[1<<i]=i;
	for(int i=2; i<N; ++i){
		if(!npr[i]){
			prm[++cnp]=mn_pr[i]=i;
			id_pr[i]=cnp;
		}
		for(int j=1; j<=cnp&&i*prm[j]<N; ++j){
			npr[i*prm[j]]=1;
			mn_pr[i*prm[j]]=prm[j];
			if(i%prm[j]==0) break;
		}
	}
	for(int i=1; i<=cnp; ++i){
		mi[i][0]=1;
		for(int j=1; 2e18/prm[i]>=mi[i][j-1]; ++j){
			mi[i][j]=mi[i][j-1]*prm[i];
		}
	}
}

namespace DFS{
	int *buk,*used,cuse;
	lint lim;
	int dfs(const int t,const lint pre){
		if(t>cuse) return 1;
		int ans=0;
		for(int i=0; i<=buk[used[t]]; ++i){
			if(pre*mi[used[t]][i]>lim) break;
			ans+=dfs(t+1,pre*mi[used[t]][i]);
		}
		return ans;
	}

	inline int ask(int *buk,int *used,int cuse,lint lim){
		DFS::buk=buk,DFS::used=used,DFS::cuse=cuse,DFS::lim=lim;
		return dfs(1,1);
	}
}

inline lint solve1(){
	static int buk[P],used[P],cbit[1<<15],cuse;
	static lint prod[1<<15];
	cuse=0;
	for(int i=1,j=1; i<=n.cuse; ++i){
		for(; j<s.cuse&&s.used[j]<n.used[i]; ++j);
		if(s.used[j]!=n.used[i]||s.buk[s.used[j]]<n.buk[n.used[i]]){
			used[++cuse]=n.used[i];
			buk[n.used[i]]=s.buk[n.used[i]]+1;
		}
	}
	lint ans=m;
	prod[0]=1;
	for(int i=1; i<(1<<cuse); ++i){
		int lbit=i&-i,lpos=lg2[lbit]+1;
		cbit[i]=cbit[i^lbit]+1;
		prod[i]=prod[i^lbit]*mi[used[lpos]][buk[used[lpos]]];
		ans+=cbit[i]&1?-(m/prod[i]):m/prod[i];
	}
	for(int i=1; i<=cuse; ++i){
		buk[used[i]]=0;
	}
	return ans;
}

int main(){
	init();
	for(int T=nxi(); T; --T){
		n.a=nxi(),n.b=nxi(),n.c=nxi();
		m=(lint)nxi()*nxi()*nxi();
		s.a=nxi(),s.b=nxi(),s.c=nxi();
		n.init(0),s.init(1);
		s.sanitize();
		n.sanitize();
		printf("%lld\n",solve1()+DFS::ask(s.buk,s.used,s.cuse,(lint)n.a*n.b*n.c));
		n.clear();
		s.clear();
	}
	return 0;
}
