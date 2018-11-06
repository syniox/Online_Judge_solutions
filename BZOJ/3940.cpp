#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
int n,cl[N];
char str[N],ch[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	int cnt,top,st[N],que[N];
	char stk[N];
	struct node{
		int lk,end,c[26];
	}tr[N];

	inline void add(char ch[],const int id,const int len){
		int p=0;
		for(int i=1;i<=len;++i){
			const int c=ch[i]-'a';
			if(!tr[p].c[c]) tr[p].c[c]=++cnt;
			p=tr[p].c[c];
		}
		tr[p].end=id;
	}

	inline void build(){
		int hd=0,tl=1;
		while(hd!=tl){
			const int x=que[hd++],lk=tr[x].lk;
			for(int i=0;i<26;++i){
				const int y=tr[x].c[i];
				if(!y) tr[x].c[i]=tr[lk].c[i];
				else{
					if(lk!=x) tr[y].lk=tr[lk].c[i];
					que[tl++]=y;
				}
			}
		}
	}

	inline void solve(){
		const int len=strlen(str+1);
		for(int i=1,p=0;i<=len;++i){
			const int c=str[i]-'a';
			if(tr[p=tr[p].c[c]].end){
				top-=cl[tr[p].end]-1;
				p=st[top];
			}
			else{
				st[++top]=p;
				stk[top]=c+'a';
			}
		}
	}

	inline void print(){
		for(int i=1;i<=top;++i){
			putchar(stk[i]);
		}
		putchar('\n');
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	scanf("%s",str+1);
	n=nxi();
	for(int i=1;i<=n;++i){
		scanf("%s",ch+1);
		cl[i]=strlen(ch+1);
		S::add(ch,i,cl[i]);
	}
	S::build();
	S::solve();
	S::print();
	return 0;
}
