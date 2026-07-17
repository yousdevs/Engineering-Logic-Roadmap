import { z } from "zod";
import { pagedResultSchema } from "@/features/people/schemas/paged-result-schema";

export const personSchema = z.object({
  id: z.number(),
  nationalNo: z.string(),
  firstName: z.string(),
  secondName: z.string(),
  thirdName: z.string(),
  lastName: z.string(),
  gender: z.string(),
  dateOfBirth: z.coerce.date(),
  nationality: z.string(),
  phoneNumber: z.string(),
  email: z.email(),
});

export const peopleSchema = z.array(personSchema);

export type Person = z.infer<typeof personSchema>;

export const pagedPeopleSchema = pagedResultSchema(personSchema);
