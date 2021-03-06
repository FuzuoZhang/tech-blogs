<center>C++总结：类的访问控制</center>

<center>2019-4-12</center>

###### 1. 类的继承

```c++
class 派生类名： 继承方式 基类1， 继承方式 基类2...
{
    派生类成员声明
}
```

基类的构造函数和析构函数不能被派生类继承。



###### 2.访问控制

public: 公有继承

- 派生类内：基类的公有成员和保护成员在派生类中的访问属性不变，仍作为派生类的公有成员和保护成员，而基类的私有成员不可被派生类成员直接访问。
- 派生类外：通过派生类的对象只可直接访问基类的公有成员。

protected: 保护继承

- 派生类内：基类的公有成员和保护成员作为派生类的保护成员，可被派生类成员访问，而基类的私有成员不可被派生类成员直接访问。
- 派生类外：通过派生类的对象不可直接访问基类的任何成员。

private: 私有继承

- 派生类内：基类的公有成员和保护成员作为派生类的私有成员，而基类的私有成员不可被派生类成员直接访问。
- 派生类外：通过派生类的对象不可直接访问基类的任何成员。

综上：类成员的三种访问属性，public、protected、private的访问范围逐渐降低，而且在继承时是向下继承的，比如对于protected类型，通过public或者protected方式继承都是作为派生类的protected成员，而若通过private方式继承只作为派生类的private成员。<font color = "#5654a2">概括这三种访问属性对于基类成员的控制作用，public成员将访问权限延伸到对象，protected成员将访问权限延伸到派生类内，private成员将访问权限控制在类内。</font>

