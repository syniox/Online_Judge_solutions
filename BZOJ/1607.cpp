#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
const int S=1005;
int n,cnp,hx[N],prm[S],buk[N*10];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	static bool npr[N];
	for(int i=2;i<S;++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1;j<=cnp&&i*prm[j]<S;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

inline int jdg(const int x){
	static int cnt[S],que[N];
	int p=x,top=0,ans=0;
	--buk[x];
	for(int i=1;p>1&&i<=cnp;++i){
		while(p%prm[i]==0){
			++cnt[i];
			p/=prm[i];
		}
	}
	que[++top]=1;
	ans+=buk[1];
	if(p>1){
		que[++top]=p;
		ans+=buk[p];
	}
	for(int i=1;i<=cnp;++i){
		const int limit=top;
		for(int j=1;j<=limit;++j){
			for(int k=1,w=prm[i];k<=cnt[i];++k,w*=prm[i]){
				que[++top]=que[j]*w;
				ans+=buk[que[top]];
			}
		}
	}
//	printf("frac: ");
//	for(int i=1;i<=top;++i){
//		printf("%d ",que[i]);
//	}
//	puts("");
	memset(cnt,0,sizeof(cnt));
	++buk[x];
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	init();
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
		++buk[hx[i]];
	}
	for(int i=1;i<=n;++i){
		printf("%d\n",jdg(hx[i]));
	}
	return 0;
}
