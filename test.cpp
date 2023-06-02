//
// Created by shervitch on 2023/4/28.
//
#include "AVLTree.h"

void testAVLTree() {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);
    tree.insertIfNotPresent(25);
    tree.remove(40);
    tree.remove(900);
    tree.inorderTraversal(); // 10 20 25 30 50
    cout << endl;
    tree.preorderTraversal(); // 30 20 10 25 50
    cout << endl;
    tree.postorderTraversal(); // 10 25 20 50 30
    cout << endl;
}

int main() {
    testAVLTree();
}