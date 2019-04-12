<center>C++总结：类的继承基础</center>

<center>2019-4-12</center>

###### 1. 类的继承

```c++
class 派生类名： 继承方式 基类1， 继承方式 基类2...
{
    派生类成员声明
}
```

基类的构造函数和析构函数不能被派生类继承。

如果派生类中出现了和基类中相同的函数（函数名，参数类型都相同），则基类的函数会被**隐藏**。

###### 2. 构造函数、析构函数

2.1 构造函数

如果无需对派生类使用参数初始化，可以不写构造函数。此时系统会隐性写一个默认构造函数，该函数会使用基类的默认构造函数对继承自基类的成员进行初始化，并调用类成员对象的默认构造函数对其进行初始化。

派生类构造函数的一般语法：

```c++
派生类名::派生类名(参数表):基类名1(该基类初始化参数), ... 基类名n(该基类初始化参数), 成员对象名1(该成员初始化参数), ..., 成员对象名m(该成员初始化参数)
{
    派生类函数体；
}
```

构造函数的执行顺序： 

        1.  按照继承时声明的基类顺序，调用各个基类的构造函数；
        2.  按照派生类中新增成员在类中声明的顺序，对各新增成员进行初始化；
        3.  执行派生类构造函数的函数体。

```c++
#include<stdio.h>
class Base1{
    public:
       Base1(int i){printf("Constructing Base1 %d\n",i);}
};

class Base2{
    public:
       Base2(int i){printf("Constructing Base2 %d\n",i);}
};

class Base3{
    public:
       Base3(){printf("Constructing Base3\n");}
};

class Derived: public Base1, public Base2, public Base3{
    public:
    Derived(int a, int b, int c, int d):Base1(a), member2(d), member1(c),Base2(b){     //这里的顺序并不影响构造函数执行顺序，另外Base3为默认构造函数，无需显式构造。
        printf("Constructing Derived\n");
    }
    private:
       Base1 member1;
       Base2 member2;
       Base3 member3;
};

int main(){
    Derived obj(1,2,3,4);
    return 0;
}

//程序运行结果
Constructing Base1 1
Constructing Base2 2
Constructing Base3
Constructing Base1 3
Constructing Base2 4
Constructing Base3
Constructing Derived
```



2.2 复制构造函数

如果开发人员为手动添加复制构造函数，在需要时系统会生成一个隐含的复制构造函数，该复制构造函数会自动调用基类的复制构造函数，然后将新增成员一一执行复制操作。

```c++
#include<cstdio>
#include<cmath>

class Point{
    public:
        Point(int xx, int yy):x(xx), y(yy){}
        Point(const Point &p);
        int getX(){return x;}
        int getY(){return y;}
    private:
        int x, y;
};

Point::Point(const Point &p){
            x = p.x;
            y = p.y;
}

class Line: public Point{
    public:
        Line(int x, int y);
        Line(Line &l);
        void show();
    private:
        double len;
};

Line::Line(int x, int y):Point(x,y){
            len = sqrt(x*x + y*y);
}

Line::Line(Line &l):Point(l){    //根据类型兼容规则，可用派生类对象可初始化基类的引用。
            int x,y;
            x = l.getX();
            y = l.getY();
            len = sqrt(x*x + y*y);
}

void Line::show(){
    printf("x: %d, y: %d, len: %.2f\n", this->getX(), this->getY(), len);
}

int main(){
    Line l1(3,4);
    Line l2(l1);
    l1.show();
    l2.show();
    return 0;
}

//程序运行结果
x: 3, y: 4, len: 5.00
x: 3, y: 4, len: 5.00
```



2.3 析构函数

派生类不会继承基类的析构函数。析构函数主要完成程序结束时的释放内存等收尾工作。如果开发人员不手动写析构函数，系统会隐式添加默认析构函数，需要注意的是析构函数没有输入参数。

析构函数调用时的执行顺序和构造函数刚好相反。

```c++
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

//程序运行结果
Constructing Base1 1
Constructing Base2 2
Constructing Base3
Constructing Base1 3
Constructing Base2 4
Constructing Base3
**------Constructing Derived------**
**------Destructing Derived------**
Destructing Base3
destruction Base2
Destructing Base1
Destructing Base3
destruction Base2
Destructing Base1
```



###### 3. 类型兼容规则

类型兼容规则即，在任何需要基类对象的地方，都可以使用公有派生类的对象来代替，具体包括以下几种情况

1.  派生类对象可隐含转换为基类对象

   ```c++
   class Derived: public Base{
       ...
   };
   
   int main(){
       Derived d;
       Base b = d;
   }
   ```

2. 派生类的对象可初始化基类的引用

   ```c++
   Derived d;
   Base &b = d;
   ```

3. 派生类指针可隐含转换为基类的指针

   ```c++
   Derived d;
   Base *pb = &d;
   ```





