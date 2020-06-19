#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define COLUNA 5
 
/* Nome da estrutura : Student;                                               */
/* Definicao         : Essa estrutura carrega em si as informacaoes do aluno. */
 
typedef struct {
    char nome1[16], nome2[16];
    int Nusp;
    float p1, p2, trabalho, media;
} Student;
 
/* Listagem das funcoes utilizadas no projeto */
 
void limpar_a_casa1(float **estatist, int i);
void gravar_info(int *numAlunosporTurma, Student* arr, int i, float** m);
void print_student(Student *s, int pos);
void numeros_turma(int i, int number_of_students, float **estatist, Student *s);
float** Alocar_Matriz (void);
void read_student(Student *s, int number_of_students);
Student* allocate_StudentArray(int number_of_students, int i);
Student* create_class(int totalTurmas, int number_of_students);
void search_StudentByName(Student* p, int numAlunosporTurma[], int N, char nome1[16], char nome2[16]);
 
/* Funcao main */
 
int main(int argc, const char * argv[]) {
    int i = 0;                 /*      Numero de turmas     */
    float **estatist = NULL;   /* A matriz das estatisticas */
    Student* p = NULL;
    int n, Total_de_estudantes = 0, number_of_students, numAlunosporTurma[10];
    estatist = Alocar_Matriz();
    char nome1[16], nome2[16];
   
    while(1) {
        printf("               MENU DO GERENCIADOR DE NOTAS               \n");
        printf(" 1 - Criar turma                                          \n");
        printf(" 2 - Procurar aluno                                       \n");
        printf(" 3 - Gerar estatisticas das turmas                        \n");
        printf(" 4 - Gravar informacoes de uma turma                      \n");
        printf(" 5 - Encerrar sistema                                     \n");
        printf("                  ~ Digite uma opcao ~                    \n");
        scanf("%d", &n);
        switch(n) {
            case 1: {
                printf(" Numero de alunos da turma: \n");
                scanf("%d", &number_of_students);
                p = create_class(i, number_of_students);
                numeros_turma(i, number_of_students, estatist, p);
                Total_de_estudantes = Total_de_estudantes + number_of_students;
                numAlunosporTurma[i]=number_of_students;
                i++;
                break;
            }
            case 2: {
                printf(" Digite o nome e o sobrenome do aluno que procura: \n");
                scanf("%s %s", nome1, nome2);
                search_StudentByName(p, numAlunosporTurma, i, nome1, nome2);
                break;
            }
            case 3: {
                printf(" Media P1  Media P2  Media Trabalho  Media Final  Porcentagem de Aprovados ");
                for(int a = 0; a < i; a++){
                    for(int aux = 0; aux < 5; aux++){
                        printf("%f\t\t", estatist[a][aux]);
                    }
                    printf("\n");
                }
                break;
            }
            case 4: {
                gravar_info(numAlunosporTurma, p, i, estatist);
                break;
            }
            case 5: {
                limpar_a_casa1(estatist, i);
                for(int aux=0; aux<i;aux++){
                    free(p-aux);
                }
                printf(" Encerrando o sistema...\n");
                return 0;
                break;
            }
            default : {
                printf(" Entrada Invalida \n");
                return 0;
                break;
            }  
            break;
        }
    }
    return 0;
}
 
/* Nome da funcao : create_class(int i, int number_of_students);                                                  */
/* Definicao      : Essa faz uso da funcao allocate_StudentArray visando formar o bloco de cadastro de uma turma. */
 
Student* create_class(int i, int number_of_students) {
    Student* arr;
    arr = allocate_StudentArray(number_of_students, i);
    return arr;
}
 
/* Nome da funcao : read_student(Student* s, int number_of_students);                                              */
/* Definicao      : Essa funcao le as informações do aluno que está sendo registrado e a posição do aluno no array */
/* é definida pela ordem de cadastro no sistema.                                                                   */
 
void read_student(Student* s, int number_of_students) {
    int i = 0;
    for(i = 0; i < number_of_students; i++){
        printf(" Nome do aluno: ");
        scanf("%s", s[i].nome1);
        printf(" Sobreome do aluno: ");
        scanf("%s", s[i].nome2);
        printf(" Numero USP: ");
        scanf("%d", &s[i].Nusp);
        printf(" Nota da P1: ");
        scanf("%f", &s[i].p1);
        printf(" Nota da P2: ");
        scanf("%f", &s[i].p2);
        printf(" Nota do Trabalho: ");
        scanf("%f", &s[i].trabalho);
        s[i].media = (s[i].trabalho + s[i].p1 + s[i].p2)/3;
    }
}
 
/* Nome da funcao : allocate_StudentArray(int number_of_students, int i); */
/* Definicao      : Essa funcao aloca dinamicamente o array de structs.   */
 
Student* allocate_StudentArray(int number_of_students, int i) {
    Student *p;
    p = (Student*) malloc(sizeof(Student)*number_of_students);
    read_student(p, number_of_students);
    return (p);
}
 
/* Nome da funcao : search_StudentByName(Student* p, int pos, int N, char nome1[16], char nome2[16]);                             */
/* Definicao      : Essa funcao busca a posição do aluno que o usúario digitou o nome completo. Tal função imprime "Aluno não     */
/* encontrado", caso o aluno não tenha sido cadastrado, ou imprime os dados do aluno buscado, por meio da função print_student(). */
 
void search_StudentByName(Student* p, int numAlunosporTurma[], int N, char nome1[16], char nome2[16]) {
  Student* x=p;
   int pos=numAlunosporTurma[N];
    if (pos == -1 && p == x- N) {
        printf(" Aluno nao encontrado.\n");
    }
   
    else if (strncmp(nome1, p[pos].nome1, strlen(p[pos].nome1)) == 0 && strncmp(nome2, p[pos].nome2, strlen(p[pos].nome2)) == 0) {
        print_student(p, pos);
    }
    
    else if(pos==-1 && p != x- N){
      p--;
      search_StudentByName(p, numAlunosporTurma, N-1, nome1, nome2);

    }
    else {
        
        pos--;
        search_StudentByName(p, numAlunosporTurma, N, nome1, nome2);
    }


}
 
/* Nome da funcao : print_student(Student *s);                   */
/* Definicao      : Essa funcao imprime as informacoes do aluno. */
 
void print_student(Student *s, int pos) {
    printf("Nome: %s", s[pos].nome1);
    printf("Sobrenome: \t%s\n", s[pos].nome2);
    printf("Numero USP: %d\n", s[pos].Nusp);
    printf("Nota P1: %f\n", s[pos].p1);
    printf("Nota P2: %f\n", s[pos].p2);
    printf("Nota Trabalho: %f\n", s[pos].trabalho);
    printf("Media Final do Aluno: %f\n",s[pos].media);
}
 
/* Nome da funcao : Alocar_Matriz ();                                                            */
/* Definicao      : Essa funcao aloca uma lista de estudantes para poder escreve-las no arquivo. */
 
float** Alocar_Matriz () {
    int aux;
    float **m = (float**)malloc(10 * sizeof(float*));
    for (aux = 0; aux < 10; aux++){
        m[aux] = (float*) malloc(COLUNA * sizeof(float));
    }
    return m;
}
 
/* Nome da funcao : numeros_turma(int i, int number_of_students, float **estatist, Student *s);   */
/* Definicao      : Essa funcao cria as estatísticas e insere na matriz. À medida que se cria uma */
/* turma, ela cria as estatísticas pedidas.                                                       */
 
void numeros_turma(int i, int number_of_students, float **estatist, Student *s) {
    float mediaP1, mediaP2, mediaTrabalho, medFinalTurma, nAprovados, porcent;
    mediaP1 = 0; mediaP2 = 0; mediaTrabalho = 0; medFinalTurma = 0; nAprovados = 0;
    for(int aux = 0; aux < number_of_students; aux++) {
        mediaP1 = s[aux].p1 + mediaP1;
        mediaP2 = mediaP2 + s[aux].p2;
        mediaTrabalho = mediaTrabalho + s[aux].trabalho;
        medFinalTurma = medFinalTurma + s[aux].media;
        if(s[aux].media >= 5){
            nAprovados++;
        }
    }
    mediaP1 = (float) mediaP1/number_of_students;
    mediaP2 = (float)mediaP2/number_of_students;
    mediaTrabalho = (float)mediaTrabalho/number_of_students;
    medFinalTurma = (float)medFinalTurma/number_of_students;
    porcent = (float)(nAprovados*100)/number_of_students;
   
    estatist[i][0] = (float)mediaP1;
    estatist[i][1] = (float)mediaP2;
    estatist[i][2] = (float)mediaTrabalho;
    estatist[i][3] = (float)medFinalTurma;
    estatist[i][4] = (float)porcent;
}
 
/* Nome da funcao : gravar_info(int *numAlunosporTurma, Student* arr, int i, float** m);   */
/* Definicao      : Essa funcao gera arquivos textos para cada uma das turmas, contendo as */
/* estatísticas de cada uma delas, sendo o nome do arquivo é inserido pelo usuário.        */  
 
void gravar_info(int *numAlunosporTurma, Student* arr, int i, float** m) {
    char nomArqv[20];
    int aux = 0;
    for(aux = 0; aux < i; aux++) {
        FILE *arqEst;
        FILE *arq;
        arqEst = fopen("stat.bin","ab");
        printf(" Digite nome do arquivo texto\n");
        scanf("%s", nomArqv);
        arq=fopen(nomArqv, "a");
        fprintf(arq, "Nome Completo   Numero USP  Nota P1  Nota P2  Nota Trabalho  Media\n");
        for(int t=0; t<numAlunosporTurma[aux]; t++){
            fprintf(arq, "%s %s, %d, %f, %f, %f, %f\n", arr[t].nome1, arr[t].nome2, arr[t].Nusp, arr[t].p1, arr[t].p2, arr[t].trabalho, arr[t].media);
            fwrite(&m[aux], sizeof(float), COLUNA, arqEst);
        }
        fclose(arq);
        fclose(arqEst);
    }
}
 
/* Nome da funcao : limpar_a_casa1(float** estatist, int i);                                               */
/* Definicao      : Essa funcao desaloca dinamicamente a matriz "estatist", liberando o espaço de memória. */
 
void limpar_a_casa1(float** estatist, int i) {
    int aux = 0;
    for (aux = 0; aux < i; aux++){
        free (estatist[aux]);
    }
    free (estatist);
}
