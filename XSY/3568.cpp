#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=5005;
int n,q;
char str[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline int msum(const int x,const int y){
	if(x>y) return 0;
	return (x+y)*(y-x+1)/2;
}

namespace S{
	int cnt,lst,ch[N<<1][26];
	lint rk;
	struct node{
		int sz,lk,len,pos,c[26];
	}tr[N<<1];
	struct _init{
		_init(){tr[0].lk=-1;}
	}init;

	void insert(const int c,const int pos){
		int p=lst,k=lst=++cnt;
		tr[k].len=tr[p].len+1;
		tr[k].pos=pos;
		tr[k].sz=1;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
		}
		if(p==-1) return;
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[k].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			tr[cnt].sz=0;
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk){
				tr[p].c[c]=cnt;
			}
			tr[q].lk=tr[k].lk=cnt;
		}
	}

	void dfs_tr(const int x){
		for(int i=0; i<26; ++i){
			if(ch[x][i]){
				dfs_tr(ch[x][i]);
				tr[x].sz+=tr[ch[x][i]].sz;
			}
		}
	}

	void build_tr(){
		for(int i=1; i<=cnt; ++i){
			int lk=tr[i].lk,c=str[tr[i].pos+tr[lk].len]-'a';
			assert(ch[lk][c]==0);
			ch[lk][c]=i;
		}
		dfs_tr(0);
	}

	char dfs_ans(const int x){
		for(int i=0; i<26; ++i){
			if(!ch[x][i]) continue;
			const int y=ch[x][i],sz=tr[y].sz;
			lint tot=sz*msum(tr[x].len+1,tr[y].len);
			if(rk<=tot){
				//l=最后一个跑满的数
				int l=tr[x].len,r=tr[y].len,mid;
				while(l!=r){
					mid=(l+r+1)>>1;
					if((lint)sz*msum(tr[x].len+1,mid)<=rk) l=mid;
					else r=mid-1;
				}
				int p=tr[y].pos;
				rk-=(lint)sz*msum(tr[x].len+1,l);
				if(!rk) p+=l-1;
				else{
					assert(l<tr[y].len);
					p+=(rk-1)%(l+1);
				}
				return str[p];
			}
			rk-=tot;
			int ans=dfs_ans(ch[x][i]);
			if(ans>0) return ans;
		}
		return -1;
	}

	char get_ans(const lint rk){
		S::rk=rk;
		char ans=dfs_ans(0);
		assert(ans!=-1);
		return ans;
	}
}

int main(){
	q=nxi();
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=n; i>=1; --i){
		S::insert(str[i]-'a',i);
	}
	S::build_tr();
	while(q--){
		printf("%c",S::get_ans(nxi()));
	}
	puts("");
	return 0;
}
