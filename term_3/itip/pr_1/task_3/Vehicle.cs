public abstract class Vehicle : IMovable
{
    public static string Type = "Vehicle";
    private string brand { get; set; }
    private double engineCap { get; set; }
    private double maxSpeed { get; set; }
    private string bodyType { get; set; }

    public Vehicle()
    {
        brand = "";
        engineCap = 0d;
        maxSpeed = 0d;
        bodyType = "";
    }
    public Vehicle(string brnd, double ngnCp, double mxSpd, string bdTp)
    {
        brand = brnd;
        engineCap = ngnCp;
        maxSpeed = mxSpd;
        bodyType = bdTp;
    }
    public void Start()
        => Console.WriteLine($"{this.GetType()} {brand} ready to travel.");
    public void Travel()
    {
        double dist = 0;
        while (dist <= 0)
        {
            Console.WriteLine($"Enter distance:");
            double.TryParse(Console.ReadLine(), out dist);
        }
        Console.WriteLine(
            $"{this.GetType()} {brand} is traveling on distance {dist} km.");
    }
    public void Fill()
        => Console.WriteLine($"{this.GetType()} {brand} filled.");
    public static void AlarmInTheYard()
        => Console.WriteLine($"{Type}: Event: Alarm in the yard.");
    public override string ToString()
        => $"Brand: {brand}\nEngine capasity: {engineCap} L\nMax speed: {maxSpeed} Km/h\nBody type: {bodyType}";
    public virtual void Input()
    {
        engineCap = -1d;
        maxSpeed = -1d;
        while (brand == null || brand.Length == 0)
        {
            Console.WriteLine($"Enter {this.GetType()} brand:");
            brand = Console.ReadLine();
        }
        while (bodyType == null || bodyType.Length == 0)
        {
            Console.WriteLine($"Enter {this.GetType()} body type:");
            bodyType = Console.ReadLine();
        }
        while (engineCap <= 0 || engineCap >= 30)
        {
            Console.WriteLine($"Enter {this.GetType()} engine capacity:");
            double temp;
            double.TryParse(Console.ReadLine(), out temp);
            engineCap = temp;
        }
        while (maxSpeed <= 0 || maxSpeed >= 600)
        {
            double temp;
            Console.WriteLine($"Enter {this.GetType()} max speed:");
            double.TryParse(Console.ReadLine(), out temp);
            maxSpeed = temp;
        }
    }
    public virtual void PrintClassName()
    => Console.WriteLine($"Name of class: {Type}");
    public virtual void OwnMethod() { }
}