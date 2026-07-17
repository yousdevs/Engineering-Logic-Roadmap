import { Button } from "@/components/ui/button";
import { Plus } from "lucide-react";
import { DataTable } from "@/features/people/components/data-table";
import { columns } from "@/features/people/components/data-table-columns";
import { usePeople } from "@/features/people/hooks/use-people";
import { useSearchParams } from "react-router-dom";
import { Link } from "react-router-dom";

import type { OnChangeFn, PaginationState } from "@tanstack/react-table";

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

    console.log(nextPagination.pageIndex);
    console.log(nextPagination.pageSize);
    setSearchParams({
      page: `${nextPagination.pageIndex + 1}`,
      pageSize: `${nextPagination.pageSize}`,
    });
  };

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
          columns={columns}
          data={data.items}
          onPaginationChange={handlePaginationChange}
          pagination={pagination}
          rowCount={data.total}
        />
      )}
    </>
  );
};
