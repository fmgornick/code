const mysql = require("mysql");
const bcrypt = require('bcrypt');

const dbCon = mysql.createConnection({
  host: "cse-mysql-classes-01.cse.umn.edu",
  user: "C4131S22U37",
  password: "1399",
  database: "C4131S22U37",
  port: 3306
});

console.log("Attempting database connection");
dbCon.connect(function(err) {
  if (err) {
    throw err;
  }

  console.log("Connected to database!");

  const saltRounds = 10;
  const myPlaintextPassword = 'DrDanIsDaddy';
  const passwordHash = bcrypt.hashSync(myPlaintextPassword, saltRounds);

  const rowToBeInserted = {
    acc_name: 'Fletcher Gornick',
    acc_login: 'fmgornick',
    acc_password: passwordHash
  };

  console.log("Attempting to insert record into tbl_accounts");
  dbCon.query('INSERT tbl_accounts SET ?', rowToBeInserted, function(err, result) {
    if (err) {
      throw err;
    }
    console.log("Table record inserted!");
  });

  dbCon.end();
});
