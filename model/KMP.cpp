#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e6+2;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
	static char s1[N],s2[N];
	static int nx[N];
	scanf("%s%s",s1+1,s2+1);
	int n=strlen(s1+1),m=strlen(s2+1);

	for(int i=2,j=0;i<=m;++i){
		while(j&&s2[j+1]!=s2[i]) j=nx[j];
		if(s2[j+1]==s2[i]) ++j;
		nx[i]=j;
	}
	for(int i=1,j=1;i<=n&&j<=m;++i){
		while(j&&s1[i]!=s2[j+1]) j=nx[j];
		if(s1[i]==s2[j+1]) ++j;
		if(j==m){
			printf("%d\n",i-m+1);
			j=nx[j];
		}
	}
	return 0;
}
