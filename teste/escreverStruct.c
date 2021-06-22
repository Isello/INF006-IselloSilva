#include <stdio.h>


    typedef struct {
        char nome[10];
        char nota[2];
    } tp_aluno;

main() {
    tp_aluno alunos[] = {{"Luiz", "5"}, {"Paulo", "5"}, {"Maria", "5"},
                         {"Luiza", "5"}, {"Felipe", "5"}, {"Fabiana", "5"}};
    int ret;
    int na =6;
    FILE *arq;
    char nomearq[] = "turma.txt";
    arq = fopen(nomearq, "wb");
    if (arq != NULL) {
        ret = fwrite(alunos, sizeof(tp_aluno), na, arq);
        if (ret == na)
            printf("Gravacao %d registros com sucesso\n", ret);
        else
            printf("Foram gravados apenas %d elementos\n", ret);
        fclose(arq);
    }
    else
        puts("Erro: abertura do arquivo");
}
