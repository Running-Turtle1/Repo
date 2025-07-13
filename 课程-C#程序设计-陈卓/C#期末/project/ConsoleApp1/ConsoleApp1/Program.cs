using System;
using System.Collections.Generic;


class Solution
{
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 
     * @return int整型
     */ 
    void test(int[] f)
    {
        f[1] = 0;
    }
    public int Fibonacci(int n)
    {
        // write code here
        int[] f = new int[n + 1];
        for (int i = 0; i <= n; i++)
        {
            f[i] = -1;
        }
        f[1] = 1, f[2] = 2;
        test(f);
        return f[1];
    }
}

class Program
{
    static void Main(string[] args)
    {
        Solution solution = new Solution();
        Console.WriteLine(solution.Fibonacci(2));
    }
}