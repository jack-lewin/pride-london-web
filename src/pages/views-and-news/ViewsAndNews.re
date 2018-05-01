type action =
  | UpdateViews(array(ViewData.view));

type state = {
  views: array(ViewData.view)
};

let component = ReasonReact.reducerComponent("ViewsAndNews");

let make = _children => {
  ...component,

  initialState: () => ({
    views: Array.make(4, ViewData.placeholder)
  }),

  didMount: (self) => {
    ViewData.getViews()
      |> Js.Promise.then_(
        views => {
          self.send(UpdateViews(views));
          Js.Promise.resolve();
        }
      )
      |> ignore;

    ReasonReact.NoUpdate;
  },

  reducer: (action, _state) =>
    switch (action) {
      | UpdateViews(views) =>
        ReasonReact.Update({ views: views })
    },

  render: self =>
    <div>
      (
        Array.mapi(
          (index, view: ViewData.view) =>
            <View key={"view-" ++ string_of_int(index)} view={view} />,
            self.state.views
        )
        |> ReasonReact.arrayToElement
      )
    </div>
};
