using System;

class 父亲
{
    public virtual void 打铁()
    {
        Console.WriteLine("父亲打铁练剑");
    }
}

class 儿子 : 父亲
{
    public override void 打铁()
    {
        Console.WriteLine("儿子打铁练剑");
    }
}

class Program
{
    static void Main(string[] args)
    {
        父亲 a = new 儿子();
        a.打铁();
    }
}