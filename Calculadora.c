#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <limits.h> /* para limites inteiros */

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* ---------- Configurações ---------- */
#define MAX_TIPO 20
#define HIST_SIZE 100
#define LINE_LEN 256
#define FACT_LIMIT 20   /* limite seguro para fatorial */
#define EPSILON 1e-9

/* ---------- Struct para histórico ---------- */
typedef struct {
    char tipo[MAX_TIPO];
    double a;
    double b;
    double resultado;
    int id;
} Operacao;

typedef struct {
    Operacao ops[HIST_SIZE];
    int start;
    int count;
    int next_id;
} Historico;

/* ---------- Prototipos (I/O e util) ---------- */
int read_line(char *buf, size_t sz);
int read_int(const char *prompt, int *out);
int read_double(const char *prompt, double *out);
static void clear_input_rest(void);

/* ---------- Prototipos (cálculo, sem I/O) ---------- */
/* básicas */
double calc_add(double a, double b);
double calc_sub(double a, double b);
double calc_mul(double a, double b);
int calc_div(double a, double b, double *res); /* retorna 0 OK, -1 div/0 */

/* avançadas */
double calc_pow_d(double base, double exp);
int calc_root(double value, double n, double *res);
int calc_log_base(double v, double base, double *res);
unsigned long long calc_factorial_int(int n, int *err);
double calc_mean(const double vals[], size_t n);
double calc_median(const double vals[], size_t n);
double calc_stddev(const double vals[], size_t n);
double calc_max(const double vals[], size_t n);
double calc_min(const double vals[], size_t n);
long long calc_gcd(long long a, long long b);
long long calc_lcm(long long a, long long b);

/* matrizes */
typedef struct { double m[2][2]; } Mat2;
typedef struct { double m[3][3]; } Mat3;
Mat2 mat2_add(const Mat2 *a, const Mat2 *b);
Mat2 mat2_mul(const Mat2 *a, const Mat2 *b);
Mat3 mat3_add(const Mat3 *a, const Mat3 *b);
Mat3 mat3_mul(const Mat3 *a, const Mat3 *b);

/* ---------- Prototipos (histórico) ---------- */
void init_historico(Historico *h);
void hist_add(Historico *h, const char *tipo, double a, double b, double resultado);
void hist_print(const Historico *h);
int hist_save_csv(const Historico *h, const char *filename);
int hist_load_csv(Historico *h, const char *filename);

/* ---------- Implementações: utilitários I/O ---------- */
static void clear_input_rest(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int read_line(char *buf, size_t sz) {
    if (!buf || sz == 0) return -1;
    if (!fgets(buf, (int)sz, stdin)) return -1;
    size_t len = strlen(buf);
    if (len && buf[len-1] == '\n') buf[len-1] = '\0';
    return 0;
}

int read_int(const char *prompt, int *out) {
    char line[LINE_LEN];
    if (prompt) printf("%s", prompt);
    if (!fgets(line, sizeof(line), stdin)) return -1;
    char *endptr = NULL;
    errno = 0;
    long val = strtol(line, &endptr, 10);
    if (endptr == line || errno == ERANGE || val < INT_MIN || val > INT_MAX) return -2;
    *out = (int)val;
    return 0;
}

int read_double(const char *prompt, double *out) {
    char line[LINE_LEN];
    if (prompt) printf("%s", prompt);
    if (!fgets(line, sizeof(line), stdin)) return -1;
    char *endptr = NULL;
    errno = 0;
    double val = strtod(line, &endptr);
    if (endptr == line || errno == ERANGE) return -2;
    *out = val;
    return 0;
}

/* ---------- Implementações: cálculos puros ---------- */
double calc_add(double a, double b) { return a + b; }
double calc_sub(double a, double b) { return a - b; }
double calc_mul(double a, double b) { return a * b; }
int calc_div(double a, double b, double *res) {
    if (b == 0.0) return -1;
    *res = a / b;
    return 0;
}
double calc_pow_d(double base, double exp) { return pow(base, exp); }

/*
  calc_root:
  - se n == 0 -> erro
  - se value < 0: só permite quando n é inteiro ímpar
*/
int calc_root(double value, double n, double *res) {
    if (fabs(n) < EPSILON) return -1; /* n == 0 inválido */
    /* verificar se n é inteiro (próximo) */
    double n_round = round(n);
    int n_is_int = (fabs(n - n_round) < 1e-9) ? 1 : 0;
    if (value < 0.0) {
        if (!n_is_int) return -2; /* raiz fracionária de negativo inválida */
        long ni = (long) n_round;
        if ((ni % 2) == 0) return -2; /* raiz par de negativo inválida */
        /* para inteiro ímpar, resultado é negativo real */
        *res = -pow(fabs(value), 1.0 / n_round);
        return 0;
    }
    *res = pow(value, 1.0 / n);
    return 0;
}

int calc_log_base(double v, double base, double *res) {
    if (v <= 0.0 || base <= 0.0 || fabs(base - 1.0) < EPSILON) return -1;
    *res = log(v) / log(base);
    return 0;
}
unsigned long long calc_factorial_int(int n, int *err) {
    if (n < 0) { if (err) *err = -1; return 0; }
    if (n > FACT_LIMIT) { if (err) *err = -2; return 0; }
    unsigned long long f = 1ULL;
    for (int i = 2; i <= n; ++i) f *= (unsigned long long)i;
    if (err) *err = 0;
    return f;
}
double calc_mean(const double vals[], size_t n) {
    if (n == 0) return NAN;
    double s = 0.0;
    for (size_t i = 0; i < n; ++i) s += vals[i];
    return s / (double)n;
}
static int cmp_double(const void *a, const void *b) {
    double da = *(const double*)a;
    double db = *(const double*)b;
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}
double calc_median(const double vals[], size_t n) {
    if (n == 0) return NAN;
    double *copy = malloc(sizeof(double) * n);
    if (!copy) return NAN;
    for (size_t i = 0; i < n; ++i) copy[i] = vals[i];
    qsort(copy, n, sizeof(double), cmp_double);
    double med;
    if (n % 2 == 1) med = copy[n/2];
    else med = (copy[n/2 - 1] + copy[n/2]) / 2.0;
    free(copy);
    return med;
}
double calc_stddev(const double vals[], size_t n) {
    if (n == 0) return NAN;
    double mean = calc_mean(vals, n);
    double s = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double d = vals[i] - mean;
        s += d * d;
    }
    return sqrt(s / (double)n);
}
double calc_max(const double vals[], size_t n) {
    if (n == 0) return NAN;
    double m = vals[0];
    for (size_t i = 1; i < n; ++i) if (vals[i] > m) m = vals[i];
    return m;
}
double calc_min(const double vals[], size_t n) {
    if (n == 0) return NAN;
    double m = vals[0];
    for (size_t i = 1; i < n; ++i) if (vals[i] < m) m = vals[i];
    return m;
}
long long calc_gcd(long long a, long long b) {
    if (a < 0) a = -a; if (b < 0) b = -b;
    while (b != 0) { long long t = a % b; a = b; b = t; }
    return a;
}
long long calc_lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    long long g = calc_gcd(a, b);
    long long div = a / g;
    /* cuidado com overflow, mas mantemos a versão simples */
    long long res = div * b;
    return (res < 0) ? -res : res;
}

/* Matrizes */
Mat2 mat2_add(const Mat2 *a, const Mat2 *b) {
    Mat2 r;
    for (int i=0;i<2;++i) for (int j=0;j<2;++j) r.m[i][j] = a->m[i][j] + b->m[i][j];
    return r;
}
Mat2 mat2_mul(const Mat2 *a, const Mat2 *b) {
    Mat2 r;
    for (int i=0;i<2;++i) for (int j=0;j<2;++j) {
        r.m[i][j] = 0.0;
        for (int k=0;k<2;++k) r.m[i][j] += a->m[i][k] * b->m[k][j];
    }
    return r;
}
Mat3 mat3_add(const Mat3 *a, const Mat3 *b) {
    Mat3 r;
    for (int i=0;i<3;++i) for (int j=0;j<3;++j) r.m[i][j] = a->m[i][j] + b->m[i][j];
    return r;
}
Mat3 mat3_mul(const Mat3 *a, const Mat3 *b) {
    Mat3 r;
    for (int i=0;i<3;++i) for (int j=0;j<3;++j) {
        r.m[i][j] = 0.0;
        for (int k=0;k<3;++k) r.m[i][j] += a->m[i][k] * b->m[k][j];
    }
    return r;
}

/* ---------- Histórico (buffer circular) ---------- */
void init_historico(Historico *h) {
    if (!h) return;
    h->start = 0;
    h->count = 0;
    h->next_id = 1;
    for (int i=0;i<HIST_SIZE;++i) {
        h->ops[i].tipo[0] = '\0';
        h->ops[i].a = h->ops[i].b = h->ops[i].resultado = 0.0;
        h->ops[i].id = 0;
    }
}
void hist_add(Historico *h, const char *tipo, double a, double b, double resultado) {
    if (!h || !tipo) return;
    int idx = (h->start + h->count) % HIST_SIZE;
    if (h->count == HIST_SIZE) {
        idx = h->start;
        h->start = (h->start + 1) % HIST_SIZE;
        /* count stays HIST_SIZE */
    } else {
        h->count++;
    }
    Operacao *op = &h->ops[idx];
    strncpy(op->tipo, tipo, MAX_TIPO-1);
    op->tipo[MAX_TIPO-1] = '\0';
    op->a = a;
    op->b = b;
    op->resultado = resultado;
    op->id = h->next_id++;
}
void hist_print(const Historico *h) {
    if (!h) return;
    printf("\n--- Histórico (%d registros) ---\n", h->count);
    if (h->count == 0) { printf("Vazio.\n"); return; }
    for (int i=0;i<h->count;++i) {
        int idx = (h->start + i) % HIST_SIZE;
        const Operacao *op = &h->ops[idx];
        printf("ID %d | %s | a=%.10g b=%.10g => resultado=%.10g\n",
               op->id, op->tipo, op->a, op->b, op->resultado);
    }
    printf("------------------------------\n");
}
int hist_save_csv(const Historico *h, const char *filename) {
    if (!h || !filename) return -1;
    FILE *f = fopen(filename, "w");
    if (!f) return -1;
    fprintf(f, "id,tipo,a,b,resultado\n");
    for (int i=0;i<h->count;++i) {
        int idx = (h->start + i) % HIST_SIZE;
        const Operacao *op = &h->ops[idx];
        fprintf(f, "%d,%s,%.15g,%.15g,%.15g\n", op->id, op->tipo, op->a, op->b, op->resultado);
    }
    fclose(f);
    return 0;
}
int hist_load_csv(Historico *h, const char *filename) {
    if (!h || !filename) return -1;
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    char line[LINE_LEN];
    /* pular cabeçalho */
    if (!fgets(line, sizeof(line), f)) { fclose(f); return -1; }
    init_historico(h);
    while (fgets(line, sizeof(line), f)) {
        int id = 0;
        char tipo[MAX_TIPO];
        double a=0.0, b=0.0, res=0.0;
        /* esperamos 5 campos: id,tipo,a,b,resultado */
        int matched = sscanf(line, "%d,%19[^,],%lf,%lf,%lf", &id, tipo, &a, &b, &res);
        if (matched >= 4) {
            /* usa hist_add para inserir (reserva posição circular), mas preserva ID do arquivo */
            hist_add(h, tipo, a, b, res);
            /* sobrescreve id gerado pelo hist_add com o id do arquivo */
            int last_idx = (h->start + h->count - 1) % HIST_SIZE;
            h->ops[last_idx].id = id;
            if (h->next_id <= id) h->next_id = id + 1;
        }
    }
    fclose(f);
    return 0;
}

/* ---------- Menu / I/O separadas das funções de cálculo ---------- */

void mostrar_menu(void) {
    puts("\n=============== CALCULADORA CIENTÍFICA (MOD) ===============");
    puts(" --- Operações em Cadeia (resultado único) ---");
    puts(" 1. Adição (+)");
    puts(" 2. Subtração (-)");
    puts(" 3. Multiplicação (*)");
    puts(" 4. Divisão (/)");
    puts("19. Resto da Divisão (%)");
    puts(" --- Operações por Elemento (vetor) ---");
    puts(" 5. Seno (graus)");
    puts(" 6. Cosseno (graus)");
    puts(" 7. Tangente (graus)");
    puts(" 8. Raiz Quadrada");
    puts("10. Logaritmo Natural");
    puts("11. Log10");
    puts("13. Valor Absoluto");
    puts("14. Fatorial");
    puts("15. Inverso (1/x)");
    puts("16. Arredondar");
    puts("17. Piso (floor)");
    puts("18. Teto (ceil)");
    puts("20. Converter Graus <> Radianos");
    puts(" --- Operações padrão (dois números) ---");
    puts(" 9. Potenciação");
    puts("12. Porcentagem");
    puts(" --- Matrizes ---");
    puts("21. Mat2 soma");
    puts("22. Mat2 multiplicação");
    puts("23. Mat3 soma");
    puts("24. Mat3 multiplicação");
    puts(" --- Histórico / Persistência ---");
    puts("30. Ver histórico");
    puts("31. Salvar histórico em CSV");
    puts("32. Carregar histórico de CSV");
    puts("0. Sair");
    printf("===========================================================\n");
    printf("Escolha uma opção: ");
}

/* Operações em cadeia: várias entradas reduzidas a um resultado */
void operacoesEmCadeia(int opcao, Historico *hist) {
    int quantidade;
    if (read_int("Quantos números você quer usar na operação? ", &quantidade) != 0 || quantidade < 2) {
        printf("Erro: é necessário fornecer um inteiro >= 2.\n");
        return;
    }
    double *numeros = malloc((size_t)quantidade * sizeof(double));
    if (!numeros) { puts("Erro de alocação."); return; }
    for (int i = 0; i < quantidade; ++i) {
        char prompt[64];
        snprintf(prompt, sizeof(prompt), "Digite o %dº número: ", i+1);
        if (read_double(prompt, &numeros[i]) != 0) { puts("Entrada inválida."); free(numeros); return; }
    }

    double resultado = numeros[0];
    int erro = 0;

    for (int i = 1; i < quantidade && !erro; ++i) {
        switch (opcao) {
            case 1: resultado = calc_add(resultado, numeros[i]); break;
            case 2: resultado = calc_sub(resultado, numeros[i]); break;
            case 3: resultado = calc_mul(resultado, numeros[i]); break;
            case 4:
                if (calc_div(resultado, numeros[i], &resultado) != 0) { printf("Erro: divisão por zero!\n"); erro = 1; }
                break;
            case 19:
                if ((int)numeros[i] == 0) { printf("Erro: divisão por zero no módulo!\n"); erro = 1; }
                else resultado = (double)((int)resultado % (int)numeros[i]);
                break;
            default: erro = 1; break;
        }
    }

    if (!erro) {
        printf("Resultado final: %.10g\n", resultado);
        /* registra histórico: tipo e operandos simplificados (a=primeiro, b=último) */
        hist_add(hist, (opcao==1)?"soma":(opcao==2)?"subtracao":(opcao==3)?"multiplicacao":(opcao==4)?"divisao":"modulo",
                 numeros[0], numeros[quantidade-1], resultado);
    }

    free(numeros);
}

/* Operações por elemento: aplica função a cada elemento do vetor */
void operacoesPorElemento(int opcao, Historico *hist) {
    int quantidade;
    if (read_int("Quantos números você quer processar? ", &quantidade) != 0 || quantidade < 1) {
        printf("Erro: é necessário pelo menos 1 número.\n");
        return;
    }
    double *numeros = malloc((size_t)quantidade * sizeof(double));
    if (!numeros) { puts("Erro de alocação."); return; }
    for (int i = 0; i < quantidade; ++i) {
        char prompt[64];
        snprintf(prompt, sizeof(prompt), "Digite o %dº número: ", i+1);
        if (read_double(prompt, &numeros[i]) != 0) { puts("Entrada inválida."); free(numeros); return; }
    }

    int sub_op = 0;
    if (opcao == 20) {
        if (read_int("1 - Graus para radianos | 2 - Radianos para graus: ", &sub_op) != 0 ||
            (sub_op != 1 && sub_op != 2)) {
            puts("Opção inválida.");
            free(numeros);
            return;
        }
    }

    puts("\n--- Resultados ---");
    for (int i = 0; i < quantidade; ++i) {
        printf("Entrada %d (%.10g): ", i+1, numeros[i]);
        switch (opcao) {
            case 5: { double r = sin(numeros[i] * M_PI / 180.0); printf("Seno = %.10g\n", r); hist_add(hist, "sin", numeros[i], 0.0, r); } break;
            case 6: { double r = cos(numeros[i] * M_PI / 180.0); printf("Cosseno = %.10g\n", r); hist_add(hist, "cos", numeros[i], 0.0, r); } break;
            case 7: { double r = tan(numeros[i] * M_PI / 180.0); printf("Tangente = %.10g\n", r); hist_add(hist, "tan", numeros[i], 0.0, r); } break;
            case 8:
                if (numeros[i] < 0.0) { printf("Erro: raiz de número negativo!\n"); }
                else { double r = sqrt(numeros[i]); printf("Raiz Quadrada = %.10g\n", r); hist_add(hist, "sqrt", numeros[i], 0.0, r); }
                break;
            case 10:
                if (numeros[i] <= 0.0) { printf("Erro: log de número não positivo!\n"); }
                else { double r = log(numeros[i]); printf("Log Natural = %.10g\n", r); hist_add(hist, "ln", numeros[i], 0.0, r); }
                break;
            case 11:
                if (numeros[i] <= 0.0) { printf("Erro: log10 de número não positivo!\n"); }
                else { double r = log10(numeros[i]); printf("Log10 = %.10g\n", r); hist_add(hist, "log10", numeros[i], 0.0, r); }
                break;
            case 13: { double r = fabs(numeros[i]); printf("Valor Absoluto = %.10g\n", r); hist_add(hist, "abs", numeros[i], 0.0, r); } break;
            case 14:
                if (numeros[i] < 0.0 || fabs(numeros[i] - round(numeros[i])) > EPSILON) { printf("Erro: fatorial de não inteiro ou negativo!\n"); }
                else {
                    int err = 0;
                    unsigned long long f = calc_factorial_int((int)round(numeros[i]), &err);
                    if (err == 0) { printf("Fatorial = %llu\n", f); hist_add(hist, "fact", numeros[i], 0.0, (double)f); }
                    else if (err == -1) printf("Erro: fatorial indefinido para negativo.\n");
                    else printf("Erro: fatorial grande demais (limite %d).\n", FACT_LIMIT);
                }
                break;
            case 15:
                if (numeros[i] == 0.0) printf("Erro: divisão por zero!\n");
                else { double r = 1.0 / numeros[i]; printf("Inverso = %.10g\n", r); hist_add(hist, "inv", numeros[i], 0.0, r); }
                break;
            case 16: { double r = round(numeros[i]); printf("Arredondado = %.10g\n", r); hist_add(hist, "round", numeros[i], 0.0, r); } break;
            case 17: { double r = floor(numeros[i]); printf("Piso = %.10g\n", r); hist_add(hist, "floor", numeros[i], 0.0, r); } break;
            case 18: { double r = ceil(numeros[i]); printf("Teto = %.10g\n", r); hist_add(hist, "ceil", numeros[i], 0.0, r); } break;
            case 20:
                if (sub_op == 1) { double r = numeros[i] * M_PI / 180.0; printf("Em radianos = %.10g\n", r); hist_add(hist, "deg2rad", numeros[i], 0.0, r); }
                else { double r = numeros[i] * 180.0 / M_PI; printf("Em graus = %.10g\n", r); hist_add(hist, "rad2deg", numeros[i], 0.0, r); }
                break;
            default:
                printf("Operação não suportada por elemento.\n");
                break;
        }
    }

    free(numeros);
}

/* Operações padrão com dois números */
void operacoesPadrao(int opcao, Historico *hist) {
    double a, b;
    if (opcao == 9) {
        if (read_double("Digite a base: ", &a) != 0 || read_double("Digite o expoente: ", &b) != 0) { puts("Entrada inválida."); return; }
        double r = calc_pow_d(a, b);
        printf("Resultado: %.10g\n", r);
        hist_add(hist, "potencia", a, b, r);
    } else if (opcao == 12) {
        if (read_double("Digite o valor total: ", &a) != 0 || read_double("Digite a porcentagem: ", &b) != 0) { puts("Entrada inválida."); return; }
        double r = (a * b / 100.0);
        printf("%.10g%% de %.10g = %.10g\n", b, a, r);
        hist_add(hist, "porcentagem", a, b, r);
    }
}

/* Matrizes I/O */
static int ler_mat2(Mat2 *m, const char *nome) {
    if (!m) return -1;
    for (int i=0;i<2;++i) for (int j=0;j<2;++j) {
        char p[64];
        snprintf(p, sizeof(p), "%s[%d][%d]: ", nome, i, j);
        if (read_double(p, &m->m[i][j]) != 0) return -1;
    }
    return 0;
}
static int ler_mat3(Mat3 *m, const char *nome) {
    if (!m) return -1;
    for (int i=0;i<3;++i) for (int j=0;j<3;++j) {
        char p[64];
        snprintf(p, sizeof(p), "%s[%d][%d]: ", nome, i, j);
        if (read_double(p, &m->m[i][j]) != 0) return -1;
    }
    return 0;
}

/* ---------- main ---------- */
int main(void) {
    Historico hist;
    init_historico(&hist);

    int opcao = -1;
    int continuar = 1;

    while (continuar) {
        mostrar_menu();
        if (read_int("", &opcao) != 0) { puts("Entrada inválida."); clear_input_rest(); continue; }

        if ((opcao >= 1 && opcao <= 4) || opcao == 19) {
            operacoesEmCadeia(opcao, &hist);
        } else if ((opcao >=5 && opcao <=8) || opcao == 10 || opcao == 11 ||
                   (opcao >=13 && opcao <=18) || opcao == 20) {
            operacoesPorElemento(opcao, &hist);
        } else if (opcao == 9 || opcao == 12) {
            operacoesPadrao(opcao, &hist);
        } else if (opcao == 21 || opcao == 22 || opcao == 23 || opcao == 24) {
            if (opcao == 21 || opcao == 22) {
                Mat2 A, B, R;
                puts("Leitura Mat2 A:");
                if (ler_mat2(&A, "A") != 0) { puts("Entrada inválida."); continue; }
                puts("Leitura Mat2 B:");
                if (ler_mat2(&B, "B") != 0) { puts("Entrada inválida."); continue; }
                if (opcao == 21) {
                    R = mat2_add(&A, &B);
                    puts("Resultado (Mat2 soma):");
                    for (int i=0;i<2;++i) { for (int j=0;j<2;++j) printf("%12.6g ", R.m[i][j]); putchar('\n'); }
                    hist_add(&hist, "mat2_soma", 0.0, 0.0, 0.0);
                } else {
                    R = mat2_mul(&A, &B);
                    puts("Resultado (Mat2 multiplicação):");
                    for (int i=0;i<2;++i) { for (int j=0;j<2;++j) printf("%12.6g ", R.m[i][j]); putchar('\n'); }
                    hist_add(&hist, "mat2_mul", 0.0, 0.0, 0.0);
                }
            } else {
                Mat3 A, B, R;
                puts("Leitura Mat3 A:");
                if (ler_mat3(&A, "A") != 0) { puts("Entrada inválida."); continue; }
                puts("Leitura Mat3 B:");
                if (ler_mat3(&B, "B") != 0) { puts("Entrada inválida."); continue; }
                if (opcao == 23) {
                    R = mat3_add(&A, &B);
                    puts("Resultado (Mat3 soma):");
                    for (int i=0;i<3;++i) { for (int j=0;j<3;++j) printf("%12.6g ", R.m[i][j]); putchar('\n'); }
                    hist_add(&hist, "mat3_soma", 0.0, 0.0, 0.0);
                } else {
                    R = mat3_mul(&A, &B);
                    puts("Resultado (Mat3 multiplicação):");
                    for (int i=0;i<3;++i) { for (int j=0;j<3;++j) printf("%12.6g ", R.m[i][j]); putchar('\n'); }
                    hist_add(&hist, "mat3_mul", 0.0, 0.0, 0.0);
                }
            }
        } else if (opcao == 30) {
            hist_print(&hist);
        } else if (opcao == 31) {
            char filename[LINE_LEN];
            printf("Nome do arquivo para salvar (ex: historico.csv): ");
            if (read_line(filename, sizeof(filename)) != 0 || filename[0] == '\0') { puts("Nome inválido."); continue; }
            if (hist_save_csv(&hist, filename) == 0) printf("Histórico salvo em '%s'\n", filename);
            else printf("Erro ao salvar em '%s'\n", filename);
        } else if (opcao == 32) {
            char filename[LINE_LEN];
            printf("Nome do arquivo para carregar (ex: historico.csv): ");
            if (read_line(filename, sizeof(filename)) != 0 || filename[0] == '\0') { puts("Nome inválido."); continue; }
            if (hist_load_csv(&hist, filename) == 0) printf("Histórico carregado de '%s'\n", filename);
            else printf("Erro ao carregar '%s'\n", filename);
        } else if (opcao == 0) {
            puts("Encerrando a calculadora...");
            break;
        } else {
            puts("Opção inválida! Tente novamente.");
        }

        /* perguntar se deseja continuar */
        int ans = -1;
        if (read_int("\nDeseja realizar outro cálculo? (1 - Sim / 0 - Não): ", &ans) != 0) {
            puts("Entrada inválida. Encerrando.");
            break;
        }
        if (ans == 0) {
            puts("Obrigado por usar a calculadora!");
            break;
        }
    } /* fim while */

    return 0;
}
