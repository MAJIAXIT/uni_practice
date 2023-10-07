class Cart : Vehicle
{
    public static new string Type = "Cart";
    private string stolenFrom;
    public Cart() : base()
    => stolenFrom = "";
    public Cart(string brnd, double ngnCp, double mxSpd, string bdTp)
    : base(brnd, ngnCp, mxSpd, bdTp) => stolenFrom = "";
    override public void PrintClassName()
    { Console.WriteLine($"Name of class: {Type}"); base.PrintClassName(); }
    override public void OwnMethod()
    => Console.WriteLine($"{Type} own method: ride on it!");
    override public void Input()
    {
        while (stolenFrom == null || stolenFrom.Length == 0)
        {
            Console.WriteLine($"Enter {Type} stolen from:");
            stolenFrom = Console.ReadLine();
        }
        base.Input();
    }
    public override string ToString()
        => $"Type: {Type}\nStolenFrom: {stolenFrom}\n" + base.ToString();
}
