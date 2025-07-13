using System;

class A
{
    public int age = 0;
    public int Age
    {
        get { if(age < 50) age = 18; return age; }
        set { age = value * 10; }
    }
}

class Program
{
    static void Main()
    {
        A a = new A();
        Console.WriteLine(a.age);
        Console.WriteLine(a.Age);
        a.age = 12;
        Console.WriteLine(a.age);
        a.Age = 20;
        Console.WriteLine(a.Age);
    }
}