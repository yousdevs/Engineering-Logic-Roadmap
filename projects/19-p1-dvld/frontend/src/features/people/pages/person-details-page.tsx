import { useLocation, useNavigate, useParams } from "react-router-dom";
import type { PersonDetails } from "@/features/people/schemas/person-details-schema";
import { usePersonDetails } from "@/features/people/hooks/usePersonDetails";
import {
  Card,
  CardContent,
  CardFooter,
  CardHeader,
} from "@/components/ui/card";
import { Avatar, AvatarFallback, AvatarImage } from "@/components/ui/avatar";
import { Separator } from "@/components/ui/separator";
import { Button } from "@/components/ui/button";
import { Alert, AlertDescription, AlertTitle } from "@/components/ui/alert";
import { CircleCheckIcon } from "lucide-react";
import { cn } from "@/lib/utils";

export const DetailsItem = ({
  label,
  value,
  className,
  ...params
}: {
  label: string;
  value: string;
} & React.ComponentProps<"div">) => {
  return (
    <div className={cn("space-y-1", className)} {...params}>
      <p className="text-sm text-muted-foreground"> {label}</p>

      <p className="font-medium">{value}</p>
    </div>
  );
};

export const PersonDetail = ({
  data,
  onEdit,
}: {
  data: PersonDetails;
  onEdit: () => void;
}) => {
  const fallbackImageUrl = data.gender == 0 ? "/men32.png" : "/women32.png";

  const imageUrl = data.imagePath
    ? "https://localhost:7152/" + data.imagePath
    : fallbackImageUrl;

  return (
    <Card className="w-3xl">
      <CardHeader className="flex flex-row items-center">
        <Avatar className="size-28">
          <AvatarImage src={imageUrl} />
          <AvatarFallback>MS</AvatarFallback>
        </Avatar>

        <div className="space-y-2 ml-20">
          <h2>
            {[
              data?.firstName,
              data?.secondName,
              data?.thirdName ?? "",
              data?.lastName,
            ].join(" ")}
          </h2>

          <DetailsItem
            className="flex flex-row gap-2"
            label="National No"
            value={data.nationalNo}
          />
        </div>
      </CardHeader>

      <Separator />

      <CardContent className="grid grid-cols-3 gap-4">
        <h2 className="col-span-full">Personal Information</h2>
        <DetailsItem
          label="Date Of Birth"
          value={data.dateOfBirth.toISOString().split("T")[0]}
        />
        <DetailsItem
          label="Gender"
          value={data.gender == 0 ? "Male" : "Female"}
        />
        <DetailsItem label="Nationality" value={data.country} />
        <Separator className="col-span-full" />
        <h2 className="col-span-full">Contact Information</h2>
        <DetailsItem label="Phone Number" value={data.phoneNumber} />
        {data.email && <DetailsItem label="Email" value={data.email} />}
        <DetailsItem
          className="col-span-full"
          label="Address"
          value={data.address}
        />
      </CardContent>

      <CardFooter className="flex flex-row gap-4 items-center">
        <Button variant={"outline"} onClick={onEdit}>
          Edit
        </Button>
      </CardFooter>
    </Card>
  );
};

export const PersonDetailsPage = () => {
  const { id } = useParams<{ id: string }>();

  if (!id) throw new Error("Missing personId.");

  const personId = Number(id);

  const { data, isPending, isError, error } = usePersonDetails(personId);
  if (error) console.log(error.message);

  const { state } = useLocation();

  const personJustCreated = state?.created ?? false;

  const navigate = useNavigate();

  return (
    <main className="space-y-4">
      <h1>Person Details</h1>

      <div className="space-y-4">
        {personJustCreated && (
          <div>
            <Alert>
              <CircleCheckIcon />
              <AlertTitle>Person created successfully</AlertTitle>
              <AlertDescription>
                The person has been added to the system successfully.
                <div className="mt-4 flex gap-2">
                  <Button onClick={() => navigate("/people")}>
                    Return to People
                  </Button>
                  <Button
                    variant="outline"
                    onClick={() => navigate("/people/new")}
                  >
                    Add Another
                  </Button>
                </div>
              </AlertDescription>
            </Alert>
          </div>
        )}
        {data && (
          <div className="ml-auto mr-auto w-fit">
            <PersonDetail
              data={data}
              onEdit={() => navigate(`/people/${data.id}/edit`)}
            />
          </div>
        )}
        {isPending && <p>loading ..</p>}
        {isError && <p>error occured. see console</p>}
      </div>
    </main>
  );
};
