#ifndef TRIES_DATA_SRUCTURE_TRIES_H
#define TRIES_DATA_SRUCTURE_TRIES_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class TrieNode{
public:
    map<char,TrieNode*> child;
    bool valid_end;

    TrieNode(){
        valid_end = false;
    }

    TrieNode(char c){
        child.insert(pair<char,TrieNode*>(c,new TrieNode()));
        valid_end = false;
    }

    void insert(string const &word){
        char c = word[0];
        string new_word = word;
        new_word.erase(0,1);
        auto it = child.find(c);
        if(it==child.end()){
            auto TN = new TrieNode;
            child.insert(pair<char,TrieNode*>(c,TN));
            if(new_word.empty()){
                TN->valid_end = true;
            }else{
                TN->insert(new_word);
            }
        }else {
            (*it).second->insert(new_word);
        }
    }

    vector<string> search_prefixes(string const &word){
        auto vec_string = new vector<string>;
        string aux;
        for(auto it = child.begin(); it != child.end(); it++){
            if((*it).first==word[0]){
                aux += word[0];
                vec_string->push_back(aux);
                string new_word = word;
                new_word = new_word.erase(0,1);
                return rec_search_prefix(new_word,(*it).second, vec_string, aux);
            }
        }
        return *vec_string;
    }

    vector<string> rec_search_prefix(string const &word, TrieNode* TN, vector<string> *vec_string, string aux){
        if(word.empty() && TN->valid_end){
            return *vec_string;
        }
        for(auto it = TN->child.begin(); it != TN->child.end(); it++){
            if((*it).first==word[0]){
                aux += word[0];
                vec_string->push_back(aux);
                string new_word = word;
                new_word = new_word.erase(0,1);
                return rec_search_prefix(new_word,(*it).second, vec_string, aux);
            }
        }
        return vector<string>();
    }

    bool search_word(string word){
        for(auto it = child.begin(); it != child.end(); it++){
            if((*it).first==word[0]){
                string new_word = word;
                new_word = new_word.erase(0,1);
                return rec_search(new_word,(*it).second);
            }
        }
        return false;
    }

    bool rec_search(string const &word, TrieNode* TN){
        if(word.empty()&&TN->valid_end){
            return true;
        }
        for(auto it = TN->child.begin(); it != TN->child.end(); it++){
            if((*it).first==word[0]){
                string new_word = word;
                new_word = new_word.erase(0,1);
                return rec_search(new_word,(*it).second);
            }
        }
        return false;
    }

    void delete_word(string const &word){
        for(auto it = child.begin(); it != child.end(); it++){
            if((*it).first==word[0]){
                string new_word = word;
                new_word = new_word.erase(0,1);
                rec_delete(new_word,(*it).second);
            }
        }
    }

    void rec_delete(string const &word, TrieNode *TN){
        if(word.empty()&&TN->valid_end){
            TN->valid_end=false;
        }
        for(auto it = TN->child.begin(); it != TN->child.end(); it++){
            if((*it).first==word[0]){
                string new_word = word;
                new_word = new_word.erase(0,1);
                rec_delete(new_word,(*it).second);
            }
        }
    }

    void print(){
        string s;
        for(auto it = child.begin(); it != child.end(); it++){
            s = (*it).first;
            rec_print(s,(*it).second);
        }
    }

    void rec_print(string const &word, TrieNode* TN){
        if(TN->valid_end){
            cout<<word<<endl;
        }else{
            string aux_word = word;
            for(auto it = TN->child.begin(); it != TN->child.end(); it++){
                aux_word += (*it).first;
                rec_print(aux_word, (*it).second);
                aux_word = word;
            }
        }
    }

};

class Trie{
public:
    TrieNode* root;

    Trie():root(new TrieNode()){};

    void insert(string const &word){root->insert(word);}

    vector<string> search_prefixes(string const &word){return root->search_prefixes(word);}

    bool search_word(string const &word){return root->search_word(word);}

    void delete_word(string const &word){root->delete_word(word);}

    void print(){root->print();}

    void insert_text(string const &text){
        string word;
        auto it = text.begin();
        while(it!=text.end()){
            char c = *it;
            if(c == ' '||c==','||c=='.'||c==';'||c=='?'||c=='!'||c=='('||c=='"'||c==')'||c=='\n'){
                if(!word.empty()){
                    insert(word);
                    word.clear();
                }
            }else{
                word += c;
            }
            it++;
        }
    }
};

#endif //TRIES_DATA_SRUCTURE_TRIES_H
