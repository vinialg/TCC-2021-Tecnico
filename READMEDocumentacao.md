# Documentação da Exchange de Criptomoedas

**Aluno**: Daniel Barroso de Oliveira  
**R.A**: 22.124.054-2  

**Aluno**: Hendrick Gonçalves Camporese Burielo  
**R.A**: 22.124.038-5  

**Aluno**: Vinicius Alves Gimenez  
**R.A**: 22.124.088-0  

## 1. Objetivo 🎯

A exchange de criptomoedas, da qual nomeamos de **Cripto Bank**, simula a interação de um investidor com uma plataforma de compra e venda de criptomoedas, estas que são moedas digitais emitidas por nenhuma entidade governamental. O Cripto Bank possui funcionalidades de armazenamento de dados do usuário, opções de investimento (Bitcoin, Ripple, Ethereum), extrato, flutuação de cotações e entre outros.

## 2. Forma de Compilação 👨‍💻

O comando `gcc -o main main.c` é usado para compilar um programa em C com o GCC (GNU Compiler Collection), que é o compilador em si. Ao utilizar o comando `gcc`, você está chamando o compilador para processar arquivos de código-fonte C e transformá-los em um programa executável. O argumento `-o main` especifica o nome do arquivo de saída; `-o` significa "output", indicando que o nome do arquivo gerado deve ser o que segue o argumento, neste caso, `main`. Sem o argumento `-o`, o GCC geraria um arquivo executável com o nome padrão `a.out` no Linux/macOS ou `a.exe` no Windows. Com o `-o main`, o arquivo executável é nomeado `main` (ou `main.exe` no Windows). O arquivo `main.c` é o código-fonte escrito em C que está sendo compilado. O GCC processa esse arquivo e, após a compilação, cria o executável. Portanto, o GCC lê o arquivo `main.c`, compila o código contido nele e gera um executável com o nome `main` em vez de usar o nome padrão. Depois disso, é possível executar o arquivo diretamente no terminal, como `.\main.exe` no Windows ou `./main` no Linux/macOS.

## 3. Funcionamento 🧩

### `salvarUsuarios()`

Essa função permite a manipulação do arquivo binário, escrevendo nele informações imputadas pelo usuário. No projeto, as funções de manipulação de arquivo são essenciais para a permanência de dados entre execuções. Ela inicia abrindo o arquivo `usuarios.txt` com a operação *write binary* (ou `wb`), onde ocorre a escrita da quantidade atual de usuários, assim como seus respectivos dados informados e armazenados no struct `Usuario`. Essa função é chamada todas as vezes em que é necessário cadastrar um usuário, ou atualizar informações do mesmo.

### `carregarUsuarios()`

Se a função anterior era responsável por escrever no arquivo binário, esta, por sua vez, abre o arquivo `usuarios.txt` com a operação *read binary* (ou `rb`), se o arquivo existir, lê o número total de usuários seguido dos dados de cada usuário, que são armazenados para consulta nas outras funções.

### `carregarCotacoes()`

Aqui é feita a leitura do arquivo binário `moedas.txt`. Se o arquivo já existir, ele é aberto em modo de leitura binária, e as cotações do Bitcoin, Ethereum, e Ripple são lidos e armazenados no struct `Moedas`. Se o arquivo não for encontrado, a função define valores padrão para as cotações, caso o arquivo exista a função faz a leitura das cotações disponíveis.

### `salvarCotacoes()`

Esta função abre o arquivo em modo de escrita binária e escreve os valores das cotações das criptomoedas no arquivo. Entretanto, só é criado o arquivo para escrita da cotação na primeira chamada da função `op_atlCotacao()`, enquanto o arquivo `moedas.txt` não existir são utilizadas cotações padrão definidas na função anterior.

### `cadastro()`

Realiza cadastro de novos usuários, coletando informações como nome, CPF e senha, realizando o devido tratamento com cada um dos dados. Primeiro, a função verifica se existem mais de dez usuários cadastrados, caso verdadeiro, a função encerra. Caso contrário, a função começa a coleta de dados, perguntando o nome, verificando se o CPF informado possui 11 dígitos ou se este já está cadastrado, e afinal pede uma senha que possua mais que 6 caracteres, permitindo tanto números quanto letras. Então são inicializados os dados iniciais de saldo e extrato do usuário, para que possam ser realizadas as operações futuramente, chamando a função `salvarUsuarios()`, para garantir a integridade dos dados. A cada cadastro, o número de usuários cadastrados é incrementado.

### `login()`

Além do login, essa função mostra a opção para o usuário realizar o `cadastro()` ou sair. O login é o processo que valida as credenciais do usuário, como CPF e senha, permitindo que ele acesse suas informações e execute operações como depósitos, saques e consultas. Essa validação é feita através de um loop `for` que percorre as posições do struct `usuario`, utilizando como parâmetro a quantidade de usuários cadastrados. Se as informações informadas batem com algum dos usuários cadastrados, a função exibe uma mensagem de êxito e registra qual dos usuários realizou o login por meio da variável `usuario_log`, o que vai ser necessário para consultas futuras. O funcionamento do login só é possível graças ao carregamento dos usuários no começo da função realizando a leitura do arquivo para comparação.

### `menu()`

O menu exibe as opções disponíveis para o usuário após o login, apresentando uma interface simples com um conjunto de operações que o usuário pode realizar, como depósitos, saques, consultar saldos, verificar extratos e comprar criptomoedas. A função captura a escolha do usuário, valida se a entrada pertence ao intervalo de 0 a 7, e direciona o programa para a função correspondente à operação selecionada. Esta função é chamada em um loop `while` infinito na `main`, assim o usuário só encerra o programa ao selecionar “0” (que chama a função `login()`), e então seleciona zero novamente para encerrar o programa. Desta forma é possível realizar o logoff do sistema para alternar usuários.

### `op_saldo()`

Acessado através do `menu()`, a opção “saldo” permite que o usuário visualize seu saldo em todas as moedas disponíveis, fazendo a consulta através do carregamento de usuários e buscando as informações armazenadas no struct `usuario` na posição `usuario_log`, desta forma é possível exibir o nome, CPF e saldos.

### `op_extrato()`

Tal como a visualização do saldo, o extrato chama o carregamento de usuários e acessa o extrato através do struct na posição `usuario_log`, todavia, a forma pela qual a visualização ocorre é um pouco mais complexa. Dado que o extrato deve conter no máximo 100 transações de modo que na 101° transação a operação mais antiga seja apagada, projetamos um loop para formatação das linhas do extrato e verificação do limite de processos.

A maneira que escolhemos manusear o extrato é através da concatenação de uma longa string, cada nova operação é adicionada ao fim dessa string no struct `usuario`, com uma “/” para diferenciar processos. Para a leitura dessa string utilizamos a função `strtok()` da biblioteca `<string.h>` que permite dividir a string em partes menores (tokens) com base em um delimitador, neste caso, a barra "/", e, ao ser lida, a função percorre a string separando cada operação individualmente. O tratamento ocorre até não existirem mais barras na string.

No mesmo loop onde é feito a formatação, os tokens são adicionados a um array, que suporta até 100 operações, e incrementamos um contador (`totalop`) para controlarmos o total de processos. Em seguida, ocorre uma verificação do valor armazenado no contador, caso seja maior que 100, todas as operações voltam uma posição para trás, removendo a mais antiga. Então ocorre a exibição das operações armazenadas no array.

### `op_deposito()`

Esta opção do menu chama o carregamento dos dados do usuário para então poder incrementar seu saldo em reais. O usuário insere o valor que deseja adicionar, e a função atualiza o saldo correspondente no sistema chamando a função `salvarUsuarios()`. Além disso, essa função registra a operação no extrato do usuário.

### `op_saque()`

O saque chama o carregamento dos dados do usuário para então poder decrementar seu saldo em reais. Mas antes disso, é necessário informar a senha, só então o usuário insere o valor que deseja sacar, e a função atualiza o saldo correspondente no sistema chamando a função `salvarUsuarios()`. É impossível sacar um valor maior que aquele disponível no saldo em reais. Essa função também registra a operação no extrato do usuário.

### `op_Compramoeda()`

Diferente das outras funções, essa não chama apenas o carregamento de usuários, mas também de cotações (funções previamente discutidas). Antes de realizar a compra, ocorre uma verificação de senha, então é disponibilizado ao usuário as três opções de moeda. Ao selecionar um dos tipos de moeda, é informado ao usuário valores como cotação atual e taxa de compra, em seguida a função pergunta o valor do investimento, esse que não pode ser maior que seu saldo em reais. Caso ele tenha dinheiro suficiente, seu saldo é decrementado, o valor do investimento é decrementado pela taxa de compra e finalmente é calculado o câmbio entre moedas. Ao final da função, o saldo na moeda selecionada é incrementado e uma operação é adicionada no extrato.

### `op_Vendemoeda()`

Possui o mesmo princípio de funcionamento da função de compra de moedas, pedindo inclusive, verificação de senha. Ao selecionar um tipo de moeda, a função informa ao usuário valores como cotação atual e taxa de venda. A função solicita então o valor que o usuário deseja vender, que não pode ser maior que o saldo disponível na criptomoeda escolhida. Caso o usuário tenha saldo suficiente, o valor da venda é processado: o saldo na criptomoeda é decrementado e o valor obtido é incrementado no saldo em reais do usuário. O valor da venda é ajustado pela taxa de venda aplicável.

### `op_atlCotacao()`

Função responsável por atualizar o valor atual das cotações, portanto, inicia fazendo o carregamento das mesmas. Então, utilizando a função `geracotacao()` (Explicada na próxima seção), um valor de 5% a -5%(em decimal) é gerado para simular a flutuação da cotação de criptomoedas em reais. O cálculo da flutuação consiste em multiplicar a cotação atual pela porcentagem gerada, o produto dessa multiplicação é incrementada ao valor da moeda em reais, ou decrementada, caso a função `geracotacao()` retorne um valor negativo. Ao final da função é apresentado ao usuário a transformação dos valores, e então a função `salvarCotacoes()` escreve os novos valores em um arquivo binário para consulta.

## 4. Funções Complementares 🧩

### `geracotacao()`

Gera um valor aleatório, de 5% a -5% (ou, 0,05 e -0,05 em decimal). Aplicando os limitadores a função rand() é possível ter certeza que os valores sempre vão pertencer a este intervalo.

### `clearbuffer()`

Aplicando esta função após a leitura dos dados, principalmente aqueles que usam `scanf()`, garantimos que o buffer de entrada estará limpo e não haverá interferência com leituras subsequentes. A função percorre e descarta caracteres residuais, até encontrar o fim do arquivo (EOF).

### `DataHora()`

A função `DataHora()` obtém a data e hora atuais do sistema. Ela formata esses dados em uma string legível ou diretamente imprime o horário e a data no formato desejado (ex.: DD/MM/AAAA HH:MM). Essa função é chamada em todos os momentos que salvamos informações no extrato.

