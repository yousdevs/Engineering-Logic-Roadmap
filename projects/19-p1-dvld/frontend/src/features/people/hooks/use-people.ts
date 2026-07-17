import { getPeople } from "@/features/people/api/get-people";
import { useQuery } from "@tanstack/react-query";

export function usePeople(page: number, pageSize: number) {
  return useQuery({
    queryKey: ["people", page, pageSize],
    queryFn: () => getPeople(page, pageSize),
  });
}
