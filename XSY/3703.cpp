#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e6+5;
int n;
char str[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace S{
	int cnt,lst;
	struct node{
		int lk,len,c[2];
	}tr[N<<1];
	struct _init{
		_init(){tr[0].lk=-1;}
	}_init_;

	void insert(const int c){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
		}
		if(p==-1) return;
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[k].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk){
				tr[p].c[c]=cnt;
			}
			tr[k].lk=tr[q].lk=cnt;
		}
	}

	void work(int &st,int &l,int r){
		const int c=str[r]-'0';
		for(; !tr[st].c[c]; ++l){
			insert(str[l]-'0');
			while(st&&tr[tr[st].lk].len>=r-l-1)
				st=tr[st].lk;
		}
		if(l<=r) st=tr[st].c[c];
	}
}

int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int st=0,l=1,i=1; i<=n; ++i){
		S::work(st,l,i);
		printf("%d\n",i-l+1);
	}
	return 0;
}
