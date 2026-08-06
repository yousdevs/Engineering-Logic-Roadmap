import { z } from "zod";

export const personDetailsSchema = z.object({
  firstName: z.string().nonempty(),
  secondName: z.string().nonempty(),
  thirdName: z.string().nullable(),
  lastName: z.string().nonempty(),
  nationalNo: z.string().nonempty(),
  dateOfBirth: z.coerce.date(),
  gender: z.string().nonempty(),
  phoneNumber: z.string().nonempty(),
  email: z.email().nullable(),
  country: z.string().nonempty(),
  address: z.string(),
  imageUrl: z.string().nullable(),
});

export type PersonDetails = z.infer<typeof personDetailsSchema>;
