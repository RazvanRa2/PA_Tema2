#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#define NMAX 509
#define oo (1 << 21)
using namespace std;

int n, m, q;
int d[NMAX][NMAX], p[NMAX][NMAX];
vector<pair <int, int> > queries;

void read_input() {
    ifstream in("revedges.in");
    in >> n >> m >> q;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] = oo;  // toate laturile sunt puse initial pe infinit
        }
    }
  for (int i = 0, x, y; i < m; i++) {
      in >> x >> y;  // citesc muchiile
      d[x][y] = 1;  // pun distante pe muchiile "reale"
      p[x][y] = x;  // notez "parintii" pentru noduri
  }

  for (int i = 0, x, y; i < q; i++) {  // citesc querry-uri
      in >> x >> y;
      queries.push_back(make_pair(x, y));
  }
  in.close();

  for (int x = 1; x <= n; x++) {
      for (int y = 1; y <= n; y++) {
          if (d[y][x] == oo && d[x][y] == 1) {
              d[y][x] = 7826;  // this is explained in the readme
          }
      }
  }
}

void RoyFloyd() {
  for (int k = 1; k <= n; ++k) {  // un RoyFloyd corect
    for (int i = 1; i <= n; ++i) {  // corespunzator
      for (int j = 1; j <= n; ++j) {  // cum ne place noua
        if (i != j && d[i][k] + d[k][j] < d[i][j]) {
          d[i][j] = d[i][k] + d[k][j];
          p[i][j] = p[k][j];
        }
      }
    }
  }
}

int main() {
  read_input();
  RoyFloyd();

  ofstream out("revedges.out");
  for (int i = 0; i < q; i++) {
      if (queries[i].first != queries[i].second) {
          out << d[queries[i].first][queries[i].second] / 7826 << '\n';
      } else {
          out << 0 << '\n';
      }
  }
  out.close();

  return 0;
}
