using System;

namespace 命名空间名
{
    public class Customer { }
}

namespace a
{
    namespace b
    {
        public class 必须放在类里定义东西
        {
            public int x = 5;
        }
    }
}

namespace a.c
{
    public class 必须放在类里定义东西
    {
        public static int y = 10;
    }
}


namespace ns2
{
    using 命名空间名;
    using a.b;
    using System.Collections.Specialized;
     

    class Program
    {
        static void Main(string[] args)
        {
            //int 变量 = 10;
            //Console.WriteLine(变量);

            Customer cs = new Customer();

            必须放在类里定义东西 lei = new 必须放在类里定义东西();

            Console.WriteLine(lei.x);

            Console.WriteLine(a.c.必须放在类里定义东西.y);
        }
    }
}


