
// feita por Ana Karla Alves da Cruz <3

#include <stdio.h>
#include <math.h>
#include <string.h>
#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

int main()
{
	double num1, num2, resultado;
	char op;
	char continuar;

	do {
		printf("\n\n====CALCULADORA CIENTIFICA====\n");
		printf("*INFORMACAO*\n");
		printf("Digite + para soma\n");
		printf("Digite - para subtracao\n");
		printf("Digite * para multiplicacao\n");
		printf("Digite / para divisao\n");
		printf("Digite ^ para exponenciacao\n");
		printf("Digite R para raiz quadrada\n");
		printf("Digite L para logaritmo (base 10)\n");
		printf("Digite N para Logaritmo Neperiano (ln))\n");
		printf("Digite E para Exponencial (e^x)\n");
		printf("Digite S para seno de um angulo\n");
		printf("Digite C para cosseno de um angulo\n");
		printf("Digite T para tangente de um angulo\n");
		printf("Qual e a operacao desejada? ");
		scanf(" %c", &op);


		if (op == '+' || op == '-' || op == '*' || op == '/' || op == '^') {
			printf("Digite o primeiro numero: ");
			scanf("%lf", &num1);
			printf("Digite o segundo numero: ");
			scanf("%lf", &num2);
		}
		switch (op) {
		case '+' :
			resultado = num1 + num2;
			printf("Resultado: %.0lf\n", resultado);
			break;
		case '-' :
			resultado = num1 - num2;
			printf("Resultado: %.0lf\n", resultado);
			break;
		case '*' :
			resultado = num1 * num2;
			printf("Resultado: %.0lf\n", resultado);
			break;
		case '/' :
			if (num2 != 0) {
				resultado = num1 / num2;
				printf("Resultado: %.0lf\n", resultado);
			} else {
				printf("Erro: Nao se pode dividir por 0!!!\n");
			}
			break;
		case '^' :
			resultado = pow (num1, num2);
			printf("%.2lf elevado a %.2lf = %.2lf\n", num1, num2, resultado);
			break;
		case 'R' :
			printf("Digite um numero: ");
			scanf("%lf", &num1);
			if (num1 >= 0) {
				resultado = sqrt(num1);
				printf("A raiz quadrada de %.2lf = %.2lf\n", num1, resultado);
			} else {
				printf("Erro: numero negativo nao possui raiz.\n");
			}
			break;
		case 'L' :
			printf("Digite um numero: ");
			scanf("%lf", &num1);
			if(num1 > 0) {
				resultado = log10(num1);
				printf("Resultado: %.2lf\n", resultado);
			} else {
				printf("Erro: log de numero nao positivo!\n");
			}
			break;
		case 'N' :
			printf("Digite um numero: ");
			scanf("%lf", &num1);
			if(num1 > 0) {
				resultado = log(num1);
				printf("Resultado: %.2lf\n", resultado);
			} else {
				printf("Erro: log de numero nao positivo!\n");
			}
			break;
		case 'S' :
			printf("Digite o angulo em graus: ");
			scanf("%lf", &num1);
			resultado = sin(num1 * M_PI / 180);
			printf("O Seno de %.2lf = %.2lf", num1, resultado);
			break;
		case 'C' :
			printf("Digite o angulo em graus: ");
			scanf("%lf", &num1);
			resultado = cos(num1 * M_PI / 180);
			printf("O Coseno de %.2lf = %.2lf", num1, resultado);
			break;
		case 'T' :
			printf("Digite o angulo em graus: ");
			scanf("%lf", &num1);
			resultado = tan(num1 * M_PI / 180);
			printf("A tangente de %.2lf = %.2lf", num1, resultado);
			break;
		case 'E':
			printf("Digite o expoente x para e^x: ");
			scanf("%lf", &num1);
			resultado = exp(num1);
			printf("Resultado: %.2lf\n", resultado);
			break;
		default:
			printf("ESSA OPERACAO NAO EXISTE!!\n");
		}
		printf("\nDeseja fazer outro cálculo? (S/N): ");
        scanf(" %c", &continuar);
	} while (continuar == 'S' || continuar == 's');

	printf("\nEncerrando a calculadora. Ate mais!\n");
	return 0;

}
