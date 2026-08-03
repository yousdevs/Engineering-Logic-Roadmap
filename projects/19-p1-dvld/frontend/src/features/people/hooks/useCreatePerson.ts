import { useMutation, useQueryClient } from "@tanstack/react-query";
import { createPerson } from "@/features/people/api/createPerson";

export function useCreatePerson() {
  const queryClient = useQueryClient();
  return useMutation({
    mutationFn: createPerson,
    onSuccess: () => {
      queryClient.invalidateQueries({
        queryKey: ["people"],
      });
    },
  });
}
