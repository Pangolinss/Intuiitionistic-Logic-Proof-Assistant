#ifndef ASSISTANT_H
#define ASSISTANT_H 
#include<string>
#include<vector>
#include<set>
#include<map>
#include<iostream>
#include<cstdarg>

class Type;
class Assistant{
        public:
    std::map<std::string, Type*> context;
    Type* goal;
    Type* initial_goal;
    int name_count;
    Assistant* nextState;
        Assistant() : context{}, goal{nullptr}, initial_goal{nullptr}, name_count{0}, nextState{nullptr} {}
        Assistant(const Assistant& other);
        ~Assistant();
        Type* getGoal(){return goal;}
        void setGoal(Type* g);
        void intro();
        void intro(std::string);
        void right();
        void left();
        void exact(std::string);
        void assert(Type* t);

        void implElim(std::string impl, std::string arg);
        void andElim(std::string andName, std::string name = "");
        void orElim(std::string orName);
        void botElim(std::string botName);

        void impIntro(std::string imp, std::string then);
        void andIntro(std::string a1, std::string a2);
        void eliminate(std::string, std::vector<std::string>);

        void output();
        void nextGoal();
    private:
        std::string createName();

};

#endif