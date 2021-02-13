#include "TreeSearch.h"

int TreeSearch::searchAllMax()
{
	backToRoot();
	int path, result;
	double r, temp;
	if (nowAt->child == nullptr) return -1;
	moveToChild();
	path = 0;
	result = 0;
	r = minNode();
	while (nowAt->Rsibling != nullptr) {
		moveToRSibling();
		path++;
		temp = minNode();
		if (temp > r) {
			r = temp;
			result = path;
		}
	}
	backToRoot();
	return result;
}

int TreeSearch::searchAllMin()
{
	backToRoot();
	int path, result;
	double r, temp;
	moveToChild();
	path = 0;
	result = 0;
	r = maxNode();
	while (nowAt->Rsibling != nullptr) {
		moveToRSibling();
		path++;
		temp = maxNode();
		if (temp < r) {
			r = temp;
			result = path;
		}
	}
	backToRoot();
	return result;
}

double TreeSearch::maxNode()
{
	if (nowAt->child == nullptr) {
		return nowAt->score;
	}
	moveToChild();
	double result, temp;
	result = minNode();
	while (nowAt->Rsibling != nullptr) {
		moveToRSibling();
		temp = minNode();
		if (temp > result) {
			result = temp;
		}
	}
	moveToParent();
	return result;
}

double TreeSearch::minNode()
{
	if (nowAt->child == nullptr) {
		return nowAt->score;
	}
	moveToChild();
	double result, temp;
	result = maxNode();
	while (nowAt->Rsibling != nullptr) {
		moveToRSibling();
		temp = maxNode();
		if (temp < result) {
			result = temp;
		}
	}
	moveToParent();
	return result;
}