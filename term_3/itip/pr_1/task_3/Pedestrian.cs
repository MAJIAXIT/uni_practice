class Pedestrian : IMovable
{
    private string name { get; set; }
    private double avgSpeed { get; set; }

    public Pedestrian() { name = ""; avgSpeed = 0d; }
    public void Travel()
    {
        double dist = 0;
        while (dist <= 0)
        {
            Console.WriteLine($"Enter distance:");
            double.TryParse(Console.ReadLine(), out dist);
        }
        Console.WriteLine($"Pedestrian {name} travel on {dist} km");
    }

    public void Start()
    => Console.WriteLine($"Pedestrian {name} is ready to travel.");

    public void Input()
    {
        while (name == "" || name == null)
        {
            Console.WriteLine($"Enter pedestrian name:");
            name = Console.ReadLine();
        }
        double avgSpd = 0;
        while (avgSpd <= 0d)
        {
            Console.WriteLine($"Enter average speed:");
            double.TryParse(Console.ReadLine(), out avgSpd);
        }
        avgSpeed = avgSpd;
    }

    public override string ToString()
    => $"Pedestrian:\nName: {name}\nAverage speed: {avgSpeed} Km/h";
}