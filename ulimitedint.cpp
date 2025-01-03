/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
// #include<iostream>  //remove before submitting
// using namespace std;


UnlimitedInt::UnlimitedInt(){
    size = 0;
    sign = 1;
    capacity = 100;
    unlimited_int = new int[capacity];
}

UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}

UnlimitedInt::UnlimitedInt(string s){
    int i=0;
    while(s[i]){
        i++;
    }
    if(s[0]=='-'){
        size=i-1;
        sign=-1;
        capacity=size;
    }
    else{
        size=i;
        sign=1;
        capacity=size;
    }
    unlimited_int = new int[capacity];
    if(sign==1){
        for(int i=0;i<size;i++){
            unlimited_int[i]=s[size-i-1]-char('0');
        }
    }
    else{
        for(int i=1;i<=size;i++){
            unlimited_int[i-1]=s[size-i+1]-char('0');
        }
    }
}

UnlimitedInt::UnlimitedInt(int i){
    if(i==0){
        size=1;
    }
    else{
        int j=i;
        int s=0;
        while(j!=0){
            j=j/10;
            s++;
        }
        size=s;
    }
    if(i<0){
        sign=-1;
    }
    else{
        sign=1;
    }
    capacity=size;
    unlimited_int = new int[capacity];
    if(sign==1){
        if(i==0){
            unlimited_int[0]=0;
        }
        int j=i;
        int idx=0;
        while(j!=0){
            unlimited_int[idx]=j%10;
            j=j/10;
            idx++;
        }
    }
    else{
        int j=i;
        int idx=0;
        while(j!=0){
            unlimited_int[idx]=0-j%10;
            j=j/10;
            idx++;
        }
    }
    
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    unlimited_int=ulimited_int;
    capacity=cap;
    sign=sgn;
    size=sz;
}

int UnlimitedInt::get_size(){
    return size;
}

int* UnlimitedInt::get_array(){
    // for(int i=0;i<size;i++){
    //     cout<<unlimited_int[i]<<",";
    // }cout<<endl;
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    int sn1 = i1->get_sign();
    int sn2 = i2->get_sign();
    int* a1 = i1->get_array();
    int* a2 = i2->get_array();
    int sz1 = i1->get_size();
    int sz2 = i2->get_size();

    if((sn1==1 && sn2==1) || (sn1==-1 && sn2==-1)){
        UnlimitedInt* newint = new UnlimitedInt();
        newint->capacity=max(i1->size, i2->size)+1;
        int* a = newint->unlimited_int;
        delete[] a;
        a=nullptr;
        newint->unlimited_int = new int[newint->capacity];
        int car=0;
        int i=0;
        for(;i<min(sz1,sz2); i++){
            if(a1[i]+a2[i]+car>9){
                newint->unlimited_int[i]=(a1[i]+a2[i]+car)%10;
                newint->size++;
                car=1;
            }
            else{
                newint->unlimited_int[i]=(a1[i]+a2[i]+car);
                newint->size++;
                car=0;
            }
        }
        for(;i<max(sz1,sz2);i++){
            if(sz1>sz2){
                if(a1[i]+car>9){
                    newint->unlimited_int[i]=(a1[i]+car)%10;
                    newint->size++;
                    car=1;
                }
                else{
                    newint->unlimited_int[i]=(a1[i]+car);
                    newint->size++;
                    car=0;
                }
            }
            else{
                if(a2[i]+car>9){
                    newint->unlimited_int[i]=(a2[i]+car)%10;
                    newint->size++;
                    car=1;
                }
                else{
                    newint->unlimited_int[i]=(a2[i]+car);
                    newint->size++;
                    car=0;
                }
            }
            
        }
        if(car==1){
            newint->unlimited_int[i]=car;
            newint->size++;
        }
        if(sn1==1 && sn2==1){
            newint->sign=1;
        }
        else{
            newint->sign=-1;
        }
        return newint;
    }
    else if(sn1==-1 && sn2==1){
        i1->sign=1;
        UnlimitedInt* u = sub(i2, i1);
        i1->sign=-1;
        return u;
    }
    else{
        i2->sign=1;
        UnlimitedInt* u = sub(i1, i2);
        i2->sign=-1;
        return u;
    }
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    int sn1 = i1->get_sign();
    int sn2 = i2->get_sign();
    int* a1 = i1->get_array();
    int* a2 = i2->get_array();
    int sz1 = i1->get_size();
    int sz2 = i2->get_size();
    
    if((sn1==1 && sn2==1) || (sn1==-1 && sn2==-1)){
        UnlimitedInt* newint = new UnlimitedInt();
        newint->capacity=max(i1->capacity, i2->capacity);
        int* a = newint->unlimited_int;
        delete[] a;
        a=nullptr;
        newint->unlimited_int = new int[newint->capacity];

        int borr=0;
        int i=0;
        int flag=-1;
        if(sz1==sz2){
            for(int i=0;i<sz1;i++){
                if(a1[sz1-i-1]>a2[sz2-i-1]){
                    flag=1;
                    break;
                }
                else if(a2[sz1-i-1]>a1[sz2-i-1]){
                    flag=2;
                    break;
                }
            }
            if(flag==-1){
                flag=0;
            }
        }
        if(sz1>sz2 || flag==1){
            if(sn1==1 && sn2==1){
                newint->sign=1;
            }
            else{
                newint->sign=-1;
            }
            for(i;i<sz2;i++){
                if(a1[i]-a2[i]-borr<0){
                    newint->unlimited_int[i]=(a1[i]+10-a2[i]-borr);
                    newint->size++;
                    borr=1;
                }
                else{
                    newint->unlimited_int[i]=(a1[i]-a2[i]-borr);
                    newint->size++;
                    borr=0;
                }
            }
            for(i;i<sz1;i++){
                if(a1[i]-borr<0){
                    newint->unlimited_int[i]=a1[i]+10-borr;
                    newint->size++;
                    borr=1;
                }
                else{
                    newint->unlimited_int[i]=a1[i]-borr;
                    newint->size++;
                    borr=0;
                }
            }
            int k=i-1;
            while(newint->unlimited_int[k]==0){
                newint->size--;
                k--;
            }
        }
        else if(sz2>sz1 || flag==2){
            if(sn1==1 && sn2==1){
                newint->sign=-1;
            }
            else{
                newint->sign=1;
            }
            for(i;i<sz1;i++){
                if(a2[i]-a1[i]-borr<0){
                    newint->unlimited_int[i]=(a2[i]+10-a1[i]-borr);
                    newint->size++;
                    borr=1;
                }
                else{
                    newint->unlimited_int[i]=(a2[i]-a1[i]-borr);
                    newint->size++;
                    borr=0;
                }
            }
            for(i;i<sz2;i++){
                if(a2[i]-borr<0){
                    newint->unlimited_int[i]=a2[i]+10-borr;
                    newint->size++;
                    borr=1;
                }
                else{
                    newint->unlimited_int[i]=a2[i]-borr;
                    newint->size++;
                    borr=0;
                }
            }
            int k=i-1;
            while(newint->unlimited_int[k]==0){
                newint->size--;
                k--;
            }
        }
        else if(flag==0){
            newint->unlimited_int[0]=0;
            newint->size++;
        }  
        return newint;
    }
    else if(sn1==-1 && sn2==1){
        i1->sign=1;
        UnlimitedInt* y = add(i1, i2);
        y->sign=-1;
        i1->sign=-1;
        return y;
    }
    else{
        i2->sign=1;
        UnlimitedInt* y = add(i1, i2);
        y->sign=1;
        i2->sign=-1;
        return y;
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    int sn1 = i1->get_sign();
    int sn2 = i2->get_sign();
    int* a1 = i1->get_array();
    int* a2 = i2->get_array();
    int sz1 = i1->get_size();
    int sz2 = i2->get_size();
    UnlimitedInt* newint = new UnlimitedInt();
    newint->capacity=sz1+sz2;
    int* t = newint->unlimited_int;
    delete[] t;
    t=nullptr;
    newint->unlimited_int = new int[newint->capacity];
    for (int i = 0; i < newint->capacity; i++) {
        newint->unlimited_int[i] = 0;
    }
    int carr=0;
    int i=0;
    for(;i<sz1;i++){
        int carr2=0;
        int j=0;
        for(;j<sz2;j++){
            if(a1[i]*a2[j]+carr>9){
                if(newint->unlimited_int[i+j]+((a1[i]*a2[j]+carr)%10)+carr2>9){
                    newint->unlimited_int[i+j]+=((a1[i]*a2[j]+carr)%10)+carr2-10;
                    carr=(a1[i]*a2[j]+carr)/10;
                    carr2=1;
                }
                else{
                    newint->unlimited_int[i+j]+=((a1[i]*a2[j]+carr)%10)+carr2;
                    carr=(a1[i]*a2[j]+carr)/10;
                    carr2=0;
                }
            }
            else{
                if(newint->unlimited_int[i+j]+(a1[i]*a2[j]+carr)+carr2>9){
                    newint->unlimited_int[i+j]+=(a1[i]*a2[j]+carr)+carr2-10;
                    carr=0;
                    carr2=1;
                }
                else{
                    newint->unlimited_int[i+j]+=((a1[i]*a2[j]+carr)+carr2);
                    carr=0;
                    carr2=0;
                }
            }
        }
        if(carr2!=0){
            newint->unlimited_int[i+j]+=carr2;
            // cout<<"carryyyy: "<<carr2<<endl;
            carr2=0;
        }
        if(carr!=0){
            newint->unlimited_int[i+j]+=carr;
            carr=0;
        }
    }

    int k=sz1+sz2-1;
    int a=0;
    for(k;k>=0;k--){
        if(newint->unlimited_int[k]==0){
            a++;
        }
        else{
            break;
        }
    }
    newint->size=newint->capacity-a;

    if((sn1==1 && sn2==1) || (sn1==-1 && sn2==-1)){
        newint->sign=1;
    }
    else{
        newint->sign=-1;
    }
    return newint;
}

// UnlimitedInt* getMax(UnlimitedInt* i1, UnlimitedInt* i2){
//     int* a1 = i1->get_array();
//     int* a2 = i2->get_array();
//     int sz1 = i1->get_size();
//     int sz2 = i2->get_size();
//     int flag=-1;
//     if(sz1==sz2){
//         for(int i=0;i<sz1;i++){
//             if(a1[sz1-i-1]>a2[sz2-i-1]){
//                 flag=1;
//                 break;
//             }
//             else if(a2[sz1-i-1]>a1[sz1-i-1]){
//                 flag=2;
//                 break;
//             }
//         }
//         if(flag==-1){
//             flag=0;
//         }
//     }
//     if(sz1>sz2 || flag==1){
//         return i1;
//     }
//     else if(sz2>sz1 || flag==2){
//         return i2;
//     }
//     else
//         return i2;
// }

// bool isEqual(UnlimitedInt* i1, UnlimitedInt* i2){
//     int* a1 = i1->get_array();
//     int* a2 = i2->get_array();
//     int sz1 = i1->get_size();
//     int sz2 = i2->get_size();
//     int flag=-1;
//     if(sz1==sz2){
//         for(int i=0;i<sz1;i++){
//             if(a1[sz1-i-1]>a2[sz2-i-1]){
//                 flag=1;
//                 return false;
//             }
//             else if(a2[sz1-i-1]>a1[sz1-i-1]){
//                 flag=2;
//                 return false;
//             }
//         }
//         if(flag==-1){
//             flag=0;
//         }
//     }
//     if(flag==0){
//         return true;
//     }
//     else{
//         return false;
//     }
// }


// UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
//     int sn1 = i1->get_sign();
//     int sn2 = i2->get_sign();
//     int* a1 = i1->get_array();
//     int* a2 = i2->get_array();
//     int sz1 = i1->get_size();
//     int sz2 = i2->get_size();
//     UnlimitedInt* newint = new UnlimitedInt();
//     newint->capacity=max(sz1,sz2);
//     int* t = newint->unlimited_int;
//     delete[] t;
//     t=nullptr;
//     newint->unlimited_int = new int[newint->capacity];
//     UnlimitedInt* one = new UnlimitedInt(1);
//     UnlimitedInt* temp = new UnlimitedInt(0);
//     if((sn1==1 && sn2==1) || (sn1==-1 && sn2==-1)){
//         while(getMax(mul(i2,temp), i1)==i1){
//             temp=add(temp,one);
//         }
//         newint=sub(temp,one);
//         return newint;
//     }
//     else{
//         while(getMax(mul(i2,temp), i1)==i1){
//             temp=add(temp,one);
//         }
//         newint=sub(temp,one);
//         if(!isEqual(mul(newint, i2), i1)){
//             newint=add(newint, one);
//         }
//         newint->sign=-1;
//         return newint;
//     }

// }

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    int sz1 = i1->get_size();
    int sz2 = i2->get_size();
    int* a1 = i1->get_array();
    int* a2 = i2->get_array();
    int sgn = i1->get_sign()*i2->get_sign();
    UnlimitedInt* j2 = i2;
    if(i2->get_sign()==-1){
        j2->sign=1;
    }

    if(sz1>=sz2){

        int it=sz2-1;
        string s;
        int i=0;
        while(i<it){
            s+=std::to_string(a1[sz1-i-1]);
            i++;
        }

        string ans;
        UnlimitedInt* rem=nullptr;
        while(it<sz1){
            s+=std::to_string(a1[sz1-it-1]);
            UnlimitedInt* dividend = new UnlimitedInt(s);
            UnlimitedInt* a=nullptr;
            UnlimitedInt* b=nullptr;
            int it2=0;
            while(true){
                a = sub(dividend, j2);
                if(a->get_sign()==-1){
                    break;
                }
                it2++;
                // cout<<"here"<<endl;
                UnlimitedInt* bin = dividend;
                dividend=a;
                delete bin;
            }
            delete dividend;
            b = add(a,j2);
            delete a;

            ans+=std::to_string(it2);

            s.clear();
            for(int i=0;i<b->get_size();i++){
                s+=std::to_string(b->get_array()[b->get_size()-i-1]);
            }
            if(s=="0"){
                s.clear();
            }

            rem=b;

            it++;
        }

        if(ans.size()==1 && ans[0]==0){
            if(sgn==1){
                return new UnlimitedInt("0");
            }
            else{
                return new UnlimitedInt("-1");
            }
        }

        int k=0; //remove zeroes
        if(ans.length()>1){
        for(;k<ans.length();k++){
            if(ans[0]=='0'){
                ans.erase(ans.begin());
            }
            else{
                break;
            }
        }
        }

        UnlimitedInt* c = new UnlimitedInt(ans);
        if(sgn==1){
            c->sign=1;
        }
        else{
            if(i1->get_sign()==1){
                j2->sign=1;
            }
            if(rem->to_string()=="0"){
                c->sign=-1;
            }
            else{
            UnlimitedInt* one = new UnlimitedInt("1");
            UnlimitedInt* bin = c;
            c=add(c,one);
            c->sign=-1;
            delete bin;
            delete one;
            }
        }
        
        j2=nullptr;
        return c;

    }
    else{
        if(sgn==1){
            return new UnlimitedInt("0");
        }
        else{
            return new UnlimitedInt("-1");
        }
    }
}


UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    // UnlimitedInt* newint=sub(i1, (mul(i2, (div(i1,i2)))));
    UnlimitedInt* d = div(i1,i2);
    UnlimitedInt* m = mul(i2,d);
    UnlimitedInt* s = sub(i1,m);
    UnlimitedInt* ans = new UnlimitedInt(s->to_string());
    delete d;
    delete m;
    delete s;
    return ans;
}

string UnlimitedInt::to_string(){
    string ans;
    if(sign==1){
        for(int i=0;i<size;i++){
            ans+=std::to_string(unlimited_int[size-i-1]);
        }
    }
    else{  
        ans='-';
        for(int i=1;i<=size;i++){
            ans+=std::to_string(unlimited_int[size-i]);
        }
    }
    return ans;
}

// int main(){
//     UnlimitedInt* a = new UnlimitedInt("100001");
//     cout<<a->to_string()<<endl;
    // cout<<a.get_size()<<endl;
    // UnlimitedInt* e=new UnlimitedInt("2");
    // UnlimitedInt* f=new UnlimitedInt("8412352325467978348796786756785679878098760768089077");
    // UnlimitedInt* b=new UnlimitedInt("924323418323423514356568776898079567789089790078984");
    // UnlimitedInt* c=new UnlimitedInt("379");
    // UnlimitedInt* b = new UnlimitedInt("-234");
    // cout<<isEqual(a,b)<<endl;
    // cout<<b.get_size()<<endl;
    // UnlimitedInt* sum = UnlimitedInt::div(a,e);
    // cout<<sum->to_string()<<endl;
    // cout<<sum->get_size()<<endl;
    // cout<<sum->get_sign()<<endl;
    // for(int i=0;i<sum->get_size();i++){
    //     cout<<sum->get_array()[i];
    // }cout<<endl;                           
    
    // cout<<a.get_size()<<endl;
    // cout<<a.get_capacity()<<endl;
    // cout<<a.get_sign()<<endl;
    // a.get_array();

// }

