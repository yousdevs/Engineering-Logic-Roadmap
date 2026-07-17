import { AddPersonPage } from "@/features/people/pages/add-person-page";
import { PeopleListPage } from "@/features/people/pages/people-list-page";
import DashboardLayout from "@/layouts/dashboard-layout";
import { BrowserRouter, Routes, Route, Outlet } from "react-router-dom";

export function AppRouter() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<DashboardLayout />}>
          <Route index element={<h1>Dashboard</h1>} />
          <Route path="people" element={<Outlet />}>
            <Route index element={<PeopleListPage />} />
            <Route path="/people/new" element={<AddPersonPage />} />
          </Route>
        </Route>
        <Route path="/login" element={<h1>login</h1>}></Route>
      </Routes>
    </BrowserRouter>
  );
}
