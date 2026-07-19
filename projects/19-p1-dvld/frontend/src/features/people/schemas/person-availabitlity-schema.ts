import {z} from "zod";

export const PersonAvailabilitySchema = z.object({
    exists: z.boolean(),
});


export type PersonAvailability = z.infer<typeof PersonAvailabilitySchema>;
