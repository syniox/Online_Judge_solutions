#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
using namespace std;
const int N=1e5+5;
int n,m,cnt,ans,fir[N*10];
struct node{
	int s,t,nx;
}pt[N*10];

inline void add(int p,int s,int t){
	pt[++cnt]=(node){s,t,fir[p]};
	fir[p]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void merge(int &x){
	int p=pt[x].nx;
	if(p&&pt[x].s==pt[p].t+1){
		pt[x].s=pt[p].s;
		pt[x].nx=pt[p].nx;
		--ans;
	}
	else x=p;
}


int main(){
#ifndef ONLINE_JUDGE
	freopen("1658.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int x(0),f(0),s,i=1;i<=n;++i){
		x=nxi();
		if(x!=f){
			if(i!=1) add(f,s,i-1);
			++ans;
			s=i;
		}
		f=x;
		if(i==n) add(x,s,i);
	}
	for(int op,a,b;m--;){
		op=nxi();
		if(op==2) printf("%d\n",ans);
		else{
			a=nxi(),b=nxi();
			int i=fir[a],j=fir[b];
			if(!j){
				fir[b]=i,fir[a]=0;
				continue;
			}
			if(pt[i].s>pt[j].s){
				fir[b]=i;
				while(pt[pt[i].nx].s>pt[j].s) i=pt[i].nx;
				int p=i;
				i=pt[i].nx;
				if(pt[p].s==pt[j].t+1) pt[p].s=pt[j].s;
				else pt[p].nx=j;
			}
			while(i){
				int &nx=pt[j].nx;
				if(pt[i].s>pt[nx].s){
					int p=i;
					i=pt[i].nx;
					pt[p].nx=nx;
					nx=p;
				}
				merge(j);
			}
			merge(j);
			fir[a]=0;
		}
	}
	return 0;
}
