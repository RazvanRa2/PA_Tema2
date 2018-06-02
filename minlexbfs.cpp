#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;

int n;
int m;
vector<int> adj[kNmax];


vector<int> get_result() {
    vector<bool> visited(n + 1, false);
    list<int> queue;
    vector<int>::iterator i;
    vector<int> result;
    int source = 1;
    visited[source] = true;
    queue.push_back(source);

    while (!queue.empty()) {  // o parcurgere eleganta cat de cat
        result.push_back(queue.front());
        source = queue.front();
        queue.pop_front();

        vector<int> currSoruceNeighbours; // aici o sa pun vecinii nodului curent

        for (i = adj[source].begin(); i != adj[source].end(); i++) {
            if (visited[*i] == false) {
                visited[*i] = true;
                currSoruceNeighbours.push_back(*i);
            }
        }
        sort(currSoruceNeighbours.begin(), currSoruceNeighbours.end());  // aici o sa ii sortez
        for (unsigned int cnt = 0; cnt < currSoruceNeighbours.size(); cnt++) {
            queue.push_back(currSoruceNeighbours[cnt]);  // aici ii bag dupa in coada
        } // aici i-am bagat deja in coada
    }
    return result;
}


int main() {
    ifstream in("minlexbfs.in");
    in >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
        in >> x >> y; // citesc matricea de adiacenta
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    in.close();

    vector<int> result = get_result();  // fac bfs minim lexi

    ofstream out("minlexbfs.out");
    for(unsigned int i = 0; i < result.size(); i++) {  // si il afisez
        out << result[i] << " ";
    }
    out << '\n';
    out.close();

	return 0;
}
