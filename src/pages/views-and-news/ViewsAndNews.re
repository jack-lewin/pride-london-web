type action =
  | UpdateViews(array(ViewData.view))
  | PaginateViewsBack
  | PaginateViewsForward;

type state = {
  views: array(ViewData.view),
  viewIndex: int
};

let viewsToDisplay = 4;

let component = ReasonReact.reducerComponent("ViewsAndNews");

let make = _children => {
  ...component,

  initialState: () => ({
    /* views: Array.make(4, ViewData.placeholder), */
    views: [|
      {title: "Placeholder 1"},
      {title: "Placeholder 2"},
      {title: "Placeholder 3"},
      {title: "Placeholder 4"},
      {title: "Placeholder 5"},
      {title: "Placeholder 6"},
      {title: "Placeholder 7"},
      {title: "Placeholder 8"},
      {title: "Placeholder 9"},
      {title: "Placeholder 10"},
      {title: "Placeholder 11"}
    |],
    viewIndex: 0
  }),

  didMount: (self) => {
    /* ViewData.getViews()
      |> Js.Promise.then_(
        views => {
          self.send(UpdateViews(views));
          Js.Promise.resolve();
        }
      )
      |> ignore; */

    ReasonReact.NoUpdate;
  },

  reducer: (action, state) =>
    switch (action) {
      | UpdateViews(views) =>
        ReasonReact.Update({...state, views: views})
      | PaginateViewsBack => {
        Js.log("TODO");
        ReasonReact.NoUpdate;
      }
      | PaginateViewsForward => {
        let numViews = Array.length(state.views);
        let newViewIndex = min(state.viewIndex + viewsToDisplay, numViews) mod numViews;

        ReasonReact.Update({...state, viewIndex: newViewIndex})
      }
    },

  render: self =>
    <div>
      <button onClick={(_e) => self.send(PaginateViewsBack)}>
        (ReasonReact.stringToElement("<"))
      </button>
      <button onClick={(_e) => self.send(PaginateViewsForward)}>
        (ReasonReact.stringToElement(">"))
      </button>
      (
        Array.mapi(
          (index, view: ViewData.view) =>
            <View key={"view-" ++ string_of_int(index)} view={view} />,
            Array.sub(
              self.state.views,
              self.state.viewIndex,
              min(viewsToDisplay, Array.length(self.state.views) - self.state.viewIndex)
            )
        )
        |> ReasonReact.arrayToElement
      )
    </div>
};
