open Jest;

describe("Views and News component", () =>
  test("renders", () => {
    let component = <ViewsAndNews /> |> Enzyme.shallow;
    Expect.expect(Enzyme.length(component)) |> Expect.toBe(1);
  })
);