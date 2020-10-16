#include"Assistant.h"
#include"Type.h"

Assistant::Assistant(const Assistant& other) : context{}{
    if (other.goal != nullptr){
        goal = other.goal->clone();
    }
    else {
        goal = nullptr;
    }
    initial_goal = other.goal->clone();
    name_count = other.name_count;
    nextState = other.nextState;
    for (auto it = other.context.begin(); it != other.context.end(); ++it){
        context.insert(std::pair<std::string, Type*>(it->first, it->second->clone())) ;
    }
}

Assistant::~Assistant(){
    delete goal;
    Assistant* p;
    Assistant* q;
    while (p != nullptr){
        q = p;
        p = p->nextState;
        delete q;
    }
}

void Assistant::setGoal(Type* g){
    goal = g->clone();
    initial_goal = g->clone();
}

void Assistant::intro(){
    if (goal->getType() == 0){
        Type* temp;
        Type* t;
        std::string h = "H"+std::to_string(name_count++);
        t = goal->getArg()[0];
        context.insert(std::pair<std::string, Type*>(h, t));
        temp = goal->getArg()[1];
        goal->getArg()[0] = nullptr;
        goal->getArg()[1] = nullptr;
        delete goal;
        goal = temp;
        
    }
}

void Assistant::intro(std::string h){
    if (goal->getType() == 0){
        if (context.find(h) != context.end() || h == ""){
            h= "H"+std::to_string(name_count++);
        }
        Type* t;
        Type* temp;
        t = goal->getArg()[0];
        context.insert(std::pair<std::string, Type*>(h,t));
        temp = goal->getArg()[1];
        goal->getArg()[0] = nullptr;
        goal->getArg()[1] = nullptr;
        delete goal;
        goal = temp;
        
    }
}


void Assistant::exact(std::string s){
    auto it = context.find(s);
    if (it != context.end()){
        if (*(it->second) == *goal ) {
            delete goal;
            goal = nullptr;
            return;
        }
    }
}

void Assistant::right(){
    if (goal->getType() == 2){
        Type* t = goal->getArg()[0];
        delete goal->getArg()[1];
        goal->getArg()[0] = nullptr;
        goal->getArg()[1] = nullptr;
        delete goal;
        goal = t;
    }
}

void Assistant::left(){
    if (goal->getType() == 2){
        Type* t = goal->getArg()[1];
        delete goal->getArg()[1];
        goal->getArg()[0] = nullptr;
        goal->getArg()[1] = nullptr;
        delete goal;
        goal = t;
    }
}

void Assistant::assert(std::string prop){
    
}

void Assistant::implElim(std::string impl, std::string arg){
    auto implType = context.find(impl);
    auto argType = context.find(arg);
    if (implType != context.end() && argType != context.end()){
        if (implType->second->getType() == 0){
            if ( *(implType->second->getArg()[0]) == *(argType->second)){
                Type* t = implType->second->getArg()[1];
                implType->second->getArg()[0]->~Type();
                implType->second->getArg()[0] = nullptr;
                implType->second->getArg()[1] = nullptr;
                delete implType->second;
                implType->second = t;
            }
        }
    }
}

void Assistant::andElim(std::string andName, std::string name){
    auto andType = context.find(andName);
    if (andType != context.end()){
        if (andType->second->getType() == 1){
            Type* t1 = andType->second->getArg()[0];
            Type* t2 = andType->second->getArg()[1];
            andType->second->getArg()[0] = nullptr;
            andType->second->getArg()[1] = nullptr;
            delete andType->second;
            andType->second = t1;
            if (name == ""){
                std::string h = createName();
                context.insert(std::pair<std::string, Type*>(h, t2));
            }
            else{
                auto it = context.find(name);
                if (it != context.end()){
                    context.insert(std::pair<std::string, Type*>(name, t2));
                }
            }
            andType->second = t1;
        }
    }
}

void Assistant::orElim(std::string orName){
    auto orType = context.find(orName);
    if (orType != context.end() && orType->second->getType() == 2) {
            Assistant* a = new Assistant(*this);
            auto otherOr = a->context.find(orName);
            Type* t1 = orType->second->getArg()[0];
            Type* t2 = orType->second->getArg()[1];
            orType->second->getArg()[0] = nullptr;
            orType->second->getArg()[1] = nullptr;
            otherOr->second->getArg()[0] = nullptr;
            otherOr->second->getArg()[1] = nullptr;
            delete orType->second;
            delete otherOr->second;
            orType->second = t1;
            otherOr->second = t2;
            nextState = a;
    }
}

void Assistant::botElim(std::string botName){
    auto botType = context.find(botName);
    if (botType != context.end() && botType->second->getType() == 4){
        delete goal;
        goal = nullptr;
    }
}

void Assistant::impIntro(std::string imp, std::string then){
    auto impType = context.find(imp);
    auto thenType = context.find(then);
    if(impType != context.end() && thenType  != context.end()){
        Type* t = new Imp;
        t->addArg(impType->second);
        t->addArg(thenType->second);
        thenType->second = t;
    }
}

void Assistant::andIntro(std::string a1, std::string a2){
    auto and1 = context.find(a1);
    auto and2 = context.find(a2);
    Type* t;
    if (and1 != context.end() && and2 != context.end()){
        t = new And;
        t->addArg(and1->second);
        t->addArg(and2->second);
        and2->second = nullptr;
        and1->second = t;
        context.erase(and2);
    }
}


void Assistant::output(){
    for (auto it = context.begin(); it != context.end(); ++it){
        std::cout<<it->first<<": ";
        it->second->print();
        std::cout<<std::endl;
    }
    std::cout<<"================================================"<<std::endl;
    std::cout<<"Goal: ";
    if (goal == nullptr){
        std::cout<<"No goal";
        if (nextState != nullptr){
            std::cout<<", "<<"more goals exists, proof incomplete.";
        }
    }
    else goal->print();
    std::cout<<std::endl<<std::endl;
    std::cout<<std::endl;
}

void Assistant::nextGoal(){
    if (nextState != nullptr){
        for (auto it = context.begin(); it != context.end(); ++it){
            delete it->second;
            it->second = nullptr;
        }
        context.clear();
        delete goal;
        context = nextState->context;
        goal = nextState->goal;
        name_count = nextState->name_count;
        nextState = nextState->nextState;
    }

}

std::string Assistant::createName(){
    std::string h = "H" + std::to_string(name_count++);
    while (context.find(h) != context.end()){
        h = "H" + std::to_string(name_count++);
    }
    return h;
}