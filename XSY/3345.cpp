#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n,q,m;
lint ans[N];
struct edge{
	int x,y,v;

	bool operator < (const edge &b) const {
		return v<b.v;
	}
}eg[N<<1];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	int fa[N<<1],list_x[N*3],list_y[N*3];

	inline int find_rt(int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}

	inline void solve(int w){
		memset(fa,0,sizeof(fa));
		int top=0,cnt_edge=0;
		lint pre_edge;
		for(int i=1; i<=m&&eg[i].v<=w; ++i){
			int x=find_rt(eg[i].x),y=find_rt(eg[i].y);
			if(x!=y){
				++cnt_edge;
				fa[std::min(x,y)]=std::max(x,y);
				if(x>n&&y>n){
					list_x[++top]=x-n,list_y[top]=y-n;
				}
			}
		}
		ans[1]+=(n<<1)-1-cnt_edge;
		pre_edge=cnt_edge;
		for(int i=2; i<=q; ++i){
			const int bef_top=top;
			top=0;
			for(int j=1; j<=bef_top; ++j){
				int x=find_rt(list_x[j]),y=find_rt(list_y[j]);
				if(x==y) --cnt_edge;
				else{
					fa[std::min(x,y)]=std::max(x,y);
					if(x>n&&y>n){
						list_x[++top]=x-n,list_y[top]=y-n;
					}
				}
			}
			pre_edge+=cnt_edge;
			ans[i]+=(lint)n*(i+1)-1-pre_edge;
		}
	}
}

int main(){
	n=nxi(),q=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		eg[i].x=nxi(),eg[i].y=nxi()+n,eg[i].v=nxi();
	}
	std::sort(eg+1,eg+m+1);
	for(int i=0; i<30; ++i){
		S::solve(i);
	}
	for(int i=1; i<=q; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
