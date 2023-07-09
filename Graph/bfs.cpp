vector<int> bfs(vector<vector<int>> &G, int s) {
  vector<int> dist((int)G.size(), -1);
  dist[s] = 0;
  queue<int> qu;
  qu.push(s);
  while (!qu.empty()) {
    int v = qu.front();
    qu.pop();
    for (const int &x: G[v]) {
      if (dist[x] != -1) continue;
      dist[x] = dist[v] + 1;
      qu.push(x);
    }
  }
  return dist;
}

vector<int> bfs(vector<vector<pair<int, int>>> &G, int s) {
  vector<int> dist((int)G.size(), -1);
  dist[s] = 0;
  queue<int> qu;
  qu.push(s);
  while (!qu.empty()) {
    int v = qu.front();
    qu.pop();
    for (auto &[x, c]: G[v]) {
      if (dist[x] != -1) continue;
      dist[x] = dist[v] + c;
      qu.push(x);
    }
  }
  return dist;
}
