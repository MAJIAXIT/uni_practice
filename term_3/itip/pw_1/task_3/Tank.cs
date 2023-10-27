class Tank : Vehicle
{
    public static new string Type = "Tank";
    private string model;
    public Tank() : base()
    => model = "";
    public Tank(string brnd, double ngnCp, double mxSpd, string bdTp)
    : base(brnd, ngnCp, mxSpd, bdTp) => model = "";
    override public void PrintClassName()
    { Console.WriteLine($"Name of class: {Type}"); base.PrintClassName(); }
    override public void OwnMethod()
    => Console.WriteLine($"{Type} own method: BOOOM!");
    override public void Input()
    {
        while (model == null || model.Length == 0)
        {
            Console.WriteLine($"Enter {Type} model:");
            model = Console.ReadLine();
        }
        base.Input();
    }
    public override string ToString()
        => $"Type: {Type}\nModel: {model}\n" + base.ToString();
}
