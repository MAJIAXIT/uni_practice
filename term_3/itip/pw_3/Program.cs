using System.Text;

class Program
{
    static FileManager GetFileManager(bool readOnly = true)
    {
        string path = "";
        while (path == "")
        {
            Console.WriteLine("Enter path to file:");
            path = Console.ReadLine();
        }

        FileManager fm = new(path, readOnly);
        return fm;
    }

    static void ShowFileContent()
    {
        FileManager fm;
        try { fm = GetFileManager(); }
        catch (ArgumentException e)
        {
            Console.WriteLine(e.Message);
            return;
        }
        StringBuilder strbldr = fm.ReadAll();
        Console.WriteLine(strbldr);
    }

    static void ShowFileLenght()
    {
        FileManager fm;
        try { fm = GetFileManager(); }
        catch (ArgumentException e)
        {
            Console.WriteLine(e.Message);
            return;
        }

        int ans = -1;
        while (ans != 0)
        {
            Console.WriteLine("1: In words.");
            Console.WriteLine("2: In symbols.");
            Console.WriteLine("0: Back to menu.");
            int.TryParse(Console.ReadLine(), out ans);
            if (ans == 1) Console.WriteLine($"File lenght in words: {fm.WordsCount}");
            if (ans == 2) Console.WriteLine($"File lenght in symbols: {fm.SymbCount}");
        }
    }

    static void CreateNewFileWithWordCoincidences()
    {
        FileManager fm1;
        FileManager fm2;
        FileManager fmNew;
        try
        {
            Console.WriteLine("First file to compare:");
            fm1 = GetFileManager();
            Console.WriteLine("Second file to compare:");
            fm2 = GetFileManager();
            Console.WriteLine("New result file:");
            fmNew = GetFileManager(false);
        }
        catch (ArgumentException e)
        {
            Console.WriteLine(e.Message);
            return;
        }

        HashSet<string> hshst = new();
        StringBuilder strbldr = new();
        for (int i = 1; i <= fm1.WordsCount; i++)
            hshst.Add(fm1.Read(i).ToString());

        for (int i = 1; i <= fm2.WordsCount; i++)
            if (hshst.Contains(fm2.Read(i).ToString()))
                strbldr.Append(fm2.Read(i).ToString() + " ");
        fmNew.Write(strbldr.ToString());
    }

    static void ReverseFileToNewFile()
    {
        FileManager fm;
        FileManager fmNew;
        try
        {
            Console.WriteLine("File to reverse:");
            fm = GetFileManager();
            Console.WriteLine("Result file:");
            fmNew = GetFileManager(false);
        }
        catch (ArgumentException e)
        {
            Console.WriteLine(e.Message);
            return;
        }
        HashSet<string> hshst = new();
        for (int i = 1; i <= fm.WordsCount; i++)
            hshst.Add(fm.Read(i).ToString());
        fmNew.Write(string.Join(" ", hshst.Reverse()));
    }
    
    static void Main()
    {
        int ans = -1;
        while (ans != 0)
        {
            Console.Clear();
            Console.WriteLine("1: Show file content.");
            Console.WriteLine("2: Show file lenght.");
            Console.WriteLine("3: Get new file with word coincidences.");
            Console.WriteLine("4: Reverse words in file.");
            Console.WriteLine("0: Exit");
            int.TryParse(Console.ReadLine(), out ans);
            switch (ans)
            {
                case 1:
                    ShowFileContent();
                    break;
                case 2:
                    ShowFileLenght();
                    break;
                case 3:
                    CreateNewFileWithWordCoincidences();
                    break;
                case 4:
                    ReverseFileToNewFile();
                    break;
            }
            Console.WriteLine("Enter any key to continue.");
            Console.ReadKey();
        }
    }
}
