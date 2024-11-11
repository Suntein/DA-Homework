#include <iostream>

/// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

/**
 * @brief 二叉搜索树模板类
 * 
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template <typename Comparable>
class BinarySearchTree {
public:
    /**
     * @brief 默认构造函数
     * 
     * 初始化一个空的二叉搜索树。
     */
    BinarySearchTree() : root{ nullptr } {}

    /**
     * @brief 拷贝构造函数
     * 
     * 创建一个新树，它是给定树的深拷贝。这里相比课本代码，引用更直接，有利于编译器优化。
     * 
     * @param rhs 要拷贝的二叉搜索树
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    /**
     * @brief 移动构造函数
     * 
     * 将给定树的资源转移到新树中。这里 noexcept 用于指示该函数不会抛出异常。
     * 因为移动构造不涉及内存分配，所以不会抛出异常。这里显式声明 noexcept 是为了提高性能。
     * 让编译器知道这个函数不会抛出异常，从而优化代码。
     * 
     * @param rhs 要移动的二叉搜索树
     */
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    /**
     * @brief 析构函数
     * 
     * 释放树中所有节点占用的内存。
     */
    ~BinarySearchTree() {
        makeEmpty();
    }

    /**
     * @brief 查找并返回树中的最小元素
     * 
     * 这是一个公有接口，它调用了私有的递归函数。
     * 
     * @return 最小元素的引用
     */
    const Comparable &findMin() const {
        if (isEmpty())
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    /**
     * @brief 查找并返回树中的最大元素
     * 
     * @return 最大元素的引用
     */
    const Comparable &findMax() const {
        if (isEmpty())
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    /**
     * @brief 检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    /**
     * @brief 检查树是否为空
     * 
     * @return 如果树为空，则返回 true；否则返回 false
     */
    bool isEmpty() const {
        return root == nullptr;
    }

    /**
     * @brief 打印树的结构
     * 
     * 将树的结构输出到指定的输出流，默认输出到标准输出流。
     * 
     * @param out 输出流，默认为 std::cout
     */
    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    /**
     * @brief 清空树中的所有元素
     * 
     * 释放树中所有节点占用的内存，使树变为空。
     */
    void makeEmpty() {
        makeEmpty(root);
    }

    /**
     * @brief 插入一个常量引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(const Comparable &x) {
        insert(x, root);
    }

    /**
     * @brief 插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     */
    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    /**
     * @brief 从树中移除指定的元素
     * 
     * @param x 要移除的元素
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

    void old_remove(const Comparable &x) {
        old_remove(x, root);
    }

    void old_old_remove(const Comparable &x) {
        old_old_remove(x, root);
    }
    /**
     * @brief 拷贝赋值运算符
     * 
     * 将一个树的资源拷贝到当前树中。对自赋值进行了排除。
     * 
     * @param rhs 要拷贝的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        if (this != &rhs) {
            BinarySearchTree temp(rhs);
            std::swap(root, temp.root);
        }
        return *this;
    }

    /**
     * @brief 移动赋值运算符
     * 
     * 将一个树的资源移动到当前树中。
     * 
     * @param rhs 要移动的二叉搜索树
     * @return 当前树的引用
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    /**
     * @brief 二叉树节点结构体
     */
    struct BinaryNode {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针
        int height;          ///< 子树高度

        /**
         * @brief 构造函数，接受常量引用
         * 
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, int h = 1)
            : element{ theElement }, left{ lt }, right{ rt }, height{ h } {}

        /**
         * @brief 构造函数，接受右值引用
         * 
         * @param theElement 要存储的元素
         * @param lt 左子节点指针
         * @param rt 右子节点指针
         */
        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt, int h = 1)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, height{ h } {}
    };

    BinaryNode *root;  ///< 树的根节点指针

    /**
     * @brief 递归查找最小元素
     * 
     * @param t 当前节点指针
     * @return 最小元素所在的节点指针
     */
    BinaryNode *findMin(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    /**
     * @brief 递归查找最大元素
     * 
     * @param t 当前节点指针
     * @return 最大元素所在的节点指针
     */
    BinaryNode *findMax(BinaryNode *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    int getHeight(BinaryNode *t) {
        return t == nullptr ? 0 : t->height;
    }

    void updateHeight(BinaryNode *t) {
        if (t != nullptr) {
            t->height = std::max(getHeight(t->left), getHeight(t->right)) + 1;
        }
    }

    // 四大旋转
    BinaryNode *rotateWithLeftChild(BinaryNode *k2) {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        updateHeight(k2);
        updateHeight(k1);
        return k1;
    }

    BinaryNode *rotateWithRightChild(BinaryNode *k2) {
        BinaryNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        updateHeight(k2);
        updateHeight(k1);
        return k1;
    }

    BinaryNode *doubleWithLeftChild(BinaryNode *k3) {
        k3->left = rotateWithRightChild(k3->left);
        return rotateWithLeftChild(k3);
    }

    BinaryNode *doubleWithRightChild(BinaryNode *k3) {
        k3->right = rotateWithLeftChild(k3->right);
        return rotateWithRightChild(k3);
    }

    /**
     * @brief 递归检查树中是否包含指定的元素
     * 
     * @param x 要查找的元素
     * @param t 当前节点指针
     * @return 如果树中包含该元素，则返回 true；否则返回 false
     */
    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } else if (x > t->element) {
            return contains(x, t->right);
        } else {
            return true;  // 找到元素
        }
    }

    /**
     * @brief 递归打印树的结构
     * 
     * @param t 当前节点指针
     * @param out 输出流
     */
    void printTree(BinaryNode *t, std::ostream &out) const {
        if (t != nullptr) {
            printTree(t->left, out);  // 先打印左子树
            out << t->element << std::endl;  // 打印当前节点
            printTree(t->right, out);  // 再打印右子树
        }
    }

    /**
     * @brief 递归清空树中的所有元素
     * 
     * @param t 当前节点指针
     */
    void makeEmpty(BinaryNode *&t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    /**
     * @brief 递归插入一个常量引用元素到树中
     * 
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }
    }

    /**
     * @brief 递归插入一个右值引用元素到树中
     * 
     * @param x 要插入的元素
     * @param t 当前节点指针
     */
    void insert(Comparable &&x, BinaryNode *&t) {
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        }
    }

    /**
     * @brief 递归从树中移除指定的元素
     * 
     * @param x 要移除的元素
     * @param t 当前节点指针
     */
    void old_remove(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) return;

        if (x < t->element) {
            old_remove(x, t->left);
        } else if (x > t->element) {
            old_remove(x, t->right);
        } else {
            if (t->left != nullptr && t->right != nullptr) {
                BinaryNode *minNode = detachMin(t->right);
                minNode->left = t->left;
                minNode->right = t->right;
                delete t;
                t = minNode;
            } else {
                BinaryNode *oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete oldNode;
            }
        }
    }

    void remove(const Comparable &x, BinaryNode *&t) {
        if (t == nullptr) 
			return;

        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        } else {
            if (t->left != nullptr && t->right != nullptr) {
                BinaryNode *min = detachMin(t->right);
                min->left = t->left;
                min->right = t->right; //删除这个节点
                t = min;
            } else {
                BinaryNode *old = t;
                if (t->left != nullptr) {
                    t = t->left;
                } else {
                    t = t->right;
                }
                delete old;
            }
        }
        updateHeight(t);
        if (t != nullptr) { 
            int balance = getHeight(t->left) - getHeight(t->right);
            if (balance > 1) {
                if (getHeight(t->left->left) >= getHeight(t->left->right)) {
                    t = rotateWithLeftChild(t);
                } else {
                    t = doubleWithLeftChild(t);
                }
            } else if (balance < -1) {
                if (getHeight(t->right->right) >= getHeight(t->right->left)) {
                    t = rotateWithRightChild(t);
                } else {
                    t = doubleWithRightChild(t);
                }
            }
        }
    }

    BinaryNode *detachMin(BinaryNode *&t) {
        if (t == nullptr) return nullptr;

        if (t->left == nullptr) {
            BinaryNode *minNode = t;
            t = t->right;
            return minNode;
        }

        return detachMin(t->left);
    }

    /**
     * @brief 递归克隆树的结构
     * 
     * @param t 当前节点指针
     * @return 新的节点指针
     */
    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
};
