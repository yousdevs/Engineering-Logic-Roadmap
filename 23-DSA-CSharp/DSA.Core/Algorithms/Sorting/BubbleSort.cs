namespace DSA.Core.Algorithms;

public static class BubbleSort
{
    public static void Sort(int[] arr)
    {
        
        for (int i = 0; i < arr.Length; i++)
        {
            for(int j = 0; j < (arr.Length - 1) - i; j++)
            {
                if(arr[j] > arr[j + 1])
                {
                    (arr[j], arr[j+1]) = (arr[j+1], arr[j]);
                }
            }
        }
    }
}