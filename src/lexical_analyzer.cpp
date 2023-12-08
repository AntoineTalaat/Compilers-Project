#include "lexical_analyzer.h"

std::vector<Token> LexicalAnalyzer::getTokens(std::string input, int startStateID,int deadStateID,
                                              std::map<int, State> dfaMap){
    int currentStateID = startStateID;
    std::vector<Token> acceptedTokens;
    int i=0;
    Token* lastAcceptedToken = nullptr;
    int lastAcceptedPos = -1;
    std::string lexeme = "";
    while (i<input.size())
    {
        std::cout<<" inspecting (" << input[i]<<")\n";
        assert((dfaMap[currentStateID].getTransitions()[input[i]]).size()<=1);
        const int nextStateID =((dfaMap[currentStateID].getTransitions()[input[i]]).size()<1)? deadStateID:*dfaMap[currentStateID].getTransitions()[input[i]].begin();
        // std::cout<<"after move id "<< nextStateID <<'\n';
        if(nextStateID == deadStateID){
            // std::cout<<"next state is dead state \n";
            assert((dfaMap[startStateID].getTransitions()[input[i]]).size()<=1);
            int otherPossibleStateID = (dfaMap[currentStateID].getTransitions()[input[i]].size()<1)?deadStateID:*dfaMap[startStateID].getTransitions()[input[i]].begin();   
            if(otherPossibleStateID == deadStateID){
                if(input[i]!= ' ' && input[i] != '\n')
                    std::cout<<"Error, encountered wrong input, ignoring: " << input[i]<< " at position: "<< i <<"\n";
                if(lastAcceptedPos==-1)
                    i++;
            }
            if(lastAcceptedToken!=nullptr){
                // std::cout<<"saving token \n";
                int k = i-1-lastAcceptedPos;
                std::string trimmedTokenLex = lexeme.substr(0, lexeme.length() - k);
                std::string remainingLex = lexeme.substr(lexeme.length() - k,k);
                lastAcceptedToken->lexeme=trimmedTokenLex;
                lexeme="";
                acceptedTokens.push_back(*lastAcceptedToken);
                lastAcceptedToken = nullptr;
                i=lastAcceptedPos+1;
                lastAcceptedPos = -1;
            }else{
                lexeme="";
            }
            currentStateID = startStateID;

        }else{
            // std::cout<<"meaningful char "<<input[i]<<"\n";

            lexeme+=input[i];
            currentStateID=nextStateID;
            if(dfaMap[currentStateID].getIsAccepting()){
                // std::cout<<"passed accepting \n";
                lastAcceptedToken = dfaMap[currentStateID].getAcceptedToken();
                lastAcceptedPos=i;
            }
            i++;
        }
        // std::cout<<"\n";
    }
    if(lastAcceptedToken!=nullptr)          {
        lastAcceptedToken->lexeme=lexeme;
        acceptedTokens.push_back(*lastAcceptedToken);}
    return acceptedTokens;
}
