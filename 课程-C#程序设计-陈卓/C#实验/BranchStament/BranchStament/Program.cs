using System;

class Program
{
    static void Main(string[] args)
    {
        int x = int.Parse(Console.ReadLine());
        switch(2 * x)
        {
            case 2:
                Console.WriteLine("2"); Console.WriteLine("2");
                break;

            case 4:
                Console.WriteLine("4"); Console.WriteLine("4");
                break;

            case 6:
                Console.WriteLine("6"); Console.WriteLine("6");
                break;
            default:
                Console.WriteLine("default");
                break;
        }
    }
}