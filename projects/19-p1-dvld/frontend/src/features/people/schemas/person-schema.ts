import { z } from "zod";
import { pagedResultSchema } from "@/features/people/schemas/paged-result-schema";

export const personSchema = z.object({
  personId: z.number(),
  nationalNo: z.string(),
  firstName: z.string(),
  secondName: z.string(),
  thirdName: z.string().nullable(),
  lastName: z.string(),
  gender: z.string(),
  dateOfBirth: z.coerce.date(),
  nationality: z.string(),
  phoneNumber: z.string(),
  email: z.email().nullable(),
});

export const peopleSchema = z.array(personSchema);

export type Person = z.infer<typeof personSchema>;

export const pagedPeopleSchema = pagedResultSchema(personSchema);
