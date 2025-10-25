#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

unsigned long long fatorial(int n) {
    if (n < 0) return 0;
    unsigned long long fat = 1;
    for (int i = 2; i <= n; i++) {
        fat *= i;
    }
    return fat;
}

void exibirMenu() {
    printf("\n=============== CALCULADORA CIENTÍFICA ===============\n");
    printf("--- Operações em Vetor (Resultado Único) ---\n");
    printf(" 1. Adição (+)\n");
    printf(" 2. Subtração (-)\n");
    printf(" 3. Multiplicação (*)\n");
    printf(" 4. Divisão (/)\n");
    printf(" 19. Resto da Divisão (%%)\n");
    printf("\n--- Operações em Vetor (Resultado por Elemento) ---\n");
    printf(" 5. Seno\n");
    printf(" 6. Cosseno\n");
    printf(" 7. Tangente\n");
    printf(" 8. Raiz Quadrada\n");
    printf(" 10. Logaritmo Natural\n");
    printf(" 11. Logaritmo Base 10\n");
    printf(" 13. Valor Absoluto\n");
    printf(" 14. Fatorial\n");
    printf(" 15. Inverso (1/x)\n");
    printf(" 16. Arredondar\n");
    printf(" 17. Piso (floor)\n");
    printf(" 18. Teto (ceil)\n");
    printf(" 20. Converter Graus <> Radianos\n");
    printf("\n--- Operações Padrão (Dois Números) ---\n");
    printf(" 9. Potenciação\n");
    printf(" 12. Porcentagem\n");
    printf("\n 0. Sair\n");
    printf("======================================================\n");
    printf("Escolha uma opção: ");
}

void operacoesEmCadeia(int opcao) {
    int quantidade;
    printf("Quantos números você quer usar na operação? ");
    scanf("%d", &quantidade);

    if (quantidade < 2) {
        printf("Erro: São necessários pelo menos 2 números.\n");
        return;
    }

    double *numeros = (double*) malloc(quantidade * sizeof(double));
    if (numeros == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("Digite o %dº número: ", i + 1);
        scanf("%lf", &numeros[i]);
    }

    double resultado = numeros[0];
    int erro = 0;

    for (int i = 1; i < quantidade; i++) {
        switch (opcao) {
            case 1: resultado += numeros[i]; break;
            case 2: resultado -= numeros[i]; break;
            case 3: resultado *= numeros[i]; break;
            case 4:
                if (numeros[i] == 0) { erro = 1; printf("Erro: Divisão por zero!\n"); }
                else { resultado /= numeros[i]; }
                break;
            case 19:
                if ((int)numeros[i] == 0) { erro = 1; printf("Erro: Divisão por zero no módulo!\n"); }
                else { resultado = (double)((int)resultado % (int)numeros[i]); }
                break;
        }
        if(erro) break;
    }

    if(!erro) {
        printf("Resultado final: %.4lf\n", resultado);
    }
    free(numeros);
}

void operacoesPorElemento(int opcao) {
    int quantidade;
    printf("Quantos números você quer processar? ");
    scanf("%d", &quantidade);

    if (quantidade < 1) {
        printf("Erro: É necessário pelo menos 1 número.\n");
        return;
    }

    double *numeros = (double*) malloc(quantidade * sizeof(double));
    if (numeros == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }

    int sub_opcao = 0;
    if (opcao == 20) {
        printf("1 - Graus para Radianos\n2 - Radianos para Graus\nEscolha: ");
        scanf("%d", &sub_opcao);
        if (sub_opcao != 1 && sub_opcao != 2) {
            printf("Opção inválida!\n");
            free(numeros);
            return;
        }
    }

    for (int i = 0; i < quantidade; i++) {
        printf("Digite o %dº número: ", i + 1);
        scanf("%lf", &numeros[i]);
    }

    printf("\n--- Resultados ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Entrada %d (%.2f): ", i + 1, numeros[i]);
        switch (opcao) {
            case 5: printf("Seno = %.4lf\n", sin(numeros[i] * M_PI / 180)); break;
            case 6: printf("Cosseno = %.4lf\n", cos(numeros[i] * M_PI / 180)); break;
            case 7: printf("Tangente = %.4lf\n", tan(numeros[i] * M_PI / 180)); break;
            case 8:
                if (numeros[i] < 0) printf("Erro: raiz de número negativo!\n");
                else printf("Raiz Quadrada = %.4lf\n", sqrt(numeros[i]));
                break;
            case 10:
                if (numeros[i] <= 0) printf("Erro: logaritmo de número não positivo!\n");
                else printf("Log Natural = %.4lf\n", log(numeros[i]));
                break;
            case 11:
                if (numeros[i] <= 0) printf("Erro: logaritmo de número não positivo!\n");
                else printf("Log Base 10 = %.4lf\n", log10(numeros[i]));
                break;
            case 13: printf("Valor Absoluto = %.2lf\n", fabs(numeros[i])); break;
            case 14:
                if (numeros[i] < 0 || numeros[i] != (int)numeros[i]) printf("Erro: fatorial de não inteiro ou negativo!\n");
                else printf("Fatorial = %llu\n", fatorial((int)numeros[i]));
                break;
            case 15:
                if (numeros[i] == 0) printf("Erro: divisão por zero!\n");
                else printf("Inverso = %.4lf\n", 1 / numeros[i]);
                break;
            case 16: printf("Arredondado = %.0lf\n", round(numeros[i])); break;
            case 17: printf("Piso = %.0lf\n", floor(numeros[i])); break;
            case 18: printf("Teto = %.0lf\n", ceil(numeros[i])); break;
            case 20:
                if (sub_opcao == 1) printf("Em radianos = %.4lf\n", numeros[i] * M_PI / 180);
                if (sub_opcao == 2) printf("Em graus = %.4lf\n", numeros[i] * 180 / M_PI);
                break;
        }
    }
    free(numeros);
}

void operacoesPadrao(int opcao) {
    double num1, num2;
    switch (opcao) {
        case 9:
            printf("Digite a base: ");
            scanf("%lf", &num1);
            printf("Digite o expoente: ");
            scanf("%lf", &num2);
            printf("Resultado: %.4lf\n", pow(num1, num2));
            break;
        case 12:
            printf("Digite o valor total: ");
            scanf("%lf", &num1);
            printf("Digite a porcentagem: ");
            scanf("%lf", &num2);
            printf("%.2lf%% de %.2lf = %.4lf\n", num2, num1, (num1 * num2 / 100));
            break;
    }
}

int main() {
    int opcao;
    int continuar = 1;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        if ((opcao >= 1 && opcao <= 4) || opcao == 19) {
            operacoesEmCadeia(opcao);
        }
        else if ((opcao >= 5 && opcao <= 8) || (opcao >= 10 && opcao <= 11) || (opcao >= 13 && opcao <= 18) || opcao == 20) {
            operacoesPorElemento(opcao);
        }
        else if (opcao == 9 || opcao == 12) {
            operacoesPadrao(opcao);
        }
        else if (opcao == 0) {
            continuar = 0;
            printf("Encerrando a calculadora...\n");
        }
        else {
            printf("Opção inválida! Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nDeseja realizar outro cálculo? (1 - Sim / 0 - Não): ");
            scanf("%d", &continuar);
            while (getchar() != '\n');
        }

    } while (continuar != 0);

    printf("\nObrigado por usar a calculadora!\n");
    return 0;
}
