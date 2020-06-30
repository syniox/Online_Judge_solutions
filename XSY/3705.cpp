#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
typedef long long lint;
const int N=3e5+5;
int n,m,fa[N],val[N],offs[N],bel[N][2],dv[N][2];
int abuk[N];
struct edge{
	int a,b,v;
}eg[N];
struct data{
	int id,v;
	friend bool operator<(const data &a,const data &b){
		return a.v>b.v;
	}
};

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

std::priority_queue <int,std::vector<int>,std::greater<int> > qvld;
std::priority_queue <data> sd[N];

int find_rt(const int x){
	return fa[x]?fa[x]=find_rt(fa[x]):x;
}
inline bool qside(const int id,const int x){
	assert(!fa[x]);
	return x==find_rt(eg[id].b);
}
inline bool useless(const int id){
	return find_rt(eg[id].a)==find_rt(eg[id].b);
}
void ins_eg(const int id,const int offa,const int offb){
	const int a=find_rt(eg[id].a),b=find_rt(eg[id].b),mv=(eg[id].v+1)>>1;
	assert(val[a]==-offa||offs[a]==offa);
	assert(val[b]==-offb||offs[b]==offb);
	sd[bel[id][0]=a].push((data){id,dv[id][0]=mv+offa});
	sd[bel[id][1]=b].push((data){id,dv[id][1]=mv+offb});
}
void san(const int x){
	while(!sd[x].empty()&&sd[x].top().v<=offs[x]){
		data d=sd[x].top();
		sd[x].pop();
		if(bel[d.id][qside(d.id,x)]!=x||useless(d.id)) 
			continue;
		int id=d.id,&v=eg[id].v;
		int a=find_rt(eg[id].a),b=find_rt(eg[id].b);
		int s=v+(v&1)-(dv[id][0]+dv[id][1]-offs[a]-offs[b]);
		if(s>=v) qvld.push(id);
		else{
			v-=s;
			ins_eg(id,offs[a],offs[b]);
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		eg[i]=(edge){a,b,v};
		if(val[a]+val[b]>=v) qvld.push(i);
		else ins_eg(i,-val[a],-val[b]);
	}
	for(int i=1; i<=n; ++i) san(i);
	int cnt=0;
	while(!qvld.empty()){
		const int e=qvld.top();
		qvld.pop();
		int a=find_rt(eg[e].a),b=find_rt(eg[e].b);
		if(a==b) continue;
		abuk[++cnt]=e;
		if(sd[a].size()<sd[b].size())
			std::swap(a,b);
		offs[a]+=val[b],offs[b]+=val[a];
		val[a]+=val[b];
		for(; !sd[b].empty(); sd[b].pop()){
			data d=sd[b].top();
			const int side=qside(d.id,b);
			if(bel[d.id][side]!=b||useless(d.id))
				continue;
			bel[d.id][side]=a;
			sd[a].push((data){d.id,dv[d.id][side]=d.v-offs[b]+offs[a]});
		}
		san(fa[b]=a);
	}
	printf("%d\n",cnt);
	for(int i=1; i<=cnt; ++i){
		printf("%d ",abuk[i]);
	}
	puts("");
	return 0;
}
