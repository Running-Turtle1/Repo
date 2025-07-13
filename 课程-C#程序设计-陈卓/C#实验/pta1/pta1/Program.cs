using System;
using System.Collections.Generic;
using System.Security.Cryptography;

class Que1 // 浮点数和差商积
{
    public static void sol()
    {
        double db1 = double.Parse(Console.ReadLine());
        double db2 = double.Parse(Console.ReadLine());
        Console.WriteLine("{0} {1} {2} {3}", db1 + db2, db1 - db2, db2 * db2, db1 / db2);
    }
}

class Que2 // 孪生素数
{
    private static bool isPrime(int x)
    {
        if (x == 1) return false; // 特判 1 不是素数
        for(int i = 2; i <= x / i; i++)
        {
            if(x % i == 0)
            {
                return false;
            }
        }
        return true;
    }
    public static void sol()
    {
        string[] input = Console.ReadLine().Split(' ');
        int l = int.Parse(input[0]);
        int r = int.Parse(input[1]);
        if(l >= r)
        {
            Console.WriteLine("Illegal Inputting");
            return;
        }
        List<int> lis = new List<int>();
        for(int i = l; i <= r; i++)
        {
            if (isPrime(i))
            {
                lis.Add(i);
            }
        }
        for(int i = 0; i + 1 < lis.Count; i++) // 2 3 不符合要求, 其余素数全是奇数, 相差一定 >= 2
        {
            if (lis[i + 1] - lis[i] == 2)
            {
                Console.WriteLine(lis[i] + " " + lis[i + 1]);
            }
        }
    }
}

class Que3 // 成绩排序
{
    struct Student
    {
        public string name;
        public int score;
    }
    public static void sol()
    {
        int n = int.Parse(Console.ReadLine());
        Student[] students = new Student[n];
        for(int i = 0; i < n; i++)
        {
            string[] input = Console.ReadLine().Split(' ');
            students[i] = new Student();
            students[i].name = input[0];
            students[i].score = int.Parse(input[1]);
        }
        int maxScore = -1000;
        for(int i = 0; i < n; i++)
        {
            maxScore = Math.Max(maxScore, students[i].score);
        }
        List<string> res = new List<string>();
        for(int i = 0; i < n; i++)
        {
            if (students[i].score == maxScore)
            {
                res.Add(students[i].name);
            }
        }
        Console.WriteLine(maxScore);
        for(int i = 0; i < res.Count; i++)
        {
            Console.Write(res[i]);
            if (i != res.Count - 1) Console.Write(' ');
        }
    }
}

class Que4 // 分支判断
{
    public static void sol()
    {
        double h, w, t;
        h = double.Parse(Console.ReadLine());
        w = double.Parse(Console.ReadLine());
        t = w / h / h;
        if(t < 18)
        {
            Console.WriteLine("thin");
        }
        else if (t >= 18 && t < 25)
        {
            Console.WriteLine("standard");
        }
        else if (t >= 25 && t < 27)
        {
            Console.WriteLine("little fat");
        }
        else
        {
            Console.WriteLine("fat");
        }
    }
}

class Que5 // 判断闰年
{
    public static void sol()
    {
        int y;
        y = int.Parse(Console.ReadLine());
        if((y % 4 == 0 && y % 100 != 0 ) || y % 400 == 0)
        {
            Console.WriteLine("Yes");
        }
        else
        {
            Console.WriteLine("No");
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        Que4.sol();
    }
}