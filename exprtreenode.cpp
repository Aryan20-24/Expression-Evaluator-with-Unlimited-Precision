/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    type="";
    val=NULL;
    evaluated_value=NULL;
    id="";
    left=NULL;
    right=NULL;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    left=NULL;
    right=NULL;
    evaluated_value=NULL;
    if(t=="+"){
        type="ADD";
        val=NULL;
        id="";
    }
    else if(t=="-"){
        type="SUB";
        val=NULL;
        id="";
    }
    else if(t=="*"){
        type="MUL";
        val=NULL;
        id="";
    }
    else if(t=="/"){
        type="DIV";
        val=NULL;
        id="";
    }
    else if(t==":="){
        type="ZZZ";
        val=NULL;
        id="";
    }
    else{
        int flag=0;
        for(char c: t){
            if((c<'0'||c>'9') && c!='-'){
                flag=-1;
            }
        }
        if(flag==0){
            type="VAL";
            val=new UnlimitedRational(v, new UnlimitedInt(1));
            evaluated_value=new UnlimitedRational(v, new UnlimitedInt(1));
            id="";
        }
        else{
            type="VAR";
            id=t;
            val=NULL;
            evaluated_value=new UnlimitedRational(v, new UnlimitedInt(1));
        }
    }
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    left=right=NULL;
    evaluated_value=NULL;
    if(t=="+"){
        type="ADD";
        val=NULL;
        id="";
    }
    else if(t=="-"){
        type="SUB";
        val=NULL;
        id="";
    }
    else if(t=="*"){
        type="MUL";
        val=NULL;
        id="";
    }
    else if(t=="/"){
        type="DIV";
        val=NULL;
        id="";
    }
    else if(t==":="){
        type="ZZZ";
        val=NULL;
        id="";
    }
    else{
        int flag=0;
        for(char c: t){
            if((c<'0'||c>'9') && c!='-'){
                flag=-1;
            }
        }
        if(flag==0){
            type="VAL";
            val=v; //!!
            id="";
        }
        else{
            type="VAR";
            id=t;
            val=NULL;
            evaluated_value=v;
        }
    }
}

ExprTreeNode::~ExprTreeNode(){
    if(left != nullptr)
        delete left;
    if(right!= nullptr) 
        delete right;
    if(val !=nullptr) 
        delete val;
    if(evaluated_value!= nullptr) 
        delete evaluated_value;
}