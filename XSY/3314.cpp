#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=1e5+5;
const int S=100;
const int mod=1e9+7;
int n,col[N];
bool bigcol[N];
std::vector <int> biglist,cbuk[N];
struct _pair{
	int x,y;
};

inline bool cmp_y(const _pair &a,const _pair &b){
	return a.y<b.y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace B{
	int tick,tag[N],tr[N];
	inline void clear(){
		++tick;
	}
	inline void upd(const int k){
		tag[k]<tick?tag[k]=tick,tr[k]=0:0;
	}
	inline void add(int x,const int v){
		for(; x<=n; x+=x&-x) upd(x),tr[x]+=v;
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) upd(x),ans+=tr[x];
		return ans;
	}
}

inline int solve_s(_pair *pr,const int size){
	std::sort(pr+1,pr+size+1,cmp_y);
	B::clear();
	int ans=0;
	for(int i=size,j=size; i; --i){
		for(; pr[j].y>pr[i].y; --j){
			B::add(pr[j].x,1);
		}
		ans=(ans+B::ask(pr[i].y-1)-B::ask(pr[i].x))%mod;
	}
	return ans;
}

inline int solve_b(const int c){
	static int pans[N];
	memset(pans+1,0,n*sizeof(int));
	int ans=0;
	for(std::vector <int> ::iterator it=cbuk[c].begin(); it!=cbuk[c].end(); ++it){
		++pans[*it];
	}
	for(int i=2; i<=n; ++i){
		pans[i]+=pans[i-1];
	}
	const int tot=cbuk[c].size();
	for(int i=1; i<=n; ++i){
		if(bigcol[i]&&c>=i) continue;
		const int sz=cbuk[i].size();
		int wval=0;
		for(int lst=0,j=0; j<sz; lst=cbuk[i][j],++j){
			int tmp=pans[cbuk[i][j]-1]-pans[lst];
			wval=(wval+(lint)tmp*j)%mod;
			ans=(ans+(lint)wval*(tot-pans[cbuk[i][j]]))%mod;
		}
		wval=0;
		for(int lst=n+1,j=sz-1; ~j; lst=cbuk[i][j],--j){
			int tmp=pans[lst-1]-pans[cbuk[i][j]];
			wval=(wval+(lint)tmp*(sz-1-j))%mod;
			ans=(ans+(lint)wval*pans[cbuk[i][j]])%mod;
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	static _pair pr[N*14];
	int pr_cnt=0;
	n=nxi();
	for(int i=1; i<=n; ++i){
		col[i]=nxi();
		cbuk[col[i]].push_back(i);
	}
	for(int i=1; i<=n; ++i){
		if(cbuk[i].size()>S){
			bigcol[i]=1;
			biglist.push_back(i);
		}
		else{
			const int sz=cbuk[i].size();
			for(int j=0; j<sz; ++j){
				for(int k=j+1; k<sz; ++k){
					pr[++pr_cnt]=(_pair){cbuk[i][j],cbuk[i][k]};
				}
			}
		}
	}
	int ans=solve_s(pr,pr_cnt);
	for(int i=1; i<=n; ++i){
		if(bigcol[i]) continue;
		pr_cnt=0;
		const int sz=cbuk[i].size();
		for(int j=0; j<sz; ++j){
			for(int k=j+1; k<sz; ++k){
				pr[++pr_cnt]=(_pair){cbuk[i][j],cbuk[i][k]};
			}
		}
		ans=(ans-solve_s(pr,pr_cnt)+mod)%mod;
	}
	for(std::vector <int> ::iterator it=biglist.begin(); it!=biglist.end(); ++it){
		ans=(ans+solve_b(*it))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
