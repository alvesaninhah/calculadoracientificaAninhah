#include <stdio.h>
#include <math.h>
//-----------------------------------
#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

int main(void){
    float n1, n2, resultado;
    int op;
    
    do{
        printf("-----------------------------------\n");
        printf("\tCALCULADORA MASSA\n");
        printf("-----------------------------------\n\n");
        printf("PARA SAIR DIGITE '0' EM OPERACAO\n\n");
        printf("DIGITE O PRIMEIRO NÚMERO: ");
        scanf("%f", &n1);
        printf("-----------------------------------\n");
        printf("1 - ADICAO\n");
        printf("2 - SUBTRACAO\n");
        printf("3 - MULTIPLICACAO\n");
        printf("4 - DIVISAO\n");
        printf("5 - POTENCIACAO\n");
        printf("6 - RAIZ QUADRADA\n");
        printf("7 - RAIZ CUBICA\n");
        printf("8 - SENO\n");
        printf("9 - COSSENO\n");
        printf("10 - TANGENTE\n");
        printf("11 - LOGARITIMO\n");
        printf("12 - LOGARITIMO NATURAL\n");
        printf("13 - LOGARITIMO DE X+1\n");
        printf("14 - EXPONENCIAl\n");
        printf("15 - ARCO SENO\n");
        printf("16 - ARCO COSSENO\n");
        printf("17 - ARCO TANGENTE\n");
        printf("18 - EXPONENCIAl DE BASE 2\n");
        printf("19 - RESTO DE DIVISAO\n");
        printf("20 - SOMA DE QUADRADOS\n");
        printf("-----------------------------------\n");
        printf("ESCOLHA A OPERACAO: ");
        scanf("%d", &op);
            switch(op){
            //ADICAO-------------------------------------
            case 1: printf("ADICAO");
                    printf("\nDIGITE O SEGUNDO NÚMERO: ");
                    scanf("%f", &n2);
                    resultado = n1 + n2;
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //SUBTRACAO----------------------------------
            case 2: printf("SUBTRACAO");
                    printf("\nDIGITE O SEGUNDO NÚMERO: ");
                    scanf("%f", &n2);
                    resultado = n1 - n2;
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //MULTIPLICACAO-------------------------------
            case 3: printf("MULTIPLICACAO");
                    printf("\nDIGITE O SEGUNDO NÚMERO: ");
                    scanf("%f", &n2);
                    resultado = n1 * n2;
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //DIVISAO--------------------------------------
            case 4: printf("DIVISAO");
                    printf("\nDIGITE O DIVISOR: ");
                    scanf("%f", &n2);
                    if (n2==0){
                    printf("\nDIVISAO POR 0 DETECTADA!!!");
                    return 0;
                    }
                    else {
                    resultado = n1 / n2;
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                    }
                break;
            //POTENCIACAO-------------------------------------
            case 5: printf("POTENCIACAO");
                    printf("\nDIGITE O EXPOENTE: ");
                    scanf("%f", &n2);
                    resultado = pow(n1, n2);
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //RAIZ QUADRADA-------------------------------------
            case 6: printf("RAIZ QUADRADA");
                    resultado = sqrt(n1);
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //RAIZ CUBICA---------------------------------------
            case 7: printf("RAIZ CUBICA");
                    resultado = cbrt(n1);
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //SENO----------------------------------------------  
            case 8: float seno = sin(n1 * M_PI/180);
                    printf("\nSENO: %.2f\n",seno);
                break;
            //COSSENO-------------------------------------------
            case 9: float cosseno = cos(n1 * M_PI/180);
                    printf("\nCOSSENO: %.2f\n",cosseno);
                break;
            //TANGENTE------------------------------------------
            case 10: float tangente = tan(n1 * M_PI/180);
                    printf("\nTANGENTE: %.2f\n",tangente);
                break;
            //LOGARITIMO----------------------------------------
            case 11: printf("LOGARITIMO");
                    resultado = log10(n1);
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //LOGARITIMO NATURAL---------------------------------
            case 12: printf("LOGARITIMO NATURAL");
                    resultado = log(n1);
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
             //LOGARITIMO DE X+1----------------------------------  
            case 13: printf("LOGARITIMO DE X+1");
                    resultado = log1p(n1);
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //EXPONENCIAL-----------------------------------------
            case 14: printf("EXPONENCIAL");
                    resultado = exp(n1);
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //ARCO SENO------------------------------------------- 
            case 15: float arcseno = asin(n1 * M_PI/180);
                    printf("\nARCO SENO: %.2f\n",arcseno);
                break;
            //ARCO COSSENO-----------------------------------------
            case 16: float arccos = acos(n1 * M_PI/180);
                    printf("\nARCO COSSENO: %.2f\n",arccos);
                break;
            //ARCO TANGENTE------------------------------------------
            case 17: float arctg = atan(n1 * M_PI/180);
                    printf("\nARCO TANGENTE: %.2f\n",arctg);
                break;
            //EXPONENCIAL DE BASE 2----------------------------------
            case 18: printf("EXPONENCIAL DE BASE 2");
                    resultado = exp2(n1);
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //RESTO DE DIVISAO---------------------------------------  
            case 19: printf("RESTO DE DIVISAO");
                    printf("\nDIGITE O SEGUNDO NÚMERO: ");
                    scanf("%f", &n2);
                    resultado = remainder(n1,n2);
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
            //SOMA DE QUADRADOS-------------------------------------- 
            case 20: printf("SOMA DE QUADRADOS");
                    printf("\nDIGITE O SEGUNDO NÚMERO: ");
                    scanf("%f", &n2);
                    resultado = hypot(n1,n2);
                    printf ("\nO RESULTADO É: %.2f\n",resultado);
                break;
                
            default: if(op==0){
                    printf("PROGRAMA ENCERRADO");
                    return 0;
                    }   
                    else {
                    printf("OPERACAO INVALIDA!\n");
                    }
                break;
            }
    }  while(op!=0);
}