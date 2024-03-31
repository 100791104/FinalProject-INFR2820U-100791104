//All done by Nishaanth Murali, 100791104

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <queue>

#define INF 0x3f3f3f3f

typedef std::pair<int, int> iPair;

class Graph {
    int V;

    std::list<std::pair<int, int> >* adj;

public:
    Graph(int V);

    void addEdge(int u, int v, int w);

    void shortestPath(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new std::list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(std::make_pair(v, w));
    adj[v].push_back(std::make_pair(u, w));
}

void Graph::shortestPath(int src)
{
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair> >pq;

    std::vector<int> dist(V, INF);

    pq.push(std::make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {

        int u = pq.top().second;
        pq.pop();

        std::list<std::pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }

    printf("Charging Station \t Distance\n");
    for (int i = 0; i < V; ++i) {
        if (i == 7 || i == 10 || i == 16 || i == 19) {
            printf("%d \t\t\t %d\n", i, dist[i]);
        }
    }

    int mini = INF;
    int min = 0;

    for (int x = 0; x < V; x++) {
        if (x == 7 || x == 10 || x == 16 || x == 19) {
            if (dist[x] < mini) {
                mini = dist[x];
                min = x;
            }
        }
        if (x == 22) {
            std::cout << "\nRecommended Charging Station: " << min << std::endl;
        }
    }
}


int main()
{
    int const size = 33;
    std::ifstream graph1("map1.csv");
    std::string tnode1, tnode2, tnode3, line;
    int node1[size], node2[size], node3[size];
    int counter = 0;

    while (getline(graph1, line)) {
        std::stringstream ss(line);
        getline(ss, tnode1, ',');
        getline(ss, tnode2, ',');
        getline(ss, tnode3, ',');
        node1[counter] = stoi(tnode1);
        node2[counter] = stoi(tnode2);
        node3[counter] = stoi(tnode3);
        counter++;
    }

    graph1.close();

    Graph g(23);

    for (int i = 0; i < size; i++) {
        g.addEdge(node1[i], node2[i], node3[i]);
    }

    int input;
    std::cout << "Enter your location (A,B,C,..) as an integer (0-22) where A = 0, B = 1, and so on.\n";
    std::cin >> input;
    std::cout << std::endl;
    g.shortestPath(input);

    return 0;
}