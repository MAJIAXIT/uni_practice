sealed class Carpet : Vehicle
{
    public static new string Type = "Carpet";
    private string pattern;
    public Carpet() : base()
    => pattern = "";
    public Carpet(string brnd, double ngnCp, double mxSpd, string bdTp)
    : base(brnd, ngnCp, mxSpd, bdTp) => pattern = "";
    override public void PrintClassName()
    { Console.WriteLine($"Name of class: {Type}"); base.PrintClassName(); }
    override public void OwnMethod()
    => Console.WriteLine($"{Type} own method: VZHUUH IT CAN MOVE!");
    override public void Input()
    {
        while (pattern == null || pattern.Length == 0)
        {
            Console.WriteLine($"Enter {Type} pattern:");
            pattern = Console.ReadLine();
        }
        base.Input();
    }
    public override string ToString()
        => $"Type: {Type}\nPattern: {pattern}\n" + base.ToString();
}
