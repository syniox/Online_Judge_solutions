#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
typedef long long lint;
const int N=3e5+5,E=3e5+5;
int n,m,fa[N],val[N],etag[E];
int abuk[N];
struct edge{
	int a,b,v;
}eg[N];
struct data{
	int id,v,t;//v: requested
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

int find_rt(const int x){
	return fa[x]?fa[x]=find_rt(fa[x]):x;
}

namespace LH{
	int cnt,rt[N];
	struct node{
		data v;
		int ls,rs,len;
	}tr[N*20];

	int merge(int a,int b){
		if(!a||!b) return a|b;
		if(tr[a].v<tr[b].v) std::swap(a,b);
		tr[a].rs=merge(tr[a].rs,b);
		if(tr[tr[a].ls].len<tr[tr[a].rs].len)
			std::swap(tr[a].ls,tr[a].rs);
		tr[a].len=tr[tr[a].rs].len+1;
		return a;
	}

	inline void push(int &a,const data &d){
		tr[++cnt]=(node){d,0,0,0};
		a=merge(a,cnt);
	}
	inline data pop(int &k){
		data tmp=tr[k].v;
		k=merge(tr[k].ls,tr[k].rs);
		return tmp;
	}
}

std::priority_queue <int,std::vector<int>,std::greater<int> > qvld;

void upd(const int id){
	const int a=find_rt(eg[id].a),b=find_rt(eg[id].b),s=val[a]+val[b];
	if(a==b) return;
	if(s>=eg[id].v) etag[id]=-1,qvld.push(id);
	else{
		const int mv=(eg[id].v-s+1)>>1;
		++etag[id];
		LH::push(LH::rt[a],(data){id,mv+val[a],etag[id]});
		LH::push(LH::rt[b],(data){id,mv+val[b],etag[id]});
	}
}
void san(const int x){
	assert(x==find_rt(x));
	while(LH::rt[x]&&LH::tr[LH::rt[x]].v.v<=val[x]){
		data d=LH::pop(LH::rt[x]);
		if(d.t==etag[d.id]) upd(d.id);
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<=m; ++i){
		eg[i]=(edge){nxi(),nxi(),nxi()};
		upd(i);
	}
	int cnt=0;
	while(!qvld.empty()){
		const int e=qvld.top();
		qvld.pop();
		int a=find_rt(eg[e].a),b=find_rt(eg[e].b);
		if(a==b) continue;
		abuk[++cnt]=e;
		val[a]+=val[b];
		LH::rt[a]=LH::merge(LH::rt[a],LH::rt[b]);
		fa[b]=a;
		san(a);
	}
	printf("%d\n",cnt);
	for(int i=1; i<=cnt; ++i){
		printf("%d ",abuk[i]);
	}
	puts("");
	return 0;
}
