#include "function.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

int main() {
    while(true){
    try {
        string expression;
        cout << "请输入一个数学表达式,支持 +, -, *, /, e, (, );退出请按exit:"<<endl;
        cin >> expression;
        if(expression=="exit"){
            return 0;
        }
        // 中缀表达式转换为后缀表达式
        vector<string> postfix = zhuanhuan(expression);

        // 打印后缀表达式
        cout << "后缀表达式为：";
        for (const auto& token : postfix) {
            cout << token << " ";
        }
        cout << endl;

        // 计算后缀表达式的值
        double result = jisuan(postfix);
        cout << "计算结果为：" << result << endl;

    } catch (const runtime_error& e) {
        cerr << "错误: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "异常: " << e.what() << endl;
    }
    }

    return 0;
}
