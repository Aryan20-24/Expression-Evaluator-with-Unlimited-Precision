/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

// #include"ulimitedint.cpp" //removeee
// #include<iostream>  //remove before submitting
// using namespace std;

UnlimitedRational::UnlimitedRational(){
    p = nullptr;
    q = nullptr;
}


bool checkzero(UnlimitedInt* x){
    if(x->get_size()==1 && x->get_array()[0]==0){
        return true;
    }
    else{
        return false;
    }
}

UnlimitedInt* gcdHelper(UnlimitedInt* i1, UnlimitedInt* i2){
    while(!checkzero(i2)){
        UnlimitedInt* r = UnlimitedInt::mod(i1,i2);
        // UnlimitedInt* bin =i1;
        i1=i2;
        // delete bin;

        // UnlimitedInt* bin2 = i2;
        i2=r;
        // delete bin2;
    }
    return i1;
}

UnlimitedInt* gcd(UnlimitedInt* i1, UnlimitedInt* i2){
    string s1;
    string s2;
    if(i1->get_sign()==-1){
        s1=i1->to_string();
        s1.erase(s1.begin());
    }
    else if(i1->get_sign()==1){
        s1=i1->to_string();
    }
    if(i2->get_sign()==-1){
        s2=i2->to_string();
        s2.erase(s2.begin());
    }
    else if(i2->get_sign()==1){
        s2=i2->to_string();
    }

    UnlimitedInt* j1 = new UnlimitedInt(s1);
    UnlimitedInt* j2 = new UnlimitedInt(s2);
    // cout<<"hui"<<endl;
    UnlimitedInt* anss=gcdHelper(j1,j2);
    // cout<<"yelo"<<endl;
    return anss;

}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    if(den->to_string()=="0"){
        p=new UnlimitedInt("0");
        q=new UnlimitedInt("0");
        return;
    }
    // cout<<"hee98ey"<<endl;
    UnlimitedInt* cf = gcd(num,den);
    // cout<<cf->to_string()<<endl;
    // cout<<"heeey"<<endl;
    p=UnlimitedInt::div(num,cf);
    // cout<<p->to_string()<<endl;
    q=UnlimitedInt::div(den,cf);
    // cout<<q->to_string()<<endl;
    //do not assume num and den are coprime!
    delete cf;
    // p=num;
    // q=den;
}

UnlimitedRational::~UnlimitedRational(){
    if(p!= nullptr) 
    delete p;
    if(q!=nullptr) 
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
}

string UnlimitedRational::get_q_str(){
    return q->to_string();
}

string UnlimitedRational::get_frac_str(){
    return p->to_string() + '/' + q->to_string();
}


// UnlimitedRational* coprime(UnlimitedRational* a){
//     UnlimitedInt* p = a->get_p();
//     UnlimitedInt* q = a->get_q();
    
//     while(true){
//         UnlimitedInt* cf = gcd(p,q);

//         if(cf->get_size()==1 && cf->get_sign()==1 && cf->get_array()[0]=='1'){
//             return new UnlimitedRational(p,q);
//         }
//         p=UnlimitedInt::div(p,cf);
//         q=UnlimitedInt::div(q,cf);
//     }
// }

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* q1 = i1->get_q();
    string a1 = i1->get_frac_str();
    string a2 = i2->get_frac_str();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q2 = i2->get_q();
    // cout<<"hey"<<endl;
    if(a1=="0/0" || a2=="0/0"){
        UnlimitedRational* newrat = new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
        return newrat;
    }
    UnlimitedInt *n1 = UnlimitedInt::mul(p1,q2);
    UnlimitedInt* n2 = UnlimitedInt::mul(p2,q1);
    UnlimitedInt* p = UnlimitedInt::add(n1, n2);
    UnlimitedInt* q = UnlimitedInt::mul(q1,q2);
    UnlimitedRational* newrat = new UnlimitedRational(p,q);
    delete n1;
    delete n2;
    delete p;
    delete q;
    return newrat;

}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* q1 = i1->get_q();
    string a1 = i1->get_frac_str();
    string a2 = i2->get_frac_str();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q2 = i2->get_q();
    if(a1=="0/0" || a2=="0/0"){
        UnlimitedRational* newrat = new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
        return newrat;
    }

    UnlimitedInt* n1 = UnlimitedInt::mul(p1,q2);
    UnlimitedInt* n2 = UnlimitedInt::mul(p2,q1);
    UnlimitedInt* p = UnlimitedInt::sub(n1,n2);
    UnlimitedInt* q = UnlimitedInt::mul(q1,q2);
    UnlimitedRational* newrat = new UnlimitedRational(p,q);
    delete n1;
    delete n2;
    delete p;
    delete q;
    return newrat;

}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* q1 = i1->get_q();
    string a1 = i1->get_frac_str();
    string a2 = i2->get_frac_str();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q2 = i2->get_q();
    if(a1=="0/0" || a2=="0/0"){
        UnlimitedRational* newrat = new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
        return newrat;
    }
    UnlimitedInt* p = UnlimitedInt::mul(p1,p2);
    UnlimitedInt* q = UnlimitedInt::mul(q1,q2);
    UnlimitedRational* newrat = new UnlimitedRational(p,q);
    delete p;
    delete q;
    return newrat;

}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* q1 = i1->get_q();
    string a1 = i1->get_frac_str();
    string a2 = i2->get_frac_str();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q2 = i2->get_q();
    if(a1=="0/0" || a2=="0/0"){
        UnlimitedRational* newrat = new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
        return newrat;
    }
    if(a2[0]=='0' && a2[1]=='/'){
        UnlimitedRational* newrat = new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
        return newrat;
    }
    UnlimitedInt* p = UnlimitedInt::mul(p1,q2);
    UnlimitedInt* q = UnlimitedInt::mul(p2,q1);
    UnlimitedRational* newrat = new UnlimitedRational(p,q);
    delete p;
    delete q;
    return newrat;

}

// int main(){
    //1678423867971  372437864123678996182372
    // UnlimitedInt* e=new UnlimitedInt("16784238642357689567893452678945236789457971");
    // UnlimitedInt* f=new UnlimitedInt("37243745237845237684567893524678945864123678996182372");
    // cout<<"heeey"<<endl;
    // UnlimitedInt* gcdd=gcd(e,f);
    // cout<<"hogya"<<endl;
    // cout<<gcdd->to_string()<<endl;
    // cout<<gcdd->get_size()<<endl;
    // UnlimitedInt* b=UnlimitedInt::mul(e,f);
    // UnlimitedInt* c=new UnlimitedInt("169");
    // UnlimitedRational* z = new UnlimitedRational(b,new UnlimitedInt("1"));
    // cout<<z->get_frac_str()<<endl;
    // UnlimitedRational* a = new UnlimitedRational(b,c);
    // cout<<a->get_frac_str()<<endl;
    // UnlimitedInt* n = UnlimitedInt::div(b,c);
    // cout<<n->to_string()<<endl;
    // UnlimitedRational* sum = UnlimitedRational::div(b,c);
    // cout<<"h"<<endl;
    // UnlimitedInt* x=new UnlimitedInt("49");
    // UnlimitedInt* y=new UnlimitedInt("100");
    // UnlimitedRational* n=new UnlimitedRational(x,y);
    // cout<<n->get_frac_str()<<endl;
    // cout<<sum->get_frac_str()<<endl;
    // cout<<"h"<<endl;
// }