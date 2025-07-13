using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Globalization;
using System.Runtime.InteropServices;
using System.Security.Cryptography;

class Que1
{
    private static void print(List<double> nums)
    {
        for (int i = 0; i < nums.Count; i++)
        {
            Console.Write(nums[i]);
            if (i != nums.Count - 1)
            {
                Console.Write(' ');
            }
        }
        Console.WriteLine();
    }
    public static void sol()
    {
        int n = int.Parse(Console.ReadLine());
        List<double> nums = new List<double>();
        for (int i = 0; i < n; i++)
        {
            nums.Add(double.Parse(Console.ReadLine()));
        }

        nums.Sort();
        print(nums);

        nums.Reverse();
        print(nums);
    }
}

class Que2
{
    public static void sol()
    {
        int cnt = 0;
        int a, b, c, d;
        string[] input = Console.ReadLine().Split(' ');
        a = int.Parse(input[0]);
        b = int.Parse(input[1]);
        c = int.Parse(input[2]);
        d = int.Parse(input[3]);
        for(int i = a; i <= b; i++)
        {
            if(i % c == 0 && i % d != 0)
            {
                cnt++;
                Console.Write(i);
                if(cnt == 5)
                {
                    cnt = 0;
                    Console.WriteLine();
                }
                else
                {
                    Console.Write(' ');
                }
            }
        }
    }
}

class Que3
{
    public static void sol()
    {
        List<KeyValuePair<string, int>> lis = new List<KeyValuePair<string, int>>();
        int n = int.Parse(Console.ReadLine());
        for(int i = 0; i < n; i++)
        {
            string[] input = Console.ReadLine().Split(' ');
            lis.Add(new KeyValuePair<string, int>(input[0], int.Parse(input[1])));
        }
        lis.Sort((x, y) =>
        {
            if (x.Value != y.Value)
            {
                return y.Value.CompareTo(x.Value);
            }
            else
            {
                return x.Key.CompareTo(y.Key);
            }
        });

        for (int i = 0; i < lis.Count; i++)
        {
            List<string> tmp = new List<string>();
            int j = i;
            while (j < lis.Count && lis[j].Value == lis[i].Value)
            {
                tmp.Add(lis[j].Key);
                j++;
            }
            for (int k = 0; k < tmp.Count; k++)
            {
                Console.Write(tmp[k]);
                if (k != tmp.Count - 1)
                {
                    Console.Write(' ');
                }
                else
                {
                    Console.WriteLine();
                }
            }
            i = j - 1;
        }
    }    
}          

class Que4
{
    public static void sol()
    {
        int n = int.Parse(Console.ReadLine());
        string[] input = Console.ReadLine().Split(' ');
        int m = int.Parse(Console.ReadLine());
        Console.WriteLine(input[m % n]);
    }
}


class Que5
{
    private static long GenerateNum(int len, int a)
    {
        long t = 0;
        for(int i = 0; i < len; i++)
        {
            t = t * 10 + a;
        }
        return t;
    }
    public static void sol()
    {
        int n = int.Parse(Console.ReadLine());
        int a = int.Parse(Console.ReadLine());
        long res = 0;
        for (int i = 1; i <= n; i++)
        {
            // Console.WriteLine(GenerateNum(i, a));
            res = (res + GenerateNum(i, a));
        }
        Console.WriteLine(res);
    }
}

class Que6
{
    public static void sol()
    {
        string s = Console.ReadLine();
        for(int i = 0, j = s.Length - 1; i <= j; i ++, j--)
        {
            if (s[i] != s[j])
            {
                Console.WriteLine("No");
                return;
            }
        }
        Console.WriteLine("Yes");
    }
}

class Program
{
    static void Main(string[] args)
    {
        Que6.sol();
    }
}