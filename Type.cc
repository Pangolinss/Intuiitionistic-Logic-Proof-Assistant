#include"Type.h"

Type::Type(Type&& other) : symbol{std::move(other.symbol)} {
    for (auto it = other.arg.begin(); it != other.arg.end(); ++it){
        arg.push_back(*it);
        (*it) = nullptr;
    }
    other.arg.clear();
}

Type& Type::operator=(Type&& other){
    symbol = std::move(other.symbol);
    auto it1 = arg.begin();
    auto it2 = other.arg.begin();
    while (it1 != arg.end() && it2 != other.arg.end()){
        *it1 = *it2;
        *it2 = nullptr;
    }
    if (it1 == arg.end() && it2 == other.arg.end()) return *this;
    else if (it1 == arg.end()) {
        for (; it2 != other.arg.end(); ++it2){
            arg.push_back(*it2);
            *it2 = nullptr;
        }
        other.arg.clear();
    }
    else{
        while (arg.size() != other.arg.size()){
            arg.pop_back();
        }
    }
    return *this;
}

Type* Type::clone() const{
    Type *t = new Type;
    t->type = type;
    t->symbol = symbol;
    for (auto it = arg.begin(); it != arg.end(); ++it){
        t->arg.push_back((*it)->clone());
    }
    return t;
}

void Type::print(){
    if (getType() == 3 || getType() == 4){
        std::cout<<this->getVis();
    }
    else{
        std::cout<<"(";
        auto it = arg.begin();
        (*it)->print();;
        std::cout<<" "<<getVis()<<" ";
        ++it;
        for (; it != arg.end(); ++it){
            (*it)->print();
        }
        std::cout<<")";
    }
}

bool Type::equal(const Type& other){
    if (symbol == other.symbol){
        if (arg.size() != other.arg.size()) return false;
        if (arg.size() > 0){
            auto it1 = arg.begin();
            auto it2 = other.arg.begin();
            while (it1 != arg.end() && it2 != other.arg.end()){
                if (!(*it1)->equal(*(*it2))){
                    return false;
                }
                ++it1;
                ++it2;
            }
        }
        return true;
    }
    else return false;
}

bool Type::operator==(const Type& other){
    return equal(other);
}


