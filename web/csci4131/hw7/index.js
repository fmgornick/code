// packages
var fs = require('fs');
var xmlparser = require('xml-js');
var express = require('express');
var session = require('express-session');
var upload = require('express-fileupload');
var handlebars = require('express-handlebars').create();
var mysql = require('mysql');
var url = require('url');
var bodyparser = require('body-parser');
var bcrypt = require('bcrypt');
var port = 9001;

var xmlFile = fs.readFileSync("dbconfig.xml", "utf8");
var xmlObj = JSON.parse(xmlparser.xml2json(xmlFile, { compact: true, spaces: 4 })).dbconfig;

const con = mysql.createConnection({
  host: xmlObj.host._text,
  user: xmlObj.user._text,
  password: xmlObj.password._text,
  database: xmlObj.database._text,
  port: xmlObj.port._text
});

con.connect(function(err) {
  if (err) throw err;
});



// create express application
const app = express();

// middleware
app.use(bodyparser.urlencoded({ extended: true }));
app.use(bodyparser.json());

app.use(upload());

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

// if already logged in, send Admin page
app.get('/login', function(req, res) {
  if (req.session.loggedIn) res.redirect('/admin');
  // else res.sendFile(__dirname + '/client/login.handlebars');
  else res.render('login', { failure: 0 });
});


// return Admin page unless not logged in (then send to login)
app.get('/admin', function(req, res) {
  if (req.session.loggedIn) res.sendFile(__dirname + '/client/admin.html');
  else res.redirect('/login');
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

app.get('/getUsers', function(req, res) {
  con.query("SELECT * FROM tbl_accounts ORDER BY acc_id", function(err, result, field) {
    if (err) throw err;
    else {
      result.push(session.userid);
      res.send(result);
    }
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
          res.redirect('/admin');
        }
        else {
          res.render('login', { failure: 1, intro: 'ERROR: ', message: 'incorrect password, try again' });
        }
      });
    }
  });
});

app.post('/switch', function(req, res) {
  let username = req.body.user;

  session = req.session;
  session.userid = username;
  req.session.loggedIn = true;
});

app.post('/postContactEntry', function(req, res) {
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

app.post('/postUserEntry', function(req, res) {
  var passwordHash = bcrypt.hashSync(req.body.password, 10);
  var values = {
    acc_name: req.body.name,
    acc_login: req.body.login,
    acc_password: passwordHash
  }
  con.query("INSERT INTO tbl_accounts SET ?", values, function(err, result) {
    if (err) throw err;
  });
});

app.post('/deleteRow', function(req, res) {
  var id = req.body.id;
  con.query("DELETE FROM tbl_accounts WHERE acc_id = ?", id, function(err, result) {
    if (err) throw err;
  });
});

app.post('/updateUser', function(req, res) {
  var id = req.body.id;

  if (req.body.newUser) {
    con.query("UPDATE tbl_accounts SET acc_name = ? WHERE acc_id = ?", [req.body.newUser, id], function(err, result) {
      if (err) throw err;
    });
  }

  if (req.body.newLogin) {
    con.query("UPDATE tbl_accounts SET acc_login = ? WHERE acc_id = ?", [req.body.newLogin, id], function(err, result) {
      if (err) throw err;
    });
  }

  if (req.body.newPassword) {
    var passwordHash = bcrypt.hashSync(req.body.newPassword, 10);
    con.query("UPDATE tbl_accounts SET acc_password = ? WHERE acc_id = ?", [passwordHash, id], function(err, result) {
      if (err) throw err;
    });
  }
});

app.post('/postFile', function(req, res) {
  if (req.files) {
    var obj = JSON.parse(req.files.file.data.toString());

    var categories = ["academic", "industry", "personal"];
    for (var i = 0; i < categories.length; i++) {
      for (var j = 0; j < obj[categories[i]].length; j++) {
        var values = {
          contact_category: categories[i],
          contact_name: obj[categories[i]][j].name,
          contact_location: obj[categories[i]][j].location,
          contact_info: obj[categories[i]][j].info,
          contact_email: obj[categories[i]][j].email,
          website_title: obj[categories[i]][j].website_title,
          website_url: obj[categories[i]][j].url,
        }
        con.query("INSERT INTO contact_table SET ?", values, function(err, result) {
          if (err) throw err;
        });
      }
    }
    res.redirect('/AllContacts');
  }
});

// API KEY: 4X5TQHQDOKG0C6YP
