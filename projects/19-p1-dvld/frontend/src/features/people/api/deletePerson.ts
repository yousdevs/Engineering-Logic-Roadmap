export async function deletePerson(id: number) {
  const res = await fetch(`https://localhost:7152/api/people/${id}`, {
    method: "DELETE",
  });

  if (!res.ok) {
    const msg = await res.text();
    console.log(msg);
    throw new Error(msg);
  }
}
