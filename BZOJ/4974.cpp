#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
int n,nx[N];
char ch[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void get(const int t){
	static bool vis[26];
	memset(vis,0,sizeof(vis));
	for(int i=t-1;;i=nx[i]){
		if(i+1!=t) vis[(int)ch[i+1]-'a']=1;
		if(i==0) break;
	}
	for(int i=0;i<26;++i){
		if(!vis[i]){
			ch[t]=i+'a';
			break;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		nx[i]=i-nxi();
		if(nx[i]) ch[i]=ch[nx[i]];
		else get(i);
	}
	printf("%s\n",ch+1);
	return 0;
}
