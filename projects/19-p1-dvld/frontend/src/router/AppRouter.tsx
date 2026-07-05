import DashboardLayout from "@/layouts/dashboard-layout";
import { BrowserRouter, Routes, Route } from "react-router-dom";

export function AppRouter() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<DashboardLayout />}>
          <Route index element={<h1>Dashboard</h1>} />
          <Route path="people" element={<h1>People</h1>}>
            
           </Route>
        </Route>
        <Route path="/login" element={<h1>login</h1>}></Route>
      </Routes>
    </BrowserRouter>
  );
}
