export type CreatePersonRequest = {
  nationalNo: string;
  firstName: string;
  secondName: string;
  thirdName: string | null;
  lastName: string;
  gender: "Male" | "Female";
  dateOfBirth: Date;
  nationalityCountryId: number;
  phoneNumber: string;
  email: string | null;
  address: string;
};
