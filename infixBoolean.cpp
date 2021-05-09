//
//  eval.cpp
//  hw2Redo
//
//  Created by Shilpa Rao on 4/27/21.
//

#include <iostream>
#include <stack>
using namespace std;

int precedence(char a);
bool validation(string infix);
int evaluate(string infix, string& postfix, bool& result);

int evaluate(string infix, string& postfix, bool& result) {

    if (validation(infix)) {

        postfix = "";
        stack<char> pfStack;

        for(int i = 0; i < infix.size(); i++) {
            char ch = infix.at(i);
            switch(ch) {
                case 'T':
                case 'F':
                    postfix += ch;
                    break;
                case '(':
                    pfStack.push(ch);
                    break;
                case ')':
                    // pop stack until matching '('
                    while (pfStack.top() != '(') {
                        postfix += pfStack.top();
                        pfStack.pop();
                    }
                    pfStack.pop();
                    break;
                case '&':
                case '^':
                    while(!pfStack.empty() && pfStack.top() != '(' && precedence(ch) <= precedence(pfStack.top())) {
                    postfix += pfStack.top();
                    pfStack.pop();
                  }
                    pfStack.push(ch);
                    break;
                case '!': // THIS WILL CREATE AN ERROR
                    while(!pfStack.empty() && pfStack.top() != '(' && precedence(ch) < precedence(pfStack.top())) {
                        postfix += pfStack.top();
                        pfStack.pop();
                    }
                    pfStack.push(ch);
                    break;

                    //            While the stack is not empty and the stack top is not '('
//                    and precedence of ch <= precedence of stack top
//                append the stack top to postfix
//                    pop the stack
//                push ch onto the stack
//                break
            }

        }

        while (!pfStack.empty()) {
            postfix += pfStack.top();
            pfStack.pop();
        }

        //    Initialize the operand stack to empty

        // Evaluate postfix string
        stack<bool> opStack;
        bool operand2;
        bool operand1;
        bool op;
        //    For each character ch in the postfix string

        for(int j = 0; j < postfix.size(); j++) {
            char ch = postfix.at(j);
            switch(ch) {
                case 'F':
                    opStack.push(false);
                    break;
                case 'T':
                    //push the value that ch represents onto the operand stack
                    opStack.push(true);
                    break;
                case '&':
                case '^':
                    operand2 = opStack.top();
                    opStack.pop();
                    operand1 = opStack.top();
                    opStack.pop();
                    if (ch == '^') {
                        opStack.push((operand1 + operand2) % 2);
                    } else if (ch == '&') {
                        opStack.push(operand1 && operand2);
                    }
                    break;
                case '!':
                    op = opStack.top();
                    opStack.pop();
                    opStack.push(!op);
            }
        }

        result = opStack.top();

        return 0;
    } else {
        return 1;
    }


}

bool validation(string infix) {

    if (infix == "") {
        return false;
    }

    // remove spaces first
    infix += 'E';
    int i = 0;
    while (infix.at(i) != 'E') {

        if (infix.at(i) == ' ') {
            infix.erase(i, 1);
        } else {
            i++;
        }

    }

    if (infix == "E") {
        return false;
    }

    int openC = 0;
    int closeC = 0;

    for (int i = 0; i < infix.size() - 1; i++) {

        char next = infix.at(i + 1);
        switch(infix.at(i)) {

            case '&':
            case '^':
                //(next != 'F' || next != 'T' || next != '(' || next != '!')
                //FT&!()^E
                // F T ( !
                // & ^ ) E
                if (next == '&' || next == '^' || next == ')' || next == 'E') {
                    return false;
                }
                break;
            case '!':
                //(next != 'F' || next != 'T' || next != '(')
                //FT&!()^E
                //  & ! ) ^ E
                if (next == '&' || next == ')' || next == '^' || next == 'E') {
                    return false;
                }
                break;
            case 'F':
            case 'T':
                // next == 'E' || next != '&' || next != '^' || next != ')'
                // &  ^  ! E
                // ( T F
                if (next == 'T' || next == '(' || next == 'F' || next == '!') {
                    return false;
                }
                break;
            case '(':
                // next != 'F' || next != 'T' || next != '!'
                // FT&!()^E
                // & () ^
                if (next == '&' || next == ')' || next == '^' || next == 'E') {
                    return false;
                }
                openC++;
                break;
            case ')':
                //next != 'E' || next != '&' || next != '^'
                // FT&!()^E
                // T&!()
                if (next == 'T' || next == '!' || next == '(') {
                    return false;
                }
                closeC++;
                if (closeC > openC) {
                    return false;
                }
                break;
            default:
                return false;

        }

    }

    if (openC != closeC) {
        return false;
    }

    return true;

}

int precedence(char a) {

    switch(a) {
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        default:
            return 0;
    }


}
