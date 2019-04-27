#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=2e5+5;
const int mod=1e9+7;
int n,dp[N];//前缀和
std::vector <int> m_ls[N];
struct _pair{
	int x,y;
}dt[N],spc[N];
//dt: pos,v
//spc: l,r

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool _pr_cmp_y(const _pair &a,const _pair &b){
	return a.y<b.y;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

namespace B{
	int tr[N];
	inline void clear(){
		memset(tr+1,0,n*sizeof(int));
	}
	inline void apl(int x,const int v){
		for(; tr[x]<v&&x<=n; x+=x&-x) tr[x]=v;
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) apx(ans,tr[x]);
		return ans;
	}
}

template <class T> class _Disc{
	public:
		T buk[N],*pt;
		int tot;

		_Disc(){pt=buk;}
		inline void insert(const T &v){
			*pt++=v;
		}
		inline void build(){
			std::sort(buk,pt);
			pt=std::unique(buk,pt);
			tot=pt-buk;
		}
		inline int ask(const T &v){
			return std::lower_bound(buk,pt,v)-buk+1;
		}
};
_Disc <int> D;

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int solve(const int t){
	static int buk[N];
	const int sz=m_ls[t].size();
	if(!sz) return 0;
	std::sort(m_ls[t].begin(),m_ls[t].end());
	for(std::vector <int> ::iterator it=m_ls[t].begin(); it!=m_ls[t].end(); ++it){
		++buk[*it];
	}
	int lst_dp=0,res=0,psum=0;
	for(std::vector <int> ::iterator it=m_ls[t].begin(); it!=m_ls[t].end(); ++it){
		if(!buk[*it]) continue;
		if(psum){
			int wgt=(dp[*it-1]-lst_dp+mod)%mod;
			res=(res+(lint)wgt*(fpow(2,psum)-1)%mod*fpow(2,sz-psum))%mod;
		}
		psum+=buk[*it];
		buk[*it]=0;
		lst_dp=*it?dp[*it-1]:0;
	}
	int wgt=dp[t-1]-lst_dp+mod;
	res=(res+(lint)wgt*(fpow(2,sz)-1+mod))%mod;
	return res;
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	n=nxi();
	for(int i=1; i<=n; ++i){
		dt[i].x=nxi(),dt[i].y=nxi();
		D.insert(dt[i].x);
	}
	D.build();
	for(int i=1; i<=n; ++i){
		dt[i].x=D.ask(dt[i].x);
	}
	std::sort(dt+1,dt+n+1,_pr_cmp_y);
	for(int i=1; i<=n; ++i){
		int res=B::ask(n-dt[i].x+1);
		spc[i].x=res?n-res+1:i;
		B::apl(n-dt[i].x+1,n-i+1);
	}
	B::clear();
	for(int i=n; i>=1; --i){
		int res=B::ask(dt[i].x);
		spc[i].y=res?res:i;
		B::apl(dt[i].x,i);
	}
	for(int i=1; i<=n; ++i){
		//printf("%d %d\n",spc[i].x,spc[i].y);
		m_ls[spc[i].y].push_back(spc[i].x-1);
	}
	dp[0]=1;
	for(int i=1; i<n; ++i){
		dp[i]=(dp[i-1]+solve(i))%mod;
	}
	printf("%d\n",solve(n));
	return 0;
}
