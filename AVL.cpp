
#include "AVL.h"
#include <iostream>
using namespace std;

// NODE FUNCTIONS

// paramaterized Constructor
Node::Node(string name, string ufid, Node* left, Node* right) {
    this->name = name;
    this->ufid = ufid;
    this->left = left;
    this->right = right;
}

// AVL TREE FUNCTIONS

// gets height of a node
int AVLTree::GetHeight(Node* node) {
    if (node == nullptr) {
        return 0; // height of a null node is 0
    }

    return 1 + max(GetHeight(node->left), GetHeight(node->right));
}

// gets the balance factor of a node
int AVLTree::GetBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }

    return GetHeight(node->left) - GetHeight(node->right);
}

// recursive helper function to insert a node with a name and ufid
Node* AVLTree::InsertHelper(Node* node, string name, string ufid) {
    // creates a node if the node is null
    if (node == nullptr) {
        cout << "successful" << endl;
        return new Node(name, ufid, nullptr, nullptr);
    }

    if (ufid < node->ufid) {
        node->left = InsertHelper(node->left, name, ufid);
    }

    else if (ufid > node->ufid) {
        node->right = InsertHelper(node->right, name, ufid);
    }

    else {
        cout << "unsuccessful" << endl; // ufid is not unique
        return node;
    }
    // updates the height of the current node
    node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));

    int balance = GetBalance(node);

    // left heavy
    if (balance > 1) {
        // left-left case (perform a right rotation)
        if (ufid < node->left->ufid) {
            return RightRotate(node);
        }
        // left-right case (perform a left rotation on the left child then perform a right roation)
        else {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }
    }

    // right heavy
    if (balance < -1) {
        // right-right case (perform a left rotation)
        if (ufid > node->right->ufid) {
            return LeftRotate(node);
        }
        // right-left case (perform a right rotation on the right child then perform a left roation)
        else {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }
    }
    // if the node is balanced, return the unchanged node
    return node;
}

// performs a left rotation on the given node
Node* AVLTree::LeftRotate(Node* parent)
{
    Node* right_child = parent->right;
    Node* left_child = right_child->left;

    right_child->left = parent;
    parent->right = left_child;

    parent->height = max(GetHeight(parent->left), GetHeight(parent->right)) + 1;
    right_child->height = max(GetHeight(right_child->left), GetHeight(right_child->right)) + 1;

    return right_child;
}


// performs a right rotation on the given node
Node* AVLTree::RightRotate(Node* parent)
{
    Node* left_child = parent->left;
    Node* right_child = left_child->right;

    left_child->right = parent;
    parent->left = right_child;

    parent->height = max(GetHeight(parent->left), GetHeight(parent->right)) + 1;
    left_child->height = max(GetHeight(left_child->left), GetHeight(left_child->right)) + 1;

    return left_child;
}

// public function that inserts a new student into the AVL tree
void AVLTree::Insert(string name, string ufid) {
    // calls the private insert helper function to insert and balance the tree
    root = InsertHelper(root, name, ufid);
}

// private recursive helper function to print inorder traversal of the tree
void AVLTree::PrintInorderHelper(Node* node, bool& is_root) {
    if (node == nullptr) {
        return;
    }
    PrintInorderHelper(node->left, is_root); // traverse left subtree
    if (is_root) {
        is_root = false;
    }
    else {
        cout << ", ";
    }
    cout << node->name; // print current node
    PrintInorderHelper(node->right, is_root); // traverse right subtree
}

// public function to print inorder traversal of the tree
void AVLTree::PrintInorder() {
    bool is_root = true;
    PrintInorderHelper(root, is_root);
    cout << endl;
}

// private recursive helper function to print preorder traversal of the tree
void AVLTree::PrintPreorderHelper(Node* node, bool& is_root) {
    if (node == nullptr) {
        return;
    }
    if (is_root) {
        is_root = false;
    }
    else {
        cout << ", ";
    }
    cout << node->name;
    PrintPreorderHelper(node->left, is_root);
    PrintPreorderHelper(node->right, is_root);
}

// public function to print preorder traversal of the tree
void AVLTree::PrintPreorder() {
    bool is_root = true;
    PrintPreorderHelper(root, is_root);
    cout << endl;
}

// private recursive function to print postorder traversal of the tree
void AVLTree::PrintPostorderHelper(Node* node, bool& is_root) {
    if (node == nullptr) {
        return; 
    }
    PrintPostorderHelper(node->left, is_root);
    PrintPostorderHelper(node->right, is_root);
    if (is_root) {
        is_root = false;
    }
    else {
        cout << ", ";
    }
    cout << node->name;
}

// private function to print Postorder traversal of the tree
void AVLTree::PrintPostorder() {
    bool is_root = true;
    PrintPostorderHelper(root, is_root);
    cout << endl;
}

// prints the current number of levels of the tree by using the height of the current root
void AVLTree::PrintLevelCount() {
    int levels = GetHeight(root);
    cout << levels << endl;
}

// private recursive function that searches through the tree for a student when given their ufid
void AVLTree::SearchUFIDHelper(Node* node, string ufid) { 
    if (node == nullptr) { // student doesn't exist
        cout << "unsuccessful" << endl;
        return;
    }
    else if (ufid < node->ufid) { // traverse the left subtree
        SearchUFIDHelper(node->left, ufid);
    }
    else if (ufid > node->ufid) { // traverse the right subtree
        SearchUFIDHelper(node->right, ufid);
    }
    else { // if the id was found, print out the student's name
        cout << node->name << endl;
    }
}

// public function that searches through the tree for a student when given a ufid
void AVLTree::SearchUFID(string ufid) {
    SearchUFIDHelper(root, ufid);
}


// private recursive function that searches through the tree for a student when given their name
void AVLTree::SearchNAMEHelper(Node* node, string name, bool& is_name_found) {
    if (node == nullptr) {
        return;
    }

    SearchNAMEHelper(node->left, name, is_name_found); // preorder traversal - left subtree first

    if (node->name == name) {
        cout << node->ufid << endl;
        is_name_found = true;
    }

    SearchNAMEHelper(node->right, name, is_name_found); // preorder traversal - right subtree next
}

void AVLTree::SearchNAME(string name) {
    bool is_name_found = false;
    SearchNAMEHelper(root, name, is_name_found);
    if (!is_name_found) {
        cout << "unsuccessful" << endl;
    }
}

// private function to find the node with the lowest value
Node* AVLTree::FindMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) { // lowest node value will be in the left subtree
        current = current->left;
    }
    return current;
}

// private recursive function to find and remove the student when given their ufid
Node* AVLTree::RemoveUFIDHelper(Node* node, string ufid) {
    if (node == nullptr) {
        cout << "unsuccessful" << endl; // if passed in node is a nullptr
        return node;
    }
    // if the ufid to be deleted is smaller, then it's in the left subtree
    if (ufid < node->ufid) {
        node->left = RemoveUFIDHelper(node->left, ufid);
    }
    // if the ufid to be deleted is larger, then it's in the right subtree
    else if (ufid > node->ufid) {
        node->right = RemoveUFIDHelper(node->right, ufid);
    }
    // if the ufid is same as node's ufid, then this is the node to be deleted
    else {
        // node with only one child or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            cout << "successful" << endl;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            cout << "successful" << endl;
            return temp;
        }

        // node with two children, get the inorder successor (smallest in the right subtree)
        Node* temp = FindMinValueNode(node->right);

        // copy the inorder successor's data to this node
        node->ufid = temp->ufid;
        node->name = temp->name;

        // delete the inorder successor
        node->right = RemoveUFIDHelper(node->right, temp->ufid);
    }

    // update the height and balance the node
    node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));

    int balance = GetBalance(node);

    // left heavy
    if (balance > 1) {
        if (GetBalance(node->left) >= 0) {
            return RightRotate(node);
        }
        else {
            node->left = LeftRotate(node->left);
            return RightRotate(node);
        }
    }

    // right heavy
    if (balance < -1) {
        if (GetBalance(node->right) <= 0) {
            return LeftRotate(node);
        }
        else {
            node->right = RightRotate(node->right);
            return LeftRotate(node);
        }
    }

    return node;
}

// public function to find and remove the student when given their ufid
void AVLTree::RemoveUFID(string ufid) {
    root = RemoveUFIDHelper(root, ufid);
}

// private recursive function to remove the nth ufid during an inorder traversal
Node* AVLTree::RemoveInorderHelper(Node* node, int& n) {
    if (node == nullptr) {
        return nullptr;
    }

    // traverse the left subtree
    node->left = RemoveInorderHelper(node->left, n);

    // if the Nth node is found, remove it
    if (n == 0) {
        n--;
        return RemoveUFIDHelper(node, node->ufid); // Use the RemoveUFIDHelper function to remove the node
    }

    // decrement the counter
    n--;

    // traverse the right subtree
    node->right = RemoveInorderHelper(node->right, n);

    return node;
}



int AVLTree::CountNodes(Node* node) { // counts number of nodes in AVL tree
    if (node == nullptr) {
        return 0;
    }
    return (1 + CountNodes(node->left) + CountNodes(node->right)); // root + number of nodes in left subtree + number of nodes in right subtree
}


// public function that the nth ufid from an inorder traversal of the current tree.
void AVLTree::RemoveInorder(int n) {
    int count = n;
    int num_nodes = CountNodes(root);
    if (count > num_nodes) {
        cout << "unsuccessful" << endl;
        return;
    }
    root = RemoveInorderHelper(root, count);

    if (count == n) {
        cout << "unsuccessful" << endl; // if the nth ufid is not found
    }
}