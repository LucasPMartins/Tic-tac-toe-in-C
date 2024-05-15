#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h> //sleep

#define ANSI_COLOR_RED "\x1b[31m" // coloca cor nos textos
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m" // cor padrao

// Esboço do designe do jogo da velha (menu)
typedef struct
{
    char nome[50];
    char senha[10];
    int vitorias;
    int derrotas;
} Player;

void imprimelento(char *p, int N);
void imprimecolorido(char *p);

void print_logo();

Player *lerRanking(const char *nomeArquivo, int *tamanho);
void salvarRanking(const char *nomeArquivo, Player *ranking, int tamanho);
void printRanking(Player *jogadores, int numJogadores);

Player *adicionarJogador(Player *jogadores, int *numJogadores);
Player *retornaJogador(Player *jogadores, int numJogadores, char *nome, char *senha);

void printBoard(int Board[3][3]);
void inicializaBoard(int Board[3][3]);
int boardVazio(int Board[3][3]);
int espacoVazio(int Board[3][3]);

void iniciarJogo(Player *jogador, int dificulade);
void printMenuJogar(Player *jogador);
int verificaVitoria(int Board[3][3]);
void bot(int Board[3][3], int Dificuldade);

int main()
{
    int indiceSelecionado = 0, dificuldade = 0, sair = 0;
    char opcao;
    char nome[50], senha[10];
    int i;
    Player *jogadores = malloc(sizeof(Player));
    Player *jogador = malloc(sizeof(Player));
    int numJogadores = 0;

    jogadores = lerRanking("ranking.txt", &numJogadores);

    do
    {
        system("cls"); // Limpa a tela
        print_logo();
        printf("\n");

        // Imprime as opções com a seta indicando a seleção
        if (indiceSelecionado == 0) // JOGAR
        {
            printf(ANSI_COLOR_YELLOW);
            printf("   JOGAR ");
            printf(ANSI_COLOR_RESET);
        }
        else
        {
            printf("   JOGAR ");
        }
        if (indiceSelecionado == 1) // RANKING
        {
            printf(ANSI_COLOR_YELLOW);
            printf("  RANKING ");
            printf(ANSI_COLOR_RESET);
        }
        else
        {
            printf("  RANKING ");
        }
        if (indiceSelecionado == 2) // CONFIGURAÇÔES
        {
            printf(ANSI_COLOR_YELLOW);
            printf("  CONFIGURACOES ");
            printf(ANSI_COLOR_RESET);
        }
        else
        {
            printf("  CONFIGURACOES ");
        }
        if (indiceSelecionado == 3) // SAIR
        {
            printf(ANSI_COLOR_YELLOW);
            printf("  SAIR\n\n");
            printf(ANSI_COLOR_RESET);
        }
        else
        {
            printf("  SAIR\n\n");
        }

        // Lê a tecla pressionada
        opcao = getch();

        // Atualiza a seleção com base na tecla pressionada
        switch (opcao)
        {
        case 'a':
        case 'A':
        case 75: // Código ASCII para seta para cima
            indiceSelecionado = (indiceSelecionado - 1 + 4) % 4;
            break;
        case 'd':
        case 'D':
        case 77: // Código ASCII para seta para baixo
            indiceSelecionado = (indiceSelecionado + 1) % 4;
            break;
        case 13:                        // Código ASCII para tecla Enter
            if (indiceSelecionado == 0) // JOGAR
            {
                indiceSelecionado = 0;
                do
                {
                    system("cls"); // Limpa a tela
                    printf(".------------------------------------------.\n");
                    printf("|");
                    printf(ANSI_COLOR_YELLOW);
                    printf("                J O G A R                 ");
                    printf(ANSI_COLOR_RESET);
                    printf("|\n");
                    printf("'------------------------------------------'\n\n");

                    // Imprime as opções com a seta indicando a seleção
                    if (indiceSelecionado == 0) // CONTINUAR
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("     CONTINUAR");
                        printf(ANSI_COLOR_RESET);
                    }
                    else
                    {
                        printf("     CONTINUAR");
                    }
                    if (indiceSelecionado == 1) // NOVO JOGO
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("    NOVO JOGO");
                        printf(ANSI_COLOR_RESET);
                    }
                    else
                    {
                        printf("    NOVO JOGO");
                    }
                    if (indiceSelecionado == 2) // VOLTAR
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("    VOLTAR\n");
                        printf(ANSI_COLOR_RESET);
                    }
                    else
                    {
                        printf("    VOLTAR\n");
                    }

                    // Lê a tecla pressionada
                    opcao = getch();

                    // Atualiza a seleção com base na tecla pressionada
                    switch (opcao)
                    {
                    case 'a':
                    case 'A':
                    case 75: // Código ASCII para seta para esquerda
                        indiceSelecionado = (indiceSelecionado - 1 + 3) % 3;
                        break;
                    case 'd':
                    case 'D':
                    case 77: // Código ASCII para seta para direita
                        indiceSelecionado = (indiceSelecionado + 1) % 3;
                        break;
                    case 13:                        // Código ASCII para tecla Enter
                        if (indiceSelecionado == 0) // CONTINUAR
                        {
                            i = 3;
                            do
                            {
                                printf("\nDigite seu nome: ");
                                printf(ANSI_COLOR_YELLOW);
                                setbuf(stdin, NULL);
                                scanf("%s", &nome);
                                printf(ANSI_COLOR_RESET);
                                printf("\nDigite sua senha: ");
                                printf(ANSI_COLOR_YELLOW);
                                setbuf(stdin, NULL);
                                scanf("%s", &senha);
                                printf(ANSI_COLOR_RESET);
                                senha[strcspn(senha, "\n")] = '\0';
                                nome[strcspn(nome, "\n")] = '\0';
                                jogador = retornaJogador(jogadores, numJogadores, nome, senha);
                                if (jogador == NULL) // Usuario não encontrado
                                {
                                    printf(ANSI_COLOR_RED);
                                    printf("\nNome de Usuario ou Senha Invalidos! Tentativas: %d\n", i - 1);
                                    printf(ANSI_COLOR_RESET);
                                    i--;
                                }
                                else // Usuario encontrado e senha correta
                                {
                                    break;
                                }
                            } while (i > 0); // Encontrou o jogador
                            if (jogador != NULL)
                            {
                                printf(ANSI_COLOR_YELLOW);
                                printf("\nCARREGANDO");
                                i = 3;
                                while (i > 0)
                                {
                                    imprimelento("...", 250);
                                    printf("\b\b\b   \b\b\b");
                                    i--;
                                }
                                printf(ANSI_COLOR_RESET);
                                iniciarJogo(jogador, dificuldade);
                            }
                        }
                        else if (indiceSelecionado == 1) // NOVO JOGO
                        {
                            jogador = adicionarJogador(jogadores, &numJogadores);
                            if (jogador != NULL) // Jogador criado com sucesso
                            {
                                printf(ANSI_COLOR_YELLOW);
                                printf("\nSALVANDO");
                                i = 3;
                                while (i > 0)
                                {
                                    imprimelento("...", 250);
                                    printf("\b\b\b   \b\b\b");
                                    i--;
                                }
                                printf(ANSI_COLOR_RESET);
                                iniciarJogo(jogador, dificuldade);
                            }
                        }
                        else if (indiceSelecionado == 2) // VOLTAR
                        {
                            sair = 1;
                            break;
                        }
                        break;
                    default:
                        break;
                    }
                } while (opcao != 27 && !sair); // Loop até que a tecla Esc (código ASCII 27) seja pressionada
                indiceSelecionado = 0;
                sair = 0;
            }
            if (indiceSelecionado == 1) // RANKING
            {
                printRanking(jogadores, numJogadores);
                printf("\n");
                printf(ANSI_COLOR_YELLOW);
                system("pause");
                printf(ANSI_COLOR_RESET);
            }
            if (indiceSelecionado == 2) // CONFIGURAÇÔES
            {
                indiceSelecionado = 0;
                do
                {
                    system("cls"); // Limpa a tela
                    printf(".------------------------------------------.\n");
                    printf("|");
                    printf(ANSI_COLOR_YELLOW);
                    printf("         C O N F I G U R A C O E S        ");
                    printf(ANSI_COLOR_RESET);
                    printf("|\n");
                    printf("'------------------------------------------'\n\n");

                    // Imprime as opções com a seta indicando a seleção
                    if (indiceSelecionado == 0) // DIFICULDADE
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("  DIFICULDADE ");
                        printf(ANSI_COLOR_RESET);
                    }
                    else
                    {
                        printf("  DIFICULDADE ");
                    }
                    if (indiceSelecionado == 1) // CREDITOS
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("  CREDITOS ");
                        printf(ANSI_COLOR_RESET);
                    }
                    else
                    {
                        printf("  CREDITOS ");
                    }
                    if (indiceSelecionado == 2) // SOBRE
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("  SOBRE ");
                        printf(ANSI_COLOR_RESET);
                    }
                    else
                    {
                        printf("  SOBRE ");
                    }
                    if (indiceSelecionado == 3) // VOLTAR
                    {
                        printf(ANSI_COLOR_YELLOW);
                        printf("  VOLTAR\n\n");
                        printf(ANSI_COLOR_RESET);
                    }
                    else
                    {
                        printf("  VOLTAR\n\n");
                    }

                    // Lê a tecla pressionada
                    opcao = getch();

                    // Atualiza a seleção com base na tecla pressionada
                    switch (opcao)
                    {
                    case 'a':
                    case 'A':
                    case 75: // Código ASCII para seta para cima
                        indiceSelecionado = (indiceSelecionado - 1 + 4) % 4;
                        break;
                    case 'd':
                    case 'D':
                    case 77: // Código ASCII para seta para baixo
                        indiceSelecionado = (indiceSelecionado + 1) % 4;
                        break;
                    case 13:                        // Código ASCII para tecla Enter
                        if (indiceSelecionado == 0) // DIFICULDADE
                        {
                            indiceSelecionado = 0;
                            do
                            {
                                system("cls"); // Limpa a tela
                                printf(".------------------------------------------.\n");
                                printf("|");
                                printf(ANSI_COLOR_YELLOW);
                                printf("           D I F I C U L D A D E          ");
                                printf(ANSI_COLOR_RESET);
                                printf("|\n");
                                printf("'------------------------------------------'\n\n");

                                // Imprime as opções com a seta indicando a seleção
                                if (indiceSelecionado == 0) // FACIL
                                {
                                    printf(ANSI_COLOR_YELLOW);
                                    printf("    FACIL ");
                                    printf(ANSI_COLOR_RESET);
                                }
                                else
                                {
                                    printf("    FACIL ");
                                }
                                if (indiceSelecionado == 1) // NORMAL
                                {
                                    printf(ANSI_COLOR_YELLOW);
                                    printf("  NORMAL ");
                                    printf(ANSI_COLOR_RESET);
                                }
                                else
                                {
                                    printf("  NORMAL ");
                                }
                                if (indiceSelecionado == 2) // IMPOSSIVEL
                                {
                                    printf(ANSI_COLOR_YELLOW);
                                    printf("  IMPOSSIVEL ");
                                    printf(ANSI_COLOR_RESET);
                                }
                                else
                                {
                                    printf("  IMPOSSIVEL ");
                                }
                                if (indiceSelecionado == 3) // VOLTAR
                                {
                                    printf(ANSI_COLOR_YELLOW);
                                    printf("  VOLTAR\n\n");
                                    printf(ANSI_COLOR_RESET);
                                }
                                else
                                {
                                    printf("  VOLTAR\n\n");
                                }

                                // Lê a tecla pressionada
                                opcao = getch();

                                // Atualiza a seleção com base na tecla pressionada
                                switch (opcao)
                                {
                                case 'a':
                                case 'A':
                                case 75: // Código ASCII para seta para cima
                                    indiceSelecionado = (indiceSelecionado - 1 + 4) % 4;
                                    break;
                                case 'd':
                                case 'D':
                                case 77: // Código ASCII para seta para baixo
                                    indiceSelecionado = (indiceSelecionado + 1) % 4;
                                    break;
                                case 13:                        // Código ASCII para tecla Enter
                                    if (indiceSelecionado == 0) // FACIL
                                    {
                                        dificuldade = 0;
                                    }
                                    else if (indiceSelecionado == 1) // NORMAL
                                    {
                                        dificuldade = 1;
                                    }
                                    else if (indiceSelecionado == 2) // IMPOSSIVEL
                                    {
                                        dificuldade = 2;
                                    }
                                    else if (indiceSelecionado == 3) // VOLTAR
                                    {
                                        sair = 1;
                                        break;
                                    }
                                    printf(ANSI_COLOR_YELLOW);
                                    printf("SALVANDO");
                                    i = 3;
                                    while (i > 0)
                                    {
                                        imprimelento("...", 250);
                                        printf("\b\b\b   \b\b\b");
                                        i--;
                                    }
                                    printf(ANSI_COLOR_RESET);
                                    sair = 1;
                                    break;
                                default:
                                    break;
                                }
                            } while (opcao != 27 && !sair); // Loop até que a tecla Esc (código ASCII 27) seja pressionada
                            indiceSelecionado = 0;
                            sair = 0;
                        }
                        else if (indiceSelecionado == 1) // CREDITOS
                        {
                            system("cls");
                            printf(".------------------------------------------.\n");
                            printf("|");
                            printf(ANSI_COLOR_YELLOW);
                            printf("              C R E D I T O S             ");
                            printf(ANSI_COLOR_RESET);
                            printf("|\n");
                            printf("'------------------------------------------'\n\n");
                            printf(ANSI_COLOR_YELLOW);
                            imprimelento("Agradecimentos Especiais:", 50);
                            printf(ANSI_COLOR_RESET);
                            imprimelento("\nProf. Me. Claudiney R. Tinoco \nProf. Dra. Amanda C. Davi Resende\n", 50);
                            printf(ANSI_COLOR_YELLOW);
                            imprimelento("Desenvolvedores:", 50);
                            printf(ANSI_COLOR_RESET);
                            imprimelento("\nLucas Martins\nLucas Araujo\n\n", 50);
                            printf(ANSI_COLOR_YELLOW);
                            system("pause");
                            printf(ANSI_COLOR_RESET);
                        }
                        else if (indiceSelecionado == 2) // SOBRE
                        {
                            system("cls");
                            printf(".------------------------------------------.\n");
                            printf("|");
                            printf(ANSI_COLOR_YELLOW);
                            printf("                 S O B R E                ");
                            printf(ANSI_COLOR_RESET);
                            printf("|\n");
                            printf("'------------------------------------------'\n\n");
                            printf(ANSI_COLOR_YELLOW);
                            printf("Nome do Progama: ");
                            printf(ANSI_COLOR_RESET);
                            printf("Game of  Old Woman Premium \nPro Max Plus\n");
                            printf(ANSI_COLOR_YELLOW);
                            printf("Versao: ");
                            printf(ANSI_COLOR_RESET);
                            printf("2.2\n");
                            printf(ANSI_COLOR_YELLOW);
                            printf("Autores: ");
                            printf(ANSI_COLOR_RESET);
                            printf("Lucas Martins e Lucas Araujo\n");
                            printf(ANSI_COLOR_YELLOW);
                            printf("Descricao: ");
                            printf(ANSI_COLOR_RESET);
                            printf("O Jogo  da Velha eh  um classico \n");
                            printf("jogo de tabuleiro  que foi desenvolvido por\n");
                            printf("dois alunos da Universidade Federal de Uber-\n");
                            printf("landia como parte de um projeto de programa-\n");
                            printf("cao em linguagem C.\n");
                            printf(ANSI_COLOR_YELLOW);
                            printf("Como Jogar: ");
                            printf(ANSI_COLOR_RESET);
                            printf("O objetivo do jogo eh preencher \n");
                            printf("uma grade 3x3 com simbolos \"X\" e \"O\" de for-\n");
                            printf("ma alternada,ate que um dos jogadores consi-\n");
                            printf("ga formar uma linha reta, horizontal, verti-\n");
                            printf("cal ou diagonalmente.\n");
                            printf(ANSI_COLOR_YELLOW);
                            printf("Data de Lancamento: ");
                            printf(ANSI_COLOR_RESET);
                            printf("22/06/2023, 23:99\n");
                            printf(ANSI_COLOR_YELLOW);
                            printf("Requisitos de sistema: ");
                            printf(ANSI_COLOR_RESET);
                            printf("OS: WINDOWS\n\n");
                            printf(ANSI_COLOR_YELLOW);
                            system("pause");
                            printf(ANSI_COLOR_RESET);
                        }
                        else if (indiceSelecionado == 3) // VOLTAR
                        {
                            sair = 1;
                            break;
                        }
                        break;
                    default:
                        break;
                    }
                } while (opcao != 27 && !sair); // Loop até que a tecla Esc (código ASCII 27) seja pressionada
                indiceSelecionado = 0;
                sair = 0;
            }
            if (indiceSelecionado == 3) // SAIR
            {
                opcao = 27;
                break;
            }
            break;
        default:
            break;
        }
    } while (opcao != 27); // Loop até que a tecla Esc (código ASCII 27) seja pressionada
    salvarRanking("ranking.txt", jogadores, numJogadores);
    //  Liberar a memória alocada para o vetor de jogadores
    free(jogadores);
    free(jogador);
    return 0;
}

void print_logo()
{
    system("cls");
    imprimecolorido(".------------------------------------------.\n");
    imprimecolorido("|     _   ___    ___   ___    ___    _     |\n");
    imprimecolorido("|  _ | | / _ \\  / __| / _ \\  |   \\  /_\\    |\n");
    imprimecolorido("| | || || (_) || (_ || (_) | | |) |/ _ \\   |\n");
    imprimecolorido("|  \\__/  \\___/  \\___| \\___/  |___//_/ \\_\\  |\n");
    imprimecolorido("|     __   __ ___  _     _  _    _         |\n");
    imprimecolorido("|     \\ \\ / /| __|| |   | || |  /_\\        |\n");
    imprimecolorido("|      \\ V / | _| | |__ | __ | / _ \\       |\n");
    imprimecolorido("|       \\_/  |___||____||_||_|/_/ \\_\\      |\n");
    imprimecolorido("'------------------------------------------'\n");
}

void imprimelento(char *p, int N)
{
    int i;
    for (i = 0; *(p + i) != '\0'; i++)
    {
        printf("%c", *(p + i));
        fflush(stdout);
        Sleep(N);
    }
}

void imprimecolorido(char *p)
{
    int i;
    for (i = 0; *(p + i) != '\0'; i++)
    {
        switch (i % 6)
        {
        case 0:
            printf(ANSI_COLOR_RED);
            break;
        case 1:
            printf(ANSI_COLOR_GREEN);
            break;
        case 2:
            printf(ANSI_COLOR_YELLOW);
            break;
        case 3:
            printf(ANSI_COLOR_BLUE);
            break;
        case 4:
            printf(ANSI_COLOR_MAGENTA);
            break;
        case 5:
            printf(ANSI_COLOR_CYAN);
            break;
        }
        printf("%c", *(p + i));
        printf(ANSI_COLOR_RESET);
    }
}

Player *lerRanking(const char *nomeArquivo, int *numJogadores)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Obter o tamanho do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    rewind(arquivo);

    // Calcular quantos jogadores existem no arquivo
    *numJogadores = tamanhoArquivo / sizeof(Player);
    // Alocar memória para o vetor de jogadores
    Player *ranking = malloc(*numJogadores * sizeof(Player));
    if (!ranking)
    {
        perror("Erro de alocação de memória");
        exit(EXIT_FAILURE);
    }

    // Ler os jogadores do arquivo para o vetor
    fread(ranking, sizeof(Player), *numJogadores, arquivo);

    fclose(arquivo);
    return ranking;
}

void salvarRanking(const char *nomeArquivo, Player *ranking, int numJogadores)
{
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Escrever os jogadores no arquivo
    fwrite(ranking, sizeof(Player), numJogadores, arquivo);

    fclose(arquivo);
}

Player *adicionarJogador(Player *jogadores, int *numJogadores)
{
    char nome[50], senha[10];
    Player *jogador = malloc(sizeof(Player));
    int i = 3;
    do
    {
        printf("\nDigite seu nome: ");
        printf(ANSI_COLOR_YELLOW);
        setbuf(stdin, NULL);
        scanf("%s", &nome);
        printf(ANSI_COLOR_RESET);
        nome[strcspn(nome, "\n")] = '\0';
        jogador = retornaJogador(jogadores, *numJogadores, nome, NULL);
        if (jogador != NULL) // Existe um jogador com esse nome
        {
            printf(ANSI_COLOR_RED);
            printf("\nNome de Usuario em uso, tente usar outro! Tentativas: %d\n", i - 1);
            printf(ANSI_COLOR_RESET);
            i--;
        }
        else // Não existe um jogador com o nome digitado
        {
            printf("\nDigite sua senha: ");
            printf(ANSI_COLOR_YELLOW);
            setbuf(stdin, NULL);
            scanf("%s", &senha);
            printf(ANSI_COLOR_RESET);
            senha[strcspn(senha, "\n")] = '\0';
            // Aumentar o tamanho do vetor de jogadores
            *numJogadores += 1;
            jogadores = realloc(jogadores, (*numJogadores) * sizeof(Player));
            if (!jogadores)
            {
                perror("Erro ao realocar memória");
                exit(EXIT_FAILURE);
            }
            strcpy(jogadores[*numJogadores - 1].nome, nome);
            strcpy(jogadores[*numJogadores - 1].senha, senha);
            jogadores[*numJogadores - 1].vitorias = 0; // Inicializar com 0 vitórias
            jogadores[*numJogadores - 1].derrotas = 0; // Inicializar com 0 derrotas
            return &jogadores[*numJogadores - 1];
        }
    } while (i > 0); // Encontrou o jogador

    return NULL;
}

Player *retornaJogador(Player *jogadores, int numJogadores, char *nome, char *senha)
{
    for (int i = 0; i < numJogadores; i++)
    {
        if (senha == NULL) // Verifica somente o nome
        {
            if (strcmp(jogadores[i].nome, nome) == 0) // Se existir um nome igual não é possivel cria novo jogador
            {
                return &jogadores[i];
            }
        }
        else if (strcmp(jogadores[i].nome, nome) == 0 && strcmp(jogadores[i].senha, senha) == 0) // verifica se o jogador e senha
        {
            return &jogadores[i];
        }
    }
    return NULL;
}

void iniciarJogo(Player *jogador, int dificulade)
{
    int board[3][3]; // 0 = vazio , 1 = x, 2 = o
    int sair;
    char tecla;
    int x, y;
    do
    {
        inicializaBoard(board);
        sair = 0;
        // Inicio do JOGO
        while (espacoVazio(board) && sair == 0)
        {
            printMenuJogar(jogador);
            printBoard(board);
            do
            {
                printf("Escolha sua Posicao: (entre 1 e 3)\n");
                printf("Linha: ");
                printf(ANSI_COLOR_YELLOW);
                setbuf(stdin, NULL);
                scanf("%d", &x);
                printf(ANSI_COLOR_RESET);
                printf("Coluna: ");
                printf(ANSI_COLOR_YELLOW);
                setbuf(stdin, NULL);
                scanf("%d", &y);
                printf(ANSI_COLOR_RESET);
                y = y - 1;
                x = x - 1;
                if (board[x][y] == 0 && x >= 0 && x < 3 && y >= 0 && y < 3) // posicao valida
                {
                    board[x][y] = 1;
                    if (verificaVitoria(board) == 1) // jogador venceu
                    {
                        jogador->vitorias++;
                        printMenuJogar(jogador);
                        printBoard(board);
                        printf(ANSI_COLOR_GREEN);
                        printf("\nVoce VENCEU! Parabens, %s.\n\n", jogador->nome);
                        printf(ANSI_COLOR_RESET);
                        sair = 1;
                        break;
                    }
                    bot(board, dificulade);
                    if (verificaVitoria(board) == 2) // bot venceu
                    {
                        jogador->derrotas++;
                        printMenuJogar(jogador);
                        printBoard(board);
                        printf(ANSI_COLOR_RED);
                        printf("\nVoce PERDEU! Talvez na proxima, %s.\n\n", jogador->nome);
                        printf(ANSI_COLOR_RESET);
                        sair = 1;
                        break;
                    }
                    break;
                }
                else // Posicao invalida
                {
                    printf(ANSI_COLOR_RED);
                    printf("\nPosicao invalida, tente outra por favor!\n\n");
                    printf(ANSI_COLOR_RESET);
                }
            } while (1);
            if (verificaVitoria(board) == 0 && espacoVazio(board) == 0) // EMPATE
            {
                printMenuJogar(jogador);
                printBoard(board);
                printf(ANSI_COLOR_BLUE);
                printf("\nEMPATE! Talvez na proxima, %s.\n\n", jogador->nome);
                printf(ANSI_COLOR_RESET);
                sair = 1;
                break;
            }
        }
        sair = 0;
        // Fim do JOGO
        printf(ANSI_COLOR_YELLOW);
        printf("Pressione 'Enter' para JOGAR ou 'Esc' para VOLTAR...\n\n");
        printf(ANSI_COLOR_RESET);
        while (1)
        {
            if (_kbhit())
            {
                tecla = _getch();
                if (tecla == 13)
                { // Verifica se a tecla pressionada é o código ASCII do "Enter"
                    break;
                }
                if (tecla == 27)
                { // Verifica se a tecla pressionada é o código ASCII do "Esc"
                    sair = 1;
                    break;
                }
            }
        }
    } while (sair != 1);
}

void printBoard(int Board[3][3])
{
    if (boardVazio(Board) == 1)
    {
        printf("             __              __\n");
        printf("            |  |            |  |\n");
        printf("            |  |            |  |\n");
        printf("            |  |            |  |\n");
        printf("            |  |            |  |\n");
        printf(" ___________|  |____________|  |___________\n");
        printf("|___________    ____________    ___________|\n");
        printf("            |  |            |  |\n");
        printf("            |  |            |  |\n");
        printf("            |  |            |  |\n");
        printf("            |  |            |  |\n");
        printf(" ___________|  |____________|  |___________\n");
        printf("|___________    ____________    ___________|\n");
        printf("            |  |            |  |\n");
        printf("            |  |            |  |\n");
        printf("            |  |            |  |\n");
        printf("            |  |            |  |\n");
        printf("            |__|            |__|\n\n");
    }
    else
    {
        printf("             __              __\n");
        for (int i = 0; i < 3; i++)
        {
            if (i == 1 || i == 2)
            {
                printf(" ___________|  |____________|  |___________\n");
                printf("|___________    ____________    ___________|\n");
            }
            int j = 0, linha = 0;
            while (j < 3 && linha < 4)
            {
                if (linha == 0)
                {
                    if (Board[i][j] == 0)
                    {
                        printf("            ");
                    }
                    else if (Board[i][j] == 1)
                    {
                        printf(ANSI_COLOR_RED);
                        printf("   __  __   ");
                        printf(ANSI_COLOR_RESET);
                    }
                    else if (Board[i][j] == 2)
                    {
                        printf(ANSI_COLOR_BLUE);
                        printf("    ___     ");
                        printf(ANSI_COLOR_RESET);
                    }
                    if (j < 2)
                    {
                        printf("|  |");
                        j++;
                    }
                    else
                    {
                        j = 0;
                        linha++;
                        printf("\n");
                    }
                }
                else if (linha == 1)
                {
                    if (Board[i][j] == 0)
                    {
                        printf("            ");
                    }
                    else if (Board[i][j] == 1)
                    {
                        printf(ANSI_COLOR_RED);
                        printf("   \\ \\/ /   ");
                        printf(ANSI_COLOR_RESET);
                    }
                    else if (Board[i][j] == 2)
                    {
                        printf(ANSI_COLOR_BLUE);
                        printf("   / _ \\    ");
                        printf(ANSI_COLOR_RESET);
                    }
                    if (j < 2)
                    {
                        printf("|  |");
                        j++;
                    }
                    else
                    {
                        j = 0;
                        linha++;
                        printf("\n");
                    }
                }
                else if (linha == 2)
                {
                    if (Board[i][j] == 0)
                    {
                        printf("            ");
                    }
                    else if (Board[i][j] == 1)
                    {
                        printf(ANSI_COLOR_RED);
                        printf("    >  <    ");
                        printf(ANSI_COLOR_RESET);
                    }
                    else if (Board[i][j] == 2)
                    {
                        printf(ANSI_COLOR_BLUE);
                        printf("  | (_) |   ");
                        printf(ANSI_COLOR_RESET);
                    }
                    if (j < 2)
                    {
                        printf("|  |");
                        j++;
                    }
                    else
                    {
                        j = 0;
                        linha++;
                        printf("\n");
                    }
                }
                else if (linha == 3)
                {
                    if (Board[i][j] == 0)
                    {
                        printf("            ");
                    }
                    else if (Board[i][j] == 1)
                    {
                        printf(ANSI_COLOR_RED);
                        printf("   /_/\\_\\   ");
                        printf(ANSI_COLOR_RESET);
                    }
                    else if (Board[i][j] == 2)
                    {
                        printf(ANSI_COLOR_BLUE);
                        printf("   \\___/    ");
                        printf(ANSI_COLOR_RESET);
                    }
                    if (j < 2)
                    {
                        printf("|  |");
                        j++;
                    }
                    else
                    {
                        j = 0;
                        linha++;
                        printf("\n");
                    }
                }
            }
            if (i == 2)
            {
                printf("            |__|            |__|      \n\n");
                break;
            }
        }
    }
}

void inicializaBoard(int Board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Board[i][j] = 0;
        }
    }
}

int boardVazio(int Board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Board[i][j] != 0)
            {
                return 0; // board não está vazio
            }
        }
    }
    return 1; // board está vazio
}

int espacoVazio(int Board[3][3])
{
    int count = 0;
    if (boardVazio(Board))
        return 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Board[i][j] == 0)
            {
                count++; // espaco vazio
            }
        }
    }
    return count;
}

int verificaVitoria(int Board[3][3])
{
    int vitoria = 0;
    for (int i = 0; i < 3; i++)
    {
        if (Board[i][0] != 0 && Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2])
        {
            vitoria = Board[i][0]; // vitoria pela linha
        }
        if (Board[0][i] != 0 && Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i])
        {
            vitoria = Board[0][i]; // vitoria pela coluna
        }
    }
    if (Board[0][0] != 0 && Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2])
    {
        vitoria = Board[0][0]; // vitoria pela diagonal primaria
    }
    if (Board[2][0] != 0 && Board[1][1] == Board[2][0] && Board[1][1] == Board[0][2])
    {
        vitoria = Board[2][0]; // vitoria pela diagonal secudaria
    }
    return vitoria; // 0 = niguem ganhou, 1 = jogador ganhou, 2 = bot ganhou
}

void bot(int Board[3][3], int Dificuldade)
{
    int x, y;
    int i, j;
    int posicaoInvalida = 1;
    srand(time(NULL));
    if (espacoVazio(Board) != 0)
    {
        if (Dificuldade == 0) // FACIL
        {
            do
            {
                x = rand() % 3;
                y = rand() % 3;
                if (Board[x][y] == 0)
                {
                    Board[x][y] = 2;
                    posicaoInvalida = 0;
                }
            } while (posicaoInvalida);
        }
        else if (Dificuldade == 1) // NORMAL
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    if (Board[i][j] == 0)
                    {
                        Board[i][j] = 2;
                        if (verificaVitoria(Board) == 2)
                            return;
                        Board[i][j] = 1;
                        if (verificaVitoria(Board) == 1)
                        {
                            Board[i][j] = 2;
                            return;
                        }
                        Board[i][j] = 0;
                    }
                }
            }
            do
            {
                x = rand() % 3;
                y = rand() % 3;
                if (Board[x][y] == 0)
                {
                    Board[x][y] = 2;
                    posicaoInvalida = 0;
                }
            } while (posicaoInvalida);
        }
        else if (Dificuldade == 2) // IMPOSSIVEL
        {
            if (espacoVazio(Board) == 8) // Primeira jogada
            {
                if (Board[1][1] == 1)
                    Board[0][0] = 2;
                else
                    Board[1][1] = 2;
                return;
            } // Prevê vitoria
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    if (Board[i][j] == 0)
                    {
                        Board[i][j] = 2;
                        if (verificaVitoria(Board) == 2)
                            return;
                        Board[i][j] = 1;
                        if (verificaVitoria(Board) == 1)
                        {
                            Board[i][j] = 2;
                            return;
                        }
                        Board[i][j] = 0;
                    }
                }
            }
            if (Board[1][1] == 1 && Board[2][2] == 1)
            {
                if (Board[2][0] == 0)
                {
                    Board[2][0] = 2;
                    return;
                }
            }
            if (Board[0][0] == 1 || Board[2][2] == 1 || Board[2][0] == 1 || Board[0][2] == 1)
            {
                if (Board[0][1] == 0)
                {
                    if (Board[2][1] == 0)
                    {
                        Board[0][1] = 2;
                        return;
                    }
                }
                if (Board[1][0] == 0)
                {
                    if (Board[1][2] == 0)
                    {
                        Board[1][0] = 2;
                        return;
                    }
                }
            }
            do
            {
                x = rand() % 3;
                y = rand() % 3;
                if (Board[x][y] == 0)
                {
                    Board[x][y] = 2;
                    posicaoInvalida = 0;
                }
            } while (posicaoInvalida);
        }
    }
}

void printMenuJogar(Player *jogador)
{
    system("cls"); // Limpa a tela
    printf(".------------------------------------------.\n|");
    printf(ANSI_COLOR_YELLOW);
    printf("                J O G A R                 ");
    printf(ANSI_COLOR_RESET);
    printf("|\n'------------------------------------------'\n");
    printf("Bem Vindo, ");
    printf(ANSI_COLOR_YELLOW);
    printf("%s", jogador->nome);
    printf(ANSI_COLOR_RESET);
    printf("!  Vitorias:");
    printf(ANSI_COLOR_YELLOW);
    printf("%d ", jogador->vitorias);
    printf(ANSI_COLOR_RESET);
    printf("  Derrotas:");
    printf(ANSI_COLOR_YELLOW);
    printf("%d\n\n", jogador->derrotas);
    printf(ANSI_COLOR_RESET);
}

void printRanking(Player *jogadores, int numJogadores)
{
    // Ordenar o vetor de jogadores de acordo com as vitórias
    // Exemplo de ordenação simples por inserção
    for (int i = 1; i < numJogadores && i < 10; i++)
    {
        Player temp = jogadores[i];
        int j = i - 1;
        while (j >= 0 && jogadores[j].vitorias < temp.vitorias)
        {
            jogadores[j + 1] = jogadores[j];
            j--;
        }
        jogadores[j + 1] = temp;
    }
    system("cls"); // Limpa a tela
    printf(".------------------------------------------.\n");
    printf("|");
    printf(ANSI_COLOR_YELLOW);
    printf("               R A N K I N G              ");
    printf(ANSI_COLOR_RESET);
    printf("|\n");
    printf("'------------------------------------------'\n\n");
    printf("      Nome:      Vitorias:      Derrotas:     \n\n");
    // Imprimir o ranking
    for (int i = 0; i < numJogadores && i < 10; i++)
    {
        printf("%d -   %s\t\t%d\t\t%d\n", (i) + 1, jogadores[i].nome, jogadores[i].vitorias, jogadores[i].derrotas);
    }
}
