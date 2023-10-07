class Program
{
    static Vehicle VehicleMenuLoop()
    {
        int ans = -1;
        while (ans != 0)
        {
            Console.Clear();
            Console.WriteLine("1: Car");
            Console.WriteLine("2: Tank");
            Console.WriteLine("3: Scoot");
            Console.WriteLine("4: Cart");
            Console.WriteLine("5: Carpet");
            Console.WriteLine("0: Exit");
            int.TryParse(Console.ReadLine(), out ans);
            switch (ans)
            {
                case 0: System.Environment.Exit(1); break;
                case 1: return new Car();
                case 2: return new Tank();
                case 3: return new Scoot();
                case 4: return new Cart();
                case 5: return new Carpet();
            }
        }
        return null; // Should never happen
    }
    static void Main()
    {
        int ans = -1;
        Vehicle vehicle = VehicleMenuLoop();
        vehicle.Input();
        while (ans != 0)
        {
            Console.Clear();
            Console.WriteLine("1: Create new vehicle.");
            Console.WriteLine("2: Show vehicle specs.");
            Console.WriteLine("3: Call method start.");
            Console.WriteLine("4: Call method travel.");
            Console.WriteLine("5: Call method fill.");
            Console.WriteLine("6: Call static method alarm in the yard.");
            Console.WriteLine("7: Call own method.");
            Console.WriteLine("8: Print class name.");
            Console.WriteLine("0: Exit");
            int.TryParse(Console.ReadLine(), out ans);
            switch (ans)
            {
                case 1: vehicle = VehicleMenuLoop(); vehicle.Input(); break;
                case 2: Console.WriteLine(vehicle); break;
                case 3: vehicle.Start(); break;
                case 4: vehicle.Travel(); break;
                case 5: vehicle.Fill(); break;
                case 6: Vehicle.AlarmInTheYard(); break;
                case 7: vehicle.OwnMethod(); break;
                case 8: vehicle.PrintClassName(); break;
            }
            Console.WriteLine("Press any key to continue:");
            Console.ReadKey();
        }
    }
}
