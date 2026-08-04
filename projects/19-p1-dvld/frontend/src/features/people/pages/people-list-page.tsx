import { Button } from "@/components/ui/button";
import { Plus } from "lucide-react";
import { DataTable } from "@/features/people/components/data-table";
import { columns } from "@/features/people/components/data-table-columns";
import { usePeople } from "@/features/people/hooks/use-people";
import { useNavigate, useSearchParams } from "react-router-dom";
import { Link } from "react-router-dom";
import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuItem,
  DropdownMenuLabel,
  DropdownMenuSeparator,
  DropdownMenuTrigger,
} from "@/components/ui/dropdown-menu";
import { MoreHorizontal } from "lucide-react";
import type { OnChangeFn, PaginationState, Row } from "@tanstack/react-table";
import type { Person } from "../schemas/person-schema";
import { useDeletePerson } from "../hooks/useDeletePerson";

export const PeopleListPage = () => {
  const [searchParams, setSearchParams] = useSearchParams({
    page: "1",
    pageSize: "10",
  });
  const pagination = {
    pageIndex: Number(searchParams.get("page") ?? "1") - 1,

    pageSize: Number(searchParams.get("pageSize") ?? "10"),
  };

  const { data, isPending, error } = usePeople(
    pagination.pageIndex + 1,
    pagination.pageSize,
  );

  const handlePaginationChange: OnChangeFn<PaginationState> = (
    updaterOrValue,
  ) => {
    const nextPagination =
      typeof updaterOrValue === "function"
        ? updaterOrValue(pagination)
        : updaterOrValue;

    setSearchParams({
      page: `${nextPagination.pageIndex + 1}`,
      pageSize: `${nextPagination.pageSize}`,
    });
  };

  const deletePersonMutation = useDeletePerson();

  const handleDeletePerson = (id: number) => {
    deletePersonMutation.mutate(id, {
      onError: (err) => console.log(err.message),

      onSuccess: () => console.log(id + "deleted"),
    });
  };

  const navigate = useNavigate();
  const columnsWithActions = [
    ...columns,
    {
      id: "actions",
      cell: ({ row }: { row: Row<Person> }) => {
        const person = row.original;

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
                  navigator.clipboard.writeText(person.personId.toString())
                }
              >
                Copy Person ID
              </DropdownMenuItem>
              <DropdownMenuSeparator />
              <DropdownMenuItem onClick={() => navigate(`${person.personId}`)}>
                View Person
              </DropdownMenuItem>
              <DropdownMenuItem
                onClick={() => navigate(`${person.personId}/edit`)}
              >
                Edit
              </DropdownMenuItem>
              <DropdownMenuItem
                onClick={() => handleDeletePerson(person.personId)}
              >
                Delete
              </DropdownMenuItem>
              <DropdownMenuItem>Email</DropdownMenuItem>
              <DropdownMenuItem>Phone call</DropdownMenuItem>
            </DropdownMenuContent>
          </DropdownMenu>
        );
      },
    },
  ];

  return (
    <>
      <div className="flex justify-between items-center">
        <h1>Manage People</h1>
        <Link to="/people/new">
          <Button>
            {" "}
            <Plus /> New Person
          </Button>
        </Link>
      </div>
      {error && console.log(error)}
      {isPending && <div>loading...</div>}
      {data == null ? (
        <>no data</>
      ) : (
        <DataTable
          columns={columnsWithActions}
          data={data.items}
          onPaginationChange={handlePaginationChange}
          pagination={pagination}
          rowCount={data.totalCount}
        />
      )}
    </>
  );
};
