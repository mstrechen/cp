#include<iostream>
#include<vector>
#include<queue>
#include<cmath>


using namespace std;

struct Network
{
    int size, be, en;
    vector<vector<int> > c{(size_t)size, vector<int>(size, 0)};
    vector<int> e{}, h{};

    Network(int size, int be, int en) : size(size), be(be), en(en) {}

    void addEdge(int x, int y, int val)
    {
        c[x][y]+=val;
    }

    void init()
    {
        h.assign(size, 0);
        e.assign(size, 0);
        e[be] = 1000*1000*1000;
        h[be] = (int)(3*sqrt(size));
    }

    void push(int x, int y)
    {
        int val = min(e[x], c[x][y]);
        c[x][y] -= val;
        c[y][x] += val;
        e[x] -= val;
        e[y] += val;
    }

    int getMaxFlow()
    {
        vector<int> used(size, 0);
        used[en] = 1;
        init();

        priority_queue<pair<int,int> > Q;
        Q.emplace(h[be], be);

        while(!Q.empty())
        {
            int i = Q.top().second;
            Q.pop();

            for(int j = 0; j < size; j++)
                if(c[i][j] && h[i] > h[j])
                {
                    push(i, j);
                    if(j!=be && !used[j])
                    {
                        Q.emplace(h[j], j);
                        used[j] = 1;
                    }
                }

            if(i!=be && e[i])
            {
                h[i]++;
                Q.emplace(h[i], i);
            }
            else
            {
                used[i] = 0;
            }
        }
        return e[en];
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n,m;
    cin >> n >> m;

    Network NW(n, 0, 1);

    for(int i = 0; i<m; i++)
    {
        int x, y, c;
        cin >> x >> y >> c;
        NW.addEdge(x,y,c);
    }

    cout << NW.getMaxFlow();

    return 0;
}
