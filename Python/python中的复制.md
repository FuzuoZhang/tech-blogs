###### python中的拷贝

**浅拷贝：**对基本数据类型进行值传递，对引用数据类型进行引用传递般的拷贝，此为浅拷贝。

**深拷贝：**对基本数据类型进行值传递，对引用数据类型，创建一个新的对象，并复制其内容，此为深拷贝。

在python中有三种复制方式：

- 直接赋值：`b = a` ， 这种方式实质上为引用，即内存上b和a表示同一块内存的内容。
- 浅拷贝：`b = copy.copy(a)`或`b = a.copy()`， 将父对象a拷贝到b，但是父对象内部的子对象拷贝的是引用。
- 深拷贝：`b = copy.deepcopy(a)`，将父对象a和a内部的子对象都拷贝到b中，a和b在内存上相互独立。

在[菜鸟教程](<http://www.runoob.com/w3cnote/python-understanding-dict-copy-shallow-or-deep.html>)中给了关于上面三种很形象的图示：

![](python-copy_1.jpg)

![](python-copy_2.jpg)

![](python-copy_3.jpg)

```python
import copy

a = [1,2,3,['a','b']]
b = a                     #引用
c = copy.copy(a)          #浅拷贝，将a子对象['a','b']的引用传递给c，此时a[3]和c[3]的地址不同，但是它们指向了同一块内存的内容。
d = copy.deepcopy(a)      #深拷贝

a.append(5)
print(" a:",a,"\n","b:",b,"\n","c:",c,"\n","d:",d)
'''
 a: [1, 2, 3, ['a', 'b'], 5] 
 b: [1, 2, 3, ['a', 'b'], 5] 
 c: [1, 2, 3, ['a', 'b']] 
 d: [1, 2, 3, ['a', 'b']]
'''

a.insert(3,4)
a[0] = 0
print(" a:",a,"\n","b:",b,"\n","c:",c,"\n","d:",d)
'''
 a: [0, 2, 3, 4, 4, ['a', 'b', 'c'], 5, 5] 
 b: [0, 2, 3, 4, 4, ['a', 'b', 'c'], 5, 5] 
 c: [1, 2, 3, ['a', 'b', 'c']] 
 d: [1, 2, 3, ['a', 'b']]
'''

a[4].append('c')   
print(" a:",a,"\n","b:",b,"\n","c:",c,"\n","d:",d)
'''
 a: [0, 2, 3, 4, ['a', 'b', 'c'], 5] 
 b: [0, 2, 3, 4, ['a', 'b', 'c'], 5] 
 c: [1, 2, 3, ['a', 'b', 'c']] 
 d: [1, 2, 3, ['a', 'b']]
'''

a[4] = ['a','b']   #将a[4]的对象改变，此时c[3]不再是a[4]的引用，二者相互独立
a[4].append('x')
c[3].append('y')
print(" a:",a,"\n","b:",b,"\n","c:",c,"\n","d:",d)
```

```python
import copy

x = [[1,2,3],[4,5,6]]
y = copy.copy(x)
z = copy.deepcopy(x)

x[0][0] = 0
x[0].append(4)
print(" x:",x,"\n","y:",y,"\n","z:",z)
'''
 x: [[0, 2, 3, 4], [4, 5, 6]] 
 y: [[0, 2, 3, 4], [4, 5, 6]] 
 z: [[1, 2, 3], [4, 5, 6]]
'''

y[1] = [4,5]
y[1].append(7)
x[1][2] = 8
z[0][0] = 10
print(" x:",x,"\n","y:",y,"\n","z:",z)
'''
 x: [[0, 2, 3, 4], [4, 5, 8]] 
 y: [[0, 2, 3, 4], [4, 5, 7]] 
 z: [[10, 2, 3], [4, 5, 6]]
'''
```



###### numpy中的拷贝

- 直接复制：`b = a`
- 视图（类似浅拷贝，但不完全相同） `b = a.view()`，常被用来改变原数组a的类型 
- 深拷贝`b = a.copy()`



----

参考资料：

【1】菜鸟教程：http://www.runoob.com/w3cnote/python-understanding-dict-copy-shallow-or-deep.html

【2】numpy文档（视图）：<https://www.numpy.org.cn/user_guide/quickstart_tutorial/copies_and_views.html>

【3】numpy文档（深拷贝）：<https://www.numpy.org.cn/user_guide/quickstart_tutorial/deep_copy.html>

【4】博客：<https://www.jessicayung.com/numpy-views-vs-copies-avoiding-costly-mistakes/>