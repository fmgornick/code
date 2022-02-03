// retrieves array of all the table rows
let rows = document.querySelectorAll("tr");

// changes source for big image to the right and toggles visibility of thumbnail
function changeImage() {
  document.querySelector("#image img").src = this.querySelector("td img").src;
  document.querySelector("#image img").alt = this.querySelector("td img").alt;
  this.querySelector("td img").style.visibility = "visible"
}

// makes thumbnail invisible when mouse leaves a row
function makeInvisible() {
  this.querySelector("td img").style.visibility = "hidden";
}

for (let i = 1; i < rows.length; i++) {
  rows[i].addEventListener("mouseover", changeImage);
  rows[i].addEventListener("mouseleave", makeInvisible);
  // shades current row
  rows[i].addEventListener("mouseover", function() {
    this.style.backgroundColor = "rgb(200, 200, 200)";
  });

  // unshades rows when mouse leaves.  Two separate alterations because they have 
  // different row background shadings
  if (i % 2 == 0) {
    rows[i].addEventListener("mouseleave", function() {
      this.style.backgroundColor = "rgb(242, 242, 242)";
    });
  } else {
    rows[i].addEventListener("mouseleave", function() {
      this.style.backgroundColor = "white";
    });
  }
}
