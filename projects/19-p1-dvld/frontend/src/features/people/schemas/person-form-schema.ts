import { z } from "zod";

export const eighteenYearsAgo = new Date();
eighteenYearsAgo.setFullYear(eighteenYearsAgo.getFullYear() - 18);
export const PersonformSchema = z.object({
  nationalNo: z
    .string()
    .min(2, "NationalNo must be at least 2 characters.")
    .max(20, "NationalNo must be at most 20 characters.")
    .nonempty(),
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
    .max(20, "third name must be at most 20 characters.")
    .nullable(),
  lastName: z
    .string()
    .min(2, "last name must be at least 2 characters.")
    .max(20, "last name must be at most 20 characters."),
  gender: z.enum(["male", "female"]).nonoptional(),
  dateOfBirth: z
    // .preprocess((arg) => {
    //   if (typeof arg === "string" && arg.trim() !== "") {
    //     return new Date(arg);
    //   }
    //   return arg;
    // }, z.date())
    .date()
    .refine(
      (date) => date <= eighteenYearsAgo,
      "age must be at least 18 years old.",
    ),
  nationality: z.string().nonempty("please select a country."),
  phoneNumber: z
    .string()
    .max(20, "Phone number must be at most 20 characters.")
    .nonempty("required."),
  email: z
    .email()
    .max(50, "email address must be at most 50 characters.")
    .nullable(),
  address: z
    .string()
    .max(500, "address most be at most 500 characters.")
    .nonempty("this field is required."),
  // image: z
  //   .instanceof(File)
  //   .nullable()
  //   .refine(
  //     (file) => file == null || file.size <= 5 * 1024 * 1024,
  //     "Maximum image size is 5 MB",
  //   )
  //   .refine(
  //     (file) =>
  //       file == null ||
  //       ["image/jpeg", "image/png", "image/webp"].includes(file?.type),
  //     "Unsupported image format.",
  //   ),
  image: z
    .object({
      state: z.enum(["unchanged", "replaced", "removed"]),
      file: z
        .instanceof(File)
        .nullable()
        .refine(
          (file) => file == null || file.size <= 5 * 1024 * 1024,
          "Mazimum image size is 5 MB.",
        )
        .refine(
          (file) =>
            file == null ||
            ["image/jpeg", "image/png", "image/webp"].includes(file?.type),
          "Unsupported image format.",
        ),
    })
    .superRefine((value, ctx) => {
      if (value.state === "replaced" && value.file == null) {
        ctx.addIssue({
          code: "custom",
          message: "A replacement image is required.",
          path: ["file"],
        });
      }

      if (value.state !== "replaced" && value.file != null) {
        ctx.addIssue({
          code: "custom",
          message: "Unexpected Image file.",
          path: ["file"],
        });
      }
    }),
});

export type PersonFormType = z.infer<typeof PersonformSchema>;
