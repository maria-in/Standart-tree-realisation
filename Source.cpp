#include <iostream>
#include <fstream>
#include <exception>
using namespace std;


class Tree {
	class TreeNode {
	public:
		TreeNode(int v) {
			value = v;
			left = nullptr;
			right = nullptr;
		}
		int value;
		TreeNode* left;
		TreeNode* right;
	};

private:
	TreeNode* root;
	TreeNode* find(TreeNode* v, int value) {
		if (v->value == value) return v;
		if (v->value > value) {
			if (v->left == nullptr) return v; //возвращается указатель на предполагаемого родителя вершины, которую ищем
			return find(v->left, value);
		}
		if (v->right == nullptr) return v; //возвращается указатель на предполагаемого родителя вершины, которую ищем
		return find(v->right, value);
	}

	void insert(TreeNode* v, int value) { //указатель на вершину
		v = find(v, value);
		if (v->value == value) return;
		if (v->value < value) {
			v->right = new TreeNode(value);
		}
		else {
			v->left = new TreeNode(value);
		}
	}
	void traverse(TreeNode* v, ofstream& fout) {
		if (v == nullptr) return;
		fout << v->value << endl; //стрелки используются для доступа к членам структуры, объявленной через указатель //что-то наподобие метода (.)
		traverse(v->left, fout);
		traverse(v->right, fout);
	}

	void deleteNode(TreeNode* pred, TreeNode* cand, int value) {
		if (cand->value != value)
		{
			if (value > cand->value && cand->right != nullptr)
				deleteNode(cand, cand->right, value);
			else if (value < cand->value && cand->left != nullptr)
				deleteNode(cand, cand->left, value);
			return;
		}


		if ((cand->left != nullptr) && (cand->right != nullptr)) {
			TreeNode* temp = cand->right;//left
			TreeNode* temp_pred = cand;
			while (temp->left/*right*/ != nullptr)
			{
				temp_pred = temp;
				temp = temp->left;//right
			}
			cand->value = temp->value;
			cand = temp;
			pred = temp_pred;
		}

		if ((cand->left == nullptr) && (cand->right == nullptr)) {
			if (pred != nullptr && pred->left == cand)
				pred->left = nullptr;
			else if (pred != nullptr && pred->right == cand)
				pred->right = nullptr;
			else //pred == nullptr
				root = nullptr;
			delete cand;
			return;
		}

		if ((cand->left == nullptr) || (cand->right == nullptr))
		{
			TreeNode* child = (cand->left == nullptr) ? cand->right : cand->left;
			if (pred != nullptr && pred->left == cand)
				pred->left = child;
			else if (pred != nullptr && pred->right == cand)
				pred->right = child;
			else
				root = child;
			delete cand;
		}
	}
public:
	Tree() {
		root = nullptr;
	}
	void insert(int value) {
		if (root == nullptr)
			root = new TreeNode(value);
		else
			insert(root, value);
	}

	bool find(int value) {
		if (root == nullptr) return false;
		TreeNode* val = find(root, value);
		return val->value == value;
	}

	void traverse(ofstream& fout) {
		traverse(root, fout);
	}

	void deleteNode(int value) {
		if (root == nullptr) return;
		deleteNode(nullptr, root, value);
	}
};

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	Tree tree;
	int n, sum = 0;
	int k;
	while (fin >> n) {
		tree.insert(n);
	}
	cout << "Insert k, that you want to delete: ";
	cin >> k;
	tree.deleteNode(k);
	tree.traverse(fout);
	system("pause");
	return 0;
}