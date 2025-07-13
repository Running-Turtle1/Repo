
class Test
{
    static void Main()
    {
        string firstName = "王";
        string lastName = "小小";
        int a = 6;
        string fullName = string.Format("我的名字是{0} {1} {2}。",  a, firstName, lastName  );
        string str = string.Format("我的名字是");



        Console.WriteLine(fullName);// 我的名字是王小小
        string FullName = $"我的名字是{firstName} {lastName}。";
        Console.WriteLine(FullName);
    }
}