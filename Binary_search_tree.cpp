#include<iostream>
#include<queue>

using std::cout;
using std::string;
using std::endl;

class BST;
class TreeNode{
    friend class BST;
    public:
        TreeNode():leftchild(0), rightchild(0), parent(0), Key(0), element(""){};
        TreeNode(int Key, string element):leftchild(0), rightchild(0), parent(0), Key(Key), element(element){};

        // 用來確認 TreeNode 是否正確
        int getKey(){return Key;}
        string getElement(){return element;}
    private:
        TreeNode *leftchild;
        TreeNode *rightchild;
        TreeNode *parent;
        string element; // 資料項目
        int Key; // 資料的比較權重
};

class BST{
    public:
        BST():root(0){};

        TreeNode* Search(int Key);
        void InsertBST(int Key, string element);
        void InorderPrint();
        void LevelorderPrint();
        void DeleteBST(int Key);
        void LeftRotation(TreeNode *current);
        void RightRotation(TreeNode *current);
    private:
        TreeNode *root;
        TreeNode* Leftmost(TreeNode *current);
        TreeNode* Successor(TreeNode *current);
    
};

TreeNode* BST::Search(int Key){
    TreeNode *current = root;

    // 終止條件 :
    // 1. 找到相對應的 TreeNode
    // 2. 到底部了，還是沒找到
    while(current != NULL && current->Key != Key){
        // Sitution 1 : 要找的 key 比 current.Key 大 -> 往 rightchild 移動
        // Sitution 2 : 要找的 key 比 current.Key 小 -> 往 leftchild 移動
        if(current->Key < Key) current = current->rightchild;
        else current = current->leftchild;
    }

    if(current == NULL){
        cout << "This element does not exist in BST." << endl;
        return 0;
    }
    return current;
}

void BST::InsertBST(int Key, string element){
    TreeNode *new_node = new TreeNode(Key, element);
    TreeNode *x = root; // x 為哨兵，用來找出 new_node 適當的插入位置
    TreeNode *y = NULL; // y 為準parent，用來在哨兵找到位置後，作為 new_node 的 parent
    
    // 先讓哨兵找到適合的準parent
    while(x != NULL){
        y = x;

        if(x->Key > Key){
            x = x->leftchild;
        }
        else{
            x = x->rightchild;
        }
    }
    new_node->parent = y;
    // If BST is empty, let new_node be the root of BST.
    // Otherwise, compare the new_node.key with its parent.key to determine which side new_node should be inserted.
    if(y == NULL){
        root = new_node;
    }
    else if(y->Key > Key){
        y->leftchild = new_node;
    }
    else{
        y->rightchild = new_node;
    }
}

TreeNode* BST::Leftmost(TreeNode *current){
    while(current->leftchild != NULL){
        current = current->leftchild;
    }
    return current;
}

TreeNode* BST::Successor(TreeNode *current){
    if(current->rightchild != NULL){
        return Leftmost(current->rightchild);
    }
    TreeNode *successor = current->parent;
    while(successor != NULL && successor->rightchild == current){
        current = successor;
        successor = successor->parent;
    }
    return successor;
}

void BST::InorderPrint(){
    TreeNode *current = Leftmost(root);
    while(current != NULL){
        cout << current->element << "(" << current->Key << ")" << " ";
        current = Successor(current);
    }
}

void BST::LevelorderPrint(){
    TreeNode *current = new TreeNode;
    std::queue<TreeNode*> que;
    que.push(root);
    while(que.empty() != 1){
        current = que.front();
        cout << current->element << "(" << current->Key << ")" << " ";
        que.pop();
        if(current->leftchild != NULL){
            que.push(current->leftchild);
        }
        if(current->rightchild != NULL){
            que.push(current->rightchild);
        }
    }
}

void BST::DeleteBST(int Key){
    TreeNode *delete_node = Search(Key);

    // if the node doesnt exist.
    if(delete_node == nullptr){
        cout << "This element does not exist." << endl;
        return;
    }
    
    TreeNode *y = 0; // The node which will be deleted.
    TreeNode *x = 0; // The child of the node which is going to be deleted.
    // Let the delete_node be the node who only has one child or none.
    if(delete_node->leftchild == NULL || delete_node->rightchild == NULL){
        y = delete_node;
    }
    else{
        // 利用 BST 的特性，具有兩個 child 的 TreeNode 的 Successor (or Predecessor) 都會是 leaf node 或是具有一個 child 的 node.
        y = Successor(delete_node);
    }

    if(y->leftchild != NULL){
        x = y->leftchild;
    }
    else if(y->rightchild != NULL){
        x = y->rightchild;
    }

    if(x != NULL){
        x->parent = y->parent;
    }

    // 將 child 跟新的 parent node 做連接
    // 當 y 是 root 的情況，直接把 x 作為新的 root
    if(y->parent == NULL){
        this->root = x;
    }
    else if(y == y->parent->leftchild){
        y->parent->leftchild = x;
    }
    else{
        y->parent->rightchild = x;
    }

    // 如果 y 是替身的話，也就是並非一開始指定要刪除的 node ， 要把代替被刪除的 node 的資料補回去
    if(y != delete_node){
        delete_node->Key = y->Key;
        delete_node->element = y->element;
    }
    
    // Delete the node.
    delete y;
    y = 0;
}

// Let the RightChild to replace the current node, and let current node to be the Leftchild of Rightchild of the current node.
void BST::LeftRotation(TreeNode *current){
    TreeNode *y = current->rightchild; // 用來取代 current 的 node

    // Step 1 :先把 y 的 leftchild 連接給 current (因為 current 也要成為 y 的 leftchild)
    //(y 原本的 leftchild 會變成 current 的 rightchild，因為 y.key > current.key)
    current->rightchild = y->leftchild;
    if(y->leftchild != neel){
        y->leftchild->parent = current;
    }

    y->parent = current->parent;

    if(current->parent == NULL){
        root = y;
    }
    else if(current->parent->leftchild == current){
        current->parent->leftchild = y;
    }
    else{
        current->parent->rightchild = y;
    }

    y->leftchild = current;
    current->parent = y;

}


int main(){

    BST T;

    T.InsertBST(8,"龜仙人");
    T.InsertBST(1000,"悟空");
    T.InsertBST(2,"克林");
    T.InsertBST(513,"比克");


    cout << "Inorder Traversal:\n";
    T.InorderPrint();
    cout << endl << endl;
    cout << "Level-order Traversal:\n";
    T.LevelorderPrint();
    cout << endl << endl;

    T.DeleteBST(8);         // 刪除龜仙人(8), 確認比克(513)會成為新的root

    cout << "Level-order Traversal:\n";
    T.LevelorderPrint();
    cout << endl << endl;

    TreeNode *node = T.Search(1000);
    if(node != NULL){
        cout << "There is " << node->getElement() << "(" << node->getKey() << ")" << endl;
    }
    else {
        cout << "no element with Key(1000)" << endl;
    }

    node = T.Search(8);
    if(node != NULL){
        cout << "There is " << node->getElement() << "(" << node->getKey() << ")" << endl;
    }
    else {
        cout << "no element with Key(8)" << endl;
    }

    return 0;
}