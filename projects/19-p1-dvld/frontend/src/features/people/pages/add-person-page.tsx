import { useForm, Controller } from "react-hook-form";
import { z } from "zod";
import { zodResolver } from "@hookform/resolvers/zod";

import { toast } from "sonner";
import { Button } from "@/components/ui/button";

import {
  Card,
  CardContent,
  CardDescription,
  CardFooter,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";

import {
  Field,
  FieldContent,
  //   FieldDescription,
  FieldError,
  FieldGroup,
  FieldLabel,
  //   FieldLegend,
  FieldSet,
} from "@/components/ui/field";

import { Textarea } from "@/components/ui/textarea";
import { Input } from "@/components/ui/input";

// import {
//   InputGroup,
//   InputGroupAddon,
//   InputGroupText,
//   InputGroupTextarea,
// } from "@/components/ui/input-group";
import { RadioGroup, RadioGroupItem } from "@/components/ui/radio-group";
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from "@/components/ui/select";
import { useEffect, useMemo, useRef, type ChangeEvent } from "react";
import { usePersonExistsByNationalNoQuery } from "../hooks/usePersonExistsByNationalNoQuery";

import { useDebounce } from "@/hooks/useDebounce";
import { useCountriesQuery } from "@/hooks/useCountriesQuery";
import { type country } from "@/schemas/countrySchema";

const eighteenYearsAgo = new Date();
eighteenYearsAgo.setFullYear(eighteenYearsAgo.getFullYear() - 18);
const formSchema = z.object({
  nationalNo: z
    .string()
    .min(2, "NationalNo must be at least 2 characters.")
    .max(20, "NationalNo must be at most 20 characters."),
  firstName: z
    .string()
    .min(2, "first name must be at least 2 characters.")
    .max(20, "first name must be at most 20 characters."),
  secondName: z
    .string()
    .min(2, "second name must be at least 2 characters.")
    .max(20, "second name must be at most 20 characters."),
  thirdName: z
    .string()
    .min(2, "third name must be at least 2 characters.")
    .max(20, "third name must be at most 20 characters."),
  lastName: z
    .string()
    .min(2, "last name must be at least 2 characters.")
    .max(20, "last name must be at most 20 characters."),
  gender: z.string(),
  dateOfBirth: z
    .preprocess((arg)=>{if (typeof arg === "string" && arg.trim() !== "") {
      return new Date(arg);
    }
    return arg;
  }, z.date())
    .refine(
      (date) => date <= eighteenYearsAgo,
      "age must be at least 18 years old.",
    ),
  nationality: z.string().nonempty("please select a country."),
  phoneNumber: z
    .string()
    .max(20, "Phone number must be at most 20 characters.").nonempty("required."),
  email: z.email().max(50, "email address must be at most 50 characters."),
  address: z.string().max(500, "address most be at most 500 characters.").nonempty("this field is required."),
  image: z
    .instanceof(File)
    .nullable()
    .refine(
      (file) => file == null || file.size <= 5 * 1024 * 1024,
      "Maximum image size is 5 MB",
    )
    .refine(
      (file) =>
        file == null ||
        ["image/jpeg", "image/png", "image/webp"].includes(file?.type),
      "Unsupported image format.",
    ),
});

interface PersonImageFieldProps {
  gender: "male" | "female";
  image: File | null;
  existingImageUrl: string | null;
  onImageChange: (file: File | null) => void;
}

const PersonImageField = ({
  gender, //  for icon (mode new)
  image, // selected image (either mode)
  existingImageUrl, // api image  (mode edit)
  onImageChange,
}: PersonImageFieldProps) => {
  const inputRef = useRef<HTMLInputElement>(null);

  const previewImageUrl = useMemo(() => {
    if (!image) return null;

    return URL.createObjectURL(image);
  }, [image]);

  useEffect(() => {
    return () => {
      if (!previewImageUrl) return;
      URL.revokeObjectURL(previewImageUrl);
    };
  }, [previewImageUrl]);

  const fallbackImageUrl = gender == "male" ? "/men32.png" : "/women32.png";
  const previewUrl = previewImageUrl ?? existingImageUrl ?? fallbackImageUrl;

  const handleImageChange = (e: ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0];
    if (!file) return;

    onImageChange(file);
    e.target.value = ""; // we clear in case user selects the same file twice
  };

  const handleImageRemove = () => {
    onImageChange(null);
  };

  return (
    <div className="">
      <div className="flex justify-center">
        <div className="flex flex-row gap-2">
          <div>
            {previewUrl && (
              <img src={previewUrl} className=" size-24 object-cover" />
            )}
            <input
              ref={inputRef}
              type="file"
              accept="image/*"
              className="sr-only"
              onChange={handleImageChange}
            />
          </div>
          <div className="flex flex-col justify-between py-2">
            <Button type="button" onClick={() => inputRef.current?.click()}>
              change
            </Button>
            <Button
              type="button"
              variant="outline"
              disabled={!image && !existingImageUrl}
              onClick={handleImageRemove}
            >
              remove
            </Button>
          </div>
        </div>
      </div>
    </div>
  );
};

export const PersonForm = ({
  countries,
}: {
  countries: country[] | undefined;
}) => {
  const {
    // register,
    handleSubmit,
    watch,
    formState: { errors },
    control,
    reset,
    setError,
    clearErrors,
  } = useForm<z.infer<typeof formSchema>>({
    resolver: zodResolver(formSchema),
    defaultValues: {
      firstName: "",
      secondName: "",
      thirdName: "",
      lastName: "",
      dateOfBirth: eighteenYearsAgo,
      gender: "male",
      email: "",
      phoneNumber: "",
      image: null,
      nationality: "",
      nationalNo: "",
      address: "",
    },
  });

  const onSubmit = (data: z.infer<typeof formSchema>) => console.log(data);

  const nationalNo = watch("nationalNo");

  const debouncedNationalNo = useDebounce(nationalNo, 600);
  const existQuery = usePersonExistsByNationalNoQuery(debouncedNationalNo);

  useEffect(() => {
    if (existQuery.data?.exists) {
      setError("nationalNo", {
        type: "server",
        message: "nationalNo is linked to another person.",
      });
    } else {
      clearErrors("nationalNo");
    }
  }, [existQuery.data, setError, clearErrors]);

  // useEffect(() => {
  //   if (!nationalNo) return;

  //   clearErrors("nationalNo");
  //   const timeoutId = setTimeout(async () => {
  //     const data = await checkPersonExistsByNationalNo(nationalNo);
  //     if (data.exists) {
  //       setError("nationalNo", {
  //         message: "nationalNo is linked to another person.",
  //       });
  //     }
  //   }, 600);

  //   return () => {
  //     clearTimeout(timeoutId);
  //   };
  // }, [nationalNo]);
  return (
    <Card className="w-full max-w-5xl">
      <CardHeader>
        <CardTitle>Add new person</CardTitle>
        <CardDescription>new person to add</CardDescription>
      </CardHeader>

      <CardContent>
        <form id="form-person" onSubmit={handleSubmit(onSubmit)}>
          <FieldGroup className="flex flex-row">
            <Controller
              name="firstName"
              control={control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel htmlFor="form-person-firstName">
                    First Name
                  </FieldLabel>
                  <Input
                    {...field}
                    id="form-person-firstName"
                    aria-invalid={fieldState.invalid}
                    placeholder="John"
                    autoComplete="off"
                  />
                  {fieldState.invalid && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </Field>
              )}
            />

            <Controller
              name="secondName"
              control={control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel htmlFor="form-person-secondName">
                    Second Name
                  </FieldLabel>

                  <Input
                    {...field}
                    id="form-person-secondName"
                    aria-invalid={fieldState.invalid}
                    placeholder="smith"
                    autoComplete="off"
                  />

                  {fieldState.invalid && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </Field>
              )}
            />

            <Controller
              name="thirdName"
              control={control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel htmlFor="form-person-thirdName">
                    Third Name
                  </FieldLabel>

                  <Input
                    {...field}
                    id="form-person-thirdName"
                    placeholder="joseiph"
                    aria-invalid={fieldState.invalid}
                    autoComplete="off"
                  />

                  {fieldState.invalid && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </Field>
              )}
            />

            <Controller
              name="lastName"
              control={control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel htmlFor="form-person-lastName">
                    Last Name
                  </FieldLabel>

                  <Input
                    {...field}
                    id="form-person-lastName"
                    aria-invalid={fieldState.invalid}
                    placeholder="last"
                    autoComplete="off"
                  />

                  {fieldState.invalid && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </Field>
              )}
            />
          </FieldGroup>

          <FieldGroup className="flex flex-row mt-4">
            <Controller
              name="nationalNo"
              control={control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel htmlFor="form-person-nationalNo">
                    National No
                  </FieldLabel>

                  <Input
                    {...field}
                    id="form-person-nationalNo"
                    placeholder="N12"
                    autoComplete="off"
                    aria-invalid={fieldState.invalid}
                  />

                  {fieldState.invalid && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </Field>
              )}
            />

            <Controller
              name="dateOfBirth"
              control={control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel htmlFor="form-person-dateOfBirth">
                    Date OF Birth
                  </FieldLabel>

                  <Input
                    {...field}
                    value={
                      field.value instanceof Date
                        ? field.value.toISOString().split("T")[0]
                        : field.value || ""
                    }
                    id="form-person-dateOfBirth"
                    aria-invalid={fieldState.invalid}
                    type="date"
                  />

                  {fieldState.invalid && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </Field>
              )}
            />
          </FieldGroup>

          <FieldGroup className="flex flex-row  mt-4">
            <Controller
              name="email"
              control={control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel htmlFor="form-person-email">Email</FieldLabel>

                  <Input
                    {...field}
                    type="email"
                    id="form-person-email"
                    placeholder="example@example.com"
                    aria-invalid={fieldState.invalid}
                    autoComplete="on"
                  />

                  {fieldState.invalid && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </Field>
              )}
            />
            <Controller
              name="phoneNumber"
              control={control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel htmlFor="form-person-phoneNumber">
                    Phone
                  </FieldLabel>

                  <Input
                    {...field}
                    id="form-person-phoneNumber"
                    placeholder="0533442"
                    aria-invalid={fieldState.invalid}
                    autoComplete="off"
                  />

                  {fieldState.invalid && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </Field>
              )}
            />
          </FieldGroup>

          <FieldGroup className="flex flex-row mt-4">
            <Controller
              name="gender"
              control={control}
              render={({ field, fieldState }) => (
                <FieldSet data-invalid={fieldState.invalid}>
                  <FieldLabel>Gender</FieldLabel>

                  <RadioGroup
                    className="flex flex-row "
                    name={field.name}
                    value={field.value}
                    onValueChange={field.onChange}
                  >
                    <FieldLabel htmlFor="form-person-male">
                      <Field
                        orientation="horizontal"
                        data-invalid={fieldState.invalid}
                      >
                        <RadioGroupItem
                          value="male"
                          id="form-person-male"
                          aria-invalid={fieldState.invalid}
                        />{" "}
                        Male
                      </Field>
                    </FieldLabel>

                    <FieldLabel htmlFor="form-person-female">
                      <Field
                        orientation="horizontal"
                        data-invalid={fieldState.invalid}
                      >
                        <RadioGroupItem
                          value="female"
                          id="form-person-female"
                          aria-invalid={fieldState.invalid}
                        />{" "}
                        Female
                      </Field>
                    </FieldLabel>
                  </RadioGroup>

                  {fieldState.invalid && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </FieldSet>
              )}
            />

            <Controller
              name="nationality"
              control={control}
              render={({ field, fieldState }) => (
                <Field orientation="vertical" data-invalid={fieldState.invalid}>
                  <FieldContent>
                    <FieldLabel htmlFor="form-person-nationality">
                      Country
                    </FieldLabel>

                    {fieldState.invalid && (
                      <FieldError errors={[fieldState.error]} />
                    )}
                  </FieldContent>

                  <Select
                    name={field.name}
                    value={field.value}
                    onValueChange={field.onChange}
                  >
                    <SelectTrigger
                      id="form-person-nationality"
                      aria-invalid={fieldState.invalid}
                    >
                      <SelectValue placeholder="Select" />
                    </SelectTrigger>

                    <SelectContent position="item-aligned">
                      {countries &&
                        countries.map((country) => (
                          <SelectItem
                            key={country.id}
                            value={country.id.toString()}
                          >
                            {country.name}
                          </SelectItem>
                        ))}
                      {!countries && (
                        <SelectItem value="-1">loading..</SelectItem>
                      )}
                    </SelectContent>
                  </Select>
                </Field>
              )}
            />
          </FieldGroup>

          <FieldGroup className="mt-4 flex-row items-start gap-6">
            <Controller
              name="address"
              control={control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel>Address</FieldLabel>

                  <Textarea
                    {...field}
                    id="form-person-address"
                    aria-invalid={fieldState.invalid}
                    placeholder="201 st, london, uk .."
                    className="min-h-[100px]"
                  />

                  {fieldState.error && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </Field>
              )}
            />

            <Controller
              name="image"
              control={control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel>Person Image</FieldLabel>
                  <PersonImageField
                    image={field.value}
                    existingImageUrl={null}
                    gender={watch("gender")}
                    onImageChange={field.onChange}
                  />

                  {fieldState.invalid && (
                    <FieldError errors={[fieldState.error]} />
                  )}
                </Field>
              )}
            />
          </FieldGroup>
        </form>
      </CardContent>

      <CardFooter className="flex flex-row justify-start gap-4">
        <Button type="button" variant="outline" onClick={() => reset()}>
          Reset
        </Button>
        <Button type="submit" form="form-person">
          Save
        </Button>
      </CardFooter>
    </Card>
  );
};

export const AddPersonPage = () => {
  const countriesQuery = useCountriesQuery();

  // const countriesMock: country[] = [
  //   { id: 1, name: "France" },
  //   { id: 2, name: "Italy" },
  //   { id: 3, name: "Germany" },
  // ];
  return (
    <main className="flex justify-center items-center h-full">
      <PersonForm countries={countriesQuery.data} />
    </main>
  );
};
