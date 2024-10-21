#ifndef __LIST_MARK__
#define __LIST_MARK__

#include <utility>
#include <initializer_list>
#include <stdexcept>  // 包含标准异常类的定义



template <typename Object>
class List
{
private:
   
    struct Node
    {
        Object data; /**<! 节点内存放的数据. */
        Node *prev;  /**<! 指向前一个节点的指针. */
        Node *next;  /**<! 指向后一个节点的指针. */
        
        Node(const Object &d = Object{}, Node *p = nullptr,
             Node *n = nullptr)
            : data{d}, prev{p}, next{n} {}

        
        Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
            : data{std::move(d)}, prev{p}, next{n} {}
    };

public:
   
    class const_iterator
    {
    public:
        
        const_iterator() : current{nullptr}
        {
        }

       
        const Object &operator*() const
        {
            return retrieve();
        }

        const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

  
        bool operator==(const const_iterator &rhs) const
        {
            return current == rhs.current;
        }

        
        bool operator!=(const const_iterator &rhs) const
        {
            /// 这里直接调用 == 运算，多了一次调用，但能确保一致性.
            return !(*this == rhs);
        }

    protected:
       

        Node *current; /**<! 当前节点的指针. */

        
        Object &retrieve() const
        {
            return current->data;
        }

        
        const_iterator(Node *p) : current{p}
        {
        }

        friend class List<Object>; /**<! 使 List 类可以访问到迭代器的私有成员和 protected 成员. */

        /// 注意到 const_iterator 并没有提供析构函数，因为它不需要也不应该释放内存.
    };

    
    class iterator : public const_iterator
    {
    public:
        /**
         * @brief 默认构造函数. 用于初始化迭代器. 为何这里不需要初始化 current 呢？
         * 因为它继承自 const_iterator，而 const_iterator 已经初始化了 current 为 nullptr.
         * 子类的构造函数会调用父类的构造函数，所以这里不需要再初始化 current 了.
         *
         */
        iterator()
        {
        }

        
        Object &operator*()
        {
            return const_iterator::retrieve();
        }

        const Object &operator*() const
        {
            return const_iterator::operator*();
        }

        
        iterator &operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        
        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }
        iterator operator--(){
            this->current=this->current->prev;
            return *this;
        }
        iterator operator--(int){
            iterator old= *this;
            --(*this);
            return old;
        }

    protected:
        /**
         * @brief 一个带参数的构造函数. 用于快速调整迭代器的位置.
         *
         * @param p 当前节点的新位置.
         */
        iterator(Node *p) : const_iterator{p}
        {
        }

        friend class List<Object>;  /**<! 同样使 List 类可以访问到迭代器的私有成员和 protected 成员. */
    };

public:
    
    List() { init( ); }

    
    List(std::initializer_list<Object> il) : List()
    {
        for (const auto & x : il)
            push_back(x);
    }

    List(const List &rhs)
    {
        /// 先初始化一个空的 List.
        init( );
        
        for (auto & x : rhs)
            /// 调用成员函数从后方（为何）插入到 List 中.
            push_back(x);
    }

    
    ~List()
    {
        clear( );
        delete head;
        delete tail;
    }

    
    List &operator=(List copy)
    {
   
        std::swap( theSize, copy.theSize );
        std::swap( head, copy.head );
        std::swap( tail, copy.tail );
        return *this;
    }

    
    List(List &&rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    
    
    iterator begin()
    {
        return { head->next };
    }

    
    const_iterator begin() const
    {
        return { head->next };
    }

   
    iterator end()
    {
        return { tail };
    }

    
    const_iterator end() const
    {
        return { tail };
    }

    int size() const
    {
        return theSize;
    }

    bool empty() const
    {
        return size() == 0;
    }

    /**
     * @brief 清空 List 中的数据.
     * 
     */
    void clear()
    {
        /// 这里其实用计数器来判断 List 是否为空.
        while (!empty())
            pop_front();
    }

   
    Object &front()
    {
        return *begin();
    }

    const Object &front() const
    {
        return *begin();
    }

   
    Object &back()
    {
        return *--end();
    }

    
    const Object &back() const
    {
        return *--end();
    }

   
    void push_front(const Object &x)
    {
        insert(begin(), x);
    }

   
    void push_front(Object &&x)
    {
        insert(begin(), std::move(x));
    }

    
    void push_back(const Object &x)
    {
        insert(end(), x);
    }

    
    void push_back(Object &&x)
    {
        insert(end(), std::move(x));
    }

    
    void pop_front()
    {
        erase(begin());
    }

    /** 
     * @brief 删除 List 的最后一个数据节点.
     * 
     */
    void pop_back()
    {
        erase(--end());
    }

   
    iterator insert(iterator itr, const Object &x)
    {
        Node *p = itr.current;
        theSize++;
        if (p == head) {  
            Node* newNode = new Node(x, head, head->next);  
            head->next->prev = newNode;  
            head->next = newNode;  
            return iterator(newNode);  
        }
        /// 仔细想一下这个过程.
        return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
    }

    
    iterator insert(iterator itr, Object &&x) {  
        Node *p = itr.current;  
        theSize++;
        Node * newNode=nullptr;
        if(p==head){
            newNode = new Node(std::move(x), head, head->next);  
            newNode->next->prev=newNode;
            head->next=newNode;
        }else{
            newNode = new Node(std::move(x), p->prev, p);
            newNode->next->prev=newNode;
            newNode->prev->next=newNode;
        }
        return iterator(newNode);  
    }  

        iterator erase(iterator itr)  
        {  
            Node* p = itr.current;  
    
        // 检查是否为 nullptr 或尝试删除哨兵节点  
            if (p == nullptr || p == head || p == tail) {  
                throw std::invalid_argument("Cannot erase sentinel or nullptr node");  
            }  
    
        // 正常删除节点  
            iterator retVal{ p->next };  
            p->prev->next = p->next;  
            p->next->prev = p->prev;  
    
            delete p;  
            theSize--;  
    
            return retVal;  
        }  

    
    iterator erase(iterator from, iterator to) {  
        if (from == to) return to;  
  
        Node *nodeFrom = from.current;  
        Node *nodeTo = to.current;  
        Node *prevNode = nodeFrom->prev;  
  
        prevNode->next = nodeTo;  
        nodeTo->prev = prevNode;  
  
        while (nodeFrom != nodeTo) {  
            Node *nextNode = nodeFrom->next;  
            delete nodeFrom;  
            nodeFrom = nextNode;  
            theSize--;  
        }  
  
        return to;  
    }  

private:
    int theSize;    /**<! 数据节点总数. */
    Node *head;     /**<! 头指针. */
    Node *tail;     /**<! 尾指针. */
    
    
    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

#else
#endif
        