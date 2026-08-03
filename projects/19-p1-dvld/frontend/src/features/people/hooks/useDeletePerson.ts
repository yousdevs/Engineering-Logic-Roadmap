import { useMutation, useQueryClient } from "@tanstack/react-query";
import { deletePerson } from "../api/deletePerson";

export function useDeletePerson() {
  const queryClient = useQueryClient();
  return useMutation({
    mutationFn: deletePerson,
    onSuccess: async () => {
      await queryClient.invalidateQueries({
        queryKey: ["people"],
      });

      // toast
      console.log("person deleted.");
    },
  });
}
