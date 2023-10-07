class Program
{
    static void AddRecord(List<IMovable> list)
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
            Console.WriteLine("6: Pedestrian");
            Console.WriteLine("0: Exit");
            int.TryParse(Console.ReadLine(), out ans);
            switch (ans)
            {
                case 0: return;
                case 1: Car car = new(); car.Input(); list.Add(car); return;
                case 2: Tank tank = new(); tank.Input(); list.Add(tank); return;
                case 3: Scoot scoot = new(); scoot.Input(); list.Add(scoot); return;
                case 4: Cart cart = new(); cart.Input(); list.Add(cart); return;
                case 5: Carpet carpet = new(); carpet.Input(); list.Add(carpet); return;
                case 6: Pedestrian ped = new(); ped.Input(); list.Add(ped); return;
            }
        }
    }

    static IMovable FindRecord(List<IMovable> list)
    {
        if (!list.Any()) return null; // Should never happen
        int idx = -1;
        while (idx < 0 || idx >= list.Count())
        {
            Console.WriteLine("Enter idx: ");
            int.TryParse(Console.ReadLine(), out idx);
        }
        foreach (IMovable imbl in list)
            if (idx-- == 0) return imbl;
        return null; // Should never happen
    }

    static void ExecuteMethod(IMovable imbl)
    {
        if (imbl == null) return; // Should never happen
        int ans = -1;
        while (ans != 0)
        {
            Console.WriteLine("1: Travel.");
            Console.WriteLine("2: Start.");
            Console.WriteLine("0: Exit.");
            int.TryParse(Console.ReadLine(), out ans);
            if (ans == 1) imbl.Travel();
            if (ans == 2) imbl.Start();
        }
    }

    static void Main()
    {
        List<IMovable> list = new List<IMovable>();
        int ans = -1;
        while (ans != 0)
        {
            Console.Clear();
            Console.WriteLine("1: Add record.");
            Console.WriteLine("2: Show records.");
            Console.WriteLine("3: Execute interface method on record by number.");
            Console.WriteLine("4: Delete record.");
            Console.WriteLine("0: Exit");
            int.TryParse(Console.ReadLine(), out ans);
            switch (ans)
            {
                case 1: AddRecord(list); break;
                case 2:
                    if (!list.Any())
                    { Console.WriteLine("List is empty."); break; }
                    int idx = 0;
                    foreach (IMovable imbl in list)
                    {
                        Console.WriteLine($"{idx++}:");
                        Console.WriteLine(imbl);
                    }
                    break;
                case 3:
                    if (!list.Any())
                    { Console.WriteLine("List is empty."); break; }
                    ExecuteMethod(FindRecord(list));
                    break;
                case 4:
                    if (!list.Any())
                    { Console.WriteLine("List is empty."); break; }
                    if (list.Remove(FindRecord(list)))
                        Console.WriteLine("Removed.");
                    break;
            }
            Console.WriteLine("Enter any key to continue.");
            Console.ReadKey();
        }
    }
}
