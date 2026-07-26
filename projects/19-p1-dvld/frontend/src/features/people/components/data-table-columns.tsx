import { type Person } from "@/features/people/schemas/person-schema";

import type { ColumnDef } from "@tanstack/react-table";
import { MoreHorizontal, ArrowUpDown } from "lucide-react";
import { Button } from "@/components/ui/button";
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuLabel,
  DropdownMenuSeparator,
  DropdownMenuTrigger,
} from "@/components/ui/dropdown-menu";
import { useNavigate } from "react-router-dom";

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

  {
    id: "actions",
    cell: ({ row }) => {
      const person = row.original;

      const navigate = useNavigate();
      return (
        <DropdownMenu>
          <DropdownMenuTrigger asChild>
            <Button variant="ghost" className="h-8 w-8 p-0">
              <span className="sr-only">Open menu</span>
              <MoreHorizontal className="w-4 h-4" />
            </Button>
          </DropdownMenuTrigger>

          <DropdownMenuContent align="end">
            <DropdownMenuLabel>Actions</DropdownMenuLabel>
            <DropdownMenuItem
              onClick={() =>
                navigator.clipboard.writeText(person.id.toString())
              }
            >
              Copy Person ID
            </DropdownMenuItem>
            <DropdownMenuSeparator />
            <DropdownMenuItem onClick={() => navigate(`${person.id}`)}>
              View Person
            </DropdownMenuItem>
            <DropdownMenuItem
              onClick={() => navigate(`${person.id}/edit`)}
            >
              Edit
            </DropdownMenuItem>
            <DropdownMenuItem>Delete</DropdownMenuItem>
            <DropdownMenuItem>Email</DropdownMenuItem>
            <DropdownMenuItem>Phone call</DropdownMenuItem>
          </DropdownMenuContent>
        </DropdownMenu>
      );
    },
  },
];
