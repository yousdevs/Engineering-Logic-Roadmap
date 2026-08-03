import { useQuery } from "@tanstack/react-query";
import { getPersonDetails } from "@/features/people/api/getPersonDetails";

export function usePersonDetails(id: number) {
  return useQuery({
    queryKey: ["personDetails", id],
    queryFn: () => getPersonDetails(id),
  });
}
