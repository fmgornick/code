const http = require('http');
const url = require('url');
const fs = require('fs');
const qs = require('querystring');

const port = 9001;

let file_paths = [
  "MyContacts.html",
  "addContact.html"
]

http.createServer(function(req, res) {
  var q = url.parse(req.url, true);
  if (q.pathname === '/' || q.pathname === '/index.html') {
    indexPage(req, res, 'index.html');
  }
  else if (q.pathname.substring(1) in file_paths) {
    indexPage(req, res, q.pathname.substring(1));
  }
  else {
    res.writeHead(404, { 'Content-Type': 'text/html' });
    return res.end("404 Not Found");
  }
}).listen(port);


function indexPage(req, res, url) {
  fs.readFile('client/' + url, function(err, html) {
    if (err) {
      throw err;
    }
    res.statusCode = 200;
    res.setHeader('Content-type', 'text/html');
    res.write(html);
    res.end();
  });
}
