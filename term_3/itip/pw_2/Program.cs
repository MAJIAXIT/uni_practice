class Program
{
    static void AddRecord(List<Car> list)
    {
        int idxToIns = -1;
        Car car = new();
        car.Input();
        if (list.Any())
        {
            while (idxToIns < 0 || idxToIns > list.Count)
            {
                Console.WriteLine("Enter index to insert car in range 0 : {0}", list.Count);
                int.TryParse(Console.ReadLine(), out idxToIns);
            }
            list.Insert(idxToIns, car);
        }
        else
            list.Add(car);
    }
    static void ReadFromFile(string path, List<Car> list)
    {
        FileStream rs;
        try
        {
            rs = new(path, FileMode.OpenOrCreate, FileAccess.Read);
        }
        catch (IOException exc)
        {
            Console.WriteLine(exc.Message);
            return;
        }
        if (rs.Length != 0)
            using (BinaryReader br = new BinaryReader(rs))
            {
                Car car = new();
                while (car.ReadWithReader(br))
                    list.Add(car);
            }
        else
            Console.WriteLine("File is empty. Empty list created.");
        rs.Close();
    }

    static void WriteToFile(string path, List<Car> list)
    {
        FileStream ws;
        try
        {
            ws = new(path, FileMode.OpenOrCreate, FileAccess.Write);
        }
        catch (IOException exc)
        {
            Console.WriteLine(exc.Message);
            return;
        }
        using (BinaryWriter bw = new BinaryWriter(ws))
            if (list.Any())
                foreach (Car car in list)
                    car.WriteWithWriter(bw);
            else
                bw.Write(string.Empty);
        ws.Close();
    }

    static void RemoveFromList(List<Car> list)
    {
        int idxToRemove = -1;
        while (idxToRemove < 0 || idxToRemove >= list.Count)
        {
            Console.WriteLine("Enter index of record to remove in range 0 : {0}", list.Count - 1);
            int.TryParse(Console.ReadLine(), out idxToRemove);
        }
        list.RemoveAt(idxToRemove);
    }

    static string GetTableHeader()
        => string.Format("| ID |     Brand     |    Manuf country    | Year | Engine cap | Gas cons |   Price   |  Copies  |");

    static void SellCars(List<Car> list)
    {
        int count = -1;
        string brand = "";
        while (brand == null || brand.Length == 0)
        {
            Console.WriteLine("Enter brand of car to sell:");
            brand = Console.ReadLine();
        }
        while (count <= 0)
        {
            Console.WriteLine("Enter count of cars to sell:");
            int.TryParse(Console.ReadLine(), out count);
        }
        for (int i = 0; i < list.Count; i++)
            if (list[i].Brand == brand)
            {
                if (list[i].CntOfCopies > count)
                {
                    Car car = list[i];
                    car.CntOfCopies -= count;
                    list[i] = car;
                    Console.WriteLine($"Cars sold. Earned {car.Price * count} $.");
                    Console.WriteLine(GetTableHeader());
                    Console.WriteLine("| {0, 2} " + list[i], i);
                }
                else
                {
                    Console.WriteLine($"All cars of brand {brand} sold.");
                    Console.WriteLine($"Earned {list[i].Price * list[i].CntOfCopies} $.");
                    list.RemoveAt(i);
                }
            }
    }
    static void EditRecord(List<Car> list)
    {
        int idxToEdit = -1;
        while (idxToEdit < 0 || idxToEdit >= list.Count)
        {
            Console.WriteLine("Enter index of record to edit in range 0 : {0}", list.Count - 1);
            int.TryParse(Console.ReadLine(), out idxToEdit);
        }
        Console.WriteLine(GetTableHeader());
        Console.WriteLine("| {0, 2} " + list[idxToEdit], idxToEdit);
        Console.WriteLine("Edit this record?(y/n)");
        string ans = Console.ReadLine();
        if (ans != null && ans.ToLower() == "y")
        {
            Car car = new();
            car.Input();
            list[idxToEdit] = car;
            Console.WriteLine("Record updated.");
        }
    }
    static void FindCarByEngCapWithLessGasCons(List<Car> list)
    {
        double engCp = -1, minGasCons = 100;
        int foundIdx = -1;
        while (engCp <= 0)
        {
            Console.WriteLine("Enter engine capacity.");
            double.TryParse(Console.ReadLine(), out engCp);
        }
        for (int i = 0; i < list.Count; i++)
            if (list[i].EngineCap == engCp && list[i].GasCons < minGasCons)
            {
                minGasCons = list[i].GasCons;
                foundIdx = i;
            }
        if (foundIdx != -1)
        {
            Console.WriteLine(GetTableHeader());
            Console.WriteLine("| {0, 2} " + list[foundIdx], foundIdx);
        }
        else
            Console.WriteLine($"There is no car with engine capacity: {engCp} l");

    }
    static void Sort(List<Car> list)
    {
        int ans = -1;
        while (ans != 0)
        {
            Console.Clear();
            Console.WriteLine("1: Sort by brand.");
            Console.WriteLine("2: Sort by manufactor country.");
            Console.WriteLine("3: Sort by manufaction year.");
            Console.WriteLine("4: Sort by engine capacity.");
            Console.WriteLine("5: Sort by gas consumption.");
            Console.WriteLine("6: Sort by price.");
            Console.WriteLine("7: Sort by count of copies.");
            Console.WriteLine("0: Exit");
            int.TryParse(Console.ReadLine(), out ans);
            switch (ans)
            {
                case 1:
                    list.Sort((car1, car2)
                        => car1.Brand.CompareTo(car2.Brand));
                    return;
                case 2:
                    list.Sort((car1, car2)
                        => car1.ManufCountry.CompareTo(car2.ManufCountry));
                    return;
                case 3:
                    list.Sort((car1, car2)
                        => car1.ManufYear.CompareTo(car2.ManufYear));
                    return;
                case 4:
                    list.Sort((car1, car2)
                        => car1.EngineCap.CompareTo(car2.EngineCap));
                    return;
                case 5:
                    list.Sort((car1, car2)
                        => car1.GasCons.CompareTo(car2.GasCons));
                    return;
                case 6:
                    list.Sort((car1, car2)
                        => car1.Price.CompareTo(car2.Price));
                    return;
                case 7:
                    list.Sort((car1, car2)
                        => car1.CntOfCopies.CompareTo(car2.CntOfCopies));
                    return;
            }
        }
    }
    static void Main()
    {
        List<Car> list = new List<Car>();
        string path = "";
        while (path == "" || path == null)
        {
            Console.WriteLine("Enter path to binary file.");
            Console.WriteLine("If file doesnt exitsts, it will be created.");
            path = Console.ReadLine();
        }

        ReadFromFile(path, list);

        int ans = -1;
        while (ans != 0)
        {
            Console.Clear();
            Console.WriteLine("1: Add record.");
            Console.WriteLine("2: Show records.");
            Console.WriteLine("3: Delete record.");
            Console.WriteLine("4: Sell cars.");
            Console.WriteLine("5: Find car by engine capacity with less gas cons.");
            Console.WriteLine("6: Sort records.");
            Console.WriteLine("7: Edit record.");
            Console.WriteLine("0: Exit");
            int.TryParse(Console.ReadLine(), out ans);
            switch (ans)
            {
                case 1:
                    AddRecord(list);
                    break;
                case 2:
                    if (!list.Any())
                    { Console.WriteLine("List is empty."); break; }
                    int idx = 0;
                    Console.WriteLine(GetTableHeader());
                    foreach (Car car in list)
                        Console.WriteLine(
                            string.Format("| {0, 2} " + car, idx++));
                    break;
                case 3:
                    if (!list.Any())
                    { Console.WriteLine("List is empty."); break; }
                    RemoveFromList(list);
                    break;
                case 4:
                    SellCars(list);
                    break;
                case 5:
                    FindCarByEngCapWithLessGasCons(list);
                    break;
                case 6:
                    Sort(list);
                    break;
                case 7:
                    EditRecord(list);
                    break;
            }
            Console.WriteLine("Enter any key to continue.");
            Console.ReadKey();
        }

        WriteToFile(path, list);
    }
}
