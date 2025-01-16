--Cria a tabela usuarios se ela não existir
CREATE TABLE users (
    id SERIAL PRIMARY KEY,              -- ID único para cada usuário
    name VARCHAR(100) NOT NULL,         -- Nome completo
    email VARCHAR(100) UNIQUE NOT NULL, -- Email único
    password VARCHAR(255) NOT NULL,     -- Hash da senha
    created_at TIMESTAMP DEFAULT NOW(), -- Data de criação do registro
    updated_at TIMESTAMP DEFAULT NOW()  -- Data de última atualização
);

CREATE TABLE sessions (
    id SERIAL PRIMARY KEY,              -- ID da sessão
    user_id INT NOT NULL,               -- ID do usuário (chave estrangeira)
    token VARCHAR(255) UNIQUE NOT NULL, -- Token de sessão único
    created_at TIMESTAMP DEFAULT NOW(), -- Data de criação da sessão
    expires_at TIMESTAMP NOT NULL,      -- Data de expiração
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);


-- CREATE TABLE scores (
--     id SERIAL PRIMARY KEY,               -- ID único da pontuação
--     user_id INT NOT NULL,                -- ID do usuário (chave estrangeira)
--     score INT NOT NULL,                  -- Pontuação do usuário
--     created_at TIMESTAMP DEFAULT NOW(),  -- Data/hora em que a pontuação foi registrada
--     FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
-- );

