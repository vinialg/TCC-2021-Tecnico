#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAM 50
#define TAM_INDETERMINADO 5000
#define ARQUIVO_USUARIOS "usuarios.txt"
int usuario_log; // determina qual usuário logou (checar login())
int menu();      // protótipo da func

typedef struct
{
    char cpf[TAM];
    char senha[TAM];
    char nome[TAM];
    double saldoReal;
    double saldoCripto;
    double saldoEthereum;
    double saldoRipple;
    char extrato[TAM_INDETERMINADO];
} Usuario;

Usuario *usuarios = NULL;
int num_usuarios = 0;

void clearbuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Função para salvar os usuários em um arquivo
int salvarUsuarios()
{
    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para salvar os usuários.\n");
        return 0;
    }

    // grava o número de usuários
    fprintf(arquivo, "%d\n", num_usuarios);

    // grava os dados de cada usuário
    for (int i = 0; i < num_usuarios; i++)
    {

        fprintf(arquivo, "%s\n", usuarios[i].nome);
        fprintf(arquivo, "%s\n", usuarios[i].cpf);
        fprintf(arquivo, "%s\n", usuarios[i].senha);
        fprintf(arquivo, "%.2lf\n", usuarios[i].saldoReal);
        fprintf(arquivo, "%.2lf\n", usuarios[i].saldoCripto);
        fprintf(arquivo, "%.2lf\n", usuarios[i].saldoEthereum);
        fprintf(arquivo, "%.2lf\n", usuarios[i].saldoRipple);
        fprintf(arquivo, "%s\n", usuarios[i].extrato);

    }

    fclose(arquivo);
    return 0;
}

// Função para carregar os usuários de um arquivo
int carregarUsuarios()
{
    FILE *arquivo = fopen(ARQUIVO_USUARIOS, "r");
    if (arquivo == NULL)
    {
        printf("Nenhum usuario cadastrado. O arquivo nao foi encontrado.\n");
        return 0;
    }

    fscanf(arquivo, "%d\n", &num_usuarios);
    usuarios = malloc(num_usuarios * sizeof(Usuario));

    // Lê os dados de cada usuário
    for (int i = 0; i < num_usuarios; i++)
    {

        fgets(usuarios[i].nome, TAM, arquivo);
        usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = '\0';

        fgets(usuarios[i].cpf, TAM, arquivo);
        usuarios[i].cpf[strcspn(usuarios[i].cpf, "\n")] = '\0';

        fgets(usuarios[i].senha, TAM, arquivo);
        usuarios[i].senha[strcspn(usuarios[i].senha, "\n")] = '\0';

        fscanf(arquivo, "%lf\n", &usuarios[i].saldoReal);
        fscanf(arquivo, "%lf\n", &usuarios[i].saldoCripto);
        fscanf(arquivo, "%lf\n", &usuarios[i].saldoEthereum);
        fscanf(arquivo, "%lf\n", &usuarios[i].saldoRipple);

        fgets(usuarios[i].extrato, TAM_INDETERMINADO, arquivo);
        usuarios[i].extrato[strcspn(usuarios[i].extrato, "\n")] = '\0';
    }

    fclose(arquivo);
    return 0;
}

// Função de cadastro
int cadastro()
{
    usuarios = realloc(usuarios, (num_usuarios + 1) * sizeof(Usuario));
    if (usuarios == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    printf("Digite o nome: ");

    // strcspn é utilizado para tirar o \n do final da string
    fgets(usuarios[num_usuarios].nome, TAM, stdin);
    usuarios[num_usuarios].nome[strcspn(usuarios[num_usuarios].nome, "\n")] = '\0';

    printf("Digite o CPF: ");
    fgets(usuarios[num_usuarios].cpf, TAM, stdin);
    usuarios[num_usuarios].cpf[strcspn(usuarios[num_usuarios].cpf, "\n")] = '\0';

    printf("Digite a senha: ");
    fgets(usuarios[num_usuarios].senha, TAM, stdin);
    usuarios[num_usuarios].senha[strcspn(usuarios[num_usuarios].senha, "\n")] = '\0';

    usuarios[num_usuarios].saldoReal = 0;
    usuarios[num_usuarios].saldoCripto = 0;
    usuarios[num_usuarios].saldoEthereum = 0;
    usuarios[num_usuarios].saldoRipple = 0;

    strcpy(usuarios[num_usuarios].extrato, "Nova conta sem transacoes até o momento.");

    num_usuarios++;
    printf("\nUsuario cadastrado com sucesso!\n");

    salvarUsuarios();
    return 0;
}

// Função de login
int login()
{
    carregarUsuarios();
    char cpf[TAM];
    char senha[TAM];
    int opcao;
    int encontrado = 0;

    while (encontrado == 0 || opcao == 0)
    {
        printf("\n::::: Bem vindo(a) ao CriptoBank :::::\n");
        printf("Gostaria de realizar login ou cadastro?\n");
        printf("1. Cadastrar Usuario\n");
        printf("2. Login\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        clearbuffer();

        switch (opcao)
        {
        case 1:
            cadastro();
            break;
        case 2:
            printf("Digite o CPF: ");
            fgets(cpf, TAM, stdin);
            cpf[strcspn(cpf, "\n")] = '\0';

            printf("Digite a senha: ");
            fgets(senha, TAM, stdin);
            senha[strcspn(senha, "\n")] = '\0';

            // Procura o usuário pelo CPF e senha
            for (int i = 0; i < num_usuarios; i++)
            {
                if (strcmp(usuarios[i].cpf, cpf) == 0 && strcmp(usuarios[i].senha, senha) == 0)
                {
                    printf("\nLogin realizado com sucesso! Bem-vindo(a), %s!\n", usuarios[i].nome);
                    encontrado = 1;
                    usuario_log = i;
                    break;
                }
            }

            if (!encontrado)
            {
                printf("\nCPF ou senha incorretos.\n");
            }
            break;

        case 0:
            printf("Encerrando o programa...\n");
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("Opção inválida.\n");
            break;
        }
    }

    return 0;
}

// Opções do Menu 🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻🡻

int op_saldo()
{
    carregarUsuarios();
    puts("\n::::: Saldo :::::\n");
    printf("Usuario: %s\n", usuarios[usuario_log].nome);
    printf("CPF: %s\n", usuarios[usuario_log].cpf);
    printf("Reais: %.2lf\n", usuarios[usuario_log].saldoReal);

    menu();
    return 0;
}

int op_extrato()
{
    carregarUsuarios();
    puts("\n::::: Extrato :::::\n");

    char *token = strtok(usuarios[usuario_log].extrato, "/");
    while (token != NULL) {
        printf("%s\n", token); 
        token = strtok(NULL, "/"); 
    }

    menu();
    return 0;
}

int op_deposito()
{

    double reais;
    puts("\n::::: Deposito :::::\n");
    printf("Informe quantos reais deseja depositar: ");
    scanf("%lf", &reais);

    usuarios[usuario_log].saldoReal += reais;

    printf("Voce depositou R$ %.2lf!\n", reais);
    printf("Seu novo saldo em reais é: R$ %.2lf\n", usuarios[usuario_log].saldoReal);

    char lin_extrato[100]; 

    sprintf(lin_extrato, "/+ Deposito R$ %.2lf || Saldo: %.2lf", reais, usuarios[usuario_log].saldoReal);
    
    if(strcmp(usuarios[usuario_log].extrato,"Nova conta sem transacoes até o momento.")== 0){
        strcpy(usuarios[usuario_log].extrato, lin_extrato);
    }
    else {
        strcat(usuarios[usuario_log].extrato, lin_extrato);
    }

    salvarUsuarios();

    menu();
    return 0;
};

int op_saque()
{
    carregarUsuarios();
    double reais;
    puts("\n::::: Saque :::::\n");
    printf("Informe quantos reais deseja sacar: ");
    scanf("%lf", &reais);
    while (reais > usuarios[usuario_log].saldoReal)
    {
        printf("=> Saldo Insuficente\n");
        printf("Informe quantos reais deseja sacar: ");
        scanf("%lf", &reais);
    }

    usuarios[usuario_log].saldoReal -= reais;

    printf("Voce sacou R$ %.2lf!\n", reais);
    printf("Seu novo saldo em reais é: R$ %.2lf\n", usuarios[usuario_log].saldoReal);

    char lin_extrato[100]; 
    sprintf(lin_extrato, "/- Saque R$ %.2lf || Saldo: %.2lf", reais, usuarios[usuario_log].saldoReal);
    strcat(usuarios[usuario_log].extrato, lin_extrato);

    salvarUsuarios();

    menu();
    return 0;
};

int menu()
{
    int selecao;

    printf("\n::::: Selecione uma opção :::::\n");
    puts("1. Consultar Saldo");
    puts("2. Consultar Extrato");
    puts("3. Depositar Reais");
    puts("4. Saque de Reais");
    puts("5. Comprar Criptomoedas");
    puts("6. Vender Criptomoedas");
    puts("7. Atualizar Cotação");
    puts("0. Sair");

    printf("Eu desejo...");
    scanf("%d", &selecao);

    switch (selecao)
    {

    case 0:
        login();
        break;
    case 1:
        op_saldo();
        break;
    case 2:
        op_extrato();
        break;
    case 3:
        op_deposito();
        break;
    case 4:
        op_saque();
        break;
    default:
        break;
    }

    return 0;
}

int main(void)
{
    carregarUsuarios();

    login();

    while (1)
    {
        menu();
    }

    // libera a memória alocada
    free(usuarios);

    return 0;
}