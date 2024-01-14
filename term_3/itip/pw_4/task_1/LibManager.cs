using System.Net.Sockets;
using System.Runtime.InteropServices;

public unsafe class LibManager
{
    [DllImport("libarr.so", CallingConvention = CallingConvention.Cdecl)]
    private static extern int countElments(int* arr, int len);
    [DllImport("libarr.so", CallingConvention = CallingConvention.Cdecl)]
    private static extern int* inputIntArray(int len);
    [DllImport("libarr.so", CallingConvention = CallingConvention.Cdecl)]
    private static extern void outputIntArray(int* arr, int len);

    public static int CountElements(ref int[] arr)
    {
        int cnt;
        fixed (int* ptr = arr)
            cnt = countElments(ptr, arr.Length);
        return cnt;
    }
    public static int[] InputIntArray(int len)
    {
        int[] arr = new int[len];
        int* ptr = inputIntArray(len);
        for (int i = 0; i < len; i++)
            arr[i] = ptr[i];
        return arr;
    }

    public static void OutputIntArray(ref int[] arr)
    {
        fixed (int* ptr = arr)
            outputIntArray(ptr, arr.Length);
    }
}