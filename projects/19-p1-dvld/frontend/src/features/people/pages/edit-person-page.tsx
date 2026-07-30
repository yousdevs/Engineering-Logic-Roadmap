import { useNavigate, useParams } from "react-router-dom";
import { usePersonDetails } from "@/features/people/hooks/usePersonDetails";
import { useForm } from "react-hook-form";
import {
  PersonformSchema,
  type PersonFormType,
} from "../schemas/person-form-schema";
import { zodResolver } from "@hookform/resolvers/zod";
import { PersonForm } from "../components/person-form";
import { useCountriesQuery } from "@/hooks/useCountriesQuery";
import type { PersonDetails } from "../schemas/person-details-schema";
import { useEffect } from "react";
import type { Country } from "@/schemas/countrySchema";
import { useEditPerson } from "../hooks/useEditPerson";
import { type EditPersonRequest } from "../api/editPerson";
export const EditPersonPage = () => {
  const { id } = useParams<{ id: string }>();

  const personId = Number(id);

  const existingPersonQuery = usePersonDetails(personId);

  const countriesQuery = useCountriesQuery();

  function mapPersonDetailsToForm(
    personDetails: PersonDetails,
    countries: Country[],
  ): PersonFormType {
    return {
      firstName: personDetails.firstName,
      secondName: personDetails.secondName,
      thirdName: personDetails.thirdName,
      lastName: personDetails.lastName,
      gender: personDetails.gender == 0 ? "male" : "female",
      dateOfBirth: personDetails.dateOfBirth,
      address: personDetails.address,
      email: personDetails.email,
      nationality:
        countries[
          countries.findIndex((e) => e.name === personDetails.country)
        ].id.toString(),
      nationalNo: personDetails.nationalNo,
      phoneNumber: personDetails.phoneNumber,
      image: {
        state: "unchanged",
        file: null,
      },
    };
  }

  const form = useForm<PersonFormType>({
    defaultValues: {
      firstName: "",
      secondName: "",
      thirdName: null,
      lastName: "",
      gender: "male",
      address: "",
      dateOfBirth: new Date(),
      email: null,
      nationality: "",
      nationalNo: "",
      phoneNumber: "",
      image: {
        state: "unchanged",
        file: null,
      },
    },
    resolver: zodResolver(PersonformSchema),
  });

  useEffect(() => {
    if (!existingPersonQuery.data || !countriesQuery.data) return;

    form.reset(
      mapPersonDetailsToForm(existingPersonQuery.data, countriesQuery.data),
    );
  }, [existingPersonQuery.data, form, countriesQuery.data]);

  const existingImage = existingPersonQuery.data?.imagePath ?? undefined;

  const existingImageUrl = existingImage
    ? "https://localhost:7152/" + existingImage
    : undefined;

  const navigate = useNavigate();

  const editPersonMutation = useEditPerson(personId);
  const handleSubmit = (data: PersonFormType) => {
    const req: EditPersonRequest = {
      id: personId,
      firstName: data.firstName,
      secondName: data.secondName,
      thirdName: data.thirdName,
      lastName: data.lastName,
      gender: data.gender == "male" ? 0 : 1,
      dateOfBirth: data.dateOfBirth,
      address: data.address,
      email: data.email,
      nationalityCountryId: Number(data.nationality),
      nationalNo: data.nationalNo,
      phoneNumber: data.phoneNumber,
      image: {
        action: data.image.state,
        file: data.image.file,
      },
    };

    editPersonMutation.mutate(req, {
      onSuccess: (res) =>
        navigate(`/people/${res.id}`, {
          state: {
            created: true,
          },
        }),
      onError: (err) => console.log(err.message),
    });
  };
  return (
    <main>
      <PersonForm
        countries={countriesQuery.data}
        form={form}
        onSubmit={handleSubmit}
        existingImageUrl={existingImageUrl}
      />
    </main>
  );
};
