import { type CreatePersonRequest } from "@/features/people/types/createPersonRequest";
import { type CreatePersonResponse } from "@/features/people/types/createPersonResponse";

export async function createPerson(
  request: CreatePersonRequest,
): Promise<CreatePersonResponse> {
  const formData = new FormData();

  formData.append("firstName", request.firstName);
  formData.append("secondName", request.secondName);

  if (request.thirdName) formData.append("thirdName", request.thirdName);
  formData.append("lastName", request.lastName);
  formData.append("phoneNumber", request.phoneNumber);

  if (request.email) formData.append("email", request.email);

  formData.append("address", request.address);
  formData.append("gender", request.gender.toString());
  formData.append(
    "dateOfBirth",
    request.dateOfBirth.toISOString().split("T")[0],
  );
  formData.append("nationalNo", request.nationalNo);
  formData.append(
    "nationalityCountryId",
    request.nationalityCountryId.toString(),
  );

  // if (request.image) formData.append("image", request.image);

  formData.append("Image.Action", request.image.action);
  if (request.image.file) formData.append("Image.File", request.image.file);

  
  const res = await fetch("https://localhost:7152/api/people", {
    method: "POST",
    body: formData,
  });

  if (!res.ok) {
    //throw await res.json();

    const err = await res.text();
    console.log(err);
    throw new Error(err);
  }

  return (await res.json()) as CreatePersonResponse;
}
