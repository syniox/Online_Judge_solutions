#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
const int N=5005;
int q;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt=1;
	class edge{
		public:
			int x,y,v;
	}eg[N];

	inline void add_edge(const int a,const int b,const int v){
		static int cnt=0;
		eg[++cnt]=(edge){a,b,v};
	}

	inline void add_block(int sum){
		int cur_rt=cnt+1;
		add_edge(1,cur_rt,1);
		for(int i=2; i<=sum; ++i){
			add_edge(cur_rt,cnt+i,0);
		}
		cnt+=sum;
	}

	inline void oput(){
		printf("%d\n",cnt);
		for(int i=1; i<cnt; ++i){
			printf("%d %d %d\n",eg[i].x,eg[i].y,eg[i].v);
		}
	}
}

inline bool jdg(const int tgt){
	int cur=q+tgt*tgt;
	int lp=0;
	for(int i=sqrt(cur); !lp&&i>=1; --i){
		if(cur%i==0) lp=i;
	}
	if(lp-tgt<=0) return 0;
	int rp=cur/lp;
	lp-=tgt,rp-=tgt;
	if(lp+rp+tgt+1>5000) return 0;
	G::add_block(lp);
	G::add_block(rp);
	G::add_block(tgt);
	G::oput();
	return 1;
}

int main(){
	q=nxi();
	for(int i=0; i*i<q; ++i){
		if(jdg(i)) break;
	}
	return 0;
}
