using System;

class Program
{
    //public static void test()
    //{
    //    enum y = {A, B };
    //}
    public static class test
    {
        enum y {A, B };
    }
    enum x { Spring, Summer, Autumn, Winter };
    static void Main(string[] args)
    {
        Console.WriteLine((x)10); // 10
        Console.WriteLine((int)x.Winter);
    }
}