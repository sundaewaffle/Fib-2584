#include <iostream>
#include <cfloat>

using namespace std;

class TreeSearch {
public:
	TreeSearch() {
		nowAt = nullptr;
	}
	~TreeSearch() {
		while (nowAt != nullptr) {
			del();
		}
	}
	
	void initRoot(double score) {
		nowAt = new node(score, 1, nullptr, nullptr, nullptr, nullptr);
	}
	void moveToParent() {
		if (nowAt->parent != nullptr) {
			//cout << "MP " << checkDepth() << " ";
			nowAt = (nowAt->parent);
			//cout << checkDepth() << endl;
		}
	}
	void moveToChild() {
		if (nowAt->child != nullptr) {
			//cout << "MC " << checkDepth() << " ";
			node* p = nowAt;
			nowAt = (nowAt->child);
			nowAt->parent = p;
			//cout << checkDepth() << endl;
			//fgetc(stdin);
		}
	}
	void moveToLSibling() {
		if (nowAt->Lsibling != nullptr) {
			node* p = nowAt;
			nowAt = (nowAt->Lsibling);
			nowAt->Rsibling = p;
		}
	}
	void moveToRSibling() {
		if (nowAt->Rsibling != nullptr) {
			node* p = nowAt;
			nowAt = (nowAt->Rsibling);
			nowAt->Lsibling = p;
		}
	}
	void backToRoot() {
		while (nowAt->parent != nullptr) {
			moveToParent();
		}
	}
	void addChild(double score) {
		if (nowAt->child != nullptr) {
			moveToChild();
			while (nowAt->Rsibling != nullptr) moveToRSibling();
			addSibling(score);
			//while (nowAt->Lsibling != nullptr) moveToLSibling();
			moveToParent();
			return;
		}
		node* p = new node(score, (checkDepth())+1, nowAt, nullptr, nullptr, nullptr);
		nowAt->child = p;
	}
	void addSibling(double score) {
		node* p = new node(score, nowAt->depth, nowAt->parent, nullptr, nowAt, nullptr);
		nowAt->Rsibling = p;
	}
	void del() {
		if (nowAt->child != nullptr) {
			moveToChild();
			del();
		}
		if (nowAt->Rsibling != nullptr) {
			moveToRSibling();
			del();
		}
		if (nowAt->Lsibling != nullptr) {
			moveToLSibling();
			node* p = nowAt->Rsibling;
			nowAt->Rsibling = nullptr;
			delete p;
		}
		else if (nowAt->parent != nullptr) {
			moveToParent();
			node* p = nowAt->child;
			nowAt->child = nullptr;
			delete p;
		}
		else {
			nowAt = nullptr;
		}
	}
	double nowScore() {
		return (nowAt->score);
	}
	bool noChild() {
		return (nowAt->child == nullptr);
	}
	bool noSibling() {
		return (nowAt->Rsibling == nullptr);
	}
	int checkDepth() {
		return nowAt->depth;
	}
	
	int searchAllMax();
	int searchAllMin();
	double minNode();
	double maxNode();
	
private:
	struct node {
		node(double s, int d, node* p, node* c, node* l, node* r) {
			score = s;
			depth = d;
			parent = p;
			child = c;
			Lsibling = l;
			Rsibling = r;
		}
		double score;
		int depth;
		node* parent;
		node* child;
		node* Lsibling;
		node* Rsibling;
	};
	node* nowAt;
};