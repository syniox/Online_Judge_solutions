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
	memcpy(v+1,que+1,top*sizeof(vec));
	n=top;
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

bool prework(){
	int turn_p=andrew(bd,n);
	for(int i=1; i<=m; ++i){
		{
			int l=0,r=turn_p,mid;
			//线段左端点
			while(l!=r){
				mid=(l+r+1)>>1;
				if(bd[mid].x>pnt[i].x) r=mid-1;
				else l=mid;
			}
			if(l==0||l==turn_p) continue;
			if(crs(bd[l-1]-bd[l],pnt[i]-bd[l])<0) continue;
		}
		{
			int l=turn_p-1,r=n,mid;
			//线段右端点
			while(l!=r){
				mid=(l+r+1)>>1;
				if(bd[mid].x<pnt[i].x) r=mid-1;
				else l=mid;
			}
			if(l<turn_p||l==n) continue;
			if(crs(bd[l-1]-bd[l],pnt[i]-bd[l])>=0) return 0;
		}
	}
	andrew(pnt,m);
	return 1;
}

bool getjmp(){
	for(int i=1,j=1,k=1; i<=m; ++i){
		//j: 内凸包最近点
		for(; j<n&&crs(bd[j+1]-pnt[i],bd[j]-pnt[i])>=0; ++j);
		if(j==n&&crs(bd[1]-pnt[i],bd[j]-pnt[i])>=0){
			for(j=1; j<n&&crs(bd[j+1]-pnt[i],bd[j]-pnt[i])>=0; ++j); 
		}
		for(; k<m&&crs(bd[j]-pnt[i],pnt[k+1]-pnt[i])<=0; ++k);
		if(k==m&&crs(bd[j]-pnt[i],pnt[1]-pnt[i])<=0){
			for(k=1; k!=i&&crs(bd[j]-pnt[i],pnt[k+1]-pnt[i])<=0; ++k);
			if(k==i) return 0;
		}
		jmp[i]=k;
	}
	return 1;
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
		wpos.insert(pnt[i]);
	}
	for(int i=1,j=0; i<=n; ++i){
		if(wpos.find(bd[i])==wpos.end()){
			bd[++j]=bd[i];
		}
		if(i==n) n=j;
	}
	if(bd_same()){
		puts("1");
		return 0;
	}
	if(!prework()||!getjmp()){
		puts("-1");
		return 0;
	}
	int ans=1e9;
	for(int i=1; i<=m; ++i){
		int res=0,step=0;
		for(int x=i; step<m; x=jmp[x]){
			++res;
			step+=(jmp[x]-x+m)%m;
		}
		apn(ans,res);
	}
	printf("%d\n",ans);
	return 0;
}
