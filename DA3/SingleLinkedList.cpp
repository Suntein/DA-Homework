#include "SingleLinkedList.h"
int main(){
    SingleLinkedList<int> a{1,2,3,4,5};
    int a_get = a.getCurrentVal();
    std::cout << a_get << std::endl;

    SingleLinkedList<char> b{'a','c','e'};
    b.setCurrentVal('g');
    b.printList(); //测 试 【 定 义 值 】 操 作 是 否 正 确 ，包 括 可 能 的 空 链 表 测 试 (//部 分 )， 每 种 情 况 9分
    SingleLinkedList<char> e;
    std::cout << b.isEmpty() << " "<< e.isEmpty() << std::endl; //测 试 【 空 链 表 判 断 】 操 作 是 否 正 确 ，18分
    SingleLinkedList<double> c1;
    SingleLinkedList<double> c2{1.5,2.0,9.0,4.7};
    SingleLinkedList<double> c3;
    c3 = c2;
    c1.insert(3.0);
    c2.insert(8.8);
    bool f_c3 = c3.find(2.0);
    c3.insert(8.8);
    c1.printList();
    c2.printList();
    c3.printList(); //测 试 【 插 入 】 操 作 是 否 正 确 ， 每 种 情 况 6分
    e.remove();
    c1.remove();
    bool f = c2.find(9.0);
    c2.remove();
    e.printList();
    c1.printList();
    c2.printList(); //测 试 【 删 除 】 操 作 是 否 正 确 ， 每 种 情 况 6分
    return 0;
}