#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
using namespace std;
typedef long long lint;
const int N=5e4+5;
int n,m,rt,ka,kb,kc;
lint ans;
struct node{
	int x,p[2],c[2],mn[2],mx[2];
	lint s;
}tr[N];

inline bool cpy(const node &a,const node &b){
	return a.p[1]<b.p[1];
}
inline bool cpx(const node &a,const node &b){
	return a.p[0]<b.p[0];
}
inline void apn(int &a,const int b,const int c){
	if(a>b) a=b;
	if(a>c) a=c;
}
inline void apx(int &a,const int b,const int c){
	if(a<b) a=b;
	if(a<c) a=c;
}

inline int nxi(){
	int x=0,f=1;
	char c;
	while((c=getchar())>'9'||c<'0') if(c=='-') f=-f;
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x*f;
}

inline void prt(lint x){
	if(x>9) prt(x/10);
	putchar(x%10+48);
}

inline void upd(int k){
	node &p=tr[k],&l=tr[p.c[0]],&r=tr[p.c[1]];
	apn(p.mn[0],l.mn[0],r.mn[0]);
	apn(p.mn[1],l.mn[1],r.mn[1]);
	apx(p.mx[0],l.mx[0],r.mx[0]);
	apx(p.mx[1],l.mx[1],r.mx[1]);
	p.s+=l.s+r.s;
}

inline int jdg(int x,int y){
	return (lint)ka*x+(lint)kb*y<kc;
}

inline int vld(node &x){
	int ans(0);
	ans+=jdg(x.mn[0],x.mn[1]);
	ans+=jdg(x.mn[0],x.mx[1]);
	ans+=jdg(x.mx[0],x.mn[1]);
	ans+=jdg(x.mx[0],x.mx[1]);
	return ans;
}

int build(int l,int r,bool f){
	int mid=(l+r)>>1;
	nth_element(tr+l,tr+mid,tr+r+1,f?cpy:cpx);
	if(l<mid) tr[mid].c[0]=build(l,mid-1,f^1);
	if(r>mid) tr[mid].c[1]=build(mid+1,r,f^1);
	upd(mid);
	return mid;
}

int ndcnt=0;
void ask(int k){
	++ndcnt;
	if(jdg(tr[k].p[0],tr[k].p[1])) ans+=tr[k].x;
	int l=tr[k].c[0],r=tr[k].c[1];
	if(l){
		int x=vld(tr[l]);
		if(x==4) ans+=tr[l].s;
		else if(x) ask(l);
	}
	if(r){
		int x=vld(tr[r]);
		if(x==4) ans+=tr[r].s;
		else if(x) ask(r);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	tr[0].mn[0]=tr[0].mn[1]=1e9;
//	int t=clock();
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		node &p=tr[i];
		p.mn[0]=p.mx[0]=p.p[0]=nxi();
		p.mn[1]=p.mx[1]=p.p[1]=nxi();
		p.x=p.s=nxi();
	}
	rt=build(1,n,0);
//	printf("***%d\n",clock()-t);
	for(int i=1;i<=n;++i){
		node &p=tr[i];
		printf("l%d r%d %d %d %d %d %d %d\n",p.c[0],p.c[1],p.p[0],p.p[1],p.mn[0],p.mn[1],p.mx[0],p.mx[1]);
	}
	while(m--){
		//      scanf("%d%d%d",&ka,&kb,&kc);
		ka=nxi(),kb=nxi(),kc=nxi();
		ans=0;
		ask(rt);
		prt(ans);
		putchar('\n');
	}
	cerr<<"ndcnt="<<ndcnt<<endl;
	return 0;
}
