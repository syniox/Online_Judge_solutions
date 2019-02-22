#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1005;
const int mod=1e9+7;
int h,w,cnt_v,cnt_row,cnt_col,con_row,con_col;
lint q;

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

class mtrx{
	public:
		int n[3][3];
		friend inline mtrx operator * (const mtrx &a,const mtrx &b);
		inline void reset();
};

inline mtrx operator * (const mtrx &a,const mtrx &b){
	mtrx c;
	for(int i=0; i<3; ++i){
		for(int j=0; j<3; ++j){
			lint tp=0;
			for(int k=0; k<3; ++k){
				tp+=(lint)a.n[i][k]*b.n[k][j];
			}
			c.n[i][j]=tp%mod;
		}
	}
	return c;
}

inline void mtrx::reset(){
	memset(n,0,sizeof(n));
	for(int i=0; i<3; ++i) n[i][i]=1;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void cal_row(char *ch){
	for(int i=1; i<w; ++i){
		if(ch[i]=='#'&&ch[i+1]=='#') ++cnt_row;
		if(ch[i]=='#') ++cnt_v;
	}
	if(ch[w]=='#') ++cnt_v;
	con_row+=ch[1]=='#'&&ch[w]=='#';
}

inline void cal_col(char *ch1,char *ch2){
	for(int i=1; i<=w; ++i){
		if(ch1[i]=='#'&&ch2[i]=='#') ++cnt_col;
	}
}

inline int solve(){
	mtrx ans,t;
	if(!con_col){
		std::swap(con_col,con_row);
		std::swap(cnt_col,cnt_row);
	}
	memset(t.n,0,sizeof(t.n));
	ans.reset();
	t.n[0][0]=t.n[1][1]=cnt_v;
	t.n[2][1]=1;
	t.n[2][2]=con_col;
	for(q-=1; q; q>>=1,t=t*t){
		if(q&1) ans=ans*t;
	}
	const int V=(lint)ans.n[0][0]*cnt_v%mod;
	const int E=((lint)ans.n[1][1]*(cnt_v-1)+(lint)cnt_col*ans.n[2][1])%mod;
	return (V+mod-E)%mod;
}

int main(){
	//static char ch[3][N];
	static char ch[N][N];
	h=nxi<int>(),w=nxi<int>(),q=nxi<lint>();
	if(q<=1){
		puts("1");
		return 0;
	}
	scanf("%s",ch[2]+1);
	for(int i=1; i<w; ++i){
		if(ch[2][i]=='#') ++cnt_v;
		if(ch[2][i]=='#'&&ch[2][i+1]=='#') ++cnt_row;
	}
	con_row+=ch[2][1]=='#'&&ch[2][w]=='#';
	if(ch[2][w]=='#') ++cnt_v;
	if(h>1){
		scanf("%s",ch[0]+1);
		cal_row(ch[0]);
		cal_col(ch[0],ch[2]);
	}
	for(int i=3; i<=h; ++i){
		scanf("%s",ch[i&1]+1);
		cal_row(ch[i&1]);
		cal_col(ch[i&1],ch[(i&1)^1]);
	}
	if(h>1){
		for(int i=1; i<=w; ++i){
			con_col+=ch[2][i]=='#'&&ch[h&1][i]=='#';
		}
	}
	else{
		for(int i=1; i<=w; ++i){
			con_col+=ch[2][i]=='#';
		}
	}
	if((con_col==0)==(con_row==0)){
		printf("%d\n",con_col?1:fpow(cnt_v,std::max(0ll,q-1)));
		return 0;
	}
	printf("%d\n",solve());
	return 0;
}
