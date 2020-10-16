#ifndef TYPE_H
#define TYPE_H
#include<vector>
#include<cstdarg>
#include<string>
#include<iostream>
#include<utility>
#define Imp Type{"->", 0}
#define And Type{"/\\", 1}
#define Or Type{"\\/", 2}
#define Var Type{"", 3}
#define Bot Type{"False", 4}

class Type{
    std::vector<Type*> arg;
    std::string symbol;
    int type;
    public:
        Type() {}
        Type(std::string sym, int t) : symbol{sym}, type{t}, arg{} {}
        ~Type(){
            for (auto it = arg.begin(); it != arg.end(); ++it){
                delete (*it);
            }
            arg.clear();
        }
        Type(Type&&);

        Type& operator=(Type&& other); 

        Type* clone() const;

        std::string getSymbol(){return symbol;}
        void addArg(Type* t){arg.push_back(t);}
        std::vector<Type*>& getArg(){return arg;}
        std::string getVis() const {return symbol;};
        int getType() const {return type;};
        bool operator==(const Type& other);
        bool equal(const Type& other);
        void print();
    private:
};

/*
class Imp : public Type {
    public:
        using Type::Type;
        std::string getVis(){return "->";}
        int getType() const {return 0;}
};

class And : public Type{
    public:
        using Type::Type;
        std::string getVis(){return "/\\";}
        int getType() const {return 1;}
};

class Or : public Type{
    public:
        using Type::Type;
        std::string getVis(){return "\\/";}
        int getType() const {return 2;}
};

class Var : public Type{
    public:
        using Type::Type;
        std::string getVis(){return getSymbol();}
        int getType() const {return 3;}
};
*/
#endif