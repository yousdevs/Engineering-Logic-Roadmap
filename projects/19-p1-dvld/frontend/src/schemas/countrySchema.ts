import { z } from "zod";

export const countrySchema = z.object({
  id: z.number().nonoptional(),
  name: z.string().nonoptional(),
});

export const countriesSchema = z.array(countrySchema);
export type Country = z.infer<typeof countrySchema>;
