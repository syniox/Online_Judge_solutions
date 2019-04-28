#include <iostream>
#include <cstdio>
#include <cstring>

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
	int n=nxi(),m=nxi(),x=nxi(),y=nxi();
	if(n%x==0&&m%y==0){
		puts("No");
		return 0;
	}
	puts("Yes");
	if(m%y){
		const int w=(y-1)*1000+1;
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				printf("%d ",j%y?1000:-w);
			}
			puts("");
		}
	}
	else if(n%x){
		const int w=(x-1)*1000+1;
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=m; ++j){
				printf("%d ",i%x?1000:-w);
			}
			puts("");
		}
	}
	return 0;
}
