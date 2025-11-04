// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define TOTAL_MISSOES 5

// Estrutura de Território
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

// Exibe o mapa atual do mundo
void exibirMapa(Territorio* territorios, int tamanho) {
printf("\n==============================\n");
printf("MAPA DO MUNDO - ESTADO ATUAL\n");
printf("==============================\n");
for (int i = 0; i < tamanho; i++) {
printf("\nTERRITÓRIO %d:\n", i + 1);
printf("   - Nome: %s\n", territorios[i].nome);
printf("   - Dominado por: Exército %s\n", territorios[i].cor);
printf("   - Tropas: %d\n", territorios[i].tropas);
}
printf("==============================\n");
}

// Sorteia e atribui uma missão ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
int sorteio = rand() % totalMissoes; // sorteia índice
strcpy(destino, missoes[sorteio]);   // copia missão sorteada
}

// Exibe a missão do jogador
void exibirMissao(const char* missao) {
printf("\nSua missão secreta é: %s\n", missao);
}

// Verifica se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
// Exemplo simples: se tiver 3 territórios seguidos da mesma cor, missão é cumprida
if (strstr(missao, "Conquistar 3 territórios seguidos")) {
int cont = 1;
for (int i = 1; i < tamanho; i++) {
if (strcmp(mapa[i].cor, mapa[i - 1].cor) == 0) {
cont++;
if (cont >= 3) return 1; // missão cumprida
} else {
cont = 1;
}
}
}
return 0;
}

// Simula ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
int dadoAtacante = rand() % 6 + 1;
int dadoDefensor = rand() % 6 + 1;

printf("\nAtaque iniciado!\n");
printf("Atacante (%s) rolou: %d\n", atacante->cor, dadoAtacante);
printf("Defensor (%s) rolou: %d\n", defensor->cor, dadoDefensor);

if (dadoAtacante > dadoDefensor) {
    printf("Vitória do atacante!\n");
    strcpy(defensor->cor, atacante->cor);
    defensor->tropas = atacante->tropas / 2;
    atacante->tropas /= 2;
} else {
    printf("Defesa bem-sucedida!\n");
    atacante->tropas--;
}

}

// --- FUNÇÃO: Libera toda memória alocada ---
void liberarMemoria(Territorio* mapa, char* missao) {
free(mapa);
free(missao);
}

// Função principal
int main() {
srand(time(NULL)); // inicializa aleatoriedade

// Missões pré-definidas
char* missoes[TOTAL_MISSOES] = {
    "Conquistar 3 territórios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Dominar todos os territórios azuis",
    "Manter ao menos 2 territórios com mais de 10 tropas",
    "Ter o dobro de territórios do inimigo"
};

// Alocação dinâmica de territórios
Territorio* territorios = (Territorio*)calloc(MAX_TERRITORIOS, sizeof(Territorio));
if (!territorios) {
    printf("Erro ao alocar memória para territórios.\n");
    return 1;
}

// Alocação dinâmica da missão do jogador
char* missaoJogador = (char*)malloc(100 * sizeof(char));
if (!missaoJogador) {
    printf("Erro ao alocar memória para missão.\n");
    free(territorios);
    return 1;
}

atribuirMissao(missaoJogador, missoes, TOTAL_MISSOES);
exibirMissao(missaoJogador);

printf("\n# Vamos cadastrar os 5 territórios iniciais do nosso mundo! #\n");

for (int i = 0; i < MAX_TERRITORIOS; i++) {
    printf("\n=== Cadastrando Território %d ===\n", i + 1);

    printf("Nome do território: ");
    fgets(territorios[i].nome, 30, stdin);
    territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

    printf("Cor do exército (ex: Amarelo, Azul): ");
    fgets(territorios[i].cor, 10, stdin);
    territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

    printf("Número de Tropas: ");
    scanf("%d", &territorios[i].tropas);
    limparBufferEntrada();
}

exibirMapa(territorios, MAX_TERRITORIOS);

// Exemplo de ataque entre territórios 1 e 2
printf("\nDeseja simular um ataque entre Território 1 e 2? (1 - Sim / 0 - Não): ");
int opcao;
scanf("%d", &opcao);
limparBufferEntrada();
if (opcao == 1) {
    atacar(&territorios[0], &territorios[1]);
    exibirMapa(territorios, MAX_TERRITORIOS);
}

// Verifica se missão foi cumprida
if (verificarMissao(missaoJogador, territorios, MAX_TERRITORIOS)) {
    printf("\nParabéns! Você cumpriu sua missão e venceu o jogo!\n");
} else {
    printf("\nMissão ainda não cumprida. Continue jogando!\n");
}

liberarMemoria(territorios, missaoJogador);
printf("\nMemória liberada e programa finalizado com sucesso.\n");

return 0;

}