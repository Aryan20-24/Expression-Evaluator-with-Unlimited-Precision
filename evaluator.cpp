/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
// #include<iostream>a
Evaluator::Evaluator(){
    symtable= new SymbolTable();
}

Evaluator::~Evaluator(){
    delete symtable;
}

void Evaluator::parse(vector<string> code){
    vector<ExprTreeNode*> vec;
    ExprTreeNode* finalroot = new ExprTreeNode(code[1], new UnlimitedInt(1));
    finalroot->left= new ExprTreeNode(code[0], new UnlimitedInt(1));
    finalroot->right= new ExprTreeNode();
    ExprTreeNode* root = finalroot->right;
    vec.push_back(root);
    for(int i=2;i<code.size();i++){
        if(code[i]=="("){
            ExprTreeNode* a = new ExprTreeNode();
            root->left=a;
            vec.push_back(root);
            root=root->left;
        }
        else if(code[i]=="+" || code[i]=="-" || code[i]=="*" || code[i]=="/"){
            if(code[i]=="+"){
                root->type="ADD";
            }
            else if(code[i]=="-"){
                root->type="SUB";
            }
            else if(code[i]=="*"){
                root->type="MUL";
            }
            else if(code[i]=="/"){
                root->type="DIV";
            }
            root->right=new ExprTreeNode();
            vec.push_back(root);
            root=root->right;
        }
        else if(code[i]==")"){
            ExprTreeNode* b = vec.back();
            root=b;
            vec.pop_back();
            // delete b;
        }
        else{
            int flag=0;
            for(char k : code[i]){
                if((k<'0'|| k>'9') && k!='-'){
                flag=-1;
                }
            }
            if(flag==0){ //val
                root->type="VAL";
                root->val= new UnlimitedRational(new UnlimitedInt(code[i]), new UnlimitedInt(1));
            }
            else if(flag==-1){
                root->type="VAR";
                root->id=code[i];
                root->val=symtable->search(root->id);
            }
            ExprTreeNode* par = vec.back();
            root=par;
            if(!vec.empty())
                vec.pop_back();
            // delete par;
        }
    }
    expr_trees.push_back(finalroot);


    // while(finalroot->right!=NULL){
    //     cout<<finalroot->type<<endl;
    // }
}

UnlimitedRational* eval2(ExprTreeNode* root, SymbolTable* symtab){
    if(root->type=="ADD"){
        root->evaluated_value=UnlimitedRational::add(eval2(root->left,symtab), eval2(root->right,symtab));
    }
    else if(root->type=="SUB"){
        root->evaluated_value=UnlimitedRational::sub(eval2(root->left,symtab), eval2(root->right,symtab));
    }
    else if(root->type=="MUL"){
        root->evaluated_value=UnlimitedRational::mul(eval2(root->left,symtab), eval2(root->right,symtab));
    }
    else if(root->type=="DIV"){
        root->evaluated_value=UnlimitedRational::div(eval2(root->left,symtab), eval2(root->right,symtab));
    }
    else if(root->type=="VAL"){
        root->evaluated_value=root->val;
    }
    else{
        root->evaluated_value=symtab->search(root->id);
    }
    return root->evaluated_value;
}

void Evaluator::eval(){
    ExprTreeNode* ev = expr_trees.back();
    UnlimitedRational* newrat= eval2(ev->right, symtable);
    ev->right->evaluated_value=newrat;
    ev->left->evaluated_value=newrat;
    symtable->insert(ev->left->id, newrat);
    // delete newrat;
    // delete ev;
}

// int main(){
//     Evaluator* a = new Evaluator();
//     vector<string> v ={"x",":=","(","3","+","5",")"};
//     a->parse(v);
// }
