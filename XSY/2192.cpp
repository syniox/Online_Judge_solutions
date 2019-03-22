#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
const int N=1e6+5;
int n,per2[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int jmp(int x,int step){
	while(step--) x=per2[x];
	return x;
}

namespace G{
	std::vector <int> buk[N];
	int lk[N];
	bool vis[N];

	inline void get_cir(const int x){
		int sz=1;
		vis[x]=1;
		for(int i=per2[x]; i!=x; ++sz,i=per2[i]){
			vis[i]=1;
		}
		buk[sz].push_back(x);
	}

	inline bool oput(){
		std::vector <int> ::iterator it;
		for(it=buk[1].begin(); it!=buk[1].end(); ++it){
			lk[*it]=*it;
		}
		for(int i=2; i<=n; ++i){
			if(!(i&1)&&buk[i].size()&1) return 0;
			if((i&1)==0){
				for(it=buk[i].begin(); it!=buk[i].end(); ++it){
					int x=*it,y=*++it;
					lk[x]=y,lk[y]=per2[x];
					for(int j=per2[x],k=per2[y]; j!=x; j=per2[j],k=per2[k]){
						lk[j]=k,lk[k]=per2[j];
					}
				}
			}
			else{
				for(it=buk[i].begin(); it!=buk[i].end(); ++it){
					int t=jmp(*it,(i+1)>>1);
					for(int i=*it,j=t; i!=t; i=per2[i],j=per2[j]){
						lk[i]=j,lk[j]=per2[i];
					}
				}
			}
		}
		for(int i=1; i<=n; ++i){
			printf("%d ",lk[i]);
		}
		puts("");
		return 1;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		per2[nxi()]=i;
		//per2[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		if(!G::vis[i]) G::get_cir(i);
	}
	if(!G::oput()) puts("-1");
	return 0;
}
