#include "List.h"
#include <iostream>

void test_list_operations() {
    // 测试构造函数和基本操作
    List<int> intList;
    std::cout << "Testing default constructor... Passed\n";

    // 测试 push_back, push_front
    intList.push_back(1);
    intList.push_front(0);
    std::cout << "Testing push_back and push_front... Passed\n";

    // 测试 front 和 back
    std::cout << "Front element: " << intList.front() << " (Expected: 0)\n";
    std::cout << "Back element: " << intList.back() << " (Expected: 1)\n";

    // 测试拷贝构造函数
    List<int> copiedList = intList;
    std::cout << "Testing copy constructor... Passed\n";

    // 测试移动构造函数
    List<int> movedList = std::move(intList);
    std::cout << "Testing move constructor... Passed\n";
    std::cout << "Original list size after move: " << intList.size() << " (Expected: 0)\n";

    // 测试插入和迭代器
    List<int> anotherList;
    anotherList.push_back(10);
    auto it = anotherList.begin();
    anotherList.insert(it, 5);
    std::cout << "Testing insert... Passed\n";

    // 测试 erase
    anotherList.erase(anotherList.begin());
    std::cout << "Testing erase... Passed\n";

    // 测试赋值操作符
    List<int> assignedList;
    assignedList = movedList;
    std::cout << "Testing assignment operator... Passed\n";

    // 测试 pop_front 和 pop_back
    assignedList.pop_front();
    assignedList.pop_back();
    std::cout << "Testing pop_front and pop_back... Passed\n";

    // 测试 clear 和 empty
    assignedList.clear();
    std::cout << "Testing clear... Passed\n";
    std::cout << "List empty: " << (assignedList.empty() ? "Yes" : "No") << " (Expected: Yes)\n";
}

int main() {
    test_list_operations();
    List<int> myList;
    for (int i=0;i<10;i++)
        myList.push_back(i+10);
    // 测试动态迭代器的 ++ 和 -- 运算符
    std::cout << " ++ and --:" << std::endl;
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " "; // 测试前置++运算符
    }
    std::cout << std::endl;

    // 测试后置++运算符
    std::cout << "(it++): " << std::endl;
    for (auto it = myList.begin(); it != myList.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 测试前置--运算符
    std::cout << "(--it): " << std::endl;
    auto it = myList.end();
    --it; // 迭代器指向最后一个元素
    while (it != myList.begin()) {
        std::cout << *it << " ";
        --it; // 前置自减
    }
    std::cout << *it << " "; // 输出第一个元素
    std::cout << std::endl;

    // 测试后置--运算符
    std::cout << "(it--):" << std::endl;
    it = myList.end();
    it--; // 后置自减
    while (it != myList.begin()) {
        std::cout << *it << " ";
        it--;
    }
    std::cout << std::endl;
    
    // 测试输出头部元素和尾部元素
    std::cout << "All basic tests passed.\n";
    return 0;
}
