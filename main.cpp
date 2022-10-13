//
// Created by voit on 13.10.2022.
//

#include "CTreeDynamic.h"
#include <iostream>

void v_tree_test(){
	CTreeDynamic<int> tree;
	CNodeDynamic<int> *root = new CNodeDynamic<int>;
	std::cout << "Created tree and root\n";
	root->vAddNewChild();
	root->vAddNewChild();
	std::cout << "Added 2 new children to root\n";
	root->vSetValue(0);
	std::cout << "Set root val\n";
	root->pcGetChild(0)->vSetValue(1);
	root->pcGetChild(1)->vSetValue(2);
	std::cout << "Set values for all nodes\n";
	root->vPrintAllBelow();
	std::cout << "\nPrinted root and below\n";
	tree.bMoveSubTree(tree.pcGetRoot(), root);
	std::cout << "Set root as the tree's child\n";
	tree.vPrintTree();
	tree.pcGetRoot()->vAddNewChild();
	tree.vPrintTree();
}

int main(){

	v_tree_test();

	return 0;
}