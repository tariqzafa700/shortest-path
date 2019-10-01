#include <iostream>
#include <vector>
#include <list>

using namespace std;

enum class state {
    VISITED,
    UNVISITED,
    VISITING
};
int shortestDistance(const vector<vector<pair<int, int>>>& graph, int end)
{
    int sz = graph.size();
    vector<int> weight(sz, 10000);

    vector<state> node_state(sz, state::UNVISITED);
    weight[0] = 0;
    for (int i = 0;i < sz; i++)
    {
        for (int j = 0; j < graph[i].size(); ++j)
        {
            if (node_state[i] == state::UNVISITED && node_state[graph[i][j].first] != state::VISITED)
            {
                int sum = graph[i][j].second  + weight[i];
                if (sum < weight[graph[i][j].first])
                {
                    weight[graph[i][j].first] = sum;
                    node_state[graph[i][j].first] = state::VISITING;
                }
            }
        }
        node_state[i] = state::VISITED;

        cout << weight[sz - 1] << endl;
        return weight[end];
    }
}

int main(int argc, char **argv)
{
    vector<vector<pair<int, int>>> graph = {{{1, 3},{2, 4},{3, 5}}, {{0, 3}}, {{0, 4}}, {{0, 5}}};
    shortestDistance(graph, 3);
    graph = {{{1, 4},{7, 8}}, {{0,4},{2, 8},{7, 11}}, {{3, 7}}, {{5, 4}, {8,2}}};
	return 0;
}
