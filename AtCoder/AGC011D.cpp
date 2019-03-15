#include <iostream>
#include <cstdio>
#include <cstring>
const int N=2e5+5;
int n,q;
char ch[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T,size_t S> class _Que{
	protected:
		T q[S];
		int hd,tl;
	public:
		_Que(){
			hd=tl=0;
		}
		inline int front(){
			return q[hd];
		}
		inline void pop_front(){
			if(++hd==S) hd=0;
		}
		inline void pop_back(){
			if(--tl==-1) tl=S-1;
		}
		inline void push_front(T x){
			if(--hd==-1) hd=S-1;
			q[hd]=x;
		}
		inline void push_back(T x){
			q[tl++]=x;
			if(tl==S) tl=0;
		}
};
_Que <bool,N> que;

inline bool step(const bool rev){
	if(que.front()^rev){
		que.pop_front();
		que.push_front(0^rev);
		return 0;
	}
	else{
		que.pop_front();
		que.push_back(rev);
		return 1;
	}
}

int main(){
	//1:'A', 2:'B'
	n=nxi(),q=nxi();
	scanf("%s",ch+1);
	for(int i=1; i<=n; ++i){
		que.push_back(ch[i]=='A');
	}
	int rev=0;
	for(int i=1; i<=std::min(q,n<<1); ++i){
		rev^=step(rev);
	}
	if(q>(n<<1)&&q&1) rev^=step(rev);
	for(int i=1; i<=n; ++i){
		putchar(que.front()^rev?'A':'B');
		que.pop_front();
	}
	puts("");
	return 0;
}
