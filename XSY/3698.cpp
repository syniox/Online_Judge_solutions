#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
typedef long long lint;
const int N=2e5+5;
int n;
lint ans,pre[N];

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

std::priority_queue <lint> q1,q2;
//洞的虚拟位置 向左走的人反悔价值(2p_old-d)//d=pos[d]-val[d]

void ins1(lint pos,int val){//加洞
	//pos+val-p_old-(p_old-d)
	if(!q2.empty()&&pos+val-q2.top()<0){
		lint top=q2.top();
		ans+=pos+val-q2.top();
		q2.pop();
		q1.push(pos*2-top);//被其他人推着反悔
		q2.push(pos+val);//自己跑到新出现的洞
	}
	else q1.push(pos-val);
}

void ins2(lint pos){
	lint top=q1.top();
	q1.pop();
	q2.push(pos*2ll-top);
	ans+=pos-top;
}

int main(){
	n=nxi();
	for(int i=2; i<=n; ++i)
		pre[i]=pre[i-1]+nxi();
	for(int i=1; i<=n; ++i){
		int v=nxi();
		ins1(pre[i],v),ins1(pre[i],v);
		ins2(pre[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
