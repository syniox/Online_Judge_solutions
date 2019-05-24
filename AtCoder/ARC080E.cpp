#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
const int N=2e5+5;
int n,lg2[N],val[N],npos0[17][N>>1],npos1[17][N>>1];
struct data{
	int l,r,x,y;
	friend bool operator < (const data &a,const data &b){
		return a.x==b.x?val[a.y]>val[b.y]:val[a.x]>val[b.x];
	}
};

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void init(){
	for(int i=2; i<=n; ++i){
		lg2[i]=lg2[i>>1]+1;
	}
}

void build_rmq(int pos[17][N>>1]){
	for(int i=1; i<=lg2[n>>1]; ++i){
		for(int j=1<<i; j<=n>>1; ++j){
			int p1=pos[i-1][j],p2=pos[i-1][j-(1<<(i-1))];
			pos[i][j]=val[p1]<val[p2]?p1:p2;
		}
	}
}

int rmq(int pos[17][N>>1],const int x,const int y){
	if(x==y) return pos[0][y];
	int len=y-x+1,lg=lg2[len];
	int p1=pos[lg][y],p2=pos[lg][x+(1<<lg)-1];
	return val[p1]<val[p2]?p1:p2;
}

int get0(const int l,const int r){
	if(l==r){
		assert((l&1)==0);
		return l;
	}
	int x=l>>1,y=r>>1;
	return rmq(npos0,x,y);
}

int get1(const int l,const int r){
	if(l==r){
		assert((l&1)==1);
		return l;
	}
	int x=(l+1)>>1,y=(r+1)>>1;
	return rmq(npos1,x,y);
}

data getdata(const int l,const int r){
	data x=(data){l,r,0,0};
	if(x.l&1){
		x.x=get1(l,r);
		x.y=get0(x.x+1,r);
	}
	else{
		x.x=get0(l,r);
		x.y=get1(x.x+1,r);
	}
	return x;
}

int main(){
	std::priority_queue <data> pq;
	n=nxi();
	init();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<=n>>1; ++i){
		npos1[0][i]=(i<<1)-1;
		npos0[0][i]=i<<1;
	}
	build_rmq(npos0);
	build_rmq(npos1);
	pq.push(getdata(1,n));
	while(!pq.empty()){
		data x=pq.top();
		pq.pop();
		printf("%d %d ",val[x.x],val[x.y]);
		if(x.x>x.l){
			pq.push(getdata(x.l,x.x-1));
		}
		if(x.y>x.x+1){
			pq.push(getdata(x.x+1,x.y-1));
		}
		if(x.r>x.y){
			pq.push(getdata(x.y+1,x.r));
		}
	}
	puts("");
	return 0;
}
