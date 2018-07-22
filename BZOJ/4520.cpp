#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long lint;
const int N=100002;
int n,q;
priority_queue <lint,vector<lint>,greater<lint> > que;

template <class T> inline void apn(T &a,T b){
	if(a>b) a=b;
}
template <class T> inline void apx(T &a,T b){
	if(a<b) a=b;
}
inline lint sq(int x){
	return (lint)x*x;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int p,rt;
	struct node{
		int x,y,l,r,sz,mn[2],mx[2];
	}tr[N];
	inline bool cpx(const node &a,const node &b){
		return a.x<b.x;
	}
	inline bool cpy(const node &a,const node &b){
		return a.y<b.y;
	}
	inline bool vld(int k){
		int x=tr[p].x,y=tr[p].y;
		lint tp(0);
		node &q=tr[k];
		apx(tp,sq(x-q.mn[0])+sq(y-q.mn[1]));
		apx(tp,sq(x-q.mn[0])+sq(y-q.mx[1]));
		apx(tp,sq(x-q.mx[0])+sq(y-q.mn[1]));
		apx(tp,sq(x-q.mx[0])+sq(y-q.mx[1]));
		return tp>que.top();
	}
	inline void upd(int k){
		node &p=tr[k],&l=tr[p.l],&r=tr[p.r];
		for(int i=0;i<2;++i){
			p.mn[i]=p.mx[i]=i?p.y:p.x;
			if(p.l){
				apn(p.mn[i],l.mn[i]);
				apx(p.mx[i],l.mx[i]);
			}
			if(p.r){
				apn(p.mn[i],r.mn[i]);
				apx(p.mx[i],r.mx[i]);
			}
		}
	}
	int build(int l,int r,int f){
		int mid=(l+r)>>1;
		nth_element(tr+l,tr+mid,tr+r+1,f?cpy:cpx);
		if(l!=mid) tr[mid].l=build(l,mid-1,f^1);
		if(r!=mid) tr[mid].r=build(mid+1,r,f^1);
		upd(mid);
		return mid;
	}
	void ask(int k){
		lint q=sq(tr[k].x-tr[p].x)+sq(tr[k].y-tr[p].y);
		if(que.top()<q){
			que.pop();
			que.push(q);
		}
		if(tr[k].l&&vld(tr[k].l)) ask(tr[k].l);
		if(tr[k].r&&vld(tr[k].r)) ask(tr[k].r);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		T::tr[i].x=nxi();
		T::tr[i].y=nxi();
	}
	T::rt=T::build(1,n,0);
	for(int i=1;i<=q<<1;++i){
		que.push(0);
	}
	for(int i=1;i<=n;++i){
		T::p=i;
		T::ask(T::rt);
	}
	printf("%lld\n",que.top());
	return 0;
}
