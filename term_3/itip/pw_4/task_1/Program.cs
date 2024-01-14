class Program
{
    static void Main()
    {
        int ans = -1;
        int[] arr = { };
        while (ans != 0)
        {
            Console.Clear();
            Console.WriteLine("1. Input array");
            Console.WriteLine("2. Show array");
            Console.WriteLine("3. Get count of elements multiple by 3");
            Console.WriteLine("0. Exit");
            int.TryParse(Console.ReadLine(), out ans);
            switch (ans)
            {
                case 1:
                    int len = 0;
                    while (len <= 0)
                    {
                        Console.WriteLine("Enter array length: ");
                        int.TryParse(Console.ReadLine(), out len);
                    }
                    Console.WriteLine("Enter elements:");
                    arr = LibManager.InputIntArray(len);
                    break;
                case 2:
                    LibManager.OutputIntArray(ref arr);
                    break;
                case 3:
                    Console.WriteLine("Count: " +
                        LibManager.CountElements(ref arr));
                    break;
            }
            Console.WriteLine("Enter any key.");
            Console.ReadKey();
        }
    }
}