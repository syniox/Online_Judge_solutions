#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=5e5+5;
int n,rt,las,cnt;
struct node{
	int s,c[2],p[2],mn[2],mx[2];
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
	node &p=tr[k];
	p.s=tr[p.c[0]].s+tr[p.c[1]].s;
	for(int i=0;i<2;++i){
		p.mn[i]=min(tr[p.c[0]].mn[i],tr[p.c[1]].mn[i]);
		p.mx[i]=max(tr[p.c[0]].mx[i],tr[p.c[1]].mx[i]);
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
	if(vld(k,a,b,x,y)) return tr[k].s;
	int ans(0);
	if(!dlv(tr[k].c[0],a,b,x,y)) ans+=ask(tr[k].c[0],a,b,x,y); 
	if(!dlv(tr[k].c[1],a,b,x,y)) ans+=ask(tr[k].c[1],a,b,x,y); 
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
			now.p[0]=nxi()^las,now.p[1]=nxi()^las,now.s=nxi()^las;
			ins(rt,0);
			if(++ct==10000){
				memcpy(pr,tr,sizeof(node)*cnt+1);
				rt=build(1,cnt,0);
				ct=0;
			}
		}
		else{
			a=nxi()^las,x=nxi()^las,b=nxi()^las,y=nxi()^las;
			printf("%d\n",las=ask(rt,a,b,x,y));
		}
	}
	return 0;
}
