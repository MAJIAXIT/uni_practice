class Car
{
    public static string Type = "Car";
    private string _brand;
    public string Brand
    { get => _brand; set => _brand = value == null ? "" : value; }
    private double _engineCap;
    public double EngineCap
    { get => _engineCap; set => _engineCap = value; }
    private double _maxSpeed;
    public double MaxSpeed
    { get => _maxSpeed; set => _maxSpeed = value; }
    private string _bodyType;
    public string BodyType
    { get => _bodyType; set => _bodyType = value == null ? "" : value; }
    public Car()
    {
        Brand = "";
        EngineCap = 0;
        MaxSpeed = 0;
        BodyType = "";
    }
    public Car(string brnd, double ngnCp, double mxSpd, string bdTp)
    {
        Brand = brnd;
        EngineCap = ngnCp;
        MaxSpeed = mxSpd;
        BodyType = bdTp;
    }
    public Car(string brnd, double ngnCp) : this()
    {
        Brand = brnd;
        EngineCap = ngnCp;
    }
    public void Start()
        => Console.WriteLine($"{Type} {Brand} ready to travel.");
    public void Travel()
    {
        double dist = 0;
        while (dist <= 0)
        {
            Console.WriteLine($"Enter distance:");
            double.TryParse(Console.ReadLine(), out dist);
        }
        Console.WriteLine(
            $"{this.GetType()} {Brand} is traveling on distance {dist} km.");
    }
    public void Fill()
        => Console.WriteLine($"{Type} {Brand} filled.");
    public static void AlarmInTheYard()
        => Console.WriteLine($"{Type}: Event: Alarm in the yard.");
    public override string ToString()
        => $"Type: {Type}\nBrand: {Brand}\nEngine capasity: {EngineCap} L\nMax speed: {MaxSpeed} Km/h\nBody type: {BodyType}";
    public void Input()
    {
        EngineCap = -1d;
        MaxSpeed = -1d;
        while (_brand == null || _brand.Length == 0)
        {
            Console.WriteLine($"Enter {Type} brand:");
            Brand = Console.ReadLine();
        }
        while (_bodyType == null || _bodyType.Length == 0)
        {
            Console.WriteLine($"Enter {Type} body type:");
            BodyType = Console.ReadLine();
        }
        while (EngineCap <= 0 || EngineCap >= 30)
        {
            Console.WriteLine($"Enter {Type} engine capacity:");
            double.TryParse(Console.ReadLine(), out _engineCap);
        }
        while (MaxSpeed <= 0 || MaxSpeed >= 600)
        {
            Console.WriteLine($"Enter {Type} max speed:");
            double.TryParse(Console.ReadLine(), out _maxSpeed);
        }
    }
    public static bool operator ==(Car l, Car r)
    => l.Brand == r.Brand && l.EngineCap == r.EngineCap &&
    l.MaxSpeed == r.MaxSpeed && l.BodyType == r.BodyType;

    public static bool operator !=(Car l, Car r)
    => l.Brand != r.Brand || l.EngineCap != r.EngineCap ||
    l.MaxSpeed != r.MaxSpeed || l.BodyType != r.BodyType;
}
