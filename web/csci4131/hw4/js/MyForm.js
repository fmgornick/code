function initMap() {
  const umn = { lat: 44.9727, lng: -93.23540000000003 };
  map = new google.maps.Map(document.getElementById("map"), {
    zoom: 15,
    center: umn,
  });
  initAutocomplete();
}

function initAutocomplete() {
  const input = document.getElementById("location");
  new google.maps.places.Autocomplete(input, {
    componentRestrictions: { "country": ["us"] },
    fields: ["place_id", "geometry", "name"]
  });
}

window.onload = function() {
  google.maps.event.addListener(map, "click", (event) => {
    var geocoder = new google.maps.Geocoder();
    geocoder.geocode({
      'latLng': event.latLng
    }, function(results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        if (results[0]) {
          document.getElementById("location").value = results[0].formatted_address;
        }
      }
    });
  });
}
