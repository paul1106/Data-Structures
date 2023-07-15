#include<iostream>
#include<list>
#include<queue>
#include<vector>


using std::cout;
using std::endl;


class Graph{
    public:
        Graph():vertex_num(0){};
        Graph(int N):vertex_num(N){ AdjList.resize(vertex_num); };
        
        void AddEdgeList(int from, int to);
        void BFS(int strart);

        void PrintPred(){
            for(int i = 0; i < vertex_num; i++){
                cout << i << " ";
            }
            cout << endl;
            for(int i = 0; i < vertex_num; i++){
                cout << predecessor[i] << " ";
            }
            cout << endl;
        }

        void PrintDis(){
            for(int i = 0; i < vertex_num; i++){
                cout << distance[i] << " ";
            }
            cout << endl;
            for(int i = 0; i < vertex_num; i++){
                cout << color[i] << " ";
            }
            cout << endl;

        }

    private:
        int vertex_num;
        int *distance; // distance = 0 代表為起點vertex, distance 為無限代表從起點到不了
        int *color; // 0 : 白色(還未走過), 1 : 灰色(走過), 2 : 黑色(走過且被用來當過起點了)
        int *predecessor; // -1 : 代表為起點vertex (沒有 Predecessor)  

        // Adjecent list
        std::vector<std::list<int> > AdjList;      

};


void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
}

void Graph::BFS(int start){
    distance = new int[vertex_num];
    color = new int[vertex_num];
    predecessor = new int[vertex_num];

    for(int i = 0;i < vertex_num; i++){
        distance[i] = INT_MAX;
        predecessor[i] = -1;
        color[i] = 0; // 所有 vertex 預設為白色
    }

    std::queue<int> que_bfs;
    int i = start;

    for(int j = 0; j < vertex_num; j++){
        if(color[i] == 0){
            color[i] = 1;
            distance[i] = 0;
            que_bfs.push(i);
            while(que_bfs.empty() != 1){
                int s = que_bfs.front(); // 將 Queue 的第一個元素作為每一次的起點 vertex
                for(std::list<int>::iterator itr = AdjList[s].begin(); itr != AdjList[s].end(); itr++){ // Scan 與起點相連的所有 vertex
                    if(color[*itr] == 0){ // 如果是白色，代表還沒被艘搜過
                        distance[*itr] = distance[s] + 1; // 距離為 predecessor的距離 + 1
                        color[*itr] = 1; // 將搜過的 vertex 設為灰色
                        predecessor[*itr] = s; // 並把他的前一個設為現在的起點 (current)
                        que_bfs.push(*itr); // 丟到 queue 裡面，等等拿來作為起點 vertex
                    }

                }
                color[s] = 2; // 將做過起點的 vertex 設為黑色
                que_bfs.pop(); // 確定周邊的 vertex 都被搜過後，就可以把它丟出 queue
            }
            i = j;
        }
    }
}
 

int main(){
     Graph g1(9);    
    // 建立出圖二(a)的Adjacency List
    g1.AddEdgeList(0, 1);g1.AddEdgeList(0, 2);g1.AddEdgeList(0, 3);
    g1.AddEdgeList(1, 0);g1.AddEdgeList(1, 4);
    g1.AddEdgeList(2, 0);g1.AddEdgeList(2, 4);g1.AddEdgeList(2, 5);g1.AddEdgeList(2, 6);g1.AddEdgeList(2, 7);
    g1.AddEdgeList(3, 0);g1.AddEdgeList(3, 7);
    g1.AddEdgeList(4, 1);g1.AddEdgeList(4, 2);g1.AddEdgeList(4, 5);
    g1.AddEdgeList(5, 2);g1.AddEdgeList(5, 4);g1.AddEdgeList(5, 8);
    g1.AddEdgeList(6, 2);g1.AddEdgeList(6, 7);g1.AddEdgeList(6, 8);
    g1.AddEdgeList(7, 2);g1.AddEdgeList(7, 3);g1.AddEdgeList(7, 6);
    g1.AddEdgeList(8, 5);g1.AddEdgeList(8, 6);

    g1.BFS(0); 
    g1.PrintPred();
    g1.PrintDis();
    return 0;
}