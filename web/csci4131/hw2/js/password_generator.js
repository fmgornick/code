// Password Generator converted to jQuery
$(document).ready(function() {
  $("#password_button").click(function() {
    var string_length = 10;
    var result = "";
    var id = 0;
    var chars = [
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", // letters
      "0123456789", // numbers
      "!%&@#$^*?_~" // symbols
    ];
    for (var i = 0; i < string_length; i++) { // id will return 0, 1, 2
      id = Math.floor(Math.random() * 3);
      result += chars[id].charAt(Math.floor(Math.random() * chars[id].length));
    }
    $("#password_gen").val(result);
  })
});
