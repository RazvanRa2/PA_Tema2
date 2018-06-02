#include <bits/stdc++.h>
using namespace std;


struct Edge {
    int x;
    int y;
    inline bool operator!=(Edge a) {
        if (a.x!=x || a.y!= y)
            return true;
        return false;
    }
};
const int kNmax = 100005;
int n;
int m;
vector<int> adj[kNmax];


// ordinea de vizitare
// found[node] = timpul de start a lui node in parcurgerea DFS
// in laborator found se numeste idx
vector<int> found;

// low_link[node] = min { found[x] | x este accesibil din node }
// adica timpul minim al unui nou
vector<int> low_link;

// vector in care retin punctele de articulatie
vector<int> cut_vertex;

// vector cu are marchez ca node este deja in cut_vertex
// (evit duplicatele)
vector<int> is_cv;

// vector in care retin muchiile critice (puntile)
vector<Edge> critical_edges;

// parent[i] = parintele nodului i
vector<int> parent;

void DFS_util(int v, vector<bool>& visited, vector<int>& newConexComp) {
    visited[v] = true;
    newConexComp.push_back(v);

    vector<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); i++) {
        if (!visited[*i]) {
            DFS_util(*i, visited, newConexComp);
        }
    }
}

// determina componentele conexe cu dfs util de mai sus
vector<vector <int> > connected_comps() {
    vector< vector <int> > conComp;
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (visited[i] == false) {
            vector<int> newConexComp;

            DFS_util(i, visited, newConexComp);

            conComp.push_back(newConexComp);
        }
    }
    return conComp;
}

// metoda verifica daca muchia data exista in graf de mai multe ori
bool unique_edge(pair<int, int> edge) {
    int cnt = 0;
    for (int i = 0; i < adj[edge.first].size(); i++) {
        if (adj[edge.first][i] == edge.second)
            cnt++;
    }
    if (cnt > 1) {
        return false;
    }
    return true;

}
void dfs(int node, int &current_start) {
  ++current_start;

  found[node] = current_start;
  low_link[node] = current_start;

  int children = 0;

  for (auto &vecin : adj[node]) {
    if (found[vecin] == -1) {
      parent[vecin] = node;

      ++children;
      Edge temp;
      temp.x = node;
      temp.y = vecin;

      dfs(vecin, current_start);

      low_link[node] = std::min(low_link[node], low_link[vecin]);

      if (low_link[vecin] >= found[node]) {
        if (parent[node] != 0) {
          if (!is_cv[node]) {
            is_cv[node] = 1;
            cut_vertex.push_back(node);
          }
        }
      }

      if (low_link[vecin] > found[node]) {
          if (unique_edge(make_pair(temp.x, temp.y)))  // adaug o muchie doar daca e unica
            critical_edges.push_back(temp);
      }
    } else {
      if (vecin != parent[node]) {
        low_link[node] = std::min(low_link[node], found[vecin]);
      }
    }
  }
}


int tarjan() {
  // momentul curent de start
  int current_start = 0;

  for (int i = 1; i <= n; ++i) {
    if (found[i] == -1) { // nodul nu a fost descoperit deci poate fi exploatat
      parent[i] = 0;  // si ca sa il exploatam il facem radacina

      // pornim o noua cautare din nodul respectiv
      dfs(i, current_start);
    }
  }
  for (int i = 0; i < int(critical_edges.size()); i++) {  // scot toate muchiile din graf
      for (int j = 0; j < adj[critical_edges[i].x].size(); j++) {
          if (adj[critical_edges[i].x][j] == critical_edges[i].y) {
              adj[critical_edges[i].x].erase(adj[critical_edges[i].x].begin() + j);
          }
      }
}
  vector<vector <int> > conComp = connected_comps();  // determin componentele conexe
  long long sum = 0;  // din ceea ce a ramas din graf
  for (int i = 0; i < conComp.size(); i++) {
      int size = conComp[i].size();
      sum += size * (size - 1ll) / 2ll;  // fac suma adunand nr din fiecare componenta
  }
  return sum;  // returnez suma
}


int main() {
    ifstream in("disjcnt.in");
    in >> n >> m;

    found = vector<int>(n + 1, -1);
    low_link = vector<int>(n + 1, 0);
    parent = vector<int>(n + 1, 0);
    is_cv = vector<int>(n + 1, 0);


    for (int i = 1, x, y; i <= m; i++) {
        in >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    in.close();

    int answer = tarjan();

    ofstream out("disjcnt.out");
    out <<  answer << '\n';
    out.close();

	return 0;
}
