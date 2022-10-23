#include<iostream>
#include<sstream>
#include<queue>
using namespace std;

// 本樹的 BinaryTree 中實作是先用來處理給定的字串，讓它能依照 Complete BinaryTree 的順序建立, 插入跟印出
// 2022.12.23
class BinaryTree; // 需要先宣告，因為 TreeNode 的宣告會使用到
class TreeNode{
    friend class BinaryTree;
    public:
        // Constructer
        TreeNode ():leftchild (0), rightchild (0), parent (0){};
        TreeNode (char data): leftchild (0), rightchild (0), parent (0),data (data){};
    
    private:
        TreeNode *leftchild;
        TreeNode *rightchild;
        TreeNode *parent; // 連接 CurrentNode 的 parent
        char data;

};

class BinaryTree{
    public:
        // Constructer
        BinaryTree():root(0){};
        BinaryTree(const char *str);
        void LevelorderConstructer (stringstream &ss);

        // Insert
        void LevelorderInsert (char data);

        // Find some node
        TreeNode* getRoot () { return this->root; };
        TreeNode* leftmost (TreeNode *current);  
        TreeNode* rightmost (TreeNode *current);
        TreeNode* InorderSuccessor (TreeNode *current);
        TreeNode* InorderPredecessor (TreeNode *current);

        // Traversal
        void Preorder (TreeNode *current);
        void Inorder (TreeNode *current);
        void Postorder (TreeNode *current);
        void Levelorder ();
        void Inorder_by_parent (); // 進化版的 Inorder Treaversal
        void Inorder_Reverse (TreeNode *root); // 進化版的 Inorder Traversal 的順序相反版本 (右 -> 中 -> 左)

    private:
        TreeNode *root; // 以 root 作為 BinaryTree 的起始點
};



// Contructor
BinaryTree::BinaryTree (const char *str) {
    stringstream ss;
    ss.str("");
    ss.clear();

    ss << str; 
    root = new TreeNode; // allocate memory for root
    ss >> root->data; // 將 str 中第一個字母作為根的 data
    LevelorderConstructer(ss);
}

// 利用 Queue 實作，按照 Level-order 來對給定的字串建立 BinaryTree
void BinaryTree::LevelorderConstructer (stringstream &ss) {
    queue<TreeNode *> que;
    TreeNode *current = root;
    char data;

    while (ss >> data) {  // 當 ss 還有資料傳送給 data -> 重複執行
        if (data >= 'A' && data <= 'Z') { // 確認 data 是大寫字母，如果不是會直接跳過，代表 current node 會沒有 leftchild
            TreeNode *new_node = new TreeNode(data);
            current->leftchild = new_node;
            new_node->parent = current;
            que.push(new_node);
        }

        // 確認 ss 裡面是否還有資料
        if ( !(ss >> data)) { 
            break;
        }

        if (data >= 'A' && data <= 'Z' ) { // 確認 data 是大寫字母，如果不是會直接跳過，代表 current node 會沒有 rightchild
            TreeNode *new_node = new TreeNode(data);
            current->rightchild = new_node;
            new_node->parent = current;
            que.push(new_node);
        }

        current = que.front();
        que.pop();
    }

}



// VLR (visit -> leftchild -> rightchild).
void BinaryTree::Preorder (TreeNode *current) {
    if (current != 0) {
        cout << current->data << " "; // visit
        Preorder (current->leftchild); 
        Preorder (current->rightchild);
    }
}

// LVR
void BinaryTree::Inorder (TreeNode *current) {
    if (current != 0) {
        Inorder (current->leftchild);
        cout << current->data << " ";
        Inorder (current->rightchild);
    }
}

// LRV
void BinaryTree::Postorder (TreeNode *current) {
    if (current != 0) {
        Postorder (current->leftchild);
        Postorder (current->rightchild);
        cout << current->data << " ";
    }
} 

// Visit the BinaryTree from Level 1 to the Final level
void BinaryTree::Levelorder () {
    queue<TreeNode*> que;
    que.push (this->root);

    while (que.empty() != 1) { // Traversal 直到 queue 空了
        TreeNode *current = que.front();
        que.pop();
        cout << current->data << " ";

        // 將 Current Node 的 Subtree 先左再右丟入 queue
        if (current->leftchild != NULL) {
            que.push (current->leftchild); 
        }
        if (current->rightchild != NULL) {
            que.push (current->rightchild);
        }
    }
}

// Find current node 的 Subtree 中，最左邊的 node
TreeNode* BinaryTree::leftmost (TreeNode *current) {
    while (current->leftchild != NULL) {
        current = current->leftchild;
    }

    return current;
}

// Find current node 的 Subtree 中，最右邊的 node
TreeNode* BinaryTree::rightmost (TreeNode *current) {
    while (current->rightchild != NULL) {
        current = current->rightchild;
    }
    return current;
}

// 按照 Inorder 的規則找到下一個 node
TreeNode* BinaryTree::InorderSuccessor (TreeNode *current) {
    // Situation 1 : current node 的 rightchild 非 NULL
    if (current->rightchild != NULL) {
        return  leftmost (current->rightchild);
    }

    // situation 2 : current node 的 rightchild 為 NULL
    TreeNode *Successor = current->parent;
    while (Successor != NULL && Successor->leftchild != current) { // 確認 current 是否為 root
        current = Successor;
        Successor = Successor->parent;
    }
    return Successor;
}

void BinaryTree::Inorder_by_parent () {
    TreeNode *current = leftmost(root); // 先讓 current 移動到樹的最左邊

    // 利用 InorderSuccessor 找到下一個 node 來尋訪整棵樹
    while (current != NULL) {
        cout << current->data << " ";
        current = InorderSuccessor(current);
    }
}

TreeNode* BinaryTree::InorderPredecessor (TreeNode *current) {
    // 因為排序是 右 -> 中 -> 左，所以 Current 的右邊一定執行過了
    // 只需要查看下一個順序，也就是“左邊” 是否有 node
    // Situation 1 : current node 的 left node 為 NULL
    if (current->leftchild != NULL) {
        // 找到以 current->leftchild 為 root 的 subtree 中，最右邊的 node
        return rightmost(current->leftchild);
    }
    // Situation 2 : current node 的 left child 為 NULL 
    TreeNode* Predecessor = current->parent;
    // 當 Predecessor->leftchild == current 代表 Predecessor 一定比 current 先執行過
    while (Predecessor != 0 && Predecessor->leftchild == current) {
        current = Predecessor;
        Predecessor = Predecessor->parent;
    }
    return Predecessor;
}

void BinaryTree::Inorder_Reverse (TreeNode *root) {
    TreeNode* current = new TreeNode;
    current = rightmost(root);
    
    while (current != NULL) {
        cout << current->data << " ";
        current = InorderPredecessor(current);
    }
}

void BinaryTree::LevelorderInsert (char data) {
    TreeNode *current = root;
    queue<TreeNode *> que2;
    while (1) {
        if (current->leftchild != NULL) {
            que2.push(current->leftchild);
        }
        else {
            TreeNode *new_node = new TreeNode;
            current->leftchild = new_node;
            new_node->parent = current;
            new_node->data = data;
            return;
        }
        if (current->rightchild != NULL) {
            que2.push(current->rightchild);
        }
        else {
            TreeNode *new_node = new TreeNode;
            current->rightchild = new_node;
            new_node->parent = current;
            new_node->data = data;
            return;
        }
        current = que2.front();
        que2.pop();
    }
}

int main() {
    const char *a = "A B C D E F x x x G H x I";
    BinaryTree T(a);                // 以level-order規則建立Binary Tree
    T.Inorder_by_parent();          // 以inorder-traversal印出Binary Tree
    cout << endl;                   
    T.Levelorder();
    std::cout << std::endl;
    T.LevelorderInsert('K');
    cout << endl;
    T.LevelorderInsert('L');
    T.LevelorderInsert('M');
    T.LevelorderInsert('N');
    T.Levelorder();
    std::cout << std::endl;
    T.Inorder_by_parent();      // 以inorder-traversal印出Binary Tree
    std::cout << std::endl;


    return 0;
}

