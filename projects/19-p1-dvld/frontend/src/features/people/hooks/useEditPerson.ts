import { useMutation, useQueryClient } from "@tanstack/react-query";
import { editPerson } from "../api/editPerson";

export function useEditPerson(id: number) {
  const queryClient = useQueryClient();
  return useMutation({
    mutationFn: editPerson,

    onSuccess: async () => {
      await queryClient.invalidateQueries({
        queryKey: ["people"],
      });
      await queryClient.invalidateQueries({
        queryKey: ["personDetails", id],
      });
    },
  });
}
