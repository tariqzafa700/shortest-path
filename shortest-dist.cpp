#include <iostream>
#include <vector>
#include <list>

using namespace std;

enum class state {
    VISITED,
    UNVISITED,
    VISITING
};
int shortestDistance(const vector<vector<pair<int, int>>>& graph)
{
    int sz = graph.size();
    vector<int> weight(sz);

    vector<state> node_state(sz, state::UNVISITED);
    for (int i = 0;i < sz; i++)
    {
        for (int j = 0; j < graph[i].size(); ++j)
        {
            if (node_state[i] == state::UNVISITED)
            {
                node_state[i] = state::VISITING;
                if (graph[i][j].second < weight[graph[i][j].first])
                {
                    weight[graph[i][j].first] = graph[i][j].second;
                }
            }
        }
        cout << endl;
    }
}

int main(int argc, char **argv)
{
    vector<vector<pair<int, int>>> graph = {{{1, 3},{2, 4},{3, 5}}, {{0, 3}}, {{0, 4}}, {{0, 5}}};
    shortestDistance(graph);
	return 0;
}
