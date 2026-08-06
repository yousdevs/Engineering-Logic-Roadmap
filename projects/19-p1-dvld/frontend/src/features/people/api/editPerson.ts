export type EditPersonRequest = {
  firstName: string;
  secondName: string;
  thirdName: string | null;
  lastName: string;
  gender: "Male" | "Female";
  dateOfBirth: Date;
  nationalNo: string;
  nationalityCountryId: number;
  email: string | null;
  phoneNumber: string;
  address: string;
};

export async function editPerson({
  id,
  request,
}: {
  id: number;
  request: EditPersonRequest;
}) {
  const res = await fetch(`https://localhost:7152/api/people/${id}`, {
    method: "PUT",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(request),
  });

  if (!res.ok) throw new Error("Couldnt edit person." + (await res.text()));
}
