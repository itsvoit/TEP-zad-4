//
// Created by voit on 10.10.2022.
//

#ifndef TEP_ZAD_3_CTREEDYNAMIC_H
#define TEP_ZAD_3_CTREEDYNAMIC_H

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class CNodeDynamic
{
public:
	CNodeDynamic() {
		i_val = 0;
		pc_parent_node = NULL;
	};
	~CNodeDynamic();
	void vSetValue(int iNewVal) {
		i_val = iNewVal;
	};
	int iGetChildrenNumber() {
		return(v_children.size());
	};
	void vAddNewChild();
	CNodeDynamic *pcGetChild(int iChildOffset);
	void vPrint() {
		std::cout << " " << i_val;
	};
	void vPrintAllBelow();
private:
	std::vector<CNodeDynamic *> v_children;
	CNodeDynamic *pc_parent_node;
	T i_val;

	template <typename T_COPY>
	friend class CTreeDynamic;
}; //class CNodeDynamic

template <typename T>
class CTreeDynamic
{
public:
	CTreeDynamic();
	~CTreeDynamic();
	CNodeDynamic<T> *pcGetRoot() {
		return(pc_root);
	}
	void vPrintTree();
	bool bMoveSubTree(CNodeDynamic<T> *pcParentNode, CNodeDynamic<T> *pcNewChildNode);
private:
	CNodeDynamic<T> *pc_root;
}; //class CTreeDynamic

// ---------------------------------
// Constructor and methods implementations

template<typename T>
CNodeDynamic<T>::~CNodeDynamic() {
	for (int i = 0; i < v_children.size(); ++i) {
		if (v_children[i] != NULL)
			delete v_children[i];
	}
	v_children.clear();
}

template<typename T>
void CNodeDynamic<T>::vAddNewChild() {
	CNodeDynamic<T> *pcNewNode = new CNodeDynamic<T>;
	pcNewNode->pc_parent_node = this;
	v_children.push_back(pcNewNode);
}

template<typename T>
CNodeDynamic<T> *CNodeDynamic<T>::pcGetChild(int iChildOffset) {
	if (iChildOffset < 0 || iChildOffset >= v_children.size())
		return NULL;

	return v_children[iChildOffset];
}

template<typename T>
void CNodeDynamic<T>::vPrintAllBelow() {
	vPrint();
	for (int i = 0; i < v_children.size(); ++i) {
		v_children[i]->vPrintAllBelow();
	}
}

template<typename T>
CTreeDynamic<T>::CTreeDynamic() {
	pc_root = new CNodeDynamic<T>;
}

template<typename T>
CTreeDynamic<T>::~CTreeDynamic() {
	if (pc_root != NULL)
		delete pc_root;
}

template<typename T>
void CTreeDynamic<T>::vPrintTree() {
	pc_root->vPrintAllBelow();
	std::cout << std::endl;
}

template<typename T>
bool CTreeDynamic<T>::bMoveSubTree(CNodeDynamic<T> *pcParentNode, CNodeDynamic<T> *pcNewChildNode) {
	if (pcParentNode == NULL || pcNewChildNode == NULL) return false;

	// add pcNewChildNode to the new tree
	pcParentNode->v_children.push_back(pcNewChildNode);

	// no parent to remove the newChildNode from
	if (pcNewChildNode->pc_parent_node == NULL) return true;

	// else -> remove child from previous parent
	// temp vector for erase-remove
	std::vector<CNodeDynamic<T>*> v_newChild_parent_children = pcNewChildNode->pc_parent_node->v_children;

	// remove pcNewChildNode from its parent
	v_newChild_parent_children.erase( std::remove(v_newChild_parent_children.begin(), v_newChild_parent_children.end(), pcNewChildNode), v_newChild_parent_children.end());

	return true;
}


#endif //TEP_ZAD_3_CTREEDYNAMIC_H
