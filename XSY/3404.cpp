#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
const int N=3e5+5;
int n,m,ans[N<<1];
class _vec{
	public:
		int x,y;
		friend bool cmp_y(const _vec &a,const _vec &b){
			return a.y<b.y;
		}
		friend bool operator < (const _vec &a,const _vec &b){
			return a.x<b.x;
		}
}pnt[N];
class _fce: public _vec{
	public:
		int id;
}fce[N];


bool cmp_y(const _vec &a,const _vec &b);

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int fa[N],sz[N];
	bool del[N];

	inline int find_rt(const int x){
		if(!del[x]) return x;
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}

	inline void build(){
		std::set <_fce> st;
		std::set <_fce> ::iterator it;
		for(int i=m,j=n; i; --i){
			it=st.lower_bound(fce[i]);
			fa[fce[i].id]=it==st.end()?0:it->id;
			if(it!=st.begin()){
				for(--it; it!=st.begin(); ){
					if((it->id)>fce[i].id) st.erase(it--);
					else break;
				}
				if(!st.empty()&&it==st.begin()&&it->id>fce[i].id){
					st.erase(st.begin());
				}
			}
			st.insert(fce[i]);
			for(; j&&cmp_y(fce[i],pnt[j]); --j);
			for(; j&&cmp_y(fce[i-1],pnt[j]); --j){
				_fce tmp;
				tmp.x=pnt[j].x,tmp.y=pnt[j].y;
				it=st.lower_bound(tmp);
				if(it!=st.end()){
					++sz[it->id];
				}
			}
		}
	}

	inline void solve(){
		for(int i=m; i; --i){
			ans[i]=sz[i];
			del[i]=1;
			int fa=find_rt(i);
			sz[fa]+=sz[i];
		}
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		pnt[i].x=nxi(),pnt[i].y=nxi();
	}
	m=nxi();
	for(int i=1; i<=m; ++i){
		fce[i].id=i;
		fce[i].x=nxi(),fce[i].y=nxi();
	}
	std::sort(pnt+1,pnt+n+1,cmp_y);
	std::sort(fce+1,fce+m+1,cmp_y);
	G::build();
	G::solve();
	for(int i=1; i<=m; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
