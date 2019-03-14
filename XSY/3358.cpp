#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
const int N=1e5+5;
int n,m,q,col[N];
bool open[N];
class _pair{
	public:
		int x,y;
};

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace WTF{
	const int S=720;//size?
	int cnt_col[N],delta[N];
	bool is_spec[N],stat[N];
	std::map <int,int> nb[N];//neighbourlist
	std::vector <int> spec;//specialcolor(nb.size()>sqrt(n))
	std::vector <_pair> list[N];//effects

	void main(){
		for(int i=1; i<=n; ++i){
			++cnt_col[col[i]];
			if(i==n) break;
			++nb[col[i]][col[i+1]];
			++nb[col[i+1]][col[i]];
		}
		for(int i=1; i<=m; ++i){
			const int sz=nb[i].size();
			if(sz<S){
				is_spec[i]=0;
				std::map <int,int> ::iterator it;
				for(it=nb[i].begin(); it!=nb[i].end(); ++it){
					list[i].push_back((_pair){it->first,it->second});
				}
			}
			else{
				is_spec[i]=1;
				spec.push_back(i);
			}
			delta[i]=cnt_col[i];
		}
		int ans=0;
		while(q--){
			const int c=nxi();
			int res=delta[c];
			for(std::vector <int> ::iterator it=spec.begin(); it!=spec.end(); ++it){
				std::map <int,int> ::iterator tmp;
				if(*it!=c&&stat[*it]&&(tmp=nb[*it].find(c))!=nb[*it].end()){
					res-=tmp->second;
				}
			}
			stat[c]^=1;
			ans+=stat[c]?res:-res;
			if(!is_spec[c]){
				std::vector <_pair> ::iterator it;
				for(it=list[c].begin(); it!=list[c].end(); ++it){
					delta[it->x]+=stat[c]?-it->y:it->y;
				}
			}
			printf("%d\n",ans);
		}
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		col[i]=nxi();
	}
	n=std::unique(col+1,col+n+1)-col-1;
	WTF::main();
	return 0;
}
