// bunch of variables used throughout the script
let contacts = [{
  name: "Goldy Gopher", location: "Coffman Memorial Union, 300 Washington Ave SE, Minneapolis, MN 55455",
  src: "../img/gophers-mascot.png", alt: "goldy the gopher",
  info: "Our Mascott", lat: 44.9727, lng: -93.2354, distance: 0
}];
let icon = "../img/jake.png";
let map
let placeSelector = document.getElementById("location_category");
let nameSelector = document.getElementById("contact_name");
let table = document.querySelector("table.contacts_table");
let prevWindow = false;
let markers = [];


// create the map and center it at Coffman
function initMap() {
  // The location of UMN campus
  const umn = { lat: 44.9727, lng: -93.23540000000003 };
  // The map, centered at coordinate
  map = new google.maps.Map(document.getElementById("map"), {
    zoom: 15,
    center: umn,
  });
  // The marker, positioned at UMN
  initContactInfo();
  generateMarkers();
  initAutocomplete();
}


// pull contact information from table
function initContactInfo() {
  for (let i = 1; i < table.rows.length; i++) {
    let value = table.rows[i].id

    let name = table.rows[i].cells[0].innerText;
    let location = table.rows[i].cells[2].innerText;
    let info = table.rows[i].cells[3].innerText;

    let image = table.rows[i].cells[3].querySelector(".thumbnail img").src;
    let alt = table.rows[i].cells[3].querySelector(".thumbnail img").alt;

    var option = document.createElement("option");
    option.text = name;
    option.value = value;
    nameSelector.add(option);

    let contact = { name: "", location: "", info: "", src: "" };
    contact.name = name;
    contact.location = location;
    contact.info = info;
    contact.src = image;
    contact.alt = alt;
    contacts.push(contact);
  }
}


// make maps and windows for all the contacts
function generateMarkers() {
  var geocoder = new google.maps.Geocoder();
  for (let i = 0; i < contacts.length; i++) {
    var address = contacts[i].location;
    geocoder.geocode({ 'address': address }, function(results, status) {
      if (status == 'OK') {
        contacts[i].lat = results[0].geometry.location.lat();
        contacts[i].lng = results[0].geometry.location.lng();
        contacts[i].distance = getDistance(contacts[i].lat, contacts[0].lat, contacts[i].lng, contacts[0].lng);
        var marker = new google.maps.Marker({
          map: map,
          position: results[0].geometry.location,
          icon: icon
        });
        if (i == 0) marker.icon = "../img/goldy.png";
        var window = generateWindow(marker, contacts[i].name, contacts[i].src, contacts[i].alt, contacts[i].location);
        marker.addListener("click", () => {
          window.open({
            anchor: marker,
            map,
            shouldFocus: false,
          });
        });
      }
    });
  }
}


// distance calculator that goes under the large image to the right of the table
function getDistance(iLat, fLat, iLng, fLng) {
  iLat /= 57.29577951;
  fLat /= 57.29577951;
  iLng /= 57.29577951;
  fLng /= 57.29577951;

  let distance = 3963.0 * Math.acos((Math.sin(iLat) * Math.sin(fLat)) + Math.cos(iLat) * Math.cos(fLat) * Math.cos(fLng - iLng));
  distance *= 1609.344;
  distance = Math.round(distance * 100) / 100

  return distance;
}


// creates info window with CSS
function generateWindow(marker, name, src, alt, location) {
  // style window
  var div = "<div style=\'font-family: Verdana, sans-serif; text-align: center; font-size: 8pt\'>";
  // name
  var nm = "<h2 style=\'margin: 10px\'>" + name + "</h2>";
  // contains src and alt
  var image = "<img src=\'" + src + "\' alt=\'" + alt + "\' style=\'width: 150px\'><br>";

  // separate commas with breaks, this way the address looks better
  var l = location.split(",");
  var address = "<p>";
  for (let i = 0; i < l.length; i++)
    address += l[i] + "<br>";
  address += "</p>";

  var content = div + nm + image + address + "</div>";

  // create window
  const window = new google.maps.InfoWindow({ content: content });
  google.maps.event.addListener(marker, "click", function() {
    if (prevWindow) prevWindow.close();
    prevWindow = window;
    window.open(map, marker);
  })
  return window
}


// add google maps autocomplete to form on contacts page
function initAutocomplete() {
  const input = document.getElementById("start_location");
  new google.maps.places.Autocomplete(input, {
    componentRestrictions: { "country": ["us"] },
    fields: ["place_id", "geometry", "name"]
  });
}


// creates all the markers and info windows when populating search
function generateNearbyMarkers(results, status) {
  if (markers.length > 0) {
    for (let i = 0; i < markers.length; i++)
      markers[i].setMap(null);
    markers.length = 0;
  }

  if (status == google.maps.places.PlacesServiceStatus.OK) {
    for (var i = 0; i < results.length; i++) {
      let marker = new google.maps.Marker({
        position: {
          lat: results[i].geometry.location.lat(),
          lng: results[i].geometry.location.lng()
        },
        map: map,
      })
      markers.push(marker);
      // get all the needed window attributes from results object
      var name = results[i].name;
      var src;
      if (results[i].photos) {
        src = results[i].photos[0].getUrl();
      } else src = "../img/sowwy.png";
      var alt = "image of " + name;
      var location = results[i].vicinity;

      let window = generateWindow(marker, name, src, alt, location);
      google.maps.event.addListener(marker, "click", function() {
        if (prevWindow) prevWindow.close();
        prevWindow = window;
        window.open(map, marker);
      })
    }
  }
}


// calls the generateWindow function with data from form
let nearby = document.getElementById("nearby_search");
nearby.addEventListener("submit", function() {
  var lat = contacts[0].lat;
  var lng = contacts[0].lng;
  var location = new google.maps.LatLng(lat, lng);

  var type = this["location_category"].value;
  if (type == "other") type = this["other"].value;
  this["other"].value = "";

  var radius = this["radius"].value;

  var request = { location: location, radius: radius, type: [type] };
  service = new google.maps.places.PlacesService(map);
  service.nearbySearch(request, generateNearbyMarkers);
});


// adds directions for form input
let directions = document.getElementById("directions");
directions.addEventListener("submit", function() {
  var startAddress = directions["start_location"].value;
  var end = contacts[this["contact_name"].selectedIndex].location;
  var request;

  console.log(getLocation());
  if (startAddress.length > 0) request = { origin: startAddress, destination: end, travelMode: directions.travel.value }
  else request = { origin: getLocation(), destination: end, travelMode: directions.travel.value }

  var directionsService = new google.maps.DirectionsService();
  var directionsRenderer = new google.maps.DirectionsRenderer();
  directionsRenderer.setMap(map);

  directionsService.route(request, function(result, status) {
    if (status == 'OK')
      directionsRenderer.setDirections(result);
  });
});

function getLocation() {
  if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(function(position) {
      return new google.maps.LatLng(position.coords.latitude, position.coords.longitude);
    }, function(error) {
      alert("location permission denied");
    });
  }
}


// reveals textbox if user chooses other
placeSelector.addEventListener("change", function() {
  let placeCategory = this.value;
  let other = document.getElementById("other");
  if (placeCategory == "other") {
    other.type = "text";
    other.required = "true";
  }
  else {
    document.getElementById("other").type = "hidden";
    other.required = "false";
  }
});


// bunch of event listeners
window.onload = function() {
  for (let i = 1; i < table.rows.length; i++) {
    table.rows[i].addEventListener("mouseover", function() {
      // change large image
      document.querySelector(".contacts_image img").src = this.querySelector(".contacts_table img").src;
      document.querySelector(".contacts_image img").alt = this.querySelector(".contacts_table img").alt;
      // toggle thumbnail visibility
      this.querySelector("td img").style.visibility = "visible"
      // change coordinates text box under image
      document.querySelector(".contacts_image input").value = contacts[i].lat + ", " + contacts[i].lng;
      // change distance value under image
      document.querySelector(".contacts_image span").innerText = contacts[i].distance;
    });

    // hide thumbnail when mouse leaves
    table.rows[i].addEventListener("mouseleave", function() {
      this.querySelector("td img").style.visibility = "hidden";
    });

    // shades current row
    table.rows[i].addEventListener("mouseover", function() {
      this.style.backgroundColor = "rgb(200, 200, 200)";
    });

    // unshades rows when mouse leaves.  Two separate alterations because they have 
    // different row background shadings
    if (i % 2 == 0) {
      table.rows[i].addEventListener("mouseleave", function() {
        this.style.backgroundColor = "rgb(242, 242, 242)";
      });
    } else {
      table.rows[i].addEventListener("mouseleave", function() {
        this.style.backgroundColor = "white";
      });
    }
  }
}
