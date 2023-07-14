#include "TreeSet.h"
#include <iostream>
#include "../helper/Helper.h"
using namespace std;

int TreeSet::size()
{
	return treeSize;
}

void TreeSet::clear()
{
	treeSize = 0;
	root = NULL;
}

bool TreeSet::add(string value)
{
	int size1 = treeSize;
	root = addNode(root, value);
	if (treeSize>size1)
	{
		return true;
	}
	return false;
}

TreeSet::Node* TreeSet::addNode(Node* subtree, string value)
{
	if (subtree == NULL)
	{
		treeSize = treeSize + 1;
		return new Node(value);
	}

	if (subtree->value < value)
	{
		subtree->right = addNode(subtree->right, value);
	}

	if (subtree->value > value)
	{
		subtree->left = addNode(subtree->left, value);
	}
	return subtree;
}

bool TreeSet::isEmpty()
{
	if (treeSize == 0)
	{
		return true;
	}
	return false;
}

vector<string>* TreeSet::toVector()
{
	vector<string>* fill = new vector<string>();
	fillVector(fill,root);
	return fill;
}

void TreeSet::fillVector(vector<string>* fillMe, Node* subtree)
{
	if(subtree == NULL)
	{
		return ;
	}
	fillVector(fillMe, subtree->left);
	fillMe->push_back(subtree->value);
	fillVector(fillMe,subtree-> right);
}

bool TreeSet::contains(string value)
{

	return containsHelper(root,value);
}

bool TreeSet::containsHelper(TreeSet::Node* subtree, string value)
{
	if(subtree == NULL)
	{
		return false;
	}
	else if(subtree->value == value)
	{
		return true;
	}
	else if(subtree->value > value)
	{
		return containsHelper(subtree->left, value);
	}
	else
	{
		return containsHelper(subtree->right, value);
	}
}

bool TreeSet::remove(string value)
{
	int size1 = treeSize;
	removeHelper(root,value);
	if (treeSize < size1)
	{
		return true;
	}
	return false;
}

TreeSet::Node* TreeSet::removeHelper(Node* subtree, string value)
{
	if (subtree == NULL)
	{
		return NULL;
	}
	if (subtree->value > value)
	{
		subtree->left = removeHelper(subtree->left, value);
	}

	else if (subtree->value < value)
	{
		subtree->right = removeHelper(subtree->right, value);
	}

	else
	{
		if (subtree->left == NULL)
		{
			Node* delete1 = subtree->right;
			treeSize = treeSize - 1;
			return delete1;
		}

		else if (subtree->right == NULL)
		{
			Node* delete1 = subtree->left;
			treeSize = treeSize - 1;
			return delete1;
		}
		string temporary = findSmallest(subtree->right);
		subtree->value = temporary;
		subtree->right = removeHelper(subtree->right, temporary);
	}
	return subtree;
}

string TreeSet::findSmallest(TreeSet::Node* subtree)
{
	Node* curr = subtree;
	if(treeSize == 1)
	{
		return root->value;
	}
	else
	{
		while(curr->left != NULL)
		{
			curr = curr->left;
		}
		return curr->value;
	}
}

int TreeSet::height(Node* subtree)
{
	if (subtree == NULL)
	{
		return 0;
	}
	int left = 1 + height(subtree->left);
	int right = 1 + height(subtree->right);
	if (left > right)
	{
		return left;
	}
	return right;
}

void TreeSet::printStructure()
{
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
	{
		printGivenLevel(root, i);
		printf("\n");
	}
}

void TreeSet::printGivenLevel(Node* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
		cout << root->value << " -- ";
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}
