import { z } from "zod";

export const personDetailsSchema = z.object({
  id: z.number(),
  firstName: z.string().nonempty(),
  secondName: z.string().nonempty(),
  thirdName: z.string().nullable(),
  lastName: z.string().nonempty(),
  nationalNo: z.string().nonempty(),
  dateOfBirth: z.coerce.date(),
  gender: z.number().refine((num)=> num == 0 || num == 1),
  phoneNumber: z.string().nonempty(),
  email: z.email().nullable(),
  country: z.string().nonempty(),
  address: z.string(),
  imagePath: z.string().nullable(),
});

export type PersonDetails = z.infer<typeof personDetailsSchema>;
