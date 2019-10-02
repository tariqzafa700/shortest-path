#include <iostream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

enum class state {
    VISITED,
    UNVISITED,
    VISITING
};

const string stateStr[] = {"VISITED",
    "UNVISITED",
    "VISITING"};

std::ostream& operator << (std::ostream& os, const state& obj)
{
   os << static_cast<std::underlying_type<state>::type>(obj);
   return os;
}

//node_state[j] == state::UNVISITED && 
int shortestDistance(const vector<vector<pair<int, int>>>& graph, int end)
{
    int sz = graph.size();
    vector<int> weight(sz, 10000);

    vector<state> node_state(sz, state::UNVISITED);
    weight[0] = 0;
    for (int i = 0;i < sz; i++)
    {
        cout << "visiting " << i << endl; 
        for (int j = 0; j < graph[i].size(); ++j)
        {
            cout << "node " << node_state[graph[i][j].first] << " of " << graph[i][j].first <<  endl;
            if (node_state[graph[i][j].first] != state::VISITED)
            {
                int sum = graph[i][j].second  + weight[i];
                cout << "visited " << sum << " " << weight[graph[i][j].first] << endl;

                if (sum < weight[graph[i][j].first])
                {
                    weight[graph[i][j].first] = sum;
                    node_state[graph[i][j].first] = state::VISITING;
                }
                copy(weight.begin(), weight.end(), ostream_iterator<int>(std::cout, " "));
            }
        }
        node_state[i] = state::VISITED;     
    }
    cout << weight[end] << endl;
    return weight[end];
}

int main(int argc, char **argv)
{
    vector<vector<pair<int, int>>> graph = {{{1, 3},{2, 4},{3, 5}}, {{0, 3}}, {{0, 4}}, {{0, 5}}};
    //shortestDistance(graph, 3);
    graph = {{{1, 4},{7, 8}}, {{0,4},{2, 8},{7, 11}}, {{1,8},{3, 7},{5,4},{8,2}}, {{2,7},{4,9},{5,14}}, {{3,9}, {5,10}}, 
    {{2,4},{3,14}, {4,10},{6,2}}, {{5,2},{7,1},{8,6}}, {{0,8},{1,11},{6,1},{8,7}},{{2,2},{6,6},{7,7}}};
        shortestDistance(graph, 4);

	return 0;
}
