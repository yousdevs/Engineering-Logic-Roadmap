import { personDetailsSchema } from "@/features/people/schemas/person-details-schema";

export async function getPersonDetails(personId: number) {
  if (Number.isNaN(personId)) throw new Error("personId invalid.");

  const response = await fetch(`https://localhost:7152/api/people/${personId}`);

  if (!response.ok) throw new Error("couldnt fetch person details.");

  const json = await response.json();

  return personDetailsSchema.parse(json);
}
