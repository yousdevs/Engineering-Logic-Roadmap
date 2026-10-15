namespace DSA.Core.Algorithms;

public static class InsertionSort
{
    public static void Sort(int[] arr)
    {
      
        for(int i = 1; i < arr.Length; i++)
        {
            int j = i;
            int copy = arr[j];

            while(j > 0 && copy < arr[j - 1])
            {
                arr[j] = arr[j - 1];
                j --;
            }
            
            arr[j] = copy;
        }

    }

    
}