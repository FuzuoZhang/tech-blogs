#include<stdio.h>

class Base1{
    public:
       Base1(int i){printf("Constructing Base1 %d\n",i);}
       ~Base1(){printf("Destructing Base1\n");}
};

class Base2{
    public:
       Base2(int i){printf("Constructing Base2 %d\n",i);}
       ~Base2(){printf("destruction Base2\n");}
};

class Base3{
    public:
       Base3(){printf("Constructing Base3\n");}
       ~Base3(){printf("Destructing Base3\n");}
};

class Derived: public Base1, public Base2, public Base3{
    public:
    Derived(int a, int b, int c, int d):Base1(a), member2(d), member1(c),Base2(b){
        printf("**------Constructing Derived------**\n");
    }
    ~Derived(){
        printf("**------Destructing Derived------**\n");}
    
    private:
       Base1 member1;
       Base2 member2;
       Base3 member3;
};

int main(){
    Derived obj(1,2,3,4);
    return 0;
}

