#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long lint;
const int N=5e4+5;
int n,m,rt,ka,kb,kc;
struct node{
	int x,p[2],c[2],mn[2],mx[2];
	lint s;
}tr[N];

inline bool cpy(node a,node b){
	return a.p[1]<b.p[1];
}
inline bool cpx(node a,node b){
	return a.p[0]<b.p[0];
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

inline void upd(int k){
	node &p=tr[k],&l=tr[p.c[0]],&r=tr[p.c[1]];
	for(int i=0;i<2;++i){
		apn(p.mn[i],l.mn[i]);
		apn(p.mn[i],r.mn[i]);
		apx(p.mx[i],l.mx[i]);
		apx(p.mx[i],r.mx[i]);
	}
	p.s+=l.s+r.s;
}

int vld(node &x){
	int ans=0;
	ans+=(ka*x.mn[0]+ka*x.mn[1]<kc);
	ans+=(ka*x.mn[0]+ka*x.mx[1]<kc);
	ans+=(ka*x.mx[0]+ka*x.mn[1]<kc);
	ans+=(ka*x.mx[0]+ka*x.mx[1]<kc);
	return ans;
}

int build(int l,int r,bool f){
	if(l>r) return 0;
	int mid=(l+r)>>1;
	nth_element(tr+l,tr+mid,tr+r,f?cpy:cpx);
	tr[mid].c[0]=build(l,mid-1,f^1);
	tr[mid].c[1]=build(mid+1,r,f^1);
	upd(mid);
	return mid;
}

lint ask(int k){
	if(!k) return 0;
	node &p=tr[k];
	int q=vld(p);
	if(!q) return 0;
	if(q==4) return p.s;
	lint ans=(ka*p.p[0]+kb*p.p[1]<kc)*p.x;
	int l=p.c[0],r=p.c[1];
	if(vld(tr[l].mn[0],tr[l].mn[1])) ans+=ask(l);
	if(vld(tr[r].mn[0],tr[r].mn[1])) ans+=ask(r);
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	tr[0].mn[0]=tr[0].mn[1]=1e9;
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		node &p=tr[i];
		scanf("%d%d",p.p[0],p.p[1]);
		p.mn[0]=p.mx[0]=p.p[0];
		p.mn[1]=p.mx[1]=p.p[1];
		p.x=p.s=nxi();
	}
	rt=build(1,n,0);
	while(m--){
		scanf("%d%d%d",&ka,&kb,&kc);
		printf("%lld\n",ask(rt));
	}
	return 0;
}
