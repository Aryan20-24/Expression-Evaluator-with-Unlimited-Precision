/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

// #include "ulimitedrational.cpp"
// #include "entry.cpp"
// #include<iostream>
// using namespace std;

SymbolTable::SymbolTable(){
    size=0;
    root=NULL;
}

SymbolTable::~SymbolTable(){
    if (root != NULL)
    delete root;
}

SymEntry* insertRec(SymEntry* rooot, string &k, UnlimitedRational* v){
    if(rooot==NULL){
        return new SymEntry(k,v);
    }
    if(k<rooot->key){
        rooot->left = insertRec(rooot->left, k, v);
    }
    else if(k>rooot->key){
        rooot->right = insertRec(rooot->right, k,v);
    }
    //same key case?
    else{
        rooot->val=v;
    }
    return rooot;
}

void SymbolTable::insert(string k, UnlimitedRational* v){
    root = insertRec(root, k, v);
    size++;
}

SymEntry* findMin(SymEntry* a){
    if(a==NULL)
        return a;
    while(a->left!=NULL){
        a=a->left;
    }
    return a;
}

SymEntry* removeRec(SymEntry* rot, string k){
    if (k<rot->key){
        rot->left = removeRec(rot->left, k);
        return rot;
    }
    else if(k>rot->key) {
        rot->right = removeRec(rot->right, k);
        return rot;
    }
    else{
        if(rot->left==NULL && rot->right==NULL){
            delete rot;
            return NULL;
        }
        else if(rot->left==NULL){
            SymEntry* temp=rot->right;
            delete rot;
            return temp;
        }
        else if(rot->right==NULL){
            SymEntry* temp=rot->left;
            delete rot;
            return temp;
        }
        else{
            SymEntry* temp = findMin(rot->right);
            rot->key=temp->key;
            rot->val=temp->val;
            rot->right = removeRec(rot->right, temp->key);
            return rot;
        }
    }
    
}

void SymbolTable::remove(string k){
    root=removeRec(root,k);
    size--;
}

UnlimitedRational* searchRec(SymEntry* rot, string k){
    if(rot==NULL){
        return NULL;
    }
    if(rot->key==k){
        return rot->val;
    }
    if(k<rot->key){
        return searchRec(rot->left, k);
    }
    if(k>rot->key){
        return searchRec(rot->right, k);
    }
}

UnlimitedRational* SymbolTable::search(string k){
    return searchRec(root, k);
}

int SymbolTable::get_size(){
    return size;
}

SymEntry* SymbolTable::get_root(){
    return root;
}

// int main(){
//     SymbolTable a;
//     a.insert("a",new UnlimitedRational(new UnlimitedInt(2), new UnlimitedInt(1)));
//     a.insert("b",new UnlimitedRational(new UnlimitedInt(3), new UnlimitedInt(1)));
//     a.insert("c",new UnlimitedRational(new UnlimitedInt(4), new UnlimitedInt(1)));
//     a.insert("d",new UnlimitedRational(new UnlimitedInt(5), new UnlimitedInt(1)));
//     cout<<(a.search("d"))->get_frac_str()<<endl;
//     cout<<(a.get_root())->key<<endl;
//     cout<<a.get_size()<<endl;
//     a.remove("b");
//     cout<<a.get_size()<<endl;
// }