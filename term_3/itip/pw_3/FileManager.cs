using System.Runtime.InteropServices;
using System.Text;

public class FileManager
{
    private IntPtr file = 0;
    private bool readOnly;
    public int WordsCount;
    public int SymbCount;

    [DllImport("libfuncs.so")]
    // exc - Exception message to handle
    // Exceptinos handled only in constructor, because other exceptions
    // in c++ library invokes only if file not open, so they can't be reached
    private static extern IntPtr open(string path, bool read, StringBuilder exc);
    [DllImport("libfuncs.so")]
    private static extern void close(IntPtr file);
    [DllImport("libfuncs.so")]
    private static extern bool read(IntPtr file, int el, StringBuilder word);
    [DllImport("libfuncs.so")]
    private static extern void write(IntPtr file, string text);
    [DllImport("libfuncs.so")]
    private static extern void readAll(IntPtr file, StringBuilder strbldr);
    [DllImport("libfuncs.so")]
    private static extern int wordsCount(IntPtr file);
    [DllImport("libfuncs.so")]
    private static extern int symbCount(IntPtr file);

    public FileManager(string path, bool read)
    {
        StringBuilder exc = new();
        readOnly = read;
        file = open(path, read, exc);
        if (exc.Length != 0)
            throw new ArgumentException(exc.ToString());
        WordsCount = wordsCount(file);
        SymbCount = symbCount(file);
    }

    public StringBuilder Read(int el)
    {
        if (file == 0)
            throw new IOException("File not open");
        StringBuilder strbldr = new();
        read(file, el, strbldr);
        return strbldr;
    }

    public StringBuilder ReadAll()
    {
        if (file == 0)
            throw new IOException("File not open");
        StringBuilder strbldr = new(symbCount(file));
        readAll(file, strbldr);
        return strbldr;
    }

    public void Write(string str)
    {
        if (readOnly)
            throw new IOException("Can't write with readonly file mode");
        write(file, str);
    }
    // Equal overriding Finalize()
    ~FileManager()
    {
        if (file == 0)
            throw new IOException("File not open");
        close(file);
    }
}
