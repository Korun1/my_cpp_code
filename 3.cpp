#include <bits/stdc++.h>
#define  pb push_back
#define  lson l,m,rt<<1
#define  rson m+1,r,rt<<1|1
typedef  long long LL;
using namespace std;
const int maxn = 30;
string s[110];
int in[maxn];
vector<int> G[maxn];
int main()
{
    int n;
    while(cin>>n)
    {
        for(int i=1;i<=n;i++) cin>>s[i];
        memset(in,0,sizeof(in));
        for(int i=0;i<=26;i++) G[i].clear();
        int flag = 0;
        string ok="";
        for(int i=2;i<=n;i++)
        {
            int la = s[i-1].size();
            int lb = s[i].size();
            int top = 0;
            for(int j=0;j<la && j<lb;j++)
            {
                if(s[i-1][j]!=s[i][j]){
                    top++;
                    int a = s[i-1][j]-'a'+1;
                    int b = s[i][j]-'a'+1;
                    in[b]++;
                    G[a].pb(b);
                    break;
                }
            }
            if(!top && la>lb){
                flag = 1;
                break;
            }
        }
        if(flag){
            puts("Impossible");
            continue;
        }
        queue<int>Q;
        for(int i=1;i<=26;i++)
        {
            if(!in[i]){
                Q.push(i);
            }
        }
        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            ok+=(u-1+'a');
            for(int j=0;j<G[u].size();j++)
            {
                int v = G[u][j];
                in[v]--;
                if(!in[v]){
                    Q.push(v);
                }
            }
        }
        if(ok.size()==26) {
            cout<<ok<<endl;
        }
        else puts("Impossible");
    }
}
