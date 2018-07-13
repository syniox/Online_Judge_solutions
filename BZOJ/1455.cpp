#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e5+5;
int fa[N];
bool lv[N];
struct node{
	int s,l,ls,rs;
}tr[N];

int frt(int x){
	while(fa[x]) x=fa[x];
	return x;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

int merge(int x,int y){
	if(!x||!y) return x|y;
	if(tr[x].s>tr[y].s) swap(x,y);
	node &p=tr[x];
	p.rs=merge(p.rs,y);
	fa[p.rs]=x;
	if(tr[p.ls].l>tr[p.rs].l) swap(p.ls,p.rs);
	p.l=tr[p.ls].l+1;
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	int n=nxi();
	for(int i=1;i<=n;++i){
		tr[i].s=nxi();
	}
	int m=nxi();
	char op;
	for(int i,j;m--;){
		while((op=getchar())!='K'&&op!='M');
		i=nxi();
		if(op=='K'){
			if(lv[i]) puts("0");
			else{
				int x=frt(i);
				lv[x]=1;
				printf("%d\n",tr[x].s);
				fa[merge(tr[x].ls,tr[x].rs)]=0;
			}
		}
		if(op=='M'){
			j=nxi();
			if(lv[i]||lv[j]) continue;
			int x=frt(i),y=frt(j);
			if(x!=y) merge(x,y);
		}
	}
	return 0;
}
