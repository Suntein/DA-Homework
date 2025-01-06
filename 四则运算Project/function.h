#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <cmath>
using namespace std;
int isOperator(char ch){
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='e'||ch=='('){
        return 1;
    }
    return 0;
}

int youxianji(char ch){
    if(ch=='+'||ch=='-'){
        return 1;
    }else if(ch=='*'||ch=='/'){
        return 2;
    }else if(ch=='e'){
        return 3;
    }
    return 0;
}

double power(double n){
    return pow(10,n);
}

int isNumber(char ch){
    if(ch<='9'&&ch>='0')
        return 1;
    return 0;
}

int Isdigit(char c){
    if(c>='0'&&c<='9')
        return 1;
    else 
        return 0;
}

vector<string> zhuanhuan(string str){
    stack <char> oper;
    vector <string> biaodashi;
    string number;
    for(int i=0;i<str.size();i++){
        char c=str[i];
        // if(number.empty()){
        //     if(c=='-'){
        //         if(i==0||isOperator(str[i-1]))
        //             number +="-";
        //             continue;
        //     }
        // }
        if(Isdigit(c)||c=='.'){
            number+=c;
        }else{
            if(!number.empty()){
                biaodashi.push_back(number);
                number.clear();
            }
            if(c=='('){
                oper.push(c);
            }else if(c==')'){
                while(!oper.empty() && oper.top()!='('){
                    biaodashi.push_back(string(1, oper.top()));
                    oper.pop();
                }
                if(!oper.empty())
                    oper.pop();
            }else if(isOperator(c)){
                while (!oper.empty() && youxianji(oper.top()) >= youxianji(c)) {
                    biaodashi.push_back(string(1, oper.top()));
                    oper.pop();
                }
                oper.push(c);
            }
        }
    }
    if (!number.empty()) {
        biaodashi.push_back(number);
    }
    while (!oper.empty()) {
        biaodashi.push_back(string(1, oper.top()));
        oper.pop();
    }
    return biaodashi;
}

double jisuan(const vector<string>& jisuanshi) {
    stack<double> values;

    for (size_t i = 0; i < jisuanshi.size(); ++i) {
        const auto& token = jisuanshi[i];
        
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            values.push(stod(token));
        } else if (isOperator(token[0])) {
            
            
            if (values.size() < 2) {
                throw runtime_error("Invalid expression ");
            }else{
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();

                switch (token[0]) {
                    case '+': values.push(a + b); break;
                    case '-': values.push(a - b); break;
                    case '*': values.push(a * b); break;
                    case '/': 
                        if (b == 0) throw runtime_error("Division by zero");
                        values.push(a / b); 
                        break;
                    case 'e':values.push(a*pow(10,b));break;
                }
            }
        }
    }

    if (values.size() != 1)
        throw runtime_error("Invalid expression ");
    return values.top();
}

   
