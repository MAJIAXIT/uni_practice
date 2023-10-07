using System.Runtime.InteropServices;

public struct Car
{
    public string Brand { get; set; }
    public string ManufCountry { get; set; }
    public int ManufYear;
    public double EngineCap;
    public double GasCons;
    public double Price;
    public int CntOfCopies;

    public Car(BinaryReader r)
    {
        Brand = "";
        ManufCountry = "";
        ManufYear = -1;
        EngineCap = -1;
        GasCons = -1;
        Price = -1;
        CntOfCopies = -1;
    }
    public bool WriteWithWriter(BinaryWriter bw)
    {
        try
        {
            bw.Write(Brand);
            bw.Write(ManufCountry);
            bw.Write(ManufYear);
            bw.Write(EngineCap);
            bw.Write(GasCons);
            bw.Write(Price);
            bw.Write(CntOfCopies);
            return true;
        }
        catch
        {
            return false;
        }
    }
    public bool ReadWithReader(BinaryReader br)
    {
        try
        {
            Brand = br.ReadString();
            ManufCountry = br.ReadString();
            ManufYear = br.ReadInt32();
            EngineCap = br.ReadDouble();
            GasCons = br.ReadDouble();
            Price = br.ReadDouble();
            CntOfCopies = br.ReadInt32();
            return true;
        }
        catch
        {
            return false;
        }
    }
    public override string ToString()
        => string.Format("| {0,13} | {1,19} | {2,4} | {3,10} |{4,9} | {5,9} | {6, 8} |",
        Brand, ManufCountry, ManufYear, EngineCap, GasCons, Price, CntOfCopies);

    public void Input()
    {
        while (Brand == null || Brand.Length == 0)
        {
            Console.WriteLine($"Enter car brand:");
            Brand = Console.ReadLine();
        }
        while (ManufCountry == null || ManufCountry.Length == 0)
        {
            Console.WriteLine($"Enter car manufactor country:");
            ManufCountry = Console.ReadLine();
        }
        while (ManufYear <= 1700 || ManufYear > 2023)
        {
            Console.WriteLine($"Enter car manufaction year:");
            int.TryParse(Console.ReadLine(), out ManufYear);
        }
        while (EngineCap <= 0 || EngineCap >= 50)
        {
            Console.WriteLine($"Enter car engine capacity (l):");
            double.TryParse(Console.ReadLine(), out EngineCap);
        }
        while (GasCons <= 0 || GasCons >= 50)
        {
            Console.WriteLine($"Enter car gas consumption (l/100km):");
            double.TryParse(Console.ReadLine(), out GasCons);
        }
        while (Price <= 0 || Price >= 100000000)
        {
            Console.WriteLine($"Enter car price ($):");
            double.TryParse(Console.ReadLine(), out Price);
        }
        while (CntOfCopies <= 0 || CntOfCopies >= 10000000)
        {
            Console.WriteLine($"Enter car number of copies:");
            int.TryParse(Console.ReadLine(), out CntOfCopies);
        }
    }
}
