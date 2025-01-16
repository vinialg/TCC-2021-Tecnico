// const db = require("./database");

const express = require('express');
const bcrypt = require('bcrypt');
const session = require('express-session');
const bodyParser = require('body-parser');
const db = require('./database');
const http = require('http');
const colors = require('colors');
// const cors = require('cors');
// app.use(cors());


const app = express();
const server = http.createServer(app);
const PORT = 3001;
console.log("Server rodando....");

// Middleware
app.use(express.static('./public'));
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
// res.redirect('/1 Home/index.html');

app.get('/', function (req, res) {
    res.redirect('/1 Home/index.html');
});

// Configuração da sessão
app.use(session({
    secret: 'infousuario',
    resave: false,
    saveUninitialized: true,
}));

// Rota inicial
app.get('/', (req, res) => {
    if (req.session.user) {
        res.send(`Welcome, ${req.session.user.name}! <a href="/logout">Logout</a>`);
    } else {
        res.send('<a href="/login">Login</a> or <a href="/register">Register</a>');
    }
});

// Rota de registro
// app.get('/register', (req, res) => {
//     res.send('<form method="post" action="/register"><input name="username" placeholder="Username"/><input name="password" type="password" placeholder="Password"/><button type="submit">Register</button></form>');
// });

app.post('/register', async (req, res) => {
    const { username, name, email, password, confirm_password } = req.body;

    if (!username || !name || !email || !password || !confirm_password) {
        return res.send('Por favor, preencha todos os campos obrigatórios.');
    }

    if (password !== confirm_password) {
        return res.send('As senhas não coincidem.');
    }

    try {
        const existingUser = await db.oneOrNone('SELECT id FROM users WHERE username = $1 OR email = $2', [username, email]);
        if (existingUser) {
            return res.send('Erro: Nome de usuário ou email já existe.');
        }

        const hashedPassword = await bcrypt.hash(password, 10);
        await db.none('INSERT INTO users (username, name, email, password) VALUES ($1, $2, $3, $4)', [username, name, email, hashedPassword]);
        res.redirect('/1 Home/usuarioregistrado.html');
    } catch (err) {
        res.send('Erro: ' + err.message);
    }
});


// Rota de login
// app.get('/login', (req, res) => {
//     res.send('<form method="post" action="/login"><input name="username" placeholder="Username"/><input name="password" type="password" placeholder="Password"/><button type="submit">Login</button></form>');
// });

app.post("/login", async (req, res) => {
    const { username, password } = req.body;

    try {
        const user = await db.oneOrNone('SELECT id, name, username, password FROM users WHERE username = $1', [username]);

        if (user && await bcrypt.compare(password, user.password)) {
            req.session.user = user;
            res.redirect('/1 Home/usuariologado.html');
        } else {
            res.status(401).send('Invalid credentials. <a href="/login">Try again</a>');
        }
    } catch (err) {
        res.status(500).json({ success: false, message: "Erro interno do servidor" });
    }
});

// Rota de logout
app.get('/logout', (req, res) => {
    req.session.destroy();
    res.redirect('/');
});

// Rota para obter o usuário logado

app.get("/user", (req, res) => {
    if (req.session.user) {
        res.json({ success: true, name: req.session.user.name }); 
    } else {
        res.json({ success: false, message: "Usuário não logado" });
    }
});

// Iniciando o servidor
server.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});


// var http = require('http');
// var express = require('express');
// var colors = require('colors');

// var app = express();

// app.use(express.static('./public'));

// var server = http.createServer(app);

// server.listen(80);

// console.log("Server rodando....".rainbow);

// app.get('/', function (req, res) {
//     res.redirect('/1 Home/index.html');
// });

