# C#期末

1、面向对象编程的特征 ：抽象、继承、封装、多态。

2、值类型和引用类型

![](C:\Users\95432\Desktop\C%23期末\pic\2.png)

![](C:\Users\95432\Desktop\C%23期末\pic\3.png)

3、所有数据类型的基类是 Object

4、异常发生在<font color="red">运行</font>时

5、C#中，回车字符对应的转义字符串为 `\r`  ；换行对应的转义字符为 `\n` 

6、类的析构函数的作用是 : <u>删除对象创建的所有对象</u>

7、在C#程序中，入口函数的正确声明为 : `static void Main(){……}` 

8、.NET框架的两个主要组件是 `公共语言运行时` 和 `.NET Framework 类库` 

9、C#中声明命名空间使用的关键字是 ____namespace________，导入命名空间使用的关键字是

_____using_______。

10、当类实例化时首先执行的是_构造____函数；当实例从内存中销毁前最后执行的是_ **析构** 

函数。

11、C#中实现循环的语句主要有 ___for___、__while____、__foreach____。

12、什么是静态方法和实例方法，请举例说明。

> 静态方法用 static 修饰，非静态方法不用 static 修饰。
> 
> 例如 :
> 
> ```csharp
> using System;
> 
> public class A{
>     public static void F1(){
>         Console.WriteLine("F1()");
>     }
>     public void F2(){
>         Console.WriteLine("F2()");
>     }
> }
> 
> class Program{
>     static void Main(string[] args){
>         A.F1();
>         A a = new A();
>         a.F2();
>     }
> }  
> ```

13、什么是装箱，什么是拆箱请举例说明。

> 装箱 ：将值类型隐式转换为引用类型。
> 
> 例如：int i=2008;object o=i;
> 
> 拆箱：将引用类型隐式转换为值类型。
> 
> 例如：int i=2008;object o=i; int j=(int)o;

14、什么是“托管代码” 什么是“非托管代码”。

> 以公用语言运行库为目标的代码为“托管代码”。
> 
> 不以公用语言运行库为目标的代码为“非托管代码”。

15、你对面向对象程序设计的理解

![](C:\Users\95432\Desktop\C%23期末\pic\4.png)

16、ref 与 out

![](C:\Users\95432\Desktop\C%23期末\pic\5.png)

 
