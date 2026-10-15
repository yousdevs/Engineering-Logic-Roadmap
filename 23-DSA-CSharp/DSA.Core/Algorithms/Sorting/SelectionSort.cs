namespace DSA.Core.Algorithms;

public static class SelectionSort
{

    private static int FindMinIndex(int[] arr, int startIndex)
    {
        int minIndex = startIndex ;
        for(int i = startIndex + 1; i< arr.Length; i++)
        {
            if(arr[i] < arr[minIndex])
            {
                minIndex = i;
            }
        }
        return minIndex;
    }
    
    public static void Sort(int[] arr)
    {
        for(int i = 0; i < arr.Length-1; i++) // arr.length-1 the last element already will be sorted.
        {
            int minIndex = FindMinIndex(arr, i);
            (arr[i], arr[minIndex]) = (arr[minIndex], arr[i]);
        }
    }
}