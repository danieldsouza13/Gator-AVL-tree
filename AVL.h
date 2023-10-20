#pragma once
#include <string>
using namespace std;

// Node structure to represent each student in the AVL tree
struct Node {
	string name;
	string ufid;
	int height = 0;
	Node* left;
	Node* right;
	Node() : name(""), ufid(""), left(nullptr), right(nullptr) {};
	Node(string name, string ufid, Node* left, Node* right);
};

// AVLTree class to represent the AVL tree and AVL Tree functions
class AVLTree {
private:
	Node* root = nullptr;
	int GetHeight(Node* node);
	int GetBalance(Node* node);
	Node* InsertHelper(Node* node, string name, string ufid);
	Node* RightRotate(Node* parent);
	Node* LeftRotate(Node* parent);
	void PrintInorderHelper(Node* node, bool& is_root);
	void PrintPreorderHelper(Node* node, bool& is_root);
	void PrintPostorderHelper(Node* node, bool& is_root);
	void SearchUFIDHelper(Node* node, string ufid);
	void SearchNAMEHelper(Node* node, string name,bool& is_name_found);
	Node* FindMinValueNode(Node* node);
	Node* RemoveUFIDHelper(Node* node, string ufid);
	Node* RemoveInorderHelper(Node* node, int& n);
	int CountNodes(Node* node);
	
public:
	AVLTree() {}
	void Insert(string name, string ufid);
	void PrintInorder();
	void PrintPreorder();
	void PrintPostorder();
	void PrintLevelCount();
	void SearchUFID(string ufid);
	void SearchNAME(string name);
	void RemoveUFID(string ufid);	
	void RemoveInorder(int n);
};