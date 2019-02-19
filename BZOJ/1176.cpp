#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int N=2e5+5;
const int Q=1e4+5;
typedef long long lint;
int m,vl,cnq;
lint ans[Q];
struct data{
	bool type;
	int x1,x2,y,v;
}dt[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

bool cmp_y(const data &a,const data &b){
	return a.y<b.y;
}

namespace D{
	int mp[N<<1],*pt=mp;

	inline void ins(const int v){
		*pt++=v;
	}
	inline void build(){
		std::sort(mp,pt);
		pt=std::unique(mp,pt);
	}
	inline int ask(const int v){
		return std::lower_bound(mp,pt,v)-mp+1;
	}
}

namespace B{
	int tick,tr[N<<1],tag[N<<1];

	inline void clear(){
		++tick;
	}
	inline void upd(const int x){
		if(tag[x]<tick) tag[x]=tick,tr[x]=0;
	}
	inline void add(int x,const int v){
		for(; x<N<<1; x+=x&-x) upd(x),tr[x]+=v;
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) upd(x),ans+=tr[x];
		return ans;
	}
	inline int ask(const int x,const int y){
		return ask(y)-ask(x-1);
	}
}

inline void solve(const int l,const int r){
	const int mid=(l+r)>>1;
	if(l<mid){
		solve(l,mid);
		std::sort(dt+l,dt+mid+1,cmp_y);
	}
	if(r>mid+1){
		solve(mid+1,r);
		std::sort(dt+mid+1,dt+r+1,cmp_y);
	}
	B::clear();
	for(int i=mid+1,j=l; i<=r; ++i){
		if(!dt[i].type) continue;
		for(; j<=mid&&dt[j].y<=dt[i].y; ++j){
			if(dt[j].type==0) B::add(dt[j].x1,dt[j].v);
		}
		if(dt[i].v<0) ans[-dt[i].v]-=B::ask(dt[i].x1,dt[i].x2);
		else ans[dt[i].v]+=B::ask(dt[i].x1,dt[i].x2);
	}
}

int main(){
	vl=nxi(),nxi();
	for(int op=nxi(); op!=3; op=nxi()){
		if(op==1){
			int x=nxi(),y=nxi();
			D::ins(x),D::ins(y);
			dt[++m]=(data){0,x,x,y,nxi()};
		}
		else{
			int x1=nxi(),y1=nxi(),x2=nxi(),y2=nxi();
			if(x1>x2||y1>y2) continue;
			D::ins(x1),D::ins(x2);
			D::ins(y1-1),D::ins(y2);
			++cnq;
			ans[cnq]=(lint)vl*(x2-x1+1)*(y2-y1+1);
			dt[++m]=(data){1,x1,x2,y1-1,-cnq};
			dt[++m]=(data){1,x1,x2,y2,cnq};
		}
	}
	D::build();
	for(int i=1; i<=m; ++i){
		dt[i].x1=D::ask(dt[i].x1);
		dt[i].x2=D::ask(dt[i].x2);
		dt[i].y=D::ask(dt[i].y);
	}
	solve(1,m);
	for(int i=1; i<=cnq; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
