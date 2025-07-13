using System;

class Learn1
{
    public static void test()
    {
        DateTime dateTime1 = DateTime.Now;
        Console.WriteLine(dateTime1.ToString());

        DateTime dateTime2 = DateTime.Parse("2024/6/23 08:2:15");
        Console.WriteLine(dateTime2.ToString());
    }
}
class Program
{
    static void Main(string[] args)
    {
        Learn1.test();
    }
}