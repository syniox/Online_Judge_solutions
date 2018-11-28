#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5,V=1e4+5,S=600;
int n,tot,hx[N],fa[N],cnt[S][V],sum[S][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void mod(const int x,const int val){
	for(int i=fa[x];i<=tot;++i){
		--sum[i][cnt[i][hx[x]]--];
		++sum[i][++cnt[i][val]];
	}
	hx[x]=val;
}

inline int ask2(const int m){
	int ans=cnt[fa[m]-1][hx[m]];
	for(int i=(fa[m]-1)*S+1;i<=m;++i){
		ans+=hx[i]==hx[m];
	}
	return ans;
}

inline int ask3(const int m){
	int val=ask2(m);
	int ans=sum[fa[m]-1][val];
	for(int i=(fa[m]-1)*S+1;i<=m;++i){
		if(++cnt[fa[m]-1][hx[i]]==val) ++ans;
	}
	for(int i=(fa[m]-1)*S+1;i<=m;++i){
		--cnt[fa[m]-1][hx[i]];
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	// freopen("b.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
		fa[i]=(i-1)/S+1;
		if(i>1&&(fa[i]-1)*S+1==i){
			memcpy(cnt[fa[i]],cnt[fa[i]-1],sizeof(cnt[0]));
			memcpy(sum[fa[i]],sum[fa[i]-1],sizeof(sum[0]));
		}
		++sum[fa[i]][++cnt[fa[i]][hx[i]]];
	}
	tot=fa[n];
	for(int q=nxi();q;--q){
		const int op=nxi(),x=nxi(),y=nxi();
		if(op==1) mod(y,x);
		else if(x==1) printf("%d\n",hx[y]);
		else printf("%d\n",x&1?ask3(y):ask2(y));
	}
	return 0;
}
