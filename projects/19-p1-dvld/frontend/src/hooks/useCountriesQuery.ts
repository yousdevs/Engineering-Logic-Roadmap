import { useQuery } from "@tanstack/react-query";
import { getCountries } from "@/api/getCountries";

export function useCountriesQuery(){

    return useQuery({
        queryKey: ["countries"],
        staleTime: Infinity,
        queryFn: getCountries,
    });
}