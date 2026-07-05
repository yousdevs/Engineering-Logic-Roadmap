import { BrowserRouter, Routes, Route } from "react-router-dom";

export function AppRouter() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<h1>Dashboard</h1>}></Route>
        <Route path="/login" element={<h1>login</h1>}></Route>
      </Routes>
    </BrowserRouter>
  );
}
