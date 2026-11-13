#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstdlib>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

    // Rekursi untuk DFS 
    void dfsUntil(int currentVertex, vector<bool>& visited) {
        visited[currentVertex] = true;
        cout << char('A' + currentVertex) << " ";

        for (int i = 0; i < V; i++) {
            if (adjMatrix[currentVertex][i] != 0 && !visited[i]) {
                dfsUntil(i, visited);
            }
        }
    }

    // Mencetak rute dari source sampai vertex v (A -> C -> B)
    void cetakRute(vector<int>& parent, int v) {
        if (parent[v] != -1) {
            cetakRute(parent, parent[v]);
            cout << " -> ";
        }
        cout << char('A' + v);
    }

public:
    Graph(int jumlahVertex) {
        V = jumlahVertex;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            adjMatrix[u][v] = weight;
            adjMatrix[v][u] = weight;
        } else {
            cout << "Index nonvalid" << endl;
        }
    }

    // Menampilkan Adjacency Matrix
    void printAdjMatrix() {
        cout << "  ";
        for (int i = 0; i < V; i++) {
            cout << char('A' + i) << " ";
        }
        cout << endl;

        for (int i = 0; i < V; i++) {
            cout << char('A' + i) << " ";
            for (int j = 0; j < V; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // BFS menggunakan queue
    void bfs(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> titikVisit;

        visited[startVertex] = true;
        titikVisit.push(startVertex);

        while (!titikVisit.empty()) {
            int currentVertex = titikVisit.front();
            titikVisit.pop();
            cout << char('A' + currentVertex) << " ";

            for (int i = 0; i < V; i++) {
                if (adjMatrix[currentVertex][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    titikVisit.push(i);
                }
            }
        }
        cout << endl;
    }

    // DFS menggunakan rekursi
    void dfs(int startVertex) {
        vector<bool> visited(V, false);
        dfsUntil(startVertex, visited);
        cout << endl;
    }

    // Djikstra : jarak terpendek dari source ke tujuan beserta rute yang dilalui
    void djikstra(int source, int tujuan) {
        vector<int> distance(V, INT_MAX);
        vector<int> parent(V, -1);
        vector<bool> visited(V, false);
        distance[source] = 0;

        for (int i = 0; i < V; i++) {
            int u = -1;

            for (int j = 0; j < V; j++) {
                if (!visited[j] &&
                    (u == -1 || distance[j] < distance[u])) {
                    u = j;
                }
            }

            if (u == -1 || distance[u] == INT_MAX)
                break;

            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !visited[v]) {
                    int newDistance = distance[u] + adjMatrix[u][v];

                    if (newDistance < distance[v]) {
                        distance[v] = newDistance;
                        parent[v] = u; // simpan asal rute
                    }
                }
            }
        }

        cout << char('A' + source) << " ke " << char('A' + tujuan) << " : ";
        if (distance[tujuan] == INT_MAX) {
            cout << "Tidak terjangkau" << endl;
        } else {
            cout << "Rute : ";
            cetakRute(parent, tujuan);
            cout << endl;
            cout << "Total jarak : " << distance[tujuan] << endl;
        }
    }
};

int main() {
    system("cls");
    Graph graph(6);

    // A=0, B=1, C=2, D=3, E=4, F=5
    graph.addEdge(0, 1, 4); // A-B
    graph.addEdge(0, 2, 2); // A-C
    graph.addEdge(1, 2, 1); // B-C
    graph.addEdge(1, 3, 5); // B-D
    graph.addEdge(1, 4, 3); // B-E
    graph.addEdge(2, 3, 8); // C-D
    graph.addEdge(2, 4, 6); // C-E
    graph.addEdge(3, 4, 2); // D-E
    graph.addEdge(3, 5, 4); // D-F
    graph.addEdge(4, 5, 3); // E-F

    cout << "Adjacency Matrix :" << endl;
    graph.printAdjMatrix();

    // Pilihan vertex awal dan tujuan dari pengguna
    char awal, tujuan;
    cout << "\nMasukkan vertex awal (A-F)   : ";
    cin >> awal;
    cout << "Masukkan vertex tujuan (A-F) : ";
    cin >> tujuan;

    int s = toupper(awal) - 'A';
    int t = toupper(tujuan) - 'A';

    if (s < 0 || s > 5 || t < 0 || t > 5) {
        cout << "Input tidak valid!" << endl;
        return 0;
    }

    cout << "\nPenelusuran BFS dari " << char('A' + s) << " : ";
    graph.bfs(s);

    cout << "Penelusuran DFS dari " << char('A' + s) << " : ";
    graph.dfs(s);

    cout << "\nJarak terpendek (Djikstra) :" << endl;
    graph.djikstra(s, t);

    return 0;
}