#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<set>
#include"Type.h"

std::vector<std::string> tokenize(std::istream& s){
    std::vector<std::string> vec;
    std::string word;
    char c;
    bool flag = true;
    while(s.get(c)){
        if (!flag){
            if (c == '(' || c == ')'){
                if (word != ""){
                    vec.push_back(word);
                    word = "";
                }
                std::string t;
                t+=c;
                vec.push_back(t);
            }
            else if (!isspace(c)){
                word += c;
            }
            else{
                if (word != ""){
                    vec.push_back(word);
                    word = "";
                }
            }
        }
        if (!isspace(c) && flag){
            flag = false;
            s.unget();
        }
    }
    if (word != ""){
        vec.push_back(word);
        word = "";
    }
    return vec;
}

std::vector<std::string> intoPre(std::vector<std::string> s, const std::set<std::string> opList){
    std::vector<std::string> opstack;
    std::vector<std::string> output;
    for (auto it = s.begin(); it != s.end(); ++it){
        if (*it == "(") {
            opstack.push_back("(");
            output.push_back("(");
        }
        else if (*it == ")"){
            while(!opstack.empty() && opstack.back() != "("){
                output.push_back(opstack.back());
                opstack.pop_back();
            }
            if (!opstack.empty()) {if (opstack.back() == "(") opstack.pop_back();}
            output.push_back(*it);
        }
        else if (opList.find(*it) != opList.end()){
            opstack.push_back(*it);
        }
        else output.push_back(*it);
    }
    return output;
}

Type* parseType(std::vector<std::string> expr){
    Type* type;
    if (expr.front() != "("){
        if (expr.front() == "False"){
            type = new Type{"False", 4};
        }
        else type = new Type{expr.front(), 3};
    }
    else{
        std::vector<std::string> arg;
        size_t count = 1;
        expr.pop_back();
        std::string op = expr.back();
        expr.pop_back();
        if (op == "->") type = new Imp;
        else if (op == "\\/") type = new Or;
        else if (op == "/\\") type = new And;
        auto it = expr.begin();
        ++it;
        //vector is now arg1 arg2 ... argn  op
        for (; it != expr.end(); ++it){
            if (*it == "(") ++count;
            else if (*it == ")") --count;
            arg.push_back(*it);
            if (count == 1) {
                type->addArg(parseType(arg));
                arg.clear();
            }
        }
    }
    return type;
}


#endif