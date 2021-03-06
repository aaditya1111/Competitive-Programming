#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxV = 1 + 100 + 100 + 1, maxN = 100, inf = 1e9; int source, target, vertices;
int horses[maxN], n, m, k;

// source (0) -[1]> soldiers (1 : m) -[1]> horsess (1 + m : 1 + m + n - 1) -[c]> target (1 + m + n)
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxV];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}
int ptr[maxV], level[maxV];
bool bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0;
  queue<int> q; q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (auto &e: graph[u])
      if (level[e.to] == -1 && e.flow)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}
int dfs(int u = source, int flow = inf)
{
  if (u == target || !flow) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    auto &e = graph[u][p];
    if (level[e.to] == level[u] + 1 && e.flow)
    {
      int delivered = dfs(e.to, min(e.flow, flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return(delivered);
    }
  }
  return(0);
}
int dinic()
{
  int maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs()) maxFlow += flow;
  }
  return(maxFlow);
}

int main()
{
  int t = 0;
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    target = 1 + m + n; vertices = target + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();

    for (int i = 0; i < n; i ++) scanf("%d", &horses[i]);
    for (int i = 0; i < m; i ++) addEdge(source, 1 + i, 1);
    for (int i = 0, u, v; i < k; i ++)
    {
      scanf("%d %d", &u, &v); u --, v --;
      addEdge(1 + v, 1 + m + u, 1);
    }
    for (int i = 0; i < n; i ++) addEdge(1 + m + i, target, horses[i]);

    int ans = dinic();
    printf("Instancia %d\n%d\n\n",  ++ t, ans);
  }

  return(0);
}