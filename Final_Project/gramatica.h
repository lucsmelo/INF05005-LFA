/*
    Segunda parte do trabalho final da disciplina de Linguagens Formais e Automatos N, 2020/1.
    Trabalho por: Aline Machado Osmar, Lucas Lima de Melo e Pedro Fronchetti Costa da Silva.
*/

#define TAM_STRING 50
#define TAM_LINHA 200
#define MAX_PRODUCOES 100
#define MAX_ESTADOS 100
#define MAX_SIMBOLOS 100
#define NUM_FINAIS 100
#define TAM_PALAVRA 1000
#define TAM_LISTA 200

/*
    A estrutura producao representa uma gramatica linear unitaria a direita (GLUD).

    char *nome: String que identifica o nome da producao. Por exemplo, em A -> wB, essa variavel armazenaria "A".
    char *simbolo: String que identifica o simbolo da GLUD. Por exemplo, em A -> wB, essa variavel armazenaria "w".
    char *proxima: String que determina a proxima producao a ser chamada. Por exemplo, em A -> wB, essa variavel armazenaria "B".
*/
struct producao
{
    char nome[TAM_STRING];
    char simbolo[TAM_STRING];
    char proxima[TAM_STRING];
};
typedef struct producao Producao;

/*
    A funcao teste_estado testa se uma determinada String eh um estado. Retorna 1 se sim e 0 se nao.

    char *nome: String com o nome do estado.
    char estados[MAX_ESTADOS][TAM_STRING]: Estados do AFD.
*/
int teste_estado(char *nome, char estados[MAX_ESTADOS][TAM_STRING]);

/*
    A funcao teste_simbolo testa se uma determinada String eh um simbolo. Retorna 1 se sim e 0 se nao.

    char *nome: String com o simoblo a ser testado.
    char simbolos[MAX_SIMBOLOS][TAM_STRING]: Simbolos do alfabeto.
*/
int teste_simbolo(char *nome, char simbolos[MAX_SIMBOLOS][TAM_STRING]);

/*
    A funcao cria_producao cria uma producao com base em uma transicao, obtida de uma linha do arquivo de entrada.
    TambÃ©m valida a transicao e retorna NULL caso exista algum erro.

    char *transicao: String obtida do arquivo de entrada no formato "(q0,a)=q1".
    char estados[MAX_ESTADOS][TAM_STRING]: Estados do AFD.
    char simbolos[MAX_SIMBOLOS][TAM_STRING]: Simbolos do alfabeto.
*/
Producao *cria_producao(char *transicao, char estados[MAX_ESTADOS][TAM_STRING], char simbolos[MAX_SIMBOLOS][TAM_STRING]);

/*
    A funcao afd_para_gramatica preenche um array de producoes com base na leitura de um arquivo.
    Tambem verifica se esse AFD eh um automato valido.

    Producao **producoes: Array de ponteiros para producoes.
    char finais[NUM_FINAIS][TAM_STRING]: Array de Strings que guarda todos os estados finais.
    char inicial[TAM_STRING]: Estado inicial.
*/
int afd_para_gramatica(Producao **producoes, char finais[NUM_FINAIS][TAM_STRING], char inicial[TAM_STRING], char simbolos[MAX_SIMBOLOS][TAM_STRING]);

/*
    A funcao reduz_palavra tira o ultimo caractere de uma palavra.

    char *palavra: Palavra a ser modificada.
*/
void reduz_palavra(char *palavra);

/*
    A funcao divide_palavra divide uma palavra de entrada em uma lista de simbolos.

    char *palavra: Palavra a ser dividida.
    char simbolos[MAX_SIMBOLOS][TAM_STRING]: Simbolos da gramatica.
    char lista[TAM_LISTA][TAM_STRING]: Array com lista de simbolos da palavra que sera dividida.
*/
int divide_palavra(char *palavra, char simbolos[MAX_SIMBOLOS][TAM_STRING], char lista[TAM_LISTA][TAM_STRING]);

/*
    A funcao atualiza_estado encontra e retorna o primeiro indice do vetor da gramatica, onde se encontra o estado dado na entrada.

    Producao **producoes: Array de ponteiros para producoes.
    char novoEstado [TAM_STRING]: Novo estado do AFD apos execucao da funcao.
    char finais[NUM_FINAIS][TAM_STRING]: Array contendo os estados finais do AFD.
*/
int atualiza_estado (Producao **gramatica, char novoEstado [TAM_STRING],char finais[NUM_FINAIS][TAM_STRING]);

/*
    A funcao acrescenta_producao acrescenta uma nova producao no primeiro espaco vazio da lista de derivacoes da palavra.

    Producao *prodG: Producao a ser acrescentada nas derivacoes.
    Producao **derivacoes[MAX_PRODUCOES]: Array com as derivacoes.
*/
void acrescenta_producao(Producao *prodG, Producao **derivacoes[MAX_PRODUCOES]);

/*
    A funcao checa_se_o_estado_eh_final verifica se o estado recebido eh final. Retorna 1 se for final e 0 se nÃ£o for final.

    char estado[TAM_STRING]: Estado a ser verificado.
    char finais[NUM_FINAIS][TAM_STRING]: Array de estados finais do AFD.
*/
int checa_se_o_estado_eh_final(char estado[TAM_STRING],char finais[NUM_FINAIS][TAM_STRING]);

/*
    A funcao verifica_palavra verifica se a palavra recebida pertence a linguagem. Retorna 1 se aceita e 0 se rejeita a palavra.

    char palavra[TAM_LISTA][TAM_STRING]: Lista de palavras a serem testadas.
    Producao *gramatica[MAX_PRODUCOES]: Lista de producoes da linguagem.
    char finais[NUM_FINAIS][TAM_STRING]: Lista de estados finais do AFD.
    Producao *derivacoes[MAX_PRODUCOES]: Lista de derivacoes da palavra.
*/
int verifica_palavra(char palavra[TAM_LISTA][TAM_STRING],Producao *gramatica[MAX_PRODUCOES], char finais[NUM_FINAIS][TAM_STRING],Producao *derivacoes[MAX_PRODUCOES]);

/*
    A funcao pega_campo_por_num pega um campo, passado por num, do arquivo csv.

    char* line: String de entrada.
    int num: Numero passado.
*/
const char* pega_campo_por_num(char* line, int num);

/*
    A funcao printa_array exibe o conteudo de um array.

    char**arrays: Array de strings para ser printado.
    int num: Numero de elementos a ser printado.
*/
void printa_array(char**arrays,int num);

/*
    A funcao verifica_se_10_linhas verifica se o arquivo tem 10 linhas, para atender as especificacoes da definicao do trabalho.

    int num: Numero de linhas.
*/
int verifica_se_10_linhas(int num);

/*
    A funcao encerra_programa mostra mensagens de encerramento na tela.
*/
void encerra_programa();
