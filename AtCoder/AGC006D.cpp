#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;

int n,a[N<<1];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

//>t
inline bool jdg(int t){
	for(int i=0;i<n;++i){
		if((a[n-i]>t)==(a[n-i-1]>t)) return a[n-i]>t;
		if((a[n+i]>t)==(a[n+i+1]>t)) return a[n+i]>t;
	}
	return a[1]>t;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<n<<1;++i){
		a[i]=nxi();
	}
	int l=1,r=(n<<1)-1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(jdg(mid)) l=mid+1;
		else r=mid;
	}
	printf("%d\n",l);
	return 0;
}
