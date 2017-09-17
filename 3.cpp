#include <bits/stdc++.h>
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
        memset(in,0,sizeof(in)); // in为记录入度的数组，in[1] = 1 代表节点1有一个入度边。
        for(int i=0;i<=26;i++) G[i].clear(); // 用vector容器记录边
        int flag = 0;
        string ok="";
        for(int i=2;i<=n;i++) //从第二个字符串开始记录，第二个和第一个字符串有解的情况肯定是第二个字符串的字典序大于第一个
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
					// 发现两个字符串不同的地方，那么建立一条a->b有向边，in[b]++,b的入度加1
                    in[b]++;
                    G[a].pb(b);
                    break;
                }
            }
            if(!top && la>lb){ // 此处代表前一字符串是bacd 后一个是bac，类似这种情况，那么无解。
                flag = 1;
                break;
            }
        }
        if(flag){ 
			//输出无解
            puts("Impossible");
            continue;
        }
		// 此处开始跑topsort
        queue<int>Q;
        for(int i=1;i<=26;i++)
        {
            if(!in[i]){
				// 把入度为0的节点首先放入队列。
                Q.push(i);
            }
        }
        while(!Q.empty())
        {
			// 遍历队列，一次次减少边，直到队列遍历完成
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
        else puts("Impossible"); // 此处代表这种情况出现了: b->a ,a->b 既出现环，那么topsort跑完此图还是有非独立节点。
    }
}
