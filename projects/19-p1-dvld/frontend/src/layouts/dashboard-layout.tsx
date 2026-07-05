import { Outlet } from "react-router-dom";

import {
  FilePlusCorner,
  Users,
  CarFront,
  UserRoundCog,
  CircleUserRound,
} from "lucide-react";


export const NavigationMenuItem = (props: {
  label: React.ReactNode;
  icon: React.ReactNode;
}) => {
  return (
    <div className="inline-flex shrink-0 items-center justify-center text-sm font-medium whitespace-nowrap transition-all outline-none focus-visible:border-ring focus-visible:ring-[3px] focus-visible:ring-ring/50     [&_svg:not([class*='size-'])]:size-5 hover:bg-accent hover:text-accent-foreground dark:hover:bg-accent/50 h-8 gap-1.5 rounded-md has-[>svg]:px-2.5 px-2.5  ">
      {props.icon} {props.label}
    </div>
  );
};

export const NavigationMenu = () => {
  
  return (
    <nav className="flex justify-start gap-6">
      <NavigationMenuItem label="Applications" icon={<FilePlusCorner />} />
      <NavigationMenuItem label="People" icon={<Users />} />
      <NavigationMenuItem label="Drivers" icon={<CarFront />} />
      <NavigationMenuItem label="Users" icon={<UserRoundCog />} />
      <NavigationMenuItem label="Account" icon={<CircleUserRound />} />
    </nav>
  );
};

export default function DashboardLayout() {
  return (
    <main className="flex flex-col h-screen px-6 py-5">
      <NavigationMenu />

      <section className="flex-1 overflow-auto">
        <Outlet />
      </section>
    </main>
  );
}
