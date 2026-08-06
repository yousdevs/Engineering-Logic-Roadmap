import { type CreatePersonRequest } from "@/features/people/types/createPersonRequest";
import { type CreatePersonResponse } from "@/features/people/types/createPersonResponse";

export async function createPerson(
  request: CreatePersonRequest,
): Promise<CreatePersonResponse> {
  const res = await fetch("https://localhost:7152/api/people", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(request),
  });

  if (!res.ok) {
    //throw await res.json();

    const err = await res.text();
    console.log(err);
    throw new Error(err);
  }

  return (await res.json()) as CreatePersonResponse;
}
