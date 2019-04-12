#### <center>C++总结：类基础</center>
<center>2019-4-10</center>
<br>

###### 1. 构造函数
构造函数在对象被创建时系统自动调用。默认构造函数可以有系统默认产生，无输入参数。
1.1 成员变量为基本类型

```c++
class Point{
public:
   Point(int xx, int yy);
...
private: 
   int x, y;
};

Point::Point(int xx, int yy){
    x = xx;
    y = yy;
}
```

1.2 类的组合
当所定义的类内存在其他类的对象作为成员时，在创建类的对象时，类的内嵌对象成员将首先被自动创建，即先调用内嵌对象的构造函数。若有多个类成员变量，创建的顺序为：按照内嵌对象在组合类的定义中出现的顺序进行创建（执行构造函数），最后执行本类构造函数的函数体。

```c++
class Line{
public:
    Line(Point xp1, Point xp2);
    ...
private:
    Point p1, p2;
    double len;
};

Line::Line(Point p1, Point p2):p1(xp1), p2(xp2){
    double x = static_cast<double>(p1.getX() - p2.getX());
    double y = static_cast<double>(p1.getY() - p2.getY());
    len = sqrt(x*x + y*y);
```
###### 2. 复制构造函数
复制构造函数即将一个已有类的对象的数据成员的值都复制到新建立的对象中。**复制构造函数的形参为类对象的引用**。
```c++
class Point{
public:
   Point(int x, int y):x(x),y(y){;}  
   ~Point() {}
   Point(Point &p);  //复制构造函数

private:
  int x, y;
 };

Point::Point(Point & p){
    x = p.x;
    y = p.y;
}
```
需要调用复制构造函数的三种情况：
1） 用类的一个对象去初始化该类的另一个对象时；
```c++
Point a(1,2);
Point b(a);    //调用复制构造函数
Point c = a;   //调用复制构造函数
```
2)   若函数的形参为类的对象，调用函数时，实参到形参的值传递；

```c++
void fun(Point p){...}

int main(){
   Point a(1,2);
   f(a);    //调用复制构造函数
   return 0; 
}
```
3)   若函数的返回值为类的对象，函数执行完成返回调用者时；
```c++
Point fun(){
  Point a(1,2);
  return a;
}

int main(){
  Point b;
  b = fun();   //编译系统在主函数创建一个临时对象接收来自函数的返回值，此时调用复制构造函数；
  return 0; 
}
```

###### 3. 析构函数
用来完成对象被删除前的一些清理工作，被系统自动调用。**析构函数不接受任何参数**。和构造函数一样，系统可以自动生成一个函数体为空的隐含析构函数。
```c++
class Point{
public:
    Line(int x, int y);
    ~Line() {}    //析构函数
    ...
private:
    int x, y;
};


```
----------
----

一个基本类定义：
```c++
class Point{
public:
   Point(int x, int y):x(x),y(y){;}  //在类定义内实现的函数为内联函数
   ~Point() {}
   Point(Point &p);  //复制构造函数
   void showPoint();

private:
  int x, y;
 };
```

成员函数的实现：
```c++
Point::Point(Point & p){
    x = p.x;
    y = p.y;
}

void showPoint(){
    printf("x:%d, y:%d\n", x, y);
}
```