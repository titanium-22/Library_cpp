vector<ll> dijkstra(vector<vector<pair<int, int>>> &G, int s) {
  int n = (int)G.size();
  vector<ll> dist(n, INF);
  priority_queue<pair<ll, int>> hq;
  hq.push({0, s});
  dist[s] = 0;
  while (!hq.empty()) {
    ll d;
    int v;
    tie(d, v) = hq.top();
    hq.pop();
    if (dist[v] > d) continue;
    for (auto &[x, c]: G[v]) {
      if (dist[x] > d + c) {
        dist[x] = d + c;
        hq.push({dist[x], x});
      }
    }
  }
  return dist;
}
