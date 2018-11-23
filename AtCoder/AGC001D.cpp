#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
int n,m,cnt1,hx[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	//	freopen("d.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		hx[i]=nxi();
		cnt1+=hx[i]&1;
	}
	if(cnt1>2){
		puts("Impossible");
		return 0;
	}
	for(int i=2;i<m;++i){
		if(hx[i]&1){
			if(hx[1]&1) std::swap(hx[i],hx[m]);
			else std::swap(hx[1],hx[i]);
		}
	}
	for(int i=1;i<=m;++i){
		printf("%d ",hx[i]);
	}
	puts("");
	if(m==1&&n!=1){
		printf("2\n%d 1\n",n-1);
		return 0;
	}
	++hx[1];
	if(!--hx[m]) --m;
	printf("%d\n",m);
	for(int i=1;i<=m;++i){
		printf("%d ",hx[i]);
	}
	puts("");
	return 0;
}
