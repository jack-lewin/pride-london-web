let component = ReasonReact.statelessComponent("View");

let make = (~view: ViewData.view, _children) => {
  ...component,

  render: _self =>
    <div>
      <h1> (view.title |> ReasonReact.stringToElement) </h1>
    </div>
};
