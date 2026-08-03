import { useQuery } from "@tanstack/react-query";
import {checkPersonExistsByNationalNo} from "@/features/people/api/checkPersonExistsByNationalNo"

export function usePersonExistsByNationalNoQuery(nationalId: string){

    return useQuery({
        queryKey: ['nationalId', nationalId],
        queryFn: ()=> checkPersonExistsByNationalNo(nationalId),

    });
}