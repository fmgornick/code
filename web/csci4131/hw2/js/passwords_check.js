// pssword strength checker, rewritten in JavaScript
document.getElementById("password_check").addEventListener("keyup", function() {
  var password = this.value;
  var result = document.getElementById("result");
  var strength = 0;

  if (password.length < 6) {
    result.className = "short";
    result.textContent = "Too Short";
    return;
  }

  if (password.length > 7) strength += 1;
  // If password contains both lower and uppercase characters, increase strength value.
  if (password.match(/([a-z].*[A-Z])|([A-Z].*[a-z])/)) strength += 1;
  // If it has numbers and characters, increase strength value.
  if (password.match(/([a-zA-Z])/) && password.match(/([0-9])/)) strength += 1;
  // If it has one special character, increase strength value.
  if (password.match(/([!,%,&,@,#,$,^,*,?,_,~])/)) strength += 1;
  // If it has two special characters, increase strength value.
  if (password.match(/(.*[!,%,&,@,#,$,^,*,?,_,~].*[!,%,&,@,#,$,^,*,?,_,~])/)) strength += 1;
  // Calculated strength value, we can return messages

  if (strength < 2) {
    result.className = "weak";
    result.textContent = "Weak";
  } else if (strength == 2) {
    result.className = "good";
    result.textContent = "Good";
  } else {
    result.className = "strong";
    result.textContent = "Strong";
  }
});
