let url = "http://cdn.contentful.com/spaces/aadqic0acprh/environments/master/entries?content_type=views&access_token=";
let apiToken = "TODO: get from env";

type view = {
  title: string
};

let placeholder: view = {
  title: "Placeholder"
};

let parseViewJson = (json) =>
  json |> Json.Decode.(at(
    ["fields"],
    json => {
      title: field("title", string, json)
    }
  ));

let parseViewsResponseJson = json =>
  Json.parseOrRaise(json) |> Json.Decode.(at([
    "items"
  ], array(parseViewJson)));

let getViews = () => {
  Js.Promise.(
    Bs_fetch.fetch(url ++ apiToken)
    |> then_(Bs_fetch.Response.text)
    |> then_(
      jsonText => {
        let result = parseViewsResponseJson(jsonText);
        resolve(result);
      }
    )
  );
};
