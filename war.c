// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Necessário para srand() e rand()




// Struct de Território
typedef struct {
char nome[30];
char cor[10];
int tropas;
} Territorio;




// Função para limpar o buffer de entrada
void limparBufferEntrada() {
int c;
while ((c = getchar()) != '\n' && c != EOF);
}




// Função para cadastrar territórios dinamicamente
void cadastrarTerritorios(Territorio *mapa, int totalTerritorios) {
printf("\n# Vamos cadastrar os territórios do mundo! #\n");
for (int i = 0; i < totalTerritorios; i++) {
printf("\n=== Cadastrando Território %d ===\n", i + 1);

    printf("Nome do território: ");
    fgets(mapa[i].nome, 30, stdin);
    mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

    printf("Cor do exército (ex: Amarelo, Azul): ");
    fgets(mapa[i].cor, 10, stdin);
    mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

    printf("Número de tropas: ");
    scanf("%d", &mapa[i].tropas);
    limparBufferEntrada();
}




}




// Função para exibir o estado atual do mapa
void exibirMapa(Territorio *mapa, int totalTerritorios) {
printf("\n==============================\n");
printf(" MAPA DO MUNDO - ESTADO ATUAL\n");
printf("==============================\n");

for (int i = 0; i < totalTerritorios; i++) {
    printf("\nTERRITÓRIO %d:\n", i + 1);
    printf("   - Nome: %s\n", mapa[i].nome);
    printf("   - Dominado por: Exército %s\n", mapa[i].cor);
    printf("   - Tropas: %d\n", mapa[i].tropas);
}




}




// Função de ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
printf("\n=== Simulação de Ataque ===\n");
printf("Atacante: %s (%s) | Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
printf("Defensor: %s (%s) | Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);

// Gera números aleatórios simulando dados (1 a 6)
int dadoAtacante = (rand() % 6) + 1;
int dadoDefensor = (rand() % 6) + 1;

printf("\nDado do atacante: %d\n", dadoAtacante);
printf("Dado do defensor: %d\n", dadoDefensor);

// Verifica quem venceu o ataque
if (dadoAtacante > dadoDefensor) {
    printf("\nO atacante venceu o combate!\n");
    strcpy(defensor->cor, atacante->cor); // Muda o dono do território
    defensor->tropas = atacante->tropas / 2; // Metade das tropas passam ao defensor
    atacante->tropas -= defensor->tropas / 2; // O atacante perde parte das tropas
} else {
    printf("\nO defensor resistiu ao ataque!\n");
    atacante->tropas -= 1; // O atacante perde uma tropa
    if (atacante->tropas < 0) atacante->tropas = 0;
}

printf("\nResultado pós-batalha:\n");
printf("Atacante: %s (%s) | Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
printf("Defensor: %s (%s) | Tropas: %d\n", defensor->nome, defensor->cor, defensor->tropas);




}




// Função para liberar memória alocada dinamicamente
void liberarMemoria(Territorio *mapa) {
free(mapa);
printf("\nMemória liberada com sucesso!\n");
}




// Função principal
int main() {
srand(time(NULL)); // Garante aleatoriedade a cada execução

int totalTerritorios;
printf("Digite o número total de territórios: ");
scanf("%d", &totalTerritorios);
limparBufferEntrada();

// Alocação dinâmica do vetor de territórios
Territorio *mapa = (Territorio *) calloc(totalTerritorios, sizeof(Territorio));
if (mapa == NULL) {
    printf("Erro: falha ao alocar memória.\n");
    return 1;
}

cadastrarTerritorios(mapa, totalTerritorios);

int opcao;
do {
    printf("\n==============================\n");
    printf("       MENU DE OPERAÇÕES\n");
    printf("==============================\n");
    printf("1 - Exibir mapa\n");
    printf("2 - Simular ataque\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    limparBufferEntrada();

    switch (opcao) {
        case 1:
            exibirMapa(mapa, totalTerritorios);
            break;

        case 2:
            exibirMapa(mapa, totalTerritorios);
            printf("\nEscolha o número do território atacante: ");
            int iAtacante, iDefensor;
            scanf("%d", &iAtacante);
            limparBufferEntrada();

            printf("Escolha o número do território defensor: ");
            scanf("%d", &iDefensor);
            limparBufferEntrada();

            iAtacante--; // Ajusta índice
            iDefensor--;

            // Valida índices e cores
            if (iAtacante < 0 || iAtacante >= totalTerritorios ||
                iDefensor < 0 || iDefensor >= totalTerritorios) {
                printf("Escolha inválida!\n");
            } else if (strcmp(mapa[iAtacante].cor, mapa[iDefensor].cor) == 0) {
                printf("Você não pode atacar um território da sua própria cor!\n");
            } else if (mapa[iAtacante].tropas <= 0) {
                printf("O território atacante não tem tropas suficientes!\n");
            } else {
                atacar(&mapa[iAtacante], &mapa[iDefensor]);
            }
            break;

        case 0:
            printf("\nEncerrando o jogo...\n");
            break;

        default:
            printf("\nOpção inválida. Tente novamente.\n");
    }

} while (opcao != 0);

liberarMemoria(mapa);
return 0;




}