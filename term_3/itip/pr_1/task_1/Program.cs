using System.Globalization;

class Program
{
    static int GetNextCarIdx(int idx)
        => idx == CarsArrayLenght - 1 ? 0 : idx + 1;
    static int Menu()
    {
        int ans = -1;
        Console.Clear();
        Console.WriteLine("1: Create car.");
        Console.WriteLine("2: Show cars specs.");
        Console.WriteLine("3: Call method start.");
        Console.WriteLine("4: Call method travel.");
        Console.WriteLine("5: Call method fill.");
        Console.WriteLine("6: Call static method alarm in the yard.");
        Console.WriteLine("7: Compare all cars.");
        Console.WriteLine("0: Exit");
        int.TryParse(Console.ReadLine(), out ans);
        return ans;
    }
    static int CarsArrayLenght = 3;
    static void Main()
    {
        Car[] cars = new Car[CarsArrayLenght];
        int carsIdx = -1;
        int carsCount = 0;
        int ans = -1;
        while (ans != 0)
        {
            ans = Menu();
            Console.WriteLine();
            switch (ans)
            {
                case 1:
                    carsIdx = GetNextCarIdx(carsIdx);
                    cars[carsIdx] = new();
                    cars[carsIdx].Input();
                    if (carsCount < CarsArrayLenght)
                        carsCount++;
                    break;
                case 2:
                    if (carsCount > 0)
                        for (int i = 0; i < carsCount; i++)
                            Console.WriteLine($"{i}:\n" + cars[i]);
                    else
                        Console.WriteLine("There are no cars yet.");
                    break;
                case 3:
                    if (carsCount > 0)
                        for (int i = 0; i < carsCount; i++)
                            cars[i].Start();
                    else
                        Console.WriteLine("There are no cars yet.");
                    break;
                case 4:
                    if (carsCount > 0)
                        for (int i = 0; i < carsCount; i++)
                            cars[i].Travel();
                    else
                        Console.WriteLine("There are no cars yet.");
                    break;
                case 5:
                    if (carsCount > 0)
                        for (int i = 0; i < carsCount; i++)
                            cars[i].Fill();
                    else
                        Console.WriteLine("There are no cars yet.");
                    break;
                case 6:
                    Car.AlarmInTheYard();
                    break;
                case 7:
                    if (carsCount > 1)
                        for (int i = 0; i < carsCount; i++)
                            for (int j = i + 1; j < carsCount; j++)
                            {
                                if (cars[i] == cars[j])
                                    Console.WriteLine($"Car {i} == Car {j}");
                                else
                                    Console.WriteLine($"Car {i} != Car {j}");
                            }
                    else
                        Console.WriteLine("Too few cars. Add more to compare.");
                    break;
            }
            Console.WriteLine("Press any key to continue:");
            Console.ReadKey();
        }
    }
}
