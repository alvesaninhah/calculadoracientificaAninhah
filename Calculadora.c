#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846

unsigned long long fatorial(int n) {
    if (n < 0) return 0; 
    unsigned long long fat = 1;
    for (int i = 2; i <= n; i++) {
        fat *= i;
    }
    return fat;
}

int main() {
    int opcao;
    double num1, num2, resultado;
    int continuar = 1;

    do {
        printf("\n===== CALCULADORA CIENTÍFICA =====\n");
        printf("1.  Adição (+)\n");
        printf("2.  Subtração (-)\n");
        printf("3.  Multiplicação (*)\n");
        printf("4.  Divisão (/)\n");
        printf("5.  Seno\n");
        printf("6.  Cosseno\n");
        printf("7.  Tangente\n");
        printf("8.  Raiz Quadrada\n");
        printf("9.  Potenciação\n");
        printf("10. Logaritmo Natural (ln)\n");
        printf("11. Logaritmo Base 10\n");
        printf("12. Porcentagem\n");
        printf("13. Valor Absoluto\n");
        printf("14. Fatorial\n");
        printf("15. Inverso (1/x)\n");
        printf("16. Arredondar (round)\n");
        printf("17. Piso (floor)\n");
        printf("18. Teto (ceil)\n");
        printf("19. Resto da divisão (mod)\n");
        printf("20. Converter Graus ↔ Radianos\n");
        printf("0.  Sair\n");
        printf("==================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 4) {
            printf("Digite o primeiro número: ");
            scanf("%lf", &num1);
            printf("Digite o segundo número: ");
            scanf("%lf", &num2);
        }

        switch (opcao) {
            case 1:
                resultado = num1 + num2;
                printf("Resultado: %.2lf\n", resultado);
                break;
            case 2:
                resultado = num1 - num2;
                printf("Resultado: %.2lf\n", resultado);
                break;
            case 3:
                resultado = num1 * num2;
                printf("Resultado: %.2lf\n", resultado);
                break;
            case 4:
                if (num2 != 0)
                    printf("Resultado: %.2lf\n", num1 / num2);
                else
                    printf("Erro: divisão por zero!\n");
                break;
            case 5:
                printf("Digite o ângulo em graus: ");
                scanf("%lf", &num1);
                printf("Seno: %.4lf\n", sin(num1 * M_PI / 180));
                break;
            case 6:
                printf("Digite o ângulo em graus: ");
                scanf("%lf", &num1);
                printf("Cosseno: %.4lf\n", cos(num1 * M_PI / 180));
                break;
            case 7:
                printf("Digite o ângulo em graus: ");
                scanf("%lf", &num1);
                printf("Tangente: %.4lf\n", tan(num1 * M_PI / 180));
                break;
            case 8:
                printf("Digite um número: ");
                scanf("%lf", &num1);
                if (num1 >= 0)
                    printf("Raiz quadrada: %.4lf\n", sqrt(num1));
                else
                    printf("Erro: número negativo!\n");
                break;
            case 9:
                printf("Digite a base: ");
                scanf("%lf", &num1);
                printf("Digite o expoente: ");
                scanf("%lf", &num2);
                printf("Resultado: %.4lf\n", pow(num1, num2));
                break;
            case 10:
                printf("Digite um número: ");
                scanf("%lf", &num1);
                if (num1 > 0)
                    printf("Logaritmo natural: %.4lf\n", log(num1));
                else
                    printf("Erro: logaritmo indefinido!\n");
                break;
            case 11:
                printf("Digite um número: ");
                scanf("%lf", &num1);
                if (num1 > 0)
                    printf("Logaritmo base 10: %.4lf\n", log10(num1));
                else
                    printf("Erro: logaritmo indefinido!\n");
                break;
            case 12:
                printf("Digite o valor total: ");
                scanf("%lf", &num1);
                printf("Digite a porcentagem: ");
                scanf("%lf", &num2);
                printf("%.2lf%% de %.2lf = %.4lf\n", num2, num1, (num1 * num2 / 100));
                break;
            case 13:
                printf("Digite um número: ");
                scanf("%lf", &num1);
                printf("Valor absoluto: %.2lf\n", fabs(num1));
                break;
            case 14:
                printf("Digite um número inteiro: ");
                scanf("%lf", &num1);
                if (num1 >= 0)
                    printf("Fatorial: %llu\n", fatorial((int)num1));
                else
                    printf("Erro: número negativo!\n");
                break;
            case 15:
                printf("Digite um número: ");
                scanf("%lf", &num1);
                if (num1 != 0)
                    printf("Inverso: %.4lf\n", 1 / num1);
                else
                    printf("Erro: divisão por zero!\n");
                break;
            case 16:
                printf("Digite um número: ");
                scanf("%lf", &num1);
                printf("Arredondado: %.0lf\n", round(num1));
                break;
            case 17:
                printf("Digite um número: ");
                scanf("%lf", &num1);
                printf("Piso: %.0lf\n", floor(num1));
                break;
            case 18:
                printf("Digite um número: ");
                scanf("%lf", &num1);
                printf("Teto: %.0lf\n", ceil(num1));
                break;
            case 19:
                printf("Digite o dividendo: ");
                scanf("%lf", &num1);
                printf("Digite o divisor: ");
                scanf("%lf", &num2);
                if ((int)num2 != 0)
                    printf("Resto da divisão: %d\n", (int)num1 % (int)num2);
                else
                    printf("Erro: divisão por zero!\n");
                break;
            case 20:
                printf("1 - Graus para Radianos\n2 - Radianos para Graus\nEscolha: ");
                scanf("%d", &continuar);
                if (continuar == 1) {
                    printf("Digite o valor em graus: ");
                    scanf("%lf", &num1);
                    printf("Em radianos: %.4lf\n", num1 * M_PI / 180);
                } else if (continuar == 2) {
                    printf("Digite o valor em radianos: ");
                    scanf("%lf", &num1);
                    printf("Em graus: %.4lf\n", num1 * 180 / M_PI);
                } else {
                    printf("Opção inválida!\n");
                }
                break;
            case 0:
                printf("Encerrando a calculadora...\n");
                continuar = 0;
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nDeseja realizar outro cálculo? (1 - Sim / 0 - Não): ");
            scanf("%d", &continuar);
        }

    } while (continuar != 0);

    printf("\nObrigado por usar a calculadora!\n");
    return 0;
}
