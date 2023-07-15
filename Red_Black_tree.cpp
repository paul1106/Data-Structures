#include<iostream>

using std::cout;
using std::endl;
using std::string;

class RBT;
class TreeNode{
    friend class RBT;
    public:
        TreeNode():leftchild(0), rightchild(0), parent(0), key(0), color(0), element(""){};
        TreeNode(int key, string element):leftchild(0), rightchild(0), parent(0), key(key), color(0), element(element){};
    private:
        TreeNode *leftchild;
        TreeNode *rightchild;
        TreeNode *parent;
        string element;
        int key;
        int color; // Red = 0, Black = 1. 
};

class RBT{
    public:
        void DeleteRBT(int key);
        void InsertRBT(int key, string element);
        TreeNode* Search(int key);
    private:
        TreeNode *root;
        TreeNode *neel; // NIL

        void LeftRotation(TreeNode *x);
        void RightRotation(TreeNode *x);
        void InsertFixedUpRBT(TreeNode *current);
        void DeleteFixedUpRBT(TreeNode *current);
        TreeNode *Successor(TreeNode *current);
        TreeNode *LeftMost(TreeNode *current);

};


// Let the RightChild of node x(= y) to replace node x, then let node x to be the Leftchild of y.
void RBT::LeftRotation(TreeNode *x){
    TreeNode *y = x->rightchild; // 用來取代 x 的 node

    // Step 1 :先把 y 的 leftchild 連接給 x (因為 x 也要成為 y 的 leftchild)
    // (y 原本的 leftchild 會變成 x 的 rightchild，因為 y.key > x.key)
    x->rightchild = y->leftchild;
    if(y->leftchild != neel){
        y->leftchild->parent = x;
    }
    // Step 2 : 把 y 的 parent 從 x 改成 x->parent
    y->parent = x->parent;

    // Step 3 : 把新的 y->parent 接回 y
    // Case 1 : x 是 root
    if(x->parent == NULL){
        root = y;
    }
    // Case 2 : x 是 leftchild
    else if(x->parent->leftchild == x){
        x->parent->leftchild = y;
    }
    // Case 3 : x 是 rightchild
    else{
        x->parent->rightchild = y;
    }

    // Step 3 : 把 y 跟 x 重新接起來
    y->leftchild = x;
    x->parent = y;

}

void RBT::RightRotation(TreeNode *y){
    TreeNode *x = y->leftchild;

    y->leftchild = x->rightchild;
    if(x->rightchild != neel){
        x->rightchild->parent = y;
    }

    x->parent = y->parent;
     
    if(y->parent == neel){
        root = y;
    }
    else if(y->parent->leftchild == y){
        y->parent->leftchild = x;
    }
    else{
        y->parent->rightchild = x;
    }

    x->rightchild = y;
    y->parent = x;

}

void RBT::InsertRBT(int key, string element){
    TreeNode *new_node = new TreeNode(key, element);
    TreeNode *x = root;
    TreeNode *y = NULL;

    while(x != neel){
        y = x;

        if(key > x->key){
            x = x->rightchild;
        }
        else{
            x = x->leftchild;
        }
    }
    new_node->parent = y;

    if(y == NULL){
        root = x;
    }
    else if(key > y->key){
        y->rightchild = x;
    }
    else{
        y->leftchild = x;
    }

    // 以下是對 RBT 的 node 具有的性質作設定
    new_node->leftchild = neel;
    new_node->rightchild = neel;
    new_node->color = 0; // 預設顏色 : red (=0)

    // 對可能出現的顏色問題做修正
    InsertFixedUpRBT(new_node);
}

void RBT::InsertFixedUpRBT(TreeNode *current){

    // Case 0 : Praent's color is black, which means does not need to Fixed up.
    while(current->parent->color != 1){
        // Consider whether the parent is the left or right child of grandparent.

        // Parent is leftchild of grandparent.
        if(current->parent->parent->leftchild == current->parent){
            TreeNode *uncle = current->parent->parent->rightchild;

            // Case 1 : Uncle's color is red.
            if(uncle->color == 0){
                // Change the color of uncle & parent to black.
                uncle->color = 1;
                current->parent->color = 1;
                // Change the color of grandparent to red.
                current->parent->parent->color = 0;
                // Move the current ptr to grandparent.
                current = current->parent->parent;
            }
            // Case 2 & 3 : Uncle's color is black.
            else{
                // Case 2 : Current is the rightchild of parent.
                if(current == current->parent->rightchild){
                    LeftRotation(current->parent); // Change into Case 3.
                }
                // Case 3 :
                current->color = 1;            // Change the current's color into Black.
                current->parent->color = 0;    // Change the parent's color into red.
                RightRotation(current->parent); // Replace the parent with current.
                current = current->parent;
            }
        }
        // Parent is rightchild of grandparent.
        else{
            TreeNode *uncle = current->parent->parent->leftchild;

            // Case 1 : Uncle's color is red.
            if(uncle->color == 0){
                // Change the color of uncle & parent to black.
                uncle->color = 1;
                current->parent->color = 1;
                // Change the color of grandparent to red.
                current->parent->parent->color = 0;
                // Move the current ptr to grandparent.
                current = current->parent->parent;
            }
            else{
                // Case 2 : Current is the leftchild of parent.
                if(current == current->parent->leftchild){
                    RightRotation(current->parent); // Change the case into Case 3.
                }
                // Case 3 : Current is the rightchild of parent.
                current->color = 1;
                current->parent->color = 0;
                LeftRotation(current->parent);
                current = current->parent;
            }

        }
    }
}

TreeNode* RBT::Search(int key){
    TreeNode *current = root;
    while(current != NULL && current->key != key){
        if(current->key > key){
            current = current->leftchild;
        }
        else{
            current = current->rightchild;
        }
    }

    if(current == NULL){
        cout << "The node does not exist in RBT." << endl;
        return NULL;
    }
    else{
        return current;
    }
}

TreeNode* RBT::LeftMost(TreeNode *current){
    while(current->leftchild != NULL){
        current = current->leftchild;
    }
    return current;
}

TreeNode* RBT::Successor(TreeNode *current){
    if(current->rightchild != NULL){
        return LeftMost(current);
    }
    TreeNode* successor = current->parent;
    while(successor != NULL && successor->rightchild == current){
        current = successor;
        successor = successor->parent;
    }
    return current;
}

void RBT::DeleteRBT(int key){
    TreeNode *delete_node = Search(key);

    if(delete_node == NULL){
        cout << "This node does not exist." << endl;
    }

    TreeNode *y = nullptr;
    TreeNode *x = nullptr;

    if(delete_node->leftchild == neel || delete_node->leftchild == neel){
        y = delete_node;
    }
    else{
        y = Successor(delete_node);
    }

    if(y->leftchild != neel){
        x = y->leftchild;
    }
    else if(y->rightchild != neel){
        x = y->rightchild;
    }

    
    x->parent = y->parent; // 即使 x 為 neel，也要把它接到有效的記憶體位置

    if(y->parent == neel){
        root = x;
    }
    else if(y->parent->leftchild == y){
        y->parent->leftchild = x;
    }
    else{
        y->parent->rightchild = x;
    }

    if(y != delete_node){ // 如果 y 並非一開始指定要刪除的資料，要把 y 的資料補在 delte_node 的位置，再刪除 node y.
        delete_node->key = y->key;
        delete_node->element = y->element;
    }

    if(y->color == 1){ // 如果要刪除的 node 的 color 為黑色，可能會需要修正。
        DeleteFixedUpRBT(x);
    }

}

void RBT::DeleteFixedUpRBT(TreeNode *current){
    // Case(I)  : If the current color is red.
    // Case(II) : If the current is root.
    while(current->color == 1 && current != root){
        // Condition 1 : current is the leftchild.
        if(current == current->parent->leftchild){
            TreeNode *sibling = current->parent->rightchild;
            // Case 1 : Sibling is red.
            if(sibling->color == 0){
                current->parent->color = 0;
                sibling->color = 1;
                LeftRotation(current->parent);
                sibling = current->parent->rightchild;
            }
            // Case 2 : Sibling's children are all black.
            if(sibling->leftchild->color == 1 && sibling->rightchild->color == 1){
                sibling->color = 0;
                current = current->parent;
            }

            // Case 3 & 4
            // Case 3 : Sibling's rightchild is black & leftchild is red.
            else{
                if(sibling->leftchild->color == 0){
                    sibling->leftchild->color = 1;
                    sibling->color = 0;
                    RightRotation(sibling);
                    sibling = current->parent->rightchild;
                }
                // Case 4 : Sibling's rightchild is red & leftchild is black.
                sibling->color = sibling->parent->color;
                sibling->parent->color = 1;
                sibling->rightchild->color = 1;
                LeftRotation(sibling->parent);
                current = root; // 將 current 移動到 root，因為 Case 4 解決完之後，一定會符合 BRT.
            }
        }
        // Condidiont 2 : current is rightchild.
        else{
            TreeNode *sibling = current->parent->leftchild;
            // Case 1 : Sibling's color is red.
            if(sibling->color == 0){
                current->parent->color = 0;
                sibling->color = 1;
                LeftRotation(current->parent);
                sibling = current->parent->leftchild;
            }
            // Case 2 : Sibling's children are all black.
            if(sibling->leftchild->color == 1 && sibling->rightchild->color == 1){
                sibling->color = 0;
                current = current->parent;
            }
            // Case 3 & 4
            // Case 3 : Sibling's leftchild is black & rightchild is red.
            else{
                if(sibling->leftchild->color == 1){
                    sibling->rightchild->color = 1;
                    sibling->color = 0;
                    LeftRotation(sibling);
                    sibling = current->parent->leftchild;
                }
                // Case 4 : Sibling's rightchild is red & leftchild is black.
                sibling->color = sibling->parent->color;
                sibling->parent->color = 1;
                sibling->leftchild->color = 1;
                RightRotation(sibling->parent);
                current = root;
            }

        }
    }   
    current->color = 1;
}

int main(){
    return 0;
}