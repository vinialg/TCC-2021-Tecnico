const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');

// Variáveis do jogo
let texto = "";
let bolinhas = [];
let pontos = 0;
let userId = null;


const options = [
    { text: 'Impulsividade', x: 150, y: 200, width: 200, height: 50 },
    { text: 'Ansiedade', x: 450, y: 200, width: 200, height: 50 },
    { text: 'Desatenção', x: 150, y: 300, width: 200, height: 50 },
    { text: 'Perder-se nos Detalhes', x: 450, y: 300, width: 200, height: 50 }
];
let mostrarOpcoes = false;

function carregarTexto(nomeArquivo) {
    fetch(nomeArquivo)
        .then(response => {
            if (!response.ok) {
                throw new Error('Erro ao carregar o arquivo');
            }
            return response.text();
        })
        .then(data => {
            texto = data;
            console.log('Texto carregado com sucesso:', texto);
        })
        .catch(error => {
            console.error('Erro ao carregar o arquivo:', error);
        });
}

function getRandomColor() {
    var letters = '0123456789ABCDEF';
    var color = '#';
    for (var i = 0; i < 6; i++) {
        color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
}

function adicionarBolinha() {
    const raio = Math.floor(Math.random() * (40 - 20)) + 20;
    const x = Math.random() * (canvas.width - 2 * raio) + raio;
    const y = Math.random() * (canvas.height - 2 * raio) + raio;
    bolinhas.push({ x, y, raio });
}

function desenharBolinhas() {
    bolinhas.forEach(bolinha => {
        var color = getRandomColor();
        ctx.filter = 'blur(10px)';
        ctx.globalAlpha = 0.5;
        ctx.beginPath();
        ctx.arc(bolinha.x, bolinha.y, bolinha.raio, 0, Math.PI * 2);
        ctx.fillStyle = color;
        ctx.fill();
        ctx.globalAlpha = 1;
        ctx.filter = 'none';
    });
}

function verificarClique(event) {
    const rect = canvas.getBoundingClientRect();
    const mouseX = event.clientX - rect.left;
    const mouseY = event.clientY - rect.top;
    
    if (mostrarOpcoes) {
        const clickedOption = getClickedOption(mouseX, mouseY);
        if (clickedOption) {
            mostrarMensagemErro();
        }
        return;
    }

    bolinhas.forEach((bolinha, index) => {
        if (Math.sqrt((mouseX - bolinha.x) ** 2 + (mouseY - bolinha.y) ** 2) < bolinha.raio) {
            bolinhas.splice(index, 1);
            pontos++;
        }
    });
}

let textoY = canvas.height; // Posição vertical inicial do texto
const velocidade = 2;

function desenharTextoAnimado() {
    ctx.fillStyle = 'black';
    ctx.font = '30px Times New Roman';

    const larguraFolha = canvas.width - 200;
    const x = (canvas.width - larguraFolha) / 2 + 10;
    const limiteLargura = larguraFolha - 20;

    const palavras = texto.split(' ');
    let linhasTexto = [''];

    palavras.forEach(palavra => {
        const medidaPalavra = ctx.measureText(palavra + ' ').width;
        const medidaLinha = ctx.measureText(linhasTexto[linhasTexto.length - 1]).width;
        if (medidaLinha + medidaPalavra <= limiteLargura) {
            linhasTexto[linhasTexto.length - 1] += (linhasTexto[linhasTexto.length - 1] === '' ? '' : ' ') + palavra;
        } 
        else {
            linhasTexto.push(palavra);
        }
    });

    let y = textoY;
    linhasTexto.forEach(linha => {
        ctx.fillText(linha, x, y);
        y += 40; // Aumenta a posição vertical para a próxima linha
    });

    textoY -= velocidade; // Velocidade constante de movimento vertical
}

function drawOptions() {
    options.forEach(option => {
        ctx.fillStyle = '#f0f0f0';
        ctx.fillRect(option.x, option.y, option.width, option.height);
        ctx.strokeRect(option.x, option.y, option.width, option.height);

        ctx.fillStyle = '#000';
        ctx.font = '16px Arial';
        ctx.fillText(option.text, option.x + 10, option.y + 30);
    });
}

function getClickedOption(x, y) {
    const clickedOption = options.find(option => 
        x >= option.x && x <= option.x + option.width && y >= option.y && y <= option.y + option.height
    );

    if (clickedOption) {
        window.location.href = 'resposta.html';
    }

    return clickedOption;
}


function main() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    desenharFundo(textoY); // Chame a função com a posição vertical do texto

    bolinhas = bolinhas.filter(bolinha => bolinha.y + bolinha.raio > 0);
    desenharBolinhas();
    desenharTextoAnimado(); // Chame a função sem passar a posição vertical

    if (textoY < -1420) {
        if (pontos > -1) {
            exibirPergunta(); // Exibe a pergunta quando o texto desaparecer completamente
            bolinhas.length = 0;
            mostrarOpcoes = true; // Define a flag para mostrar opções
            drawOptions(); // Desenha as opções
        }
    }

    exibirPontuacao();
}

function exibirPergunta() {
    ctx.fillStyle = 'white';
    ctx.fillRect(0, 0, 800, 500);
    ctx.strokeStyle = 'black';
    ctx.strokeRect(100, 50, 600, 100);
    ctx.fillStyle = 'black';
    ctx.font = '37px Arial';
    ctx.fillText("Como identificar", 255, 90);
    ctx.fillText("o TDAH sozinho?", 250, 140);
}

function desenharFundo(textoY) {
    const larguraFolha = canvas.width - 200;
    const alturaFolha = textoY + 1380; // Aumente a altura da folha para cobrir o texto

    ctx.fillStyle = '#f9f5e1';
    ctx.fillRect((canvas.width - larguraFolha) / 2, 0, larguraFolha, alturaFolha);

    ctx.strokeStyle = '#e0d7b9';
    const espacamentoHorizontal = 50;
}

function exibirPontuacao() {
    ctx.fillStyle = 'black';
    ctx.font = '20px Arial';
    ctx.fillText('Pontos: ' + pontos, 10, 30);
}

function iniciarJogo() {
    carregarTexto('text.txt'); 
    setInterval(adicionarBolinha, 1000);
    canvas.addEventListener('click', verificarClique);
    setInterval(main, 1000 / 60); 
}

document.getElementById('startButton').addEventListener('click', iniciarJogo);


