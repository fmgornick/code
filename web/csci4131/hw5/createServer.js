const http = require('http');
const url = require('url');
const fs = require('fs');
const qs = require('querystring');
const contacts = require('./contacts.json');

const port = 9001;

const file_paths = [
  '/index.html',
  '/MyContacts.html',
  '/AddContact.html'
]

http.createServer(function(req, res) {
  var q = url.parse(req.url, true);

  // sort contacts
  contacts["academic"].sort(function(a, b) { return a.name.localeCompare(b.name); });
  contacts["industry"].sort(function(a, b) { return a.name.localeCompare(b.name); });
  contacts["personal"].sort(function(a, b) { return a.name.localeCompare(b.name); });

  if (q.pathname === '/') {
    indexPage(req, res, '/index.html');
  }
  else if (file_paths.includes(q.pathname)) {
    indexPage(req, res, q.pathname);
  }
  else if (q.pathname === '/getContacts') {
    retContactsObject(req, res);
  }
  else if (q.pathname === '/postContactEntry') {
    addContactObject(req, res);
  }
  else {
    res.writeHead(404, { 'Content-Type': 'text/html' });
    return res.end("404 Not Found");
  }
}).listen(port);


function indexPage(req, res, url) {
  fs.readFile('client' + url, function(err, html) {
    if (err) {
      throw err;
    }
    res.statusCode = 200;
    res.setHeader('Content-type', 'text/html');
    res.write(html);
    res.end();
  });
}

// process and return get request for contacts.json
function retContactsObject(req, res) {
  res.statusCode = 200;
  res.setHeader('Content-type', 'application/json');
  res.write(JSON.stringify(contacts));
  res.end();
}

// process post request
function addContactObject(req, res) {
  var reqBody = '';
  req.on('data', function(data) {
    reqBody += data;
  });
  req.on('end', function() {
    // turn querystring into an object
    var reqObj = qs.parse(reqBody);

    // ready object to push into contacts object
    var category = reqObj.category.toLowerCase();
    delete reqObj.category;

    contacts[category].push(reqObj);
    // sort
    contacts[category].sort(function(a, b) { return a.name.localeCompare(b.name); });
    // sent back to MyContacts page
    indexPage(req, res, '/MyContacts.html');
  });
}
