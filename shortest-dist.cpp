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

struct node_value {
    int node;
    int val;
};

std::ostream& operator << (std::ostream& os, const node_value& obj)
{
   os << "node " << obj.node << " value " << obj.val << endl;
   return os;
}

template<class T>
void swap_T(T& first, T& second)
{
    T temp = first;
    first = second;
    second = temp;
}

void balance_up(vector<node_value>& heap)
{
    int size = heap.size();
    while (size > 1 && heap[size / 2 - 1].val > heap[size - 1].val)
    {
        if (heap[size / 2 - 1].node == heap[size - 1].node)
        {

        }
        swap_T(heap[size / 2 - 1], heap[size - 1]);
        size = size / 2;
    }
}

void balance_down(vector<node_value>& heap, int start, int end)
{
    int index = start;
    while (index < end)
    {
        if (index * 2 + 2 < end && heap[index * 2 + 1].val > heap[index * 2 + 2].val)
        {
            cout << "swapping right left" << endl;
            swap_T(heap[index * 2 + 1], heap[index * 2 + 2]);
        }
        if (index * 2 + 1 < end && heap[index * 2 + 1].val < heap[index].val)
        {
            cout << "swapping top down" << endl;
            swap_T(heap[index * 2 + 1], heap[index]);
        }
        index = index * 2 + 1;    
    }
}

void add_to_heap(vector<node_value>& heap, node_value next)
{
    heap.push_back(next);
    balance_up(heap);
    
    cout << "after balancing up" << endl;
    copy(heap.begin(), heap.end(), ostream_iterator<node_value>(cout, " "));
}

node_value get_min_from_heap(vector<node_value>& heap)
{
    swap_T(heap[0], heap[heap.size() - 1]);
    balance_down(heap, 0, heap.size() - 1);
    cout << "after balancing down" << endl;
    copy(heap.begin(), heap.end(), ostream_iterator<node_value>(cout, " "));
    return heap[heap.size() - 1];
}

int shortest_distance_2(const vector<vector<pair<int, int>>>& graph, int end)
{
    int sz = graph.size();
    vector<int> weight(sz, 10000);
    vector<node_value> heap;
    vector<state> node_state(sz, state::UNVISITED);
    
    weight[0] = 0;
    //for (int i = 0; i < sz; ++i)
    int i = 0;
    while (1)
    {
        for (int j = 0; j < graph[i].size(); ++j)
        {
            if (node_state[graph[i][j].first] != state::VISITED)    
            {
                int sum = weight[i] + graph[i][j].second;
                if (sum < weight[graph[i][j].first])
                {
                    weight[graph[i][j].first] = sum;
                    node_value nv;
                    nv.node = graph[i][j].first;
                    nv.val = weight[graph[i][j].first];
                    add_to_heap(heap, nv);
                }
                node_state[graph[i][j].first] = state::VISITING;
            }
        }
        node_state[i] = state::VISITED;
        node_value exit = get_min_from_heap(heap);
        i = exit.node;
        if (!heap.empty())
        {
            heap.pop_back();
        }
        if (i == end)
        {
            break;
        }
        
        cout << "way " << exit;
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
    
    shortest_distance_2(graph, 4);

	return 0;
}
