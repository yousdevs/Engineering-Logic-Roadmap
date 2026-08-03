


export type EditPersonRequest = {
  id: number;
  firstName: string;
  secondName: string;
  thirdName: string | null;
  lastName: string;
  gender: 0 | 1; // 0 male
  dateOfBirth: Date;
  nationalNo: string;
  nationalityCountryId: number;
  email: string | null;
  phoneNumber: string;
  address: string;
  image: {
    action: "unchanged" | "replaced" | "removed";
    file: File | null;
  };
};


export async function editPerson(request: EditPersonRequest){


    const formData = new FormData();

    formData.append("FirstName", request.firstName);
    formData.append("SecondName", request.secondName);
    if(request.thirdName)
        formData.append("ThirdName", request.thirdName);
    formData.append("LastName", request.lastName);

    formData.append("Gender", request.gender.toString());
    formData.append("DateOfBirth", request.dateOfBirth.toISOString().split("T")[0]);
    formData.append("NationalNo", request.nationalNo);
    formData.append("NationalityCountryId", request.nationalityCountryId.toString());
    if(request.email)
        formData.append("Email", request.email);
    formData.append("phoneNumber",  request.phoneNumber);
    formData.append("Address", request.address);
    formData.append("Image.Action", request.image.action);
    if(request.image.file)
        formData.append("Image.File", request.image.file);

    const res = await fetch(`https://localhost:7152/api/people/${request.id}`, {
        method: "PUT",

        body: formData,
    });

    if(!res.ok)
        throw new Error("Couldnt edit person." + await res.text());


    const json = await res.json();
    return json;
} 