namespace 一维数组
{
    using System;
    class Program
    {
        static void Main(string[] args)
        {
            int[] a = new int[] { 1, 2, 3, 4, 5 };
            int[] b = new int[5];
            Array.Copy(a, 1, b, 0, 3);
            for(int i = 0; i < 5; i++)
            {
                Console.WriteLine(b[i]);
            }
        }

    }
}

namespace 二维数组
{

}
