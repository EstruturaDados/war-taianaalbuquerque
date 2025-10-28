// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
#include <stdio.h>
#include <string.h>

//Limitando o número de territórios a serem cadastrados
#define MAX_TERRITORIOS 5

//Struct de Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

//Limpando buffer para programa rodar de forma eficaz
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Início do programa para receber os dados com as funções fgets e scanf
int main() {
    Territorio territorios[MAX_TERRITORIOS];
    int totalTerritorios = 0;

    printf("# Vamos cadastrar os 5 territórios iniciais do nosso mundo! #\n");

    for (totalTerritorios = 0; totalTerritorios < MAX_TERRITORIOS; totalTerritorios++) {
        printf("\n=== Cadastrando Território %d ===\n", totalTerritorios + 1);

        printf("Nome do território: \n");
        fgets(territorios[totalTerritorios].nome, 30, stdin);

        printf("Cor do exército (ex: Amarelo, Azul): \n");
        fgets(territorios[totalTerritorios].cor, 10, stdin);

        territorios[totalTerritorios].nome[strcspn(territorios[totalTerritorios].nome, "\n")] = '\0';
        territorios[totalTerritorios].cor[strcspn(territorios[totalTerritorios].cor, "\n")] = '\0';

        printf("Número de Tropas: \n");
        scanf("%d", &territorios[totalTerritorios].tropas);
        limparBufferEntrada();

    }
    // Cadastros finalizados
    printf("\nCadastro inicial concluído com sucesso!\n");

    //Exibindo os dados dos 5 territórios cadastrados
    printf("\n==============================\n");
    printf("MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("==============================\n");

    for (int i = 0; i < totalTerritorios; i++) {
        printf("\nTERRITÓRIO %d: \n", i + 1);
            printf("   - Nome: %s\n", territorios[i].nome);
            printf("   - Dominado por: Exército %s\n", territorios[i].cor);
            printf("   - Tropas: %d\n", territorios[i].tropas);

    }

}