// Priority_Queue 第一次實作
// 參考 http://alrightchiu.github.io/SecondRound/priority-queuebinary-heap.html#other
#include<iostream>
#include<vector>
using namespace std;

// 作為 Binary Heap 中的 Node
struct HeapNode{
    int key;
    int element;
    HeapNode():key(),element(){};
    HeapNode(int node, int key):element(node), key(key){};
};


class BinaryHeap {
    public:
        BinaryHeap() { heap.resize(1); }; // 因為 HeapNode 的存放位置預設為從 index 1 開始
        BinaryHeap(int n) {heap.resize(n + 1); }; // 存放位置為 1 ~ n ( index = 0 的位置會留空)
        bool IsHeapEmpty() { return (heap.size() == 0); };

        // Min-Priority Queue
        void MinHeapify(int node, int length);
        void BuildMinHeap(vector<pair<int, int> > &arr);
        void DecreaseKey(int node, int newKey);
        void MinHeapInsert(int node, int key);
        int Minimum();
        int ExtractMin();
        void PrintHeap();

    private:
        vector<HeapNode> heap; // 存放 HeapNode 的陣列
        void swap(HeapNode &N1, HeapNode &N2);
        int FindPosition(int node);
        int GetParentNode(int node) { return (node / 2); };
        
};

// 把 parent, leftchild, rightchild 按照 MinHeap 的規則做調整
void BinaryHeap::MinHeapify(int node, int length) {
    int left = node * 2; // leftchild
    int right = node * 2 + 1; // rightchild
    int smallest = 0; // 用來記錄最小的 node

    // Condition 1 : leftchild < parant
    // Condition 2 : rightchild < parent
    // Condition 3 : bothchild < parent
    if (left <= length && heap[left].key < heap[node].key)smallest = left;
    else smallest = node;
    if (right <= length && heap[right].key < heap[smallest].key)smallest = right;

    if (node != smallest){
        swap(heap[node], heap[smallest]); // 將最小的換到 parent
        MinHeapify(smallest, length); // 因為 HeapNode 有變動，所以它以下的子樹也要調整，直到最底層
    }
        
}

// 建置整顆完整的 MinHeap
void BinaryHeap::BuildMinHeap(vector<pair<int, int> > &arr){
    for(int i = 0; i < arr.size(); i++){
        heap[i+1].key = arr[i].first;
        heap[i+1].element = arr[i].second;
    }
    // 從 heap[n/2] 到 heap[1] 做 MinHeapify ( n = heap_size )
    // 確保有子樹的 HeapNode 都符合 MinHeap 的規則
    for(int i = (int)(heap.size() / 2); i > 0; i--){
        MinHeapify(i, heap.size() - 1); // heap.size() - 1 是實際上的 length，因為 heap[0] is empty
    }
}


void BinaryHeap::swap(HeapNode &N1, HeapNode &N2){
    HeapNode tmp = N2;
    N2.key = N1.key;
    N2.element = N1.element;
    N1 = tmp;
}

// 找到最小值，也就是 MinHeap 的 root
int BinaryHeap::Minimum(){
    return heap[1].element;
}

int BinaryHeap::FindPosition(int node){
    int index = 0;
    for(int i = 1; i < heap.size(); i++){
        if(heap[i].element == node){
            index = i;
        }
    }

    return index;
}

// Return the element whose key is the smallest and then delete it.
int BinaryHeap::ExtractMin(){

    if(IsHeapEmpty()){
        cout << "error : Heap is empty." << endl;
        exit(-1);
    }
    int min = heap[1].element; // the root of the MinHeap has the smallest key.

    // Fill the root with the last element in MinHeap and delete the last element.
    heap[1] = heap[heap.size() - 1];
    heap.erase(heap.begin() + heap.size() - 1);
    // Heapify the Vector again, because the HeapNode have changed.
    // cout << heap.size() << endl;
    MinHeapify(1, heap.size() - 1);

    return min;
}

// Changing the key of element. (if the new key is smaller tham the original one).
// Check whether the new key follow the rule od MinHeap.
void BinaryHeap::DecreaseKey(int node, int newKey){
    int node_idx = FindPosition(node); // Find the index of the node.

    // Check whether the new key is smaller than the original one.
    if(heap[node_idx].key < newKey){
        cout << "The newKey is larger than the original key.";
        return;
    }

    heap[node_idx].key = newKey;
    // Check whether the new key and its parent follow the rule od MinHeap.
    int parent_idx = GetParentNode(node_idx);
    while(node_idx > 1 && heap[parent_idx].key > heap[node_idx].key){
        swap(heap[parent_idx], heap[node_idx]);
        node_idx = parent_idx;
        parent_idx = GetParentNode(node_idx);
    }
    
}

// Insert a new node into the MinHeap
void BinaryHeap::MinHeapInsert(int node, int key){
    heap.push_back(HeapNode(node, key)); // insert the new node to the heap.
    DecreaseKey(node, key); // MinHeapify the heap after a new node is inserted.
}

// Print the Heap
void BinaryHeap::PrintHeap(){
    for(int i = 0; i < heap.size(); i++){
        cout << heap[i].key << " " << heap[i].element << endl;
    }
}



int main(){
    vector<pair<int, int> > arr = { 
        make_pair(2, 40),
        make_pair(5, 50),
        make_pair(3, 60),
        make_pair(6, 70),
        make_pair(4, 80),
        make_pair(10, 100)
    };

    BinaryHeap BH(6);
    BH.BuildMinHeap(arr);
    BH.PrintHeap();
    cout << BH.Minimum() << endl; // 40
    BH.DecreaseKey(100, -1);
    cout << BH.ExtractMin() << endl; // 100
    cout << BH.Minimum() << endl;  // 40
    BH.MinHeapInsert(90, -2); 
    cout << BH.Minimum() << endl; // 90
   
    
    return 0;
}



