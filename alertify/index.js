// Initialize and add the map
//  
async function initMap() {
  // Request needed libraries.
  const { Map } = await google.maps.importLibrary("maps");
  const { AdvancedMarkerElement } = await google.maps.importLibrary("marker");
  const map = new Map(document.getElementById("map"), {
    center: { lat: 20.29470742341686, lng: 85.74423043751754 },//20.29470742341686, 85.74423043751754
    zoom: 14,
    mapId: "4504f8b37365c3d0",
  });
//
  function createMarker(contentText, position) {
    const priceTag = document.createElement("div");
    priceTag.className = "price-tag";
    priceTag.textContent = "Safe Zone";

    const marker = new AdvancedMarkerElement({
      map,
      position: position,
      content: priceTag,
      // Other marker options go here
    });
    // Optionally, return the marker if you want to do something with it later
    return marker;
  }



  function createCurrentLoactionMarker(contentText, position) {
    const priceTag = document.createElement("div");
    priceTag.className = "current-location";
    priceTag.textContent = "Current Location";

    const marker = new AdvancedMarkerElement({
      map,
      position: position,
      content: priceTag,
      // Other marker options go here
    });
    // Optionally, return the marker if you want to do something with it later
    return marker;
  }




  // Example usage:
  const marker1 = createMarker("Safe Zone 1", { lat: 20.295411352206376, lng: 85.74316811582413 }); //Infy ckt Grnd  20.3408347768432, 85.80455195720134 | 20.295411352206376, 85.74316811582413
  const marker2 = createMarker("Safe Zone 2", { lat: 20.29320092846693, lng: 85.74385534990385}); //Sishu vihar ckt gnd  20.346603924648143, 85.81725387239686 | 20.29320092846693, 85.74385534990385
  const marker3 = createMarker("Safe Zone 3", { lat: 20.295527701007693, lng: 85.74256365259548 });//k-6 ground 20.349570849866947, 85.81628685207684 | 20.295527701007693, 85.74256365259548
  const marker4 = createMarker("Safe Zone 4", { lat:20.295074997907516, lng:  85.74440185233935 });//bbsr golf club 20.34608658843269, 85.80203552993456 | 20.295074997907516, 85.74440185233935
  const marker5 = createMarker("Safe Zone 5", { lat: 20.293969385223214, lng: 85.74532598079627 });//Sailashree vihar park 20.3363766405757, 85.80751935323464 | 20.293969385223214, 85.74532598079627
  const marker6 = createCurrentLoactionMarker("Current Location", { lat: 20.29475543863608, lng: 85.743399625616 });  //20.29475543863608, 85.743399625616
  // You can create as many markers as needed by calling the function with different content and positions.
}

initMap();
















// let map;

// async function iniMap() {
//   // The location of Uluru
//   const position = { lat: 20.340501120438528, lng: 85.80815424671403 };
//   // Request needed libraries.
//   //@ts-ignore
//   const { Map } = await google.maps.importLibrary("maps");
//   const { AdvancedMarkerElement } = await google.maps.importLibrary("marker");

//   // The map, centered at Uluru
//   map = new Map(document.getElementById("map"), {
//     zoom: 17,
//     center: position,
//     mapId: "DEMO_MAP_ID",
//   });

//   // Define the custom marker icon
//   const customMarkerIcon = {
//     path: 'M22-48h-44v43h16l6 5 6-5h16z',
//     fillColor: '#FF0000',
//     fillOpacity: 1,
//     strokeColor: '#000000',
//     strokeWeight: 2,
//     scale: 0.7,
//   };

//   // The marker, positioned at Uluru with the custom icon
//   const marker = new AdvancedMarkerElement({
//     map: map,
//     position: position,
//     title: "Trident Academy of Technology",
    
//   });
// }

// // Call the initMap function to initialize the map
// iniMap();





// A marker with a custom SVG glyph.
// const glyphImg = document.createElement("img");

// glyphImg.src =
//   "https://developers.google.com/maps/documentation/javascript/examples/full/images/google_logo_g.svg";

// const glyphSvgPinElement = new PinElement({
//   glyph: glyphImg,
// });
// const glyphSvgMarkerView = new AdvancedMarkerElement({
//   map,
//   position: { lat: 20.34087687766839, lng:  85.80444336390588
//   },
//   content: glyphSvgPinElement.element,
//   title: "A marker using a custom SVG for the glyph.",
// });


// 20.34087687766839,
//  85.80444336390588









// async function initMap() {
//   // Request needed libraries.
//   const { Map, InfoWindow } = await google.maps.importLibrary("maps");
//   const { AdvancedMarkerElement, PinElement } = await google.maps.importLibrary(
//     "marker",
//   );
//   const map = new google.maps.Map(document.getElementById("map"), {
//     zoom: 17,
//     center: { lat: 20.340501120438528, lng: 85.80815424671403 },
//     //20.340501120438528, 85.80815424671403 - TRIDENT ACADEMY OF TECHNOLOGY
//     mapId: "DEMO_MAP_ID",
//   });
//   const infoWindow = new google.maps.InfoWindow({
//     content: "",
//     disableAutoPan: true,
//   });
//   // Create an array of alphabetical characters used to label the markers.
//   const labels = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//   // Add some markers to the map.
//   const markers = locations.map((position, i) => {
//     const label = labels[i % labels.length];
//     const pinGlyph = new google.maps.marker.PinElement({
//       glyph: label,
//       glyphColor: "white",
//     });
//     const marker = new google.maps.marker.AdvancedMarkerElement({
//       position,
//       content: pinGlyph.element,
//     });

//     // markers can only be keyboard focusable when they have click listeners
//     // open info window when marker is clicked
//     marker.addListener("click", () => {
//       infoWindow.setContent(position.lat + ", " + position.lng);
//       infoWindow.open(map, marker);
//     });
//     return marker;
//   });







//   // Add a marker clusterer to manage the markers.
//   new MarkerClusterer({ markers, map });
// }

// const locations = [
//   { lat: -31.56391, lng: 147.154312 },
//   { lat: -33.718234, lng: 150.363181 },
//   { lat: -33.727111, lng: 150.371124 },
//   { lat: -33.848588, lng: 151.209834 },
//   { lat: -33.851702, lng: 151.216968 },
//   { lat: -34.671264, lng: 150.863657 },
//   { lat: -35.304724, lng: 148.662905 },
//   { lat: -36.817685, lng: 175.699196 },
//   { lat: -36.828611, lng: 175.790222 },
//   { lat: -37.75, lng: 145.116667 },
//   { lat: -37.759859, lng: 145.128708 },
//   { lat: -37.765015, lng: 145.133858 },
//   { lat: -37.770104, lng: 145.143299 },
//   { lat: -37.7737, lng: 145.145187 },
//   { lat: -37.774785, lng: 145.137978 },
//   { lat: -37.819616, lng: 144.968119 },
//   { lat: -38.330766, lng: 144.695692 },
//   { lat: -39.927193, lng: 175.053218 },
//   { lat: -41.330162, lng: 174.865694 },
//   { lat: -42.734358, lng: 147.439506 },
//   { lat: -42.734358, lng: 147.501315 },
//   { lat: -42.735258, lng: 147.438 },
//   { lat: -43.999792, lng: 170.463352 },
// ];

// initMap();










// // Note: This example requires that you consent to location sharing when
// // prompted by your browser. If you see the error "The Geolocation service
// // failed.", it means you probably did not give permission for the browser to
// // locate you.
// let map, infoWindow;

// function initMap() {
//   map = new google.maps.Map(document.getElementById("map"), {
//     center: { lat: -34.397, lng: 150.644 },
//     zoom: 6,
//   });
//   infoWindow = new google.maps.InfoWindow();

//   const locationButton = document.createElement("button");

//   locationButton.textContent = "Pan to Current Location";
//   locationButton.classList.add("custom-map-control-button");
//   map.controls[google.maps.ControlPosition.TOP_CENTER].push(locationButton);
//   locationButton.addEventListener("click", () => {
//     // Try HTML5 geolocation.
//     if (navigator.geolocation) {
//       navigator.geolocation.getCurrentPosition(
//         (position) => {
//           const pos = {
//             lat: position.coords.latitude,
//             lng: position.coords.longitude,
//           };

//           infoWindow.setPosition(pos);
//           infoWindow.setContent("Location found.");
//           infoWindow.open(map);
//           map.setCenter(pos);
//         },
//         () => {
//           handleLocationError(true, infoWindow, map.getCenter());
//         },
//       );
//     } else {
//       // Browser doesn't support Geolocation
//       handleLocationError(false, infoWindow, map.getCenter());
//     }
//   });
// }

// function handleLocationError(browserHasGeolocation, infoWindow, pos) {
//   infoWindow.setPosition(pos);
//   infoWindow.setContent(
//     browserHasGeolocation
//       ? "Error: The Geolocation service failed."
//       : "Error: Your browser doesn't support geolocation.",
//   );
//   infoWindow.open(map);
// }

// window.initMap = initMap;