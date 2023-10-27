class Scoot : Vehicle
{
    public static new string Type = "Scoot";
    private string model;
    public Scoot() : base()
    => model = "";
    public Scoot(string brnd, double ngnCp, double mxSpd, string bdTp)
    : base(brnd, ngnCp, mxSpd, bdTp) => model = "";
    override public void PrintClassName()
    { Console.WriteLine($"Name of class: {Type}"); base.PrintClassName(); }
    override public void OwnMethod()
    => Console.WriteLine($"{Type} own method: BEEP BEEP!");
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
