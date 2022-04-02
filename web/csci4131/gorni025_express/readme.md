# CSCI 4131 Assignment 6
## <a name="info"></a>Information
- **x500**: gorni025
- **acc_login**: fmgornick
- **acc_password**: DrDanIsDaddy

## Dependencies
Just in case you don't wan't spend the time typing out all the `npm install` commands...

- express
- mysql
- url
- body-parser
- bcrypt
- express-session
- express-handlebars

You can install them all at the same time with the following command...
```
npm i express mysql url body-parser bcrypt express-session express-handlebars
```
The express-handlebars package gives a warning about vulnerabilities, but it's the only package I could use that allowed me to notify the user when login fails. Since I'm not using this website for anything important I figured it's not a big deal.

## Running the Code
Just run the following command in the `gorni025_express` directory
```
node server.js
```
You can view the welcome page by going [here](http://localhost:9001/).  Once routed to the login page, just use the account login and password specified in [Information](#info).