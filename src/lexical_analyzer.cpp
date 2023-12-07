#include "lexical_analyzer.h"

std::vector<Token> LexicalAnalyzer::getTokens(std::string input, int startStateID,int deadStateID,
                                              std::map<int, State> dfaMap){
    std::cout <<  dfaMap[startStateID].getIsAccepting()<< " "<<  dfaMap[startStateID].getAcceptedToken()->type <<"\n" ;
    std::cout <<  startStateID <<" "<<  deadStateID <<"\n" ;

       for ( auto& x : dfaMap) {
           std::cout << "state: " << x.first << ", " << x.second.getIsAccepting();
           if(x.second.getIsAccepting())
                std::cout<< " " << x.second.getAcceptedToken()->type <<" " <<  x.second.getAcceptedToken()->lexeme;
           std::cout<<'\n';
       }
    int currentStateID = startStateID;
    std::vector<Token> acceptedTokens;
    int i=0;
    Token* lastAcceptedToken = nullptr;
    // int lastAcceptedPos = -1;
    std::string lexeme = "";
    while (i<input.size())
    {
        // dfaMap[currentStateID].printTransitions();
        // std::cout<<"size of set of next states: "<<(dfaMap[currentStateID].getTransitions()[input[i]]).size()<<'\n';
        // do the move
        std::cout<<" inspecting (" << input[i]<<")\n";
        assert((dfaMap[currentStateID].getTransitions()[input[i]]).size()<=1);
        const int nextStateID =((dfaMap[currentStateID].getTransitions()[input[i]]).size()<1)? deadStateID:*dfaMap[currentStateID].getTransitions()[input[i]].begin();

        //if the next state is a Deadstate,
        //           then the last accepted token will be added to the vector,
        //           current state will be start state, i will remain the same if the char is not discarded
        //else change current state to next state, save next token, keep going
        std::cout<<"after move id "<< nextStateID <<'\n';
        if(nextStateID == deadStateID){
            std::cout<<"next state is dead state \n";
            assert((dfaMap[startStateID].getTransitions()[input[i]]).size()<=1);

            int otherPossibleStateID = (dfaMap[currentStateID].getTransitions()[input[i]].size()<1)?deadStateID:*dfaMap[startStateID].getTransitions()[input[i]].begin();   
            if(otherPossibleStateID == deadStateID){
                std::cout<<"ignoring char \n";
                i++;
            }
            if(lastAcceptedToken!=nullptr){
                std::cout<<"saving token \n";

                lastAcceptedToken->lexeme=lexeme;
                acceptedTokens.push_back(*lastAcceptedToken);
                lastAcceptedToken = nullptr;
            }
            currentStateID = startStateID;
            lexeme="";
        }else{
            std::cout<<"meaningful char "<<input[i]<<"\n";

            lexeme+=input[i];
            currentStateID=nextStateID;
            if(dfaMap[currentStateID].getIsAccepting()){
                std::cout<<"passed accepting \n";
                lastAcceptedToken = dfaMap[currentStateID].getAcceptedToken();
            }
            i++;
        }
        std::cout<<"\n";
    }
    return acceptedTokens;
}
