#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
typedef long long lint;
const int N=21;
const int ST=50*10*20+5;
const double eps=1e-9;
int n,m,lenw,lenp,dgr[N],mp[N][26],nxtw[N][26];
char sw[12],sp[52];
double ans[51][11][N];
bool vld[ST];
std::vector <int> fr[ST];
//[i,j,k]表示子序列匹配到第i位，字串匹配到第j位，图上在点k

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	template <class T> inline T cabs(const T &x){
		return x<0?-x:x;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline int id2(const int a,const int b){
	return a*n+b-1;
}
inline int id3(const int a,const int b,const int c){
	return a*lenw*n+b*n+c-1;
}

void get_nxt(const char *s,const int len,int nxt[N][26]){
	static int fail[11];
	for(int i=2,j=0; i<=len; ++i){
		while(j&&s[j+1]!=s[i]) j=fail[j];
		if(s[j+1]==s[i]) ++j;
		fail[i]=j;
	}
	for(int i=0; i<len; ++i){
		for(int j=0; j<26; ++j){
			nxt[i][j]=s[i+1]-'a'==j?i+1:nxt[fail[i]][j];
		}
	}
}

void bfs_vld(){
	static int que[ST];
	int hd=0,tl=0;
	for(int i=0; i<lenp; ++i){
		for(int j=0; j<lenw; ++j){
			for(int k=1; k<=n; ++k){
				const int cid=id3(i,j,k);
				for(int l=0; l<26; ++l){
					if(!mp[k][l]) continue;
					int nxtp=i+(l==sp[i+1]-'a');
					if(nxtp==lenp||nxtw[j][l]==lenw){
						que[tl++]=cid;
						vld[cid]=1;
					}
					else{
						fr[id3(nxtp,nxtw[j][l],mp[k][l])].push_back(cid);
					}
				}
			}
		}
	}
	while(hd!=tl){
		const int id=que[hd++];
		for(std::vector <int> ::iterator it=fr[id].begin(); it!=fr[id].end(); ++it){
			if(!vld[*it]){
				vld[*it]=1;
				que[tl++]=*it;
			}
		}
	}
}

bool dfs_inf(const int a,const int b,const int c){
	static bool vis[51][11][21],is_inf[51][11][21];
	if(a==lenp||b==lenw) return 0;
	if(!vld[id3(a,b,c)]) return 1;
	if(vis[a][b][c]) return is_inf[a][b][c];
	vis[a][b][c]=1;
	bool ans=0;
	for(int i=0; !ans&&i<26; ++i){
		if(!mp[c][i]) continue;
		ans|=dfs_inf(a+(i==sp[a+1]-'a'),nxtw[b][i],mp[c][i]);
	}
	return is_inf[a][b][c]=ans;
}

void gauss(double mtrx[201][201],double res[201],const int n){
	static int rec[201];
	int cnt=0;
	for(int i=0; i<n; ++i){
		int t=cnt;
		while(t<n&&cabs(mtrx[t][i])<eps) ++t;
		if(t==n) continue;
		if(t!=cnt){
			for(int j=i; j<=n; ++j){
				std::swap(mtrx[t][j],mtrx[cnt][j]);
			}
		}
		for(int j=cnt+1; j<n; ++j){
			if(cabs(mtrx[j][i])<eps) continue;
			const double w=mtrx[j][i]/mtrx[cnt][i];
			for(int k=i; k<=n; ++k){
				mtrx[j][k]-=w*mtrx[cnt][k];
			}
		}
		rec[cnt++]=i;
	}
	memset(res,0,n*sizeof(double));
	for(int i=cnt; i>=0; --i){
		double sum=mtrx[i][n];
		for(int j=rec[i]+1; j<n; ++j){
			sum+=res[j]*mtrx[i][j];
		}
		res[rec[i]]=-sum/mtrx[i][rec[i]];
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		char c;
		while((c=getchar())>'z'||c<'a');
		++dgr[a];
		mp[a][c-'a']=b;
	}
	scanf("%s",sw+1);
	lenw=strlen(sw+1);
	scanf("%s",sp+1);
	lenp=strlen(sp+1);
	get_nxt(sw,lenw,nxtw);
	if(bfs_vld(),dfs_inf(0,0,1)){
		puts("-1");
		return 0;
	}
	for(int i=lenp-1; ~i; --i){
		static double mtrx[201][201];
		static double res[201];
		memset(mtrx,0,sizeof(mtrx));
		const int tot=lenw*n;
		for(int j=0; j<lenw; ++j){
			for(int k=1; k<=n; ++k){
				const int c=id2(j,k);
				mtrx[c][c]=-dgr[k];
				mtrx[c][tot]=dgr[k];
				for(int l=0; l<26; ++l){
					if(!mp[k][l]||nxtw[j][l]==lenw) continue;
					if(l==sp[i+1]-'a'){
						mtrx[c][tot]+=ans[i+1][nxtw[j][l]][mp[k][l]];
					}
					else{
						mtrx[c][id2(nxtw[j][l],mp[k][l])]+=1.;
					}
				}
			}
		}
		gauss(mtrx,res,tot);
		for(int j=0; j<lenw; ++j){
			for(int k=1; k<=n; ++k){
				ans[i][j][k]=res[id2(j,k)];
			}
		}
	}
	printf("%.6lf\n",ans[0][0][1]);
	return 0;
}
