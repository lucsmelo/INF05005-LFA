#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <errno.h>
//#include <unistd.h>
//#include <fcntl.h>
//#define _O_U16TEXT 0x20000 RIP LINUX
#include "gramatica.h"

int teste_estado(char *nome, char estados[MAX_ESTADOS][TAM_STRING])
{
    int i = 0;
    while(strcmp(estados[i],"") != 0)
    {
        if(!strcmp(nome,estados[i]))
            return 1;
        i++;
    }
    return 0;
}

int teste_simbolo(char *nome, char simbolos[MAX_SIMBOLOS][TAM_STRING])
{
    int i = 0;
    while(strcmp(simbolos[i],"") != 0)
    {
        if(!strcmp(nome,simbolos[i]))
            return 1;
        i++;
    }
    return 0;
}

Producao *cria_producao(char *transicao, char estados[MAX_ESTADOS][TAM_STRING], char simbolos[MAX_SIMBOLOS][TAM_STRING])
{
    Producao *nova_producao = (Producao*) malloc(sizeof(Producao));

    transicao++; //Pula a (.
    transicao = strtok(transicao,",");
    if(teste_estado(transicao,estados))
    {
        strcpy(nova_producao->nome,transicao);
        transicao = strtok(NULL,")");
        if(teste_simbolo(transicao,simbolos))
        {
            strcpy(nova_producao->simbolo,transicao);
            transicao = strtok(NULL,"\n");
            transicao++;
            if(teste_estado(transicao,estados))
            {
                strcpy(nova_producao->proxima,transicao);
                return nova_producao;
            }

        }
    }
    return NULL;
}

int afd_para_gramatica(Producao **producoes, char finais[NUM_FINAIS][TAM_STRING], char inicial[TAM_STRING], char simbolos[MAX_SIMBOLOS][TAM_STRING])
{
    FILE *source;
    source = fopen("automato.txt","r");
    char line[TAM_LINHA];
    char line_aux[TAM_LINHA]; //Utilizado para guardar uma copia de line, que eh a linha lida do AFD.
    char estados[MAX_ESTADOS][TAM_STRING] = {""};
    char *aux;
    int i = 0; //Utilizado para definir indice no qual a producao sera gravada no array.

    if(source != NULL)
    {
        //Le a primeira linha. Essa leitura auxilia na validacao do AFD.
        fgets(line,TAM_LINHA,source);
        strcpy(line_aux,line); //Armazena uma copia da linha para nao precisar reler o arquivo apos fazer operacoes na string.

        /*
            Obtem todos os estados do AFD.
        */
        aux = strchr(line,'{');
        aux++;
        aux = strtok(aux,"}");
        aux = strtok(aux,",");
        i = 0;
        strcpy(estados[i],aux);
        while(aux != NULL)
        {
            aux = strtok(NULL,",");
            i++;
            if(aux != NULL)
                strcpy(estados[i],aux);
        }

        /*
            Obtem todos os simbolos do alfabeto.
        */
        strcpy(line,line_aux); //Busca linha original.
        aux = strchr(line,'{');
        aux++;
        aux = strchr(aux,'{');
        aux++;
        aux = strtok(aux,"}");
        //Subdivide a string e guarda cada elemento no array de simbolos.
        i = 0;
        aux = strtok(aux,",");
        strcpy(simbolos[i],aux);
        while(aux != NULL)
        {
            aux = strtok(NULL,",");
            i++;
            if(aux != NULL)
                strcpy(simbolos[i],aux);
        }

        /*
            Obtem o estado inicial.
        */
        strcpy(line,line_aux); //Busca linha original.
        aux = strchr(line,'}');
        aux++;
        aux = strchr(aux,'}');
        aux++;
        aux = strchr(aux,',');
        aux++;
        aux = strchr(aux,',');
        aux++;
        aux = strtok(aux,",");
        strcpy(inicial,aux);


        /*
            Obtem todos os estados finais.
        */
        strcpy(line,line_aux);
        aux = line;
        aux = strrchr(aux,'{');
        aux++;
        aux = strtok(aux,"}");
        //Extrai estados finais
        i = 0;
        aux = strtok(aux,",");
        strcpy(finais[i],aux);
        while(aux != NULL)
        {
            aux = strtok(NULL,",");
            i++;
            if(aux != NULL)
                strcpy(finais[i],aux);
        }

        /*
            Cria as producoes da GLUD.
        */
        fgets(line,TAM_LINHA,source);
        //Loop ate achar final do arquivo
        i = 0;
        while(fgets(line,TAM_LINHA,source) != NULL)
        {
            producoes[i] = cria_producao(line,estados,simbolos);
            if(producoes[i] == NULL)
                return 0; //Erro ao criar producao
            i++;
        }
        return 1; //Sucesso.
    }
    return 0; //Erro ao abrir arquivo
}

int atualiza_estado (Producao **gramatica, char novoEstado [TAM_STRING],char finais[NUM_FINAIS][TAM_STRING])
{

    int i,achouIndice;
    i=achouIndice=0;
    while (!achouIndice && gramatica[i]!= NULL)
    {
        if(!strcmp(gramatica[i]->nome,novoEstado))
        {
            achouIndice=1;


        }

        else  i++;

    }

    return i;

}

void acrescenta_producao(Producao *prodG,Producao **derivacoes[MAX_PRODUCOES])
{
    int i=0;

    while (derivacoes[i]!= NULL)
        i++;

    derivacoes[i]=prodG;
}


int checa_se_o_estado_eh_final(char estado[TAM_STRING],char finais[NUM_FINAIS][TAM_STRING])
{
    int i,achou;
    achou=i=0;
    while(i<=NUM_FINAIS && !achou)
    {
      achou=!(strcmp(finais[i],estado));

      i++;
    }

    return achou;
}

void reduz_palavra(char *palavra)
{
    int i = 0;
    while(palavra[i] != '\0')
        i++;
    palavra[i-1] = '\0';
}

int divide_palavra(char *palavra, char simbolos[MAX_SIMBOLOS][TAM_STRING], char lista[TAM_LISTA][TAM_STRING])
{
    char palavra_reduz_final[TAM_PALAVRA];
    char *palavra_reduz_inicio;
    int simbolo_encontrado = 0; //Flag que eh ativada se simbolo eh encontrado.
    int indice = 0; //Marca indice da lista a inserir simbolo encontrado.
    int i = 0; //Loop do simbolo.
    palavra_reduz_inicio = palavra;
    while(palavra_reduz_inicio[0] != '\0')
    {
        strcpy(palavra_reduz_final,palavra_reduz_inicio);

        while(!simbolo_encontrado)
        {
            i = 0;
            while(strcmp(simbolos[i],"") && !simbolo_encontrado)
            {
                if(!strcmp(palavra_reduz_final,simbolos[i]))
                    simbolo_encontrado = 1;
                i++;
            }
            //Se nao eh palavra zerada ainda, reduz final da palavra
            if(!simbolo_encontrado)
                reduz_palavra(palavra_reduz_final);
            //Retorna 0 caso palavra nao configure simbolo algum.
            if(palavra_reduz_final[0] == '\0')
                return 0;
        }
        strcpy(lista[indice],palavra_reduz_final);
        indice++;
        palavra_reduz_inicio = palavra_reduz_inicio + strlen(palavra_reduz_final);
        simbolo_encontrado = 0;
    }
    return 1;
}




int verifica_palavra(char palavra[TAM_LISTA][TAM_STRING],Producao *gramatica[MAX_PRODUCOES], char finais[NUM_FINAIS][TAM_STRING],Producao *derivacoes[MAX_PRODUCOES])
{
    char estado_atual[TAM_STRING]= "";
    int semTransicaoIndefinida,simboloNaoLido,i,j,mesmoEstado,naoFinalPalavra,simboloNaProducao,resposta,estadoFinal,naoFinalGramatica;
    i=j=0;


    semTransicaoIndefinida=1;
    naoFinalPalavra=1;
    naoFinalGramatica=1;

    while (semTransicaoIndefinida && naoFinalPalavra && naoFinalGramatica) //enquanto nÃ£o encontra uma transicao indefinida e nÃ£o chega ao final da palavra e nÃ£o chega ao final da gramÃ¡tica.
    {
        mesmoEstado=1;
        simboloNaoLido=1;

        strcpy(estado_atual,gramatica[i]->nome);

        while (mesmoEstado && simboloNaoLido) //enquanto ainda estÃ¡ no mesmo estado e o sÃ­mbolo nÃ£o foi lido
        {
            simboloNaProducao=!(strcmp(gramatica[i]->simbolo,palavra[j])); //verifica se o simbolo Ã© igual ao da produÃ§Ã£o atual, da lista de produÃ§Ãµes da gramÃ¡tica.

            if(simboloNaProducao) // caso mesmo simbolo
            {
                acrescenta_producao(gramatica[i],derivacoes);// acrescenta producao na seq de derivacoes da palavra
                strcpy(estado_atual,gramatica[i]->proxima); // informa o novo estado atual
                if(gramatica[i+1] != NULL) // caso nÃ£o seja a Ãºltima produÃ§Ã£o da lista de produÃ§Ãµes da gramÃ¡tica
                {
                    i=atualiza_estado(gramatica,estado_atual,finais); //atualiza o Ã­ndice da produÃ§Ã£o para o estado atual
                }

                else
                {
                    naoFinalGramatica=0;
                }

                mesmoEstado=0;   //informa que mudou de estado
                simboloNaoLido=0; //informa que o sÃ­mbolo foi lido

            }


            else // caso o sÃ­mbolo nÃ£o esteja na produÃ§Ã£o
            {
                i++;// avanÃ§a posicÃ£o da produÃ§Ã£o na lista
                mesmoEstado=!(strcmp(gramatica[i]->nome,estado_atual)); //verifica se ainda a gramatica ainda esta no mesmo estado
            }

        }

        if(simboloNaoLido) // caso o simbolo n possibilite fazer uma transicao para um novo estado, marca como transicao indefinida
            semTransicaoIndefinida=0;

        if(palavra[j+1][0]== '\0')
            naoFinalPalavra=0;// verifica se a palavra chegou ao final
        j++; // atualiza Ã­ndice da palavra

    }

    estadoFinal=checa_se_o_estado_eh_final(estado_atual,finais); // verifica se o estado atual Ã© final

    if(!semTransicaoIndefinida || !estadoFinal) // se o simbolo nao permite avanÃ§ar para um novo estado e o estado atual nï¿½o ï¿½ final, a palavra ï¿½ rejeitada
        resposta=0;

    else
        resposta=1; // a palavra eh aceita
    //clear derivaÃ§Ãµes

    return resposta;
}

const char* pega_campo_por_num(char* line, int num)
{
    const char* token;
    for (token = strtok(line, ",");
            token && *token;
            token = strtok(NULL, ",\n"))
    {
        if (!num--)
            return token;
    }
    return NULL;
}
void printa_array(char**arrays,int num)
{
    for(int i=0;i<num;i++)
    {
        printf("Palavra %d:        %s\n",i+1,arrays[i]);
    }
}

int verifica_se_10_palavras(int num)
{
    if(num==10)
        return 1;
    else
    {
            /*printf("O arquivo de entrada esta incompativel com o programa,tente novamente com outro arquivo\n");
            printf("Programa encerrando com erro no arquivo de inputs\n");
            _setmode(_fileno(stdout), _O_U16TEXT);
            sleep(1);
            wprintf(L"â³âŒ\n");
            sleep(1);
            wprintf(L"â³âŒ\n");
            sleep(1);
            wprintf(L"â³âŒ\n");

            wprintf(L"volte sempre   ");

            _setmode(_fileno(stdout), _O_U16TEXT);
            wprintf(L"âœŒ");
            wprintf(L"\n \x8B1D\x8B1D\n");*/
            return 0;
    }
}

void encerra_programa()
{
       /*_setmode(_fileno(stdout), _O_U16TEXT);

        sleep(1);
        wprintf(L"âœ…\n");
        sleep(1);
        wprintf(L"âœ…\n");
        sleep(1);
        wprintf(L"âœ…\n");*/
}


