#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
char str[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
	scanf("%s",str+1);
	int ans=0;
	for(int i=strlen(str+1); i>1; --i){
		ans+=str[i]!=str[i-1];
	}
	printf("%d\n",ans);
	return 0;
}
