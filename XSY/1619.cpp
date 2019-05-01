#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n;
struct _pair{
	int x,y;
};

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> class Queue{
	protected:
		T que[N];
		int hd,tl;
	public:
		Queue():hd(0),tl(0){}
		inline bool empty(){
			return hd==tl;
		}
		inline T front(){
			return que[hd];
		}
		inline void pop_front(){
			if(++hd==N) hd=0;
		}
		inline void push_back(const T v){
			que[tl]=v;
			if(++tl==N) tl=0;
		}
};

namespace S{
	int cnt;
	struct node{
		int lk,len,c[26];
	}tr[N<<2];

	inline void init(){
		tr[0].lk=-1;
	}

	int insert(const int c,const int lst){
		int p=lst,k=++cnt;
		tr[k].len=tr[lst].len+1;
		for(; ~p&&!tr[p].c[c]; p=tr[p].lk){
			tr[p].c[c]=k;
		}
		if(p==-1) return k;
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
		return k;
	}

	inline lint solve(){
		lint ans=0;
		for(int i=1; i<=cnt; ++i){
			ans+=tr[i].len-tr[tr[i].lk].len;
		}
		return ans;
	}
}

namespace T{
	int cnt;
	struct node{
		int c[26];
	}tr[N];

	void insert(const char *str,const int len){
		int p=0;
		for(int i=1; i<=len; ++i){
			int c=str[i]-'a';
			if(!tr[p].c[c]) tr[p].c[c]=++cnt;
			p=tr[p].c[c];
		}
	}

	void bfs(){
		static Queue <_pair> que;
		que.push_back((_pair){0,0});
		while(!que.empty()){
			_pair p=que.front();
			que.pop_front();
			for(int i=0; i<26; ++i){
				if(tr[p.x].c[i]){
					que.push_back((_pair){tr[p.x].c[i],S::insert(i,p.y)});
				}
			}
		}
	}
}

int main(){
	static char str[N];
	S::init();
	n=nxi();
	for(int i=1; i<=n; ++i){
		scanf("%s",str+1);
		const int len=strlen(str+1);
		T::insert(str,len);
	}
	T::bfs();
	printf("%lld\n",S::solve());
	return 0;
}
