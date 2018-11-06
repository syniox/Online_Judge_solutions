#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e6+5;
int l1,l2,top,nx[N],st[N];
char s1[N],s2[N],ans[N];

inline void get_nx(){
	for(int i=2,j=0;i<=l2;++i){
		while(j&&s2[j+1]!=s2[i]) j=nx[j];
		if(s2[j+1]==s2[i]) ++j;
		nx[i]=j;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	scanf("%s%s",s1+1,s2+1);
	l1=strlen(s1+1);
	l2=strlen(s2+1);
	get_nx();
	for(int i=1,j=0;i<=l1;++i){
		while(j&&s2[j+1]!=s1[i]) j=nx[j];
		if(s2[j+1]==s1[i]&&++j==l2){
			top-=l2-1;
			j=st[top];
		}
		else{
			ans[++top]=s1[i];
			st[top]=j;
		}
	}
	for(int i=1;i<=top;++i){
		putchar(ans[i]);
	}
	putchar('\n');
	return 0;
}
