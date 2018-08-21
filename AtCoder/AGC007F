#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
const int N=1e6+2;
int n;
char S[N],T[N];

template <class T> inline void apx(T &x,T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int solve(){
	static std::deque<int> dq;
	int ans=0,delta=0;
	dq.push_back(n+1);
	//delta: the times line move left
	for(int i=n+1,j=n;j;--j){
		int lst=i;
		while(i&&(i>j||S[i]!=T[j])) --i;
		if(!i) return -1;
		if(i==lst){
			while(!dq.empty()&&dq.back()-delta>=j){
//				printf("pop:%d\n",dq.back());
				dq.pop_back();
			}
//			printf("push1:%d %d\n",j,j+delta);
			dq.push_back(j+delta);
		}
		else{
			++delta;
			if(i!=j){
				apx(ans,(int)dq.size());
//				printf("push2:%d %d\n",i,i+delta);
				dq.push_front(i+delta);
			}
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	scanf("%s%s",S+1,T+1);
	printf("%d\n",solve());
	return 0;
}
