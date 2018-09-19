#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
const int N=1e5+2;
int n,m,cnd,fa[N],fir[N],dep[N];
struct edge{
	int to,nx;
}eg[N];
struct data{
	int x;
	bool operator < (const data &b) const {
		return dep[x]<dep[b.x];
	}
};
std::vector <int> vt[N];
std::priority_queue <data> pq;

inline void apx(int &x,const int y){
	if(x<y) x=y;
}

inline void add(const int a,const int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

void get_dep(const int x){
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		get_dep(y);
		apx(dep[x],dep[y]+1);
	}
}

inline void solve(){
	static int que[N];
	int top=0;
	pq.push((data){1});
	while(!pq.empty()){
		int tp=std::min(m,(int)pq.size());
		++cnd;
		while(tp--){
			const int x=pq.top().x;
			vt[cnd].push_back(x);
			pq.pop();
			for(int i=fir[x];i;i=eg[i].nx){
				que[++top]=eg[i].to;
			}
		}
		while(top) pq.push((data){que[top--]});
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("387.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=2;i<=n;++i){
		fa[i]=nxi();
		add(fa[i],i);
	}
	get_dep(1);
	solve();
	printf("%d\n",cnd);
	for(int i=1;i<=cnd;++i){
		const int sz=vt[i].size();
		printf("%d ",sz);
		for(int j=0;j<sz;++j){
			printf("%d ",vt[i][j]);
		}
		puts("");
	}
	return 0;
}
