#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
const int N=2e5+5;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	int n,cnt,lst;
	struct node{
		int to,lk,c[26],len;
		bool end;
	}tr[N<<1];
	std::vector <int> ch[N<<1];

	inline void init(){
		memset(tr,0,(cnt+1)*sizeof(node));
		for(int i=0; i<=cnt; ++i){
			ch[i].clear();
		}
		cnt=lst=0;
		tr[0].lk=-1;
	}

	inline void ins(int c,int pos){
		int p=lst,x=lst=++cnt;
		tr[x].len=tr[p].len+1;
		tr[x].end=pos+tr[x].len-1==n;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=x;
		}
		if(p==-1) return;
		int q=tr[p].c[c];
		if(tr[q].len==tr[p].len+1) tr[x].lk=q;
		else{
			tr[++cnt]=tr[q];
			tr[cnt].len=tr[p].len+1;
			tr[cnt].end=0;
			for(; ~p&&tr[p].c[c]==q; p=tr[p].lk){
				tr[p].c[c]=cnt;
			}
			tr[x].lk=tr[q].lk=cnt;
		}
	}

	inline void build_tree(){
		for(int i=1; i<=cnt; ++i){
			ch[tr[i].lk].push_back(i);
		}
	}

	inline double dfs(int x){
		//when to return 0?
		if(tr[x].end) return 0;
		double buk=0;
		for(std::vector <int> ::iterator it=ch[x].begin(); it!=ch[x].end(); ++it){
			buk+=(double)1/(dfs(*it)+tr[*it].len-tr[x].len);
		}
		return (double)1/buk;
	}
}

inline double solve(){
	static char ch[N];
	S::init();
	scanf("%s",ch+1);
	S::n=strlen(ch+1);
	for(int i=S::n; i; --i){
		S::ins(ch[i]-'a',i);
	}
	S::build_tree();
	return S::dfs(0);
}

int main(){
	for(int T=nxi(); T; --T){
		printf("%.12lf\n",solve());
	}
	return 0;
}
