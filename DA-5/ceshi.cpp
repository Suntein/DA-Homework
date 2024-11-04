#include <iostream>
#include "BST.h"  

int main() {
    // 创建一个整数类型的二叉搜索树
    BinarySearchTree<int> bst;

    // 插入一些元素
    bst.insert(20);
    bst.insert(10);
    bst.insert(30);
    bst.insert(5);
    bst.insert(15);
    bst.insert(25);
    bst.insert(35);

    std::cout << "Initial tree (in-order traversal):" << std::endl;
    bst.printTree();

    // 删除叶子节点
    std::cout << "\nRemoving leaf node 5:" << std::endl;
    bst.remove(5);
    bst.printTree();

    // 删除有一个子节点的节点
    std::cout << "\nRemoving node with one child 30:" << std::endl;
    bst.remove(30);
    bst.printTree();

    // 删除有两个子节点的节点
    std::cout << "\nRemoving node with two children 10:" << std::endl;
    bst.remove(10);
    bst.printTree();

    // 尝试删除不存在的元素
    std::cout << "\nAttempting to remove non-existent element 100:" << std::endl;
    bst.remove(100);
    bst.printTree();

    // 清空树
    std::cout << "\nClearing the tree:" << std::endl;
    bst.makeEmpty();
    bst.printTree();

    return 0;
}
