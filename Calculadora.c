#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long fatorial(int n) {
    if (n < 0) return 0; // não existe fatorial negativo
    if (n == 0 || n == 1) return 1;
    unsigned long long fat = 1;
    for (int i = 2; i <= n; i++) {
        fat *= i;
    }
    return fat;
}

int main() {
    int op;
    float N1, N2, Resultado;

    printf("=== CALCULADORA CIENTIFICA ===\n");
    printf("1.  Adicao (+)\n");
    printf("2.  Subtracao (-)\n");
    printf("3.  Multiplicacao (*)\n");
    printf("4.  Divisao (/)\n");
    printf("5.  Exponencial (x^y)\n");
    printf("6.  Raiz quadrada (√x)\n");
    printf("7.  Seno (sin)\n");
    printf("8.  Cosseno (cos)\n");
    printf("9.  Tangente (tan)\n");
    printf("10. Logaritmo natural (ln)\n");
    printf("11. Logaritmo base 10 (log10)\n");
    printf("12. Fatorial (n!)\n");
    printf("13. Valor absoluto (|x|)\n");
    printf("14. Arredondar para cima (ceil)\n");
    printf("15. Arredondar para baixo (floor)\n");
    printf("16. Parte inteira (trunc)\n");
    printf("17. Exponencial de e (exp)\n");
    printf("18. Resto da divisao (fmod)\n");
    printf("19. Inverso (1/x)\n");
    printf("20. Hipotenusa (sqrt(x^2+y^2))\n");

    printf("\nEscolha a operacao: ");
    scanf("%d", &op);

    printf("Insira o primeiro numero: ");
    scanf("%f", &N1);

    if (!(op == 6 || op == 7 || op == 8 || op == 9 || op == 10 ||
          op == 11 || op == 12 || op == 13 || op == 14 || op == 15 ||
          op == 16 || op == 17 || op == 19)) {
        printf("Insira o segundo numero: ");
        scanf("%f", &N2);
    }

    switch (op) {
        case 1: Resultado = N1 + N2; printf("Soma: %f\n", Resultado); break;
        case 2: Resultado = N1 - N2; printf("Subtracao: %f\n", Resultado); break;
        case 3: Resultado = N1 * N2; printf("Multiplicacao: %f\n", Resultado); break;
        case 4: 
            if (N2 == 0) printf("Erro: divisao por zero!\n");
            else { Resultado = N1 / N2; printf("Divisao: %f\n", Resultado); }
            break;
        case 5: Resultado = pow(N1, N2); printf("Exponencial: %f\n", Resultado); break;
        case 6: 
            if (N1 < 0) printf("Erro: raiz de numero negativo!\n");
            else { Resultado = sqrt(N1); printf("Raiz quadrada: %f\n", Resultado); }
            break;
        case 7: Resultado = sin(N1); printf("Seno: %f\n", Resultado); break;
        case 8: Resultado = cos(N1); printf("Cosseno: %f\n", Resultado); break;
        case 9: 
            if (cos(N1) == 0) printf("Erro: tangente indefinida!\n");
            else { Resultado = tan(N1); printf("Tangente: %f\n", Resultado); }
            break;
        case 10: 
            if (N1 <= 0) printf("Erro: ln so para N1 > 0!\n");
            else { Resultado = log(N1); printf("Log natural: %f\n", Resultado); }
            break;
        case 11:
            if (N1 <= 0) printf("Erro: log10 so para N1 > 0!\n");
            else { Resultado = log10(N1); printf("Log base 10: %f\n", Resultado); }
            break;
        case 12:
            if (N1 < 0) printf("Erro: fatorial de numero negativo!\n");
            else printf("Fatorial: %llu\n", fatorial((int)N1));
            break;
        case 13: Resultado = fabs(N1); printf("Valor absoluto: %f\n", Resultado); break;
        case 14: Resultado = ceil(N1); printf("Arredondado para cima: %f\n", Resultado); break;
        case 15: Resultado = floor(N1); printf("Arredondado para baixo: %f\n", Resultado); break;
        case 16: Resultado = trunc(N1); printf("Parte inteira: %f\n", Resultado); break;
        case 17: Resultado = exp(N1); printf("e^x: %f\n", Resultado); break;
        case 18: Resultado = fmod(N1, N2); printf("Resto da divisao: %f\n", Resultado); break;
        case 19: 
            if (N1 == 0) printf("Erro: inverso de zero nao existe!\n");
            else { Resultado = 1 / N1; printf("Inverso: %f\n", Resultado); }
            break;
        case 20: Resultado = hypot(N1, N2); printf("Hipotenusa: %f\n", Resultado); break;
        default: printf("Erro: Operacao invalida!\n");
    }

    system("pause");
    return 0;
}
