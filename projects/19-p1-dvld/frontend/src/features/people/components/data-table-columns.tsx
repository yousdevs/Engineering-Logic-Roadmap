import { type Person } from "@/features/people/schemas/person-schema";

import type { ColumnDef } from "@tanstack/react-table";
import { ArrowUpDown } from "lucide-react";
import { Button } from "@/components/ui/button";


export const columns: ColumnDef<Person>[] = [
  {
    accessorKey: "id",
    header: "Id",
  },
  {
    accessorKey: "nationalNo",
    header: "National No",
  },
  {
    accessorKey: "firstName",
    header: "FirstName",
  },
  {
    accessorKey: "secondName",
    header: "SecondName",
  },
  {
    accessorKey: "thirdName",
    header: "ThirdName",
  },
  {
    accessorKey: "lastName",
    header: "LastName",
  },
  {
    accessorKey: "gender",
    header: "Gender",
  },
  {
    accessorKey: "dateOfBirth",
    header: () => <div /*{className="text-right"}*/>DateOfBirth</div>,
    cell: ({ row }) => {
      const dateOfBirth = row.getValue<Date>("dateOfBirth");

      return (
        <div className="font-medium">
          {dateOfBirth.toLocaleDateString("en-GB")}
        </div>
      );
    },
  },
  {
    accessorKey: "nationality",
    header: "Nationality",
  },
  {
    accessorKey: "email",
    header: ({ column }) => {
      return (
        <Button
          variant="ghost"
          onClick={() => column.toggleSorting(column.getIsSorted() === "asc")}
        >
          Email
          <ArrowUpDown className="ml-2 h-4 w-4" />
        </Button>
      );
    },
  },
  {
    accessorKey: "phoneNumber",
    header: "PhoneNumber",
  },

 
];
