# CSCI 4131 Assignment 6
## <a name="info"></a>Information
- **x500**: gorni025
- **acc_login**: fmgornick
- **acc_password**: DrDanIsDaddy

## Dependencies
Just in case you don't wan't spend the time typing out all the `npm install` commands...

- express
- express-session
- express-fileupload
- express-handlebars
- mysql
- url
- body-parser
- bcrypt

You can install them all at the same time with the following command...
```
npm i express express-session express-fileupload express-handlebars mysql url body-parser bcrypt
```

## Running the Code
Just run the following command in the `gorni025_express` directory
```
node server.js
```
You can view the welcome page by going [here](http://localhost:9001/).  Once routed to the login page, just use the account login and password specified in [Information](#info).

Also, if you want to add a contact via JSON file submission, it must be in a very specific format.  You can see my contacts.json [file](./contacts.json) file to see how it must be formatted.
