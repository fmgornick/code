
function changeImage(path, alt) {
  document.querySelector("#image img").src = path;
  document.querySelector("#image img").alt = alt;
}

document.getElementById("fletcher_gornick").addEventListener("mouseover", changeImage("../img/fletcher.jpg", "Image of Fletcher"));
