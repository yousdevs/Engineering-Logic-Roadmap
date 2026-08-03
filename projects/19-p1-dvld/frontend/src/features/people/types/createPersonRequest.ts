export type CreatePersonRequest = {
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
