

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
using namespace std;
#define N 100005
int n,rt,cnt,ans;
struct node {
	int x,n,fa,sz,ch[2];
} tr[N];
inline bool son(int x) {
	return tr[tr[x].fa].ch[1]==x;
}
inline void upd(int x) {
	tr[x].sz=tr[tr[x].ch[0]].sz+tr[tr[x].ch[1]].sz+tr[x].n;
}
inline void rot(int x) {
	bool k=son(x);
	int f=tr[x].fa,ff=tr[f].fa,s=tr[x].ch[k^1];
	tr[x].fa=ff;
	tr[ff].ch[son(f)]=x;
	tr[f].fa=x;
	tr[f].ch[k]=s;
	if(s) tr[s].fa=f;/**/
	tr[x].ch[k^1]=f;
	upd(f);
	upd(x);
	if(rt==f) rt=x;
}
inline void splay(int x) {
	int tp;
	while(x!=rt) {
		if((tp=tr[x].fa)!=rt) {
			if(son(tp)^son(x)) rot(x);
			else rot(tp);
		}
		rot(x);
	}
}
inline void add(int x,int t) {
	tr[x].ch[tr[x].x<t]=++cnt;
	tr[cnt]=(node){t,1,x,1,0,0};
	splay(cnt);
}
void ins(int x,int t) {
	if(!rt) {
		rt=++cnt;
		tr[1]=(node){t,1,0,1,0,0};
		return;
	}
	if(t==tr[x].x) {
		++tr[x].n;
		splay(x);
		return;
	}
	int tp=tr[x].ch[t>tr[x].x];
	if(tp) ins(tp,t);
	else add(x,t);
}
int fnd(int x,int t) {
	if(tr[x].x==t) return x;
	return fnd(tr[x].ch[tr[x].x<t],t);
}
int hex(int x,int t) {
	int c=tr[x].ch[0],tp=tr[c].sz;
	if(tp>=t) return hex(c,t);
	if(tp+tr[x].n>=t) return tr[x].x;
	return hex(tr[x].ch[1],t-tr[x].n-tp);
}
int rnk(int x,int t) {
	if(tr[x].x==t) return tr[tr[x].ch[0]].sz+1;
	if(tr[x].x>t) return rnk(tr[x].ch[0],t);
	return rnk(tr[x].ch[1],t)+tr[x].n+tr[tr[x].ch[0]].sz;
}
void prn(int x,int t,bool f) {
	if((tr[x].x>t)==f&&tr[x].x!=t){
		ans=x;
		if(tr[x].ch[f^1]) prn(tr[x].ch[f^1],t,f);
		return;
	}
	if(tr[x].ch[f]) prn(tr[x].ch[f],t,f);
}
void del(int x) {
	ans=0;
	prn(rt,x,0);
	int p=ans,k=fnd(rt,x);
	splay(k);
	if(tr[k].n>1) {
		--tr[k].n;
		--tr[k].sz;
		return;
	}
	int c0=tr[k].ch[0],c1=tr[k].ch[1];
	if(!c0){/**/
		rt=c1;
		return;
	}
	tr[c0].fa=0;
	rt=c0;
	splay(p);
	tr[p].ch[1]=c1;
	tr[c1].fa=p;
	upd(p);
}
int main() {
	scanf("%d",&n);
	for(int x,op; n--;) {
		scanf("%d%d",&op,&x);
		switch(op) {
			case 1:
				ins(rt,x);break;
			case 2:
				del(x);break;
			case 3:
				printf("%d\n",rnk(rt,x));break;
			case 4:
				printf("%d\n",hex(rt,x));break;
			default:
				ans=0;
				prn(rt,x,op-5);
				printf("%d\n",tr[ans].x);
		}
	}
	return 0;
}
