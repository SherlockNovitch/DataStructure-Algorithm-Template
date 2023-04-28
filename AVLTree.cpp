//
// Created by shervitch on 2023/4/28.
//
#include<iostream>

using namespace std;

class AVLTreeNode {
private:
    int val;
    int height;
    AVLTreeNode *left, *right;
public:
    explicit AVLTreeNode(int val) {
        this->val = val;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }

    [[nodiscard]] int getVal() const {
        return val;
    }

    void setVal(int value) {
        this->val = value;
    }

    [[nodiscard]] int getHeight() const {
        return height;
    }

    void setHeight(int h) {
        this->height = h;
    }

    [[nodiscard]] AVLTreeNode *getLeft() const {
        return left;
    }

    void setLeft(AVLTreeNode *node) {
        this->left = node;
    }

    [[nodiscard]] AVLTreeNode *getRight() const {
        return right;
    }

    void setRight(AVLTreeNode *node) {
        this->right = node;
    }

};

class AVLTree {
private:
    AVLTreeNode *root;

protected:
    static AVLTreeNode *rotateLeft(AVLTreeNode *node) {
        AVLTreeNode *newRoot = node->getRight();
        node->setRight(newRoot->getLeft());
        newRoot->setLeft(node);
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    static AVLTreeNode *rotateRight(AVLTreeNode *node) {
        AVLTreeNode *newRoot = node->getLeft();
        node->setLeft(newRoot->getRight());
        newRoot->setRight(node);
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    static AVLTreeNode *rotateLeftRight(AVLTreeNode *node) {
        node->setLeft(rotateLeft(node->getLeft()));
        return rotateRight(node);
    }

    static AVLTreeNode *rotateRightLeft(AVLTreeNode *node) {
        node->setRight(rotateRight(node->getRight()));
        return rotateLeft(node);
    }

    static int getHeight(AVLTreeNode *node) {
        return node == nullptr ? 0 : node->getHeight();
    }

    static void updateHeight(AVLTreeNode *node) {
        node->setHeight(max(getHeight(node->getLeft()), getHeight(node->getRight())) + 1);
    }

    static int getBalanceFactor(AVLTreeNode *node) {
        return getHeight(node->getLeft()) - getHeight(node->getRight());
    }

    static AVLTreeNode *balance(AVLTreeNode *node) {
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor == 2)
            node = getBalanceFactor(node->getLeft()) < 0 ? rotateLeftRight(node) : rotateRight(node);
        else if (balanceFactor == -2)
            node = getBalanceFactor(node->getRight()) > 0 ? rotateRightLeft(node) : rotateLeft(node);
        return node;
    }

    static AVLTreeNode *insert(AVLTreeNode *node, int val) {
        if (node == nullptr) return new AVLTreeNode(val);
        if (val < node->getVal()) node->setLeft(insert(node->getLeft(), val));
        else node->setRight(insert(node->getRight(), val));
        updateHeight(node);
        return balance(node);
    }

    static AVLTreeNode *insertIfNotPresent(AVLTreeNode *node, int val) {
        if (node == nullptr) return new AVLTreeNode(val);
        if (val != node->getVal()) {
            if (val < node->getVal()) node->setLeft(insertIfNotPresent(node->getLeft(), val));
            else node->setRight(insertIfNotPresent(node->getRight(), val));
        }
        updateHeight(node);
        return balance(node);
    }

    static AVLTreeNode *findMin(AVLTreeNode *node) {
        return node->getLeft() == nullptr ? node : findMin(node->getLeft());
    }

    static AVLTreeNode *removeMin(AVLTreeNode *node) {
        if (node->getLeft() == nullptr) return node->getRight();
        node->setLeft(removeMin(node->getLeft()));
        updateHeight(node);
        return balance(node);
    }

    static AVLTreeNode *remove(AVLTreeNode *node, int val) {
        if (node == nullptr) return nullptr;
        if (val < node->getVal()) {
            node->setLeft(remove(node->getLeft(), val));
        } else if (val > node->getVal()) {
            node->setRight(remove(node->getRight(), val));
        } else {
            AVLTreeNode *left = node->getLeft(), *right = node->getRight();
            if (right == nullptr) return left;
            AVLTreeNode *minNode = findMin(right);
            minNode->setRight(removeMin(right));
            minNode->setLeft(left);
            updateHeight(minNode);
            return balance(minNode);
        }
        updateHeight(node);
        return balance(node);
    }

    static void inorderTraversal(AVLTreeNode *node) {
        if (node != nullptr) {
            inorderTraversal(node->getLeft());
            cout << node->getVal() << " ";
            inorderTraversal(node->getRight());
        }
    }

    static void preorderTraversal(AVLTreeNode *node) {
        if (node != nullptr) {
            cout << node->getVal() << " ";
            preorderTraversal(node->getLeft());
            preorderTraversal(node->getRight());
        }
    }

    static void postorderTraversal(AVLTreeNode *node) {
        if (node != nullptr) {
            postorderTraversal(node->getLeft());
            postorderTraversal(node->getRight());
            cout << node->getVal() << " ";
        }
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(int val) {
        this->root = insert(root, val);
    }

    void insertIfNotPresent(int val) {
        this->root = insertIfNotPresent(root, val);
    }

    void remove(int val) {
        this->root = remove(root, val);
    }

    void inorderTraversal() {
        inorderTraversal(this->root);
    }

    void preorderTraversal() {
        preorderTraversal(this->root);
    }

    void postorderTraversal() {
        postorderTraversal(this->root);
    }

};


void test() {
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
    test();
}