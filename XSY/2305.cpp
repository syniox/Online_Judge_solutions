#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <set>
typedef long long lint;
const int N=1e5+5;
const int M=505;
int n,m,jmp[M];
struct vec{
	int x,y;
	friend vec operator - (const vec &a,const vec &b){
		return (vec){a.x-b.x,a.y-b.y};
	}
	friend bool operator < (const vec &a,const vec &b){
		return a.x==b.x?a.y<b.y:a.x<b.x;
	}
	friend bool operator == (const vec &a,const vec &b){
		return a.x==b.x&&a.y==b.y;
	}
}pnt[M],bd[N];
std::set <vec> wpos;

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

inline bool _vec_cp_pos(const vec &a,const vec &b){
	return a.x==b.x?a.y<b.y:a.x<b.x;
}

inline lint crs(const vec &a,const vec &b){
	return (lint)a.x*b.y-(lint)a.y*b.x;
}

int andrew(vec *v,int &n){
	static vec que[N];
	std::sort(v+1,v+n+1,_vec_cp_pos);
	int top=0;
	for(int i=1; i<=n; ++i){
		for(; top>1&&crs(que[top]-que[top-1],v[i]-que[top-1])<=0; --top);
		que[++top]=v[i];
	}
	int turn_p=top;
	for(int i=n-1; i>1; --i){
		for(; top>turn_p&&crs(que[top]-que[top-1],v[i]-que[top-1])<=0; --top);
		que[++top]=v[i];
	}
	for(; top>turn_p&&crs(que[top]-que[top-1],que[1]-que[top-1])<=0; --top);
	n=0;
	for(int i=1; i<=top; ++i){
		if(i!=1&&que[i]==que[i-1]&&i<=turn_p) --turn_p;
		else v[++n]=que[i];
	}
	return turn_p;
}

bool bd_same(){
	for(int i=2; i<=n; ++i){
		if(!(bd[i]==bd[1])) return 0;
	}
	for(int i=1; i<=m; ++i){
		if(bd[1]==pnt[i]) return 1;
	}
	return 0;
}

inline bool inside(const vec &x,const vec *v,const int len,const int turn_p){
	if(x.x<v[1].x||x.x>v[turn_p].x) return 0;
	if(v[1].x==x.x&&v[len].x==x.x){
		return v[1].y<=x.y&&v[len].y>=x.y;
	}
	if(turn_p>1&&v[turn_p].x==x.x&&v[turn_p-1].x==x.x){
		return v[turn_p].y>=x.y&&v[turn_p-1].y<=x.y;
	}
	//考虑边界
	{
		int l=1,r=turn_p,mid;
		//线段左端点
		//最后一个横座标小于x的点(在边界处卡成等于)
		while(l!=r){
			mid=(l+r+1)>>1;
			if(v[mid].x>=x.x) r=mid-1;
			else l=mid;
		}
		assert(l!=turn_p);
		if(crs(v[l+1]-v[l],x-v[l])<0) return 0;
	}
	{
		int l=turn_p,r=len,mid;
		//线段右端点
		//最后一个横座标大于x的点(在边界处卡成等于)
		while(l!=r){
			mid=(l+r+1)>>1;
			if(v[mid].x<=x.x) r=mid-1;
			else l=mid;
		}
		if(crs(v[l==len?1:l+1]-v[l],x-v[l])<0) return 0;
	}
	return 1;
}

int prework(){
	int turn_pt=andrew(pnt,m);
	if(m==1) return -bd_same();
	andrew(bd,n);
	for(int i=1; i<=n; ++i){
		if(!inside(bd[i],pnt,m,turn_pt)) return 0;
	}
	return 1;
}

inline bool need_go(const vec &pre,const vec &nxt,const vec &cur){
	if(nxt==cur) return 0;
	return crs(pre-cur,nxt-cur)<=0;
}

bool getjmp(){
	for(int i=1,j=1,k=1; i<=m; ++i){
		//j: 内凸包最近点
		for(; j<n&&need_go(bd[j],bd[j+1],pnt[i]); ++j);
		if(j==n&&need_go(bd[n],bd[1],pnt[i])){
			for(j=1; j<n&&need_go(bd[j],bd[j+1],pnt[i]); ++j);
		}
		for(; k<m&&crs(bd[j]-pnt[i],pnt[k+1]-pnt[i])<=0; ++k);
		if(k==m&&i!=1&&crs(bd[j]-pnt[i],pnt[1]-pnt[i])<=0){
			for(k=1; k+1<i&&crs(bd[j]-pnt[i],pnt[k+1]-pnt[i])<=0; ++k);
		}
		jmp[i]=k;
		if(k==i) ++k;
	}
	return 1;
}

inline int getans(const int p){
	int res=0,step=0;
	for(int x=p; step<m; x=jmp[x]){
		++res;
		if(jmp[x]==x) return 1e9;
		step+=(jmp[x]-x+m)%m;
	}
	return res;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	if(!n||!m){
		puts(n?"-1":"0");
		return 0;
	}
	for(int i=1; i<=n; ++i){
		bd[i].x=nxi(),bd[i].y=nxi();
	}
	for(int i=1; i<=m; ++i){
		pnt[i].x=nxi(),pnt[i].y=nxi();
	}
	if(bd_same()){
		puts("1");
		return 0;
	}
	switch(prework()){
		case -1: puts("1"); return 0;
		case 0: puts("-1"); return 0;
	}
	getjmp();
	int ans=1e9;
	for(int i=1; i<=m; ++i){
		apn(ans,getans(i));
	}
	printf("%d\n",ans==1e9?-1:ans);
	return 0;
}
