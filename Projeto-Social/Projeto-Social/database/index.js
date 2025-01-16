// const pgp = require("pg-promise")();
// const { join } = require ("node:path")

// const db = pgp("postgres://postgres:password@localhost:5432/infousuario");

// Configuração de conexão com o banco de dados
const pgp = require('pg-promise')();
const db = pgp({
    host: 'localhost',
    port: 5432,
    database: 'infousuario',
    user: 'postgres',
    password: 'password'
});

// db.query("SELECT 1 + 1 AS result").then((result) => console.log(result))

module.exports = db