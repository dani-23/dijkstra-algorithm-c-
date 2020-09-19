	
#include <iostream>
#include <fstream>
#include <vector>
#define DIM 50010
#define INF 100000000
 
using namespace std;
 
ifstream fin ("dijkstra.in");
ofstream fout ("dijkstra.out");
 
int nodes, connections, pos[DIM], D[DIM], nr_elem;
vector< pair<int,int> > list_of_adjacents[DIM];
int heap[DIM];
 
inline int father(int node_index){
    return node_index / 2;
}
 
inline int left_son(int node_index){
    return 2 * node_index;
}
 
inline int right_son(int node_index){
    return 2 * node_index + 1;
}
 
void up(int index){
    bool flag = true;
 
    while(flag){
        if(index == 1 || D[heap[index]] > D[heap[father(index)]]){
            flag = false;
        }
        else{
            swap(heap[index], heap[father(index)]);
            pos[heap[index]] = index;
            pos[heap[father(index)]] = father(index);
            index = father(index);
        }
    }
}
 
void down(int index){
 
    int son;
 
    do{
        son = 0;
 
        if(left_son(index) <= nr_elem){
            son = left_son(index);
 
            if(right_son(index) <= nr_elem && D[heap[right_son(index)]] < D[heap[left_son(index)]])
                son = right_son(index);
            if(D[heap[son]] > D[heap[index]])
                son = 0;
        }
 
        if(son){
            swap(heap[index], heap[son]);
            pos[heap[index]] = index;
            pos[heap[son]] = son;
            index = son;
        }
 
    }while(son);
 
}
 
 
void insert_element(int insert_elem){
    int index = nr_elem;
 
    heap[index] = insert_elem;
 
    up(index);
}
 
void delete_element(int delete_elem){
    heap[delete_elem] = heap[nr_elem--];
 
    int position = delete_elem;
 
    down(position);
}
 
int main()
{
    int Anode, Bnode, cost;
 
    fin >> nodes;
 
    fin >> connections;
 
    for(int i = 1; i <= connections; i++){
        fin >> Anode >> Bnode >> cost;
        list_of_adjacents[Anode].push_back(make_pair(Bnode, cost));
    }
 
    D[1] = 0;
    pos[1] = ++nr_elem;
    insert_element(1);
 
    for(int i = 2; i <= nodes; i++){
        D[i] = INF;
        pos[i] = ++nr_elem;
        insert_element(i);
    }
 
    for(int i = 1; i <= nodes; i++){
        int min_node = heap[1];
        delete_element(1);
 
        for(int j = 0; j < list_of_adjacents[min_node].size(); j++){
            int cost = list_of_adjacents[min_node][j].second;
            int current_node = list_of_adjacents[min_node][j].first;
            if(D[min_node] + cost < D[current_node]){
                D[current_node] = D[min_node] + cost;
                    up(pos[current_node]);
            }
        }
    }
 
    for(int i = 2; i <= nodes; i++){
        if(D[i] == INF)
            fout << "0 ";
        else
            fout << D[i] << " ";
    }
 
    return 0;
}