import { useCountriesQuery } from "@/hooks/useCountriesQuery";
import { PersonForm } from "@/features/people/components/person-form";
import type { CreatePersonRequest } from "../types/createPersonRequest";

import { useCreatePerson } from "../hooks/useCreatePerson";
import { useNavigate } from "react-router-dom";
import { useForm } from "react-hook-form";
import { zodResolver } from "@hookform/resolvers/zod";
import { usePersonExistsByNationalNoQuery } from "../hooks/usePersonExistsByNationalNoQuery";

import { useDebounce } from "@/hooks/useDebounce";

import {
  type PersonFormType,
  PersonformSchema,
} from "@/features/people/schemas/person-form-schema";
import { eighteenYearsAgo } from "@/features/people/schemas/person-form-schema";
import { useEffect } from "react";

export const AddPersonPage = () => {
  const countriesQuery = useCountriesQuery();

  const createPersonMutation = useCreatePerson();
  const navigate = useNavigate();

  const handleSubmit = (data: PersonFormType) => {
    const req: CreatePersonRequest = {
      firstName: data.firstName,
      secondName: data.secondName,
      thirdName: data.thirdName,
      lastName: data.lastName,
      gender: data.gender,
      dateOfBirth: data.dateOfBirth,
      nationalNo: data.nationalNo,
      nationalityCountryId: Number(data.nationality),
      phoneNumber: data.phoneNumber,
      email: data.email,
      address: data.address,
    };
    createPersonMutation.mutate(req, {
      onSuccess: async (res) => {
        if (data.image.file) {
          const imageForm = new FormData();

          imageForm.append("image", data.image.file);
          const result = await fetch(
            `https://localhost:7152/api/people/${res.id}/image`,
            {
              method: "PUT",
              body: imageForm,
            },
          );
          if (!result.ok) console.log(await result.json());
        }

        navigate(`/people/${res.id}`, {
          state: {
            created: true,
          },
        });
      },
      onError: () => console.log(createPersonMutation.error),
    });
  };

  const form = useForm<PersonFormType>({
    resolver: zodResolver(PersonformSchema),
    defaultValues: {
      firstName: "",
      secondName: "",
      thirdName: null,
      lastName: "",
      dateOfBirth: eighteenYearsAgo,
      gender: "Male",
      email: null,
      phoneNumber: "",
      image: {
        state: "unchanged",
        file: null,
      },
      nationality: "",
      nationalNo: "",
      address: "",
    },
  });

  const nationalNo = form.watch("nationalNo");

  const debouncedNationalNo = useDebounce(nationalNo, 600);
  const existQuery = usePersonExistsByNationalNoQuery(debouncedNationalNo);

  useEffect(() => {
    if (existQuery.data?.exists) {
      form.setError("nationalNo", {
        type: "server",
        message: "nationalNo is linked to another person.",
      });
    } else {
      form.clearErrors("nationalNo");
    }
  }, [existQuery.data, form.setError, form.clearErrors]);

  return (
    <main className="flex justify-center items-center h-full">
      <PersonForm
        countries={countriesQuery.data}
        onSubmit={handleSubmit}
        form={form}
      />
    </main>
  );
};
