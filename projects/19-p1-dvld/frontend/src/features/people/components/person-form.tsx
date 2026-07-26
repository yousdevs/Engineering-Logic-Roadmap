import { Controller, type UseFormReturn } from "react-hook-form";

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
  FieldError,
  FieldGroup,
  FieldLabel,
  FieldSet,
} from "@/components/ui/field";

import { Textarea } from "@/components/ui/textarea";
import { Input } from "@/components/ui/input";

import { RadioGroup, RadioGroupItem } from "@/components/ui/radio-group";
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from "@/components/ui/select";
import { useEffect, useMemo, useRef, type ChangeEvent } from "react";

import { type Country } from "@/schemas/countrySchema";
import type { PersonFormType } from "../schemas/person-form-schema";

type ImageState = {
  state: "unchanged" | "replaced" | "removed";
  file: File | null;
};
interface PersonImageFieldProps {
  gender: "male" | "female";
  imageState: ImageState;
  existingImageUrl: string | null;
  onImageChange: (imageState: ImageState) => void;
}

const PersonImageField = ({
  gender, //  for icon (mode new)
  imageState, // selected image (either mode)
  existingImageUrl, // api image  (mode edit)
  onImageChange,
}: PersonImageFieldProps) => {
  const inputRef = useRef<HTMLInputElement>(null);

  const previewImageUrl = useMemo(() => {
    if (!imageState.file) return null;

    return URL.createObjectURL(imageState.file);
  }, [imageState]);

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

    onImageChange({ state: "replaced", file });
    e.target.value = ""; // we clear in case user selects the same file twice
  };

  const handleImageRemove = () => {
    onImageChange({ state: "removed", file: null });
  };

  const handleCancelReplacement = () => {
    onImageChange({ state: "unchanged", file: null });
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

            {imageState.state === "unchanged" && existingImageUrl && (
              <Button
                type="button"
                variant="outline"
                disabled={!imageState.file && !existingImageUrl}
                onClick={handleImageRemove}
              >
                remove
              </Button>
            )}

            {imageState.state === "replaced" && (
              <Button
                type="button"
                variant="outline"
                onClick={handleCancelReplacement}
              >
                cancel
              </Button>
            )}
          </div>
        </div>
      </div>
    </div>
  );
};

export const PersonForm = ({
  countries,
  onSubmit,
  form,
}: {
  countries: Country[] | undefined;
  onSubmit: (data: PersonFormType) => void;
  form: UseFormReturn<PersonFormType>;
}) => {
  return (
    <Card className="w-full max-w-5xl">
      <CardHeader>
        <CardTitle>Add new person</CardTitle>
        <CardDescription>new person to add</CardDescription>
      </CardHeader>

      <CardContent>
        <form id="form-person" onSubmit={form.handleSubmit(onSubmit)}>
          <FieldGroup className="flex flex-row">
            <Controller
              name="firstName"
              control={form.control}
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
              control={form.control}
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
              control={form.control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel htmlFor="form-person-thirdName">
                    Third Name
                  </FieldLabel>

                  <Input
                    {...field}
                    id="form-person-thirdName"
                    value={field.value ?? ""}
                    onChange={(e) => field.onChange(e.target.value || null)}
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
              control={form.control}
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
              control={form.control}
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
              control={form.control}
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
                    onChange={(e) => field.onChange(new Date(e.target.value))}
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
              control={form.control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel htmlFor="form-person-email">Email</FieldLabel>

                  <Input
                    {...field}
                    value={field.value ?? ""}
                    onChange={(e) => field.onChange(e.target.value || null)}
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
              control={form.control}
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
              control={form.control}
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
              control={form.control}
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
              control={form.control}
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
              control={form.control}
              render={({ field, fieldState }) => (
                <Field data-invalid={fieldState.invalid}>
                  <FieldLabel>Person Image</FieldLabel>
                  <PersonImageField
                    imageState={field.value}
                    existingImageUrl={null}
                    gender={form.watch("gender")}
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
        <Button type="button" variant="outline" onClick={() => form.reset()}>
          Reset
        </Button>
        <Button type="submit" form="form-person">
          Save
        </Button>
      </CardFooter>
    </Card>
  );
};
