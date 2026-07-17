import { Link, Outlet } from "react-router-dom";

import {
  FilePlusCorner,
  Users,
  CarFront,
  UserRoundCog,
  CircleUserRound,
} from "lucide-react";

import {
  DropdownMenu,
  DropdownMenuContent,
  DropdownMenuTrigger,
} from "@/components/ui/dropdown-menu";
import { Button } from "@/components/ui/button";

type NavigationLinkProps = {
  icon: React.ReactNode;
  children: React.ReactNode;
  to: string;
};
export function NavigationLink({ icon, children, to }: NavigationLinkProps) {
  return (
    <Link
      to={to}
      className="inline-flex shrink-0 items-center justify-center text-sm font-medium whitespace-nowrap transition-all outline-none focus-visible:border-ring focus-visible:ring-[3px] focus-visible:ring-ring/50     [&_svg:not([class*='size-'])]:size-5 hover:bg-accent hover:text-accent-foreground dark:hover:bg-accent/50 h-8 gap-1.5 rounded-md has-[>svg]:px-2.5 px-2.5"
    >
      {icon}
      {children}
    </Link>
  );
}

type NavigationDropdownProps = {
  icon: React.ReactNode;
  label: React.ReactNode;
  children: React.ReactNode;
};

export const NavigationDropdown = (props: NavigationDropdownProps) => {
  return (
    <DropdownMenu>
      <DropdownMenuTrigger asChild>
        <Button variant="ghost">
          {props.icon}
          {props.label}
        </Button>
      </DropdownMenuTrigger>

      <DropdownMenuContent>{props.children}</DropdownMenuContent>
    </DropdownMenu>
  );
};

export const NavigationMenu = () => {
  return (
    <nav className="flex justify-start gap-6 sticky top-0 py-4 bg-background z-9999">
      <NavigationLink to="/people" icon={<FilePlusCorner />}>
        Application
      </NavigationLink>

      <NavigationLink to="/people" icon={<Users />}>
        People
      </NavigationLink>

      <NavigationLink to="/people" icon={<CarFront />}>
        Drivers
      </NavigationLink>

      <NavigationLink to="/people" icon={<UserRoundCog />}>
        Users
      </NavigationLink>

      <NavigationLink to="/people" icon={<CircleUserRound />}>
        Account
      </NavigationLink>

      {/* <NavigationDropdown label="Apppd" icon={<CircleUserRound />}>
        <NavigationLink to="/people" icon={<CircleUserRound />}>
          Account
        </NavigationLink>
        <NavigationLink to="/people" icon={<CircleUserRound />}>
          Account
        </NavigationLink>
      </NavigationDropdown> */}
    </nav>
  );
};

export default function DashboardLayout() {
  return (
    <main className="flex flex-col h-screen px-6 relative">
      <NavigationMenu />

      <section className="flex-1">
        <Outlet />
      </section>
    </main>
  );
}
