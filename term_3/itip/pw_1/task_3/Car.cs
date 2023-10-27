sealed class Car : Vehicle
{
    public static new string Type = "Car (sealed)";
    private string name;
    public Car() : base()
    => name = "";
    public Car(string brnd, double ngnCp, double mxSpd, string bdTp)
    : base(brnd, ngnCp, mxSpd, bdTp) => name = "";
    override public void PrintClassName()
    { Console.WriteLine($"Name of class: {Type}"); base.PrintClassName(); }
    override public void OwnMethod()
    => Console.WriteLine($"{Type} own method: BEEP BEEP!");
    override public void Input()
    {
        while (name == null || name.Length == 0)
        {
            Console.WriteLine($"Enter {Type} name:");
            name = Console.ReadLine();
        }
        base.Input();
    }
    public override string ToString()
        => $"Type: {Type}\nName: {name}\n" + base.ToString();
}
