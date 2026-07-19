import {z} from "zod";
import { PersonAvailabilitySchema, type PersonAvailability } from "@/features/people/schemas/person-availabitlity-schema";

export async function checkPersonExistsByNationalNo(nationalNo: string) : Promise<PersonAvailability>{

    const res = await fetch(`https://localhost:7152/api/people/availability?nationalNo=${nationalNo}`);
    
    if(!res.ok) throw new Error("couldnt fetch " + nationalNo);
    return PersonAvailabilitySchema.parse(await res.json());
}