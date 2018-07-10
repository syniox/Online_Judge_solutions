#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2e5+5;
int n,rt,las,cnt;
struct node{
	int s,x,c[2],p[2],mn[2],mx[2];
}now,pr[N],tr[N];

inline bool cp(node a,node b,bool f){
	return a.p[f]<b.p[f];
}
inline bool cpx(node a,node b){
	return a.p[0]<b.p[0];
}
inline bool cpy(node a,node b){
	return a.p[1]<b.p[1];
}
inline void apn(int &a,int b){
	if(a>b) a=b;
}
inline void apx(int &a,int b){
	if(a<b) a=b;
}


inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool vld(int k,int a,int b,int x,int y){
	node &p=tr[k];
	return p.mn[0]>=a&&p.mx[0]<=x&&p.mn[1]>=b&&p.mx[1]<=y;
}

inline bool dlv(int k,int a,int b,int x,int y){
	node &p=tr[k];
	return p.mn[0]>x||p.mx[0]<a||p.mn[1]>y||p.mx[1]<b;
}

inline void upd(int k){
	node &p=tr[k],&l=tr[p.c[0]],&r=tr[p.c[1]];
	p.s=p.x+l.s+r.s;
	for(int i=0;i<2;++i){
		p.mn[i]=p.mx[i]=p.p[i];
		apn(p.mn[i],l.mn[i]),apn(p.mn[i],r.mn[i]);
		apx(p.mx[i],l.mx[i]),apx(p.mx[i],r.mx[i]);
	}
}

void ins(int &x,bool f){
	if(!x){
		now.mx[0]=now.mn[0]=now.p[0];
		now.mx[1]=now.mn[1]=now.p[1];
		tr[x=++cnt]=now;
		return;
	}
	ins(tr[x].c[cp(tr[x],now,f)],f^1);
	upd(x);
//	if(cp(now,tr[x],f)) ins(tr[x].ch[0],f^1);
//	else ins(tr[x].ch[1],f^1);
}

//nth_element:put the nth big number on the right place(the nth place)
int build(int l,int r,bool f){
	if(r<l) return 0;
	int mid=(l+r)>>1;
	nth_element(pr+l,pr+mid,pr+r+1,f?cpy:cpx);
	tr[mid]=pr[mid];
	tr[mid].c[0]=build(l,mid-1,f^1);
	tr[mid].c[1]=build(mid+1,r,f^1);
	upd(mid);
	return mid;
}

int ask(int k,int a,int b,int x,int y){
	node &p=tr[k];
//	printf("k%d a%d b%d x%d y%d b%d\n",k,a,b,x,y,vld(k,a,b,x,y));
//	printf("p%d %dmin%d %d max%d %d\n",p.p[0],p.p[1],p.mn[0],p.mn[1],p.mx[0],p.mx[1]);
	if(vld(k,a,b,x,y)) return p.s;
	int ans=(p.p[0]>=a&&p.p[1]>=b&&p.p[0]<=x&&p.p[1]<=y)*p.x;
	if(!dlv(p.c[0],a,b,x,y)) ans+=ask(p.c[0],a,b,x,y);
	if(!dlv(p.c[1],a,b,x,y)) ans+=ask(p.c[1],a,b,x,y);
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	tr[0].mn[0]=tr[0].mn[1]=1e9;
	n=nxi();
	int a,b,x,y,ct(0),op;
	while((op=nxi())!=3){
		if(op==1){
			now.p[0]=nxi()^las,now.p[1]=nxi()^las;
			now.x=now.s=nxi()^las;
			ins(rt,0);
			if(++ct==10000){
				memcpy(pr,tr,sizeof(node)*(cnt+1));
				rt=build(1,cnt,0);
				ct=0;
			}
//			printf("s%d\n",tr[rt].s);
		}
		else{
			a=nxi()^las,b=nxi()^las,x=nxi()^las,y=nxi()^las;
			printf("%d\n",las=ask(rt,a,b,x,y));
		}
	}
	return 0;
}
