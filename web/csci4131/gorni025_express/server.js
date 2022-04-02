// packages
var express = require('express');
var session = require('express-session');
var mysql = require('mysql');
var bcrypt = require('bcrypt');
var bodyparser = require('body-parser');
var handlebars = require('express-handlebars').create();
var url = require('url');
var port = 9001;

// set up database connection
var con = mysql.createConnection({
  host: "cse-mysql-classes-01.cse.umn.edu",
  user: "C4131S22U37",
  password: "1399",
  database: "C4131S22U37",
  port: 3306
});

// connect to database
con.connect(function(err) {
  if (err) throw err;
});

// create express application
const app = express();

// middleware
app.use(bodyparser.urlencoded({ extended: true }));
app.use(bodyparser.json());

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('views', './client');

app.use(session({
  secret: "csci4131secretkey",
  saveUninitialized: true,
  resave: false
}));

app.use('/client', express.static(__dirname + '/client'));

// start listening
app.listen(port, () => console.log('Listening on port', port));

app.get('/', function(req, res) {
  res.sendFile(__dirname + '/client/welcome.html');
});

// if already logged in, send AllContacts page
app.get('/login', function(req, res) {
  if (req.session.loggedIn) res.redirect('/AllContacts');
  // else res.sendFile(__dirname + '/client/login.handlebars');
  else res.render('login', { failure: 0 });
});

// return AllContacts page unless not logged in (then send to login)
app.get('/AllContacts', function(req, res) {
  if (req.session.loggedIn) res.sendFile(__dirname + '/client/AllContacts.html');
  else res.redirect('/login');
});

// return MyContacts page unless not logged in (then send to login)
app.get('/MyContacts', function(req, res) {
  if (req.session.loggedIn) res.sendFile(__dirname + '/client/MyContacts.html');
  else res.redirect('/login');
});

// return AddContact page unless not logged in (then send to login)
app.get('/AddContact', function(req, res) {
  if (req.session.loggedIn) res.sendFile(__dirname + '/client/AddContact.html');
  else res.redirect('/login');
});

// return stocks page unless not logged in (then send to login)
app.get('/stocks', function(req, res) {
  if (req.session.loggedIn) res.sendFile(__dirname + '/client/stocks.html');
  else res.redirect('/login');
});

app.get('/logout', function(req, res) {
  req.session.destroy();
  res.redirect('/login');
});

app.get('/getContacts', function(req, res) {
  con.query("SELECT * FROM contact_table ORDER BY contact_category, contact_name", function(err, result, field) {
    if (err) throw err;
    else res.send(result);
  });
});

// function to return the 404 message and error to client
app.get('*', function(req, res) {
  // add details
  res.sendStatus(404);
});

app.post('/login', function(req, res) {
  let username = req.body.user;
  let password = req.body.password;

  con.query("SELECT * FROM tbl_accounts WHERE acc_login = '" + username + "'", function(err, result, field) {
    if (err) throw err;
    if (result.length === 0) {
      req.session.message = {
        type: 'danger',
        intro: 'ERROR',
        message: 'invalid username, please try again'
      };
      res.render('login', { failure: 1, intro: 'ERROR: ', message: 'invalid username, try again' });
    }
    else {
      bcrypt.compare(password, result[0].acc_password, function(err, isMatch) {
        if (err) throw err;
        if (isMatch) {
          session = req.session;
          session.userid = username;
          req.session.loggedIn = true;
          // req.flash('message', 'success!');
          res.redirect('/AllContacts');
        }
        else {
          res.render('login', { failure: 1, intro: 'ERROR: ', message: 'incorrect password, try again' });
        }
      });
    }
  });
});

app.post('/postContactEntry', function(req, res) {
  var sql = "INSERT INTO contact_table SET ?";
  var values = {
    contact_category: req.body.category.toLowerCase(),
    contact_name: req.body.name,
    contact_location: req.body.location,
    contact_info: req.body.info,
    contact_email: req.body.email,
    website_title: req.body.website_title,
    website_url: req.body.url
  }
  con.query("INSERT INTO contact_table SET ?", values, function(err, result) {
    if (err) throw err;
  });
  res.redirect('/AllContacts');
});
