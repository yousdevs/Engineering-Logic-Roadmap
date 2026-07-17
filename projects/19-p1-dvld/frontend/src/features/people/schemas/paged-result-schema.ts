import { z } from "zod";

export const pagedResultSchema = <T extends z.ZodTypeAny>(itemSchema: T) =>
  z.object({
    offset: z.number().int().nonnegative(),
    limit: z.number().int().positive(),
    total: z.number().int().nonnegative(),
    items: z.array(itemSchema),
  });
