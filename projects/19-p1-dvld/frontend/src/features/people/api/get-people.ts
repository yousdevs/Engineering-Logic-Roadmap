import { pagedPeopleSchema } from "@/features/people/schemas/person-schema";

export async function getPeople(page: number, pageSize: number) {
  // const offset = (page - 1) * pageSize;

  const response = await fetch(
    `https://localhost:7152/api/people?page=${page}&pageSize=${pageSize}`,
  );

  
  if (!response.ok) throw new Error("failed to fetch people.");

  const json = await response.json();
  return pagedPeopleSchema.parse(json);
}
