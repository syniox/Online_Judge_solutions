#include<iostream>
#include<cstdio>
#include<cstring>
const int N=16,M=1e6;
int n,POS,pos[N],sp[N],lf[N];

inline void apx(int &x,const int y){
	if(x<y) x=y;
}

inline int gcd(int x,int y){
	for(;y;x%=y,std::swap(x,y));
	return x;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

void exgcd(int &a,int &b,const int x,const int y){
	if(!y){
		a=1,b=0;
		return;
	}
	exgcd(a,b,y,x%y);
	const int tp=a;
	a=b;
	b=tp-b*(x/y);
}

inline bool calc(int x,int y,const int l){
	if(pos[x]>pos[y]) std::swap(x,y);
	const int step=sp[x]>sp[y]?sp[x]-sp[y]:sp[x]-sp[y]+l;
	const int ns=gcd(step,l);
	if((pos[y]-pos[x])%ns) return 0;
	const int ts=l/ns;
	int a,b;
	exgcd(a,b,step,l);
	a=(a*(pos[y]-pos[x])/ns)%ts;
	if(a<0) a+=ts;
	return a<=lf[x]&&a<=lf[y];
}

inline bool solve(const int l){
	for(int i=1;i<=n;++i){
		for(int j=1;j<i;++j){
			if(calc(i,j,l)) return 0;
		}
	}
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		pos[i]=nxi(),sp[i]=nxi(),lf[i]=nxi();
		apx(POS,pos[i]);
	}
	for(int i=POS;i<=M;++i){
		if(solve(i)){
			printf("%d\n",i);
			break;
		}
	}
	return 0;
}
