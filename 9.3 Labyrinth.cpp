#include <bits/stdc++.h>
using namespace std;
const int N = 10000;
int maze[N][N], visited[ N][N];
int level[N][N];
pair<int, int> parent[N][N];
int n, m;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
pair<int, int> src, dst;
void detection_pusher();
bool is_inside(pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;

    if (x >= 0 && x < n && y >= 0 && y < m)
    {
        return true;
    }
    return false;
}
bool is_safe(pair<int, int> coord)
{
    int x = coord.first;
    int y = coord.second;
    if (maze[x][y] == -1)
    {
        return false;
    }
    return true;
}
void bfs(pair<int, int> src)
{
    queue<pair<int, int>> q;
    visited[src.first][src.second] = 1;
    level[src.first][src.second] = 0;
    q.push(src);
    while (!q.empty())
    {
        pair<int, int> head = q.front();
        q.pop();
        int x = head.first;
        int y = head.second;

        for (int i = 0; i < 4; i++)
        {
            int new_x = x + dx[i];
            int new_y = y + dy[i];

            pair<int, int> adj_node = {new_x, new_y};

            if (is_inside(adj_node) && is_safe(adj_node) && visited[new_x][new_y] == 0)
            {
                visited[new_x][new_y] = 1;
                level[new_x][new_y] = level[x][y] + 1;
                parent[adj_node.first][adj_node.second].first = head.first;
                parent[adj_node.first][adj_node.second].second = head.second;
                if (adj_node == src)
                    return;
                q.push(adj_node);
            }
        }
    }
}
int main()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            parent[i][j].first = 0;
            parent[i][j].second = 0;
        }
    }
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            level[i][j] = -1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        string input;
        cin >> input;
        for (int j = 0; j < m; j++)
        {
            if (input[j] == '#')
            {
                maze[i][j] = -1;
            }
            else if (input[j] == 'A')
            {
                src = {i, j};
            }
            else if (input[j] == 'B')
            {
                dst = {i, j};
            }
        }
    }
    bfs(src);
    if (level[dst.first][dst.second] == -1)
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
        cout << level[dst.first][dst.second] << endl;
        //        for(int i =0 ; i <n; i++)
        //        {
        //
        //            for(int j =0; j<m; j++)
        //            {
        //                cout<<'('<<parent[i][j].first<<","<< parent[i][j].second<<')'<<"  ";
        //
        //            }
        //            cout<<"\n";
        //        }
        detection_pusher();
    }
    return 0;
}
void detection_pusher()
{
    queue<pair<int, int>> q;
    stack<char> st;
    q.push(dst);
    while (q.front() != src)
    {
        pair<int, int> head = q.front();
        q.pop();
        if (head.first - parent[head.first][head.second].first == -1 && head.second - parent[head.first][head.second].second == 0)
            st.push('U');
        else if (head.first - parent[head.first][head.second].first == 1 && head.second - parent[head.first][head.second].second == 0)
            st.push('D');
        else if (head.first - parent[head.first][head.second].first == 0 && head.second - parent[head.first][head.second].second == 1)
            st.push('R');
        else if (head.first - parent[head.first][head.second].first == 0 && head.second - parent[head.first][head.second].second == -1)
            st.push('L');
        q.push(parent[head.first][head.second]);
    }
    while (!st.empty())
    {
        cout << st.top();
        st.pop();
    }
}