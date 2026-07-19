import { type country, countriesSchema } from "@/schemas/countrySchema";

export async function getCountries(): Promise<country[]> {
  const response = await fetch(`https://localhost:7152/api/countries`);

  if (!response.ok) throw new Error("Failed to fetch countries");
  return countriesSchema.parse(await response.json());
}
