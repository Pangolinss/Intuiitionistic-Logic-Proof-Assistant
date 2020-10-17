#include<sstream>
#include"Parser.h"
#include"Assistant.h"


int main(){
    Assistant* ipa = new Assistant;
    std::set<std::string> opList{"->", "/\\", "\\/"};
    std::string cmd;
    std::string input, input1;
    std::string line;
    std::stringstream ss;
    std::vector<std::string> vec;
    /*
    std::stringstream s("(A -> ((A -> B) -> (A -> B)) )");
    auto v = tokenize(s);
    for (auto it : v){
        std::cout<<it<<" ";
    }
    system("PAUSE");
    */
    while (std::cin>>cmd){
        if (cmd == "set-goal"){
            std::getline(std::cin, line);
            std::stringstream ss(line);
            ipa->setGoal(parseType(intoPre(tokenize(ss), opList)));
        }
        else if (cmd == "intro"){
            ipa->intro();
        }
        else if (cmd == "exact"){
            std::cin>>input;
            ipa->exact(input);
        }
        else if (cmd == "right"){
            ipa->right();
        }
        else if (cmd == "left"){
            ipa->left();
        }
        else if (cmd == "impElim"){
            std::cin>>input>>input1;
            ipa->implElim(input, input1);
        }
        else if (cmd == "destruct"){
            
        }
        else if (cmd == "andElim"){
            std::cin>>input;
            ipa->andElim(input);
        }
        else if (cmd == "orElim"){
            std::cin>>input;
            ipa->orElim(input);
        }
        else if (cmd == "botElim" || cmd == "contradiction" || cmd == "absurd"){
            std::cin>>input;
            ipa->botElim(input);
        }
        else if (cmd == "impIntro"){
            std::cin>>input>>input1;
            ipa->impIntro(input, input1);
        }
        else if (cmd == "andIntro"){
            std::cin>>input>>input1;
            ipa->andIntro(input, input1);
        }
        else if (cmd == "assert"){
            std::getline(std::cin, line);
            std::stringstream ss(line);
            ipa->assert(parseType(intoPre(tokenize(ss), opList)));
        }
        ipa->nextGoal();
        std::cout<<std::endl<<std::endl;
        ipa->output();
    }
    return 0;
}