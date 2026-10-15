namespace DSA.Core.Algorithms;

public static class BinarySearch
{
    
    public static int Search(int[] arr, int target)
    {
        
        int start = 0, end = arr.Length - 1;
        while(start <= end)
        {
            int middle = start + ((end - start)/2);
            if(arr[middle] == target)
                return middle;
            
            if(arr[middle] < target)
                start = middle + 1;
            
            if(arr[middle] > target)
                end = middle - 1;

        }
        return -1;
    }
}