# Prac1

## 描述

大家都知道斐波那契数列，现在要求输入一个正整数 n ，请你输出斐波那契数列的第 n 项。

斐波那契数列是一个满足 fib(x)={1fib(x−1)+fib(x−2)​x=1,2x>2​ 的数列

数据范围：1≤n≤40

要求：空间复杂度 O(1)，时间复杂度 O(n) ，本题也有时间复杂度 O(logn) 的解法

```csharp
using System;
using System.Collections.Generic;


class Solution {
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 
     * @return int整型
     */
    int Fib(int n, int[] f){
        if(f[n] != -1) return f[n];
        return Fib(n - 1, f) + Fib(n - 2, f);
    }
    public int Fibonacci (int n) {
        // write code here
        int[] f = new int[n + 1];
        for(int i = 0; i <= n; i ++){
            f[i] = -1;
        }
        f[1] = 1;
        f[2] = 1;
        return Fib(n, f); 
    }
}
```

上面的代码漏掉了记忆化搜索，多了很多重复子计算 ：

```csharp
using System;
using System.Collections.Generic;


class Solution {
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 
     * @return int整型
     */
    int Fib(int n, int[] f){
        if(f[n] != -1) return f[n];
        return f[n] = Fib(n - 1, f) + Fib(n - 2, f);
    }
    public int Fibonacci (int n) {
        // write code here
        int[] f = new int[n + 1];
        for(int i = 0; i <= n; i ++){
            f[i] = -1;
        }
        f[1] = 1;
        f[2] = 1;
        return Fib(n, f); 
    }
}
```

事实上， $O(\log n)$ 时间复杂度内求斐波那契数列需要用到矩阵快速幂。

还要注意下面，

```csharp
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
```

传数组默认传引用，还要注意，值类型有很多，引用类型只有类，字符串，对象，即 class，string，object ；值类型就多了，int，double，long，struct。

# Prac2

## 描述

一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个 n 级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

数据范围：1≤n≤40

要求：时间复杂度：O(n) ，空间复杂度： O(1)

```cs
f[1] = 1, f[2] = 2;
```

这么写在 c# 里面居然是错误的

```cs
using System;
using System.Collections.Generic;


class Solution {
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param number int整型 
     * @return int整型
     */
    public int jumpFloor (int number) {
        // write code here
        int[] f = new int[number + 2];
        f[1] = 1;
        f[2] = 2;
        for(int i = 3; i <= number; i ++){
            f[i] = f[i - 1] + f[i - 2];
        }
        return f[number];
    }
}
```

# Prac3

## 描述

对于一个长度为 n 字符串，我们需要对它做一些变形。

首先这个字符串中包含着一些空格，就像"Hello World"一样，然后我们要做的是把这个字符串中由空格隔开的单词反序，同时反转每个字符的大小写。

比如"Hello World"变形后就变成了"wORLD hELLO"。

数据范围: 1≤n≤106 , 字符串中包括大写英文字母、小写英文字母、空格。  

进阶：空间复杂度 O(n) ， 时间复杂度 O(n)

```cs
using System;
using System.Collections.Generic;
using System.Text;


class Solution {
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param s string字符串 
     * @param n int整型 
     * @return string字符串
     */
    public string trans (string s, int n) {
        // write code here
        string[] words = s.Split(' ');
        StringBuilder res = new StringBuilder();
        for(int i = words.Length - 1; i >= 0; i --){
            string word = new string(words[i]);
            StringBuilder reverseWord = new StringBuilder();
            foreach(char c in word){
                if(char.IsLower(c)){
                    reverseWord.Append(char.ToUpper(c));
                }
                else if(char.IsUpper(c)){
                    reverseWord.Append(char.ToLower(c));
                }
            }
            if(i != 0) reverseWord.Append(' ');
            res.Append(reverseWord);
        }
        return res.ToString();
    }
}
```

# Prac4

## 描述

给你一个大小为 n 的字符串数组 strs ，其中包含n个字符串 , 编写一个函数来查找字符串数组中的最长公共前缀，返回这个公共前缀。

数据范围： 0≤n≤5000， 0≤len(strsi​)≤5000

进阶：空间复杂度 O(1)，时间复杂度 O(n∗len)

```cs
using System;
using System.Collections.Generic;
using System.Text;

class Solution {
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param strs string字符串一维数组 
     * @return string字符串
     */
    bool check(int p, List<string> strs){
        if(strs[0].Length - 1 < p) return false;
        char x = strs[0][p];
        foreach(string s in strs){
            if(s.Length - 1 < p || s[p] != x) return false;
        }
        return true;
    }
    public string longestCommonPrefix (List<string> strs) {
        // write code here
        if(strs.Count == 0) return new string("");
        StringBuilder res = new StringBuilder();
        for(int i = 0; i <= 5000; i ++){
            if(check(i, strs)){
                res.Append(strs[0][i]);
            }
        }
        return res.ToString();
    }
}
```

# Prac5

判断 IPV4 跟 IPV6 地址

```cs
using System;
using System.Collections.Generic;


class Solution {
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 验证IP地址
     * @param IP string字符串 一个IP地址字符串
     * @return string字符串
     */
    bool check1(string IP){
        if(IP.Contains(".") == false) return false;
        string[] strs = IP.Split('.');
        for(int i = 0; i < strs.Length; i ++){
            if(strs[i].Length == 0) return false;
            if(strs[i][0] == '0' && strs[i].Length != 1) return false;
            for(int j = 0; j < strs[i].Length; j ++){
                if(char.IsLetter(strs[i][j]) ) return false;
            }
            if(int.Parse(strs[i]) > 255) return false;
        }
        return true;
    }
    bool check2(string IP){
        if(IP.Contains(":") == false) return false;
        string[] strs = IP.Split(':');
        for(int i = 0; i < strs.Length; i ++){
            if(strs[i].Length > 4 || strs[i].Length == 0) return false;
            for(int j = 0; j < strs[i].Length; j ++){
                if(char.IsLower(strs[i][j]) && strs[i][j] > 'f') return false;
                if(char.IsUpper(strs[i][j]) && strs[i][j] > 'F') return false;
            }
        }
        return true;
    }
    public string solve (string IP) {
        // write code here
        if(check1(IP)) return "IPv4";
        if(check2(IP)) return "IPv6";
        return "Neither";
    }
}
```

```cs
strs.Contains()
int.Parse(string s)
char.IsLower()
```

# Prac6

实现字符串加法

char-generatice-pre-trained-transformer

```cs
using System;
using System.Collections.Generic;
using System.Text;

class Solution {
    /**
     * 计算两个数之和
     * @param s string字符串 表示第一个整数
     * @param t string字符串 表示第二个整数
     * @return string字符串
     */
    string ReverseString(string str) {
        char[] chs = str.ToCharArray();
        Array.Reverse(chs);
        return new string(chs);
    }
    
    public string solve(string s, string t) {
        s = ReverseString(s);
        t = ReverseString(t);
        
        int n = s.Length;
        int m = t.Length;
        
        StringBuilder res = new StringBuilder();
        int carry = 0;
        
        for (int i = 0; i < Math.Max(n, m); i++) {
            int digitS = (i < n) ? s[i] - '0' : 0;
            int digitT = (i < m) ? t[i] - '0' : 0;
            
            int sum = digitS + digitT + carry;
            carry = sum / 10;
            int digit = sum % 10;
            
            res.Append((char)(digit + '0')); // Convert digit to character and append to result
        }
        
        if (carry > 0) {
            res.Append((char)(carry + '0')); // Append the final carry if any
        }
        
        // Reverse the result to get the correct order
        char[] resultChars = res.ToString().ToCharArray();
        Array.Reverse(resultChars);
        
        return new string(resultChars);
    }
}

```

Modified Version

```cs
using System;
using System.Collections.Generic;
using System.Text;

class Solution {
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 计算两个数之和
     * @param s string字符串 表示第一个整数
     * @param t string字符串 表示第二个整数
     * @return string字符串
     */
    string rev(string str){
        char[] chs = str.ToCharArray();
        Array.Reverse(chs);
        return new string(chs);
    }
    public string solve (string s, string t) {
        // write code here
        // char.Parse("1");
        int n = s.Length;
        int m = t.Length;
        s = rev(s);
        t = rev(t);
        int carry = 0;
        StringBuilder res = new StringBuilder();
        for(int i = 0; i < n || i < m || carry != 0; i ++){
            int tmp = 0;
            if(i < n) tmp += s[i] - '0';
            if(i < m) tmp += t[i] - '0';
            if(carry == 1){
                tmp ++; 
                carry = 0;
            }
            if(tmp >= 10){
                carry = 1;
                tmp %= 10;
            }
            res.Append((char)(tmp + '0'));
        }
        return rev(res.ToString());
    }
}
```

There are the follwing conditions to note :

Firstly，in c#, integers types (such as int, long, etc.) can not be directly converted to boolean type(bool)

Secontly, int.Prase()，its arguments is a string type ; for char.Pasrse(), its argument is a string and its length has to be  exactly 1 ，if we need to Convert a char to int, or in the contraty , for exmple , we has a char x, int y = x - '0' ; char x = (char)(y + '0')
