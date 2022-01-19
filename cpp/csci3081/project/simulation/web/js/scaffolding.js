$(document).ready(function(){

// dynamic modal menu
$("[data-role=trigger]").on('click', function(){
  $("[data-role=extend]").each(function(){
    $(this).height(0);
    $(this).hide();
  });
  let id = $(this).attr('data-unique');
  $("[data-role=show][data-unique='"+id+"']").toggle();
  $("[data-role=target][data-unique='"+id+"']").toggle();
  $("[data-role=modal][data-unique='"+id+"']").show();
  $("[data-role=extend][data-unique='"+id+"']").show().animate({height: '400px'});
});
$("[data-role=select]").click(function(){
  let url = $(this).attr('data-selected');
  let id = $(this).attr('data-unique');
  $("[data-field='"+id+"']").val(url);
});
if($(".slim.modal:visible")){
  $(window).on('click', function(e){
    if($(e.target).is(".slim.modal")){
      $(".slim.modal").each(function(){
      $(this).hide();
      });
    }
  });
}

let alertCounter = 0;

// generates a notification
$.fn.notify = (type, message) => {
  let wrap = document.getElementById("alert-wrapper");
  let alert = document.createElement("div");
  alert.className = "alert " + alertCounter + " ";
  let icon = document.createElement("div");
  icon.className = "icon ";
  let symbol = document.createElement("i");
  symbol.className = "fas ";
  let content = document.createElement("div");
  content.className = "content ";
  content.innerHTML += message;
  switch(type) {
    case 0:
      symbol.className += "fa-check-circle ";
      symbol.className += "success";
      icon.className += "green-bg";
      content.className += "success-bg green";
      alert.className += "green-border";
      break;
    case 1:
      symbol.className += "fa-skull-crossbones ";
      symbol.className += "danger";
      icon.className += "red-bg";
      content.className += "danger-bg red";
      alert.className += "red-border";
      break;
    case 2:
      symbol.className += "fa-star ";
      symbol.className += "notice";
      icon.className += "blue-bg";
      content.className += "notice-bg blue";
      alert.className += "blue-border";
      break;
    case 3:
      symbol.className += "fa-exclamation-circle ";
      symbol.className += "warning";
      icon.className += "orange-bg";
      content.className += "warning-bg orange";
      alert.className += "orange-border";
      break;
    default: 
      break;
  }
  icon.append(symbol);
  alert.append(icon);
  alert.append(content);
  wrap.append(alert);
  alertCounter++;
  $(".alert").delay(4000).fadeOut(2000);
}

// notify examples
// $.fn.notify(1, "test failure!"); failure
// $.fn.notify(0, "drone has successfully been instantiated!"); success
// $.fn.notify(2, "Need to create console logger function!"); info
// $.fn.notify(3, "This is risky behavior!"); warning

// creates the battery display bar in top left
$.fn.batteryPanel = (val) => {
    let b = document.getElementById("battery-wrapper");
    val *= 100;
    if (val < 25) {
      b.style.backgroundColor = "red";    
    } else if (val >= 25 && val <= 75) {
      b.style.backgroundColor = "yellow";
    } else {
      b.style.backgroundColor = "green";
    }
    b.style.width = val + "%";
}

// does somthing to display depending on observer notification type
$.fn.display = (msg) => {
  // console.log(msg);
  switch (msg.notification.type) {
    case "alert":
      $.fn.notify(2, msg.notification.data);
      break;
    case "battery":
      $.fn.batteryPanel(msg.notification.data);
      break;
    case "statistics":
      break;
  }
}

// creates loading background on dynamic scene change
$("[data-role='scene-trigger']").on('click', function() {
  target = $(this).attr('href');
  scene = undefined;
  $("div#loading-background").show();
  $.fn.run();
  setTimeout(function() { $("div#loading-background").hide(); }, 2000);
});


// modals
const modals = document.querySelectorAll('.modal');
const btn = document.querySelectorAll(".modal-button");
const spans = document.getElementsByClassName("close");
for (let i = 0; i < btn.length; i++) {
  btn[i].onclick = function(e) {
    e.preventDefault();
    let modal = document.querySelector(e.target.getAttribute("href"));
    modal.style.display = "block";
  }
}
for (let i = 0; i < spans.length; i++) {
  spans[i].onclick = function() {
    for (let index in modals) {
      if (typeof modals[index].style !== 'undefined') modals[index].style.display = "none";
    }
  }
}
for (let i = 0; i < spans.length; i++) {
  spans[i].onclick = function() {
    for (let index in modals) {
      if (typeof modals[index].style !== 'undefined') modals[index].style.display = "none";
    }
  }
}
for (let i = 0; i < modals.length; i++){
  modals[i].onclick = function(e){
    for (let index in modals) {
      if (e.target.classList.contains('modal')) modals[index].style.display = "none";
    }
  }
}
  
});      
