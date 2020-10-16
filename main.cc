#include<sstream>
#include"Parser.h"
#include"Assistant.h"


int main(){
    std::string line;
    Assistant* ipa = nullptr;
    std::set<std::string> opList{"->", "/\\", "\\/"};
    while (getline(line, std::cin)){
        std::istringstream s(line);
        std::vector<std::string> input = tokenize(s);
        if (input.front() == "set-goal"){
            ipa = new Assistant;
            input.erase(input.front());
            ipa->setGoal(parseType(intoPre(, opList)))
        }
        else if (input.front() == "intro"){

        }
        else if (input.front() == "exact"){

        }
        else if (input.front() == "right"){

        }
        else if (input.front() == "left"){

        }
        else if (input.front() == "impElim"){

        }
        else if (input.front() == "destruct"){

        }
        else if (input.front() == "andElim"){

        }
        else if (input.front() == "orElim"){

        }
        else if (input.front() == "botElim" || input.front() == "contradiction" || input.front() == "absurd"){

        }
        else if (input.front() == "impIntro"){

        }
        else if (input.front() == "andIntro"){

        }
    }
    return 0;
}