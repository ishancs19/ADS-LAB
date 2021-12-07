#include<iostream>
using namespace std;
class Node {
    public:
    int key;
    Node *left;
    Node *right;
    int height;
};

int max(int a, int b){
    return (a>b) ? a:b;
}

int height(Node *n) {
    if (n == NULL)
    return 0;
    return n->height;
}

Node *new_node(int key) {
    Node *node = new Node();
    node -> key = key;
    node -> left = NULL;
    node -> right = NULL;
    node -> height = 1;
    return(node);
}

Node *right_rotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
 
    return x;
}

Node *left_rotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;
 
    return y;
}

int get_balance(Node *n) {
    if (n == NULL) return 0;
    return (height(n->left) - height(n->right));
}

Node* insert(Node* node, int key)
{
    if (node == NULL)
        return(new_node(key));
 
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
 
    node->height = 1 + max(height(node->left),height(node->right));
 
    int balance = get_balance(node);
 
    //LL
    if (balance > 1 && key < node->left->key)
        return right_rotate(node);
 
    //RR
    if (balance < -1 && key > node->right->key)
        return left_rotate(node);
 
    //LR
    if (balance > 1 && key > node->left->key)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
 
    //RL
    if (balance < -1 && key < node->right->key)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
 
    return node;
}

Node *min_value_node(Node * node) {
    Node *current = node;
    
    while(current -> left != NULL)
    current = current -> left;
    
    return current;
}

Node *delete_node(Node * root, int key) {
    if (root == NULL)
    return root;
    
    if(key < root -> key)
    root ->left = delete_node(root->left, key);
    else if(key > root -> key)
    root -> right = delete_node(root->right, key);
    else {
        if(root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;
            
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else *root = *temp;
            
            free(temp);
        }
        else {
            Node *temp = min_value_node(root->right);
            
            root->key = temp->key;
            
            root->right = delete_node(root->right, temp->key);
        }
    }
    if(root == NULL)
    return root;
    
    root->height = 1+max(height(root->left), height(root->right));
    
    int balance = get_balance(root);
    
    if (balance > 1 && get_balance(root->left) >= 0)
    return right_rotate(root);
    
    if(balance > 1 && get_balance(root->left) < 0) {
        root -> left = left_rotate(root -> left);
        return right_rotate(root);
    }
    
    if (balance < -1 && get_balance(root->right) <= 0)
    return left_rotate(root);
    
    if(balance < -1 && get_balance(root->right) > 0) {
        root -> right = right_rotate(root -> right);
        return left_rotate(root);
    }
    return root;
}

void preOrder(Node *root) {
    if(root != NULL) {
        cout<<root->key<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node *root = NULL;
    root = insert(root,9);
    root = insert(root,5);
    root = insert(root,10);
    root = insert(root,0);
    root = insert(root,6);
    root = insert(root,11);
    root = insert(root,-1);
    root = insert(root,1);
    root = insert(root,2);
    
    cout<<"Pre Order traversal: \n";
    preOrder(root);
    
    root = delete_node(root, 10);
    
    cout<<"\nPre Order traversal after deletion of 10: \n";
    preOrder(root);
    
    return 0;
}
