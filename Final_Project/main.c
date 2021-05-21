#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#define _O_U16TEXT 0x20000
#include "gramatica.h"

int main()
{
    Producao *prod[MAX_PRODUCOES] = {NULL}; //Array de producoes.
    Producao *derivacoes[MAX_PRODUCOES] = {NULL}; //Array de producoes.
    char inicial[TAM_STRING] = ""; //Variavel de estado inicial.
    char palavra[TAM_PALAVRA]= "";
    char palavra2[TAM_PALAVRA]= "";
    char palavra3[TAM_PALAVRA]= "";
    char palavra4[TAM_PALAVRA]= "";
    char palavra5[TAM_PALAVRA]= "";
    char palavra6[TAM_PALAVRA]= "";
    char palavra7[TAM_PALAVRA]= "";
    char palavra8[TAM_PALAVRA]= "";
    char palavra9[TAM_PALAVRA]= "";
    char palavra10[TAM_PALAVRA]= "";

    char lista[TAM_LISTA][TAM_STRING] = {"\0"};
    char finais[NUM_FINAIS][TAM_STRING] = {""}; //Array de variaveis que representam estados finais.
    char simbolos[MAX_SIMBOLOS][TAM_STRING] = {""}; //Array de todos os simbolos possiveis que a linguagem implementa.
    int i,verifica;
    int indice_para_verificar=0;

    char line[TAM_STRING];
    char*conjunto_aceita[TAM_STRING];
    char*conjunto_rejeita[TAM_STRING];

    int indice_aceita=0;
    int indice_rejeita=0;
    strcpy(palavra2,"pcxsssmmtbdpag");
    strcpy(palavra3,"pcgssmmtbxpag");
    strcpy(palavra4,"pcxxmxbdpag");
    strcpy(palavra5,"pcxxxxxxpag");
    strcpy(palavra6,"cgsssmmtbdpag");
    strcpy(palavra7,"pgsssmmtbdpag");
    strcpy(palavra8,"pcgsssmmtbd");
    strcpy(palavra9,"pcgssssmmtbdpag");
    strcpy(palavra10,"pcsssgmmtbdpag");
  //*******************************************************************************************************
  //Testa se uma palavra digitada pelo usu�rio pertence a linguagem, printa o resultado e as deriva��es da palavra

    if(afd_para_gramatica(prod,finais,inicial,simbolos))
    {
        printf ("Digite a palavra que deseja saber se pertence a linguagem:" );
        scanf("%s",palavra);
        fflush(stdin);

        divide_palavra(palavra,simbolos,lista);

        i=atualiza_estado(prod,"q10",finais);


        verifica=verifica_palavra(lista,prod,finais,derivacoes);
        printf("A palavra: %s eh ",palavra);
        if(verifica)
        {

                printf("aceita pela linguagem!:) \n");
        }
        else printf("rejeitada pela linguagem! :( \n");
        i=0;

        while(derivacoes[i] != NULL)
        {
               printf("%s, %s -> %s\n",(derivacoes[i])->nome,(derivacoes[i])->simbolo,(derivacoes[i])->proxima);
               i++;
        }
      //
    }
    else
    {
        printf("ERRO! Arquivo de entrada nao foi aberto corretamente ou nao possui o formato correto.\n");
    }


  //*******************************************************************************************************

    //****************************************************************************************************
    //verificação se o arquivo de entrada do usuário esta correto;
    char File_name[50];
    printf("O arquivo de entrada .csv deve possuir as palavras em uma linha separadas por virgula!\n");
    printf("Entre o nome do arquivo que deseja ler por favor!(Obs:com .csv no final)\n");
    gets(File_name);
    FILE* stream = fopen(File_name, "r");
        while (stream==NULL)
        {
            printf("Erro na abertura do arquivo,tente novamente!(Obs:com .csv no final)\n");
            gets(File_name);
            stream = fopen(File_name, "r");
            }
    //****************************************************************************************************
    //leitura do arquivo de entrada fornecido pelo usuário
    int count=0;
    char line1[1024];
    fgets(line1, 1024, stream);
    char *tmp = strtok (line1, ",");
    char *entrada_csv[10];
    while (tmp != NULL)
    {
        entrada_csv[i++] = tmp;
        count++;
        tmp = strtok (NULL, ",");
    }

    //****************************************************************************************************
    //voce foi um bom guerreiro freeeeeeeeeeeeeeeeeeeeeee descanse em paz!
if(verifica_se_10_palavras(count)==0)
{
    printf("O arquivo de inputs lido possui uma quantidade de palavras diferente de 10, Por favor tente novamente com outro arquivo!");
    printf("\nAperte qualquer tecla para encerrar o programa");
    getchar();
    printf("Programa Encerrando:\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    return 0;
}
    //****************************************************************************************************
    //continua para ler a lista de palavras
 else
 {
     /* code */


        for(int a=0;a<10;a++)//verifica a cada palavra do arquivo, se pertencer a linguagem entra no conjunto aceita,se não entra no conjunto rejeita
        {
            divide_palavra(entrada_csv[a],simbolos,lista);
            verifica=verifica_palavra(lista,prod,finais,derivacoes);//verifica se a palavra pertence

            if(verifica)//palavra pertence
            {
                    conjunto_aceita[indice_aceita]=malloc(sizeof(entrada_csv));
                    strcpy(conjunto_aceita[indice_aceita],entrada_csv[a]);//entra no conjunto aceita
                    indice_aceita++;
            }

            else //palavra não pertence
            {
                    conjunto_rejeita[indice_rejeita]=malloc(sizeof(entrada_csv));
                    strcpy(conjunto_rejeita[indice_rejeita],entrada_csv[a]);//entra no conjunto rejeita
                    indice_rejeita++;
            }
            memset(derivacoes, 0, sizeof(derivacoes));//clear derivaçoes
            memset(lista, 0, sizeof(lista));//clear lista
        }
    }

    //****************************************************************************************************
    //print dos conjuntos aceita e rejeita.
    printf("\nConjunto Aceita:\n");
    printa_array(conjunto_aceita,indice_aceita);

    printf("Conjunto Rejeita:\n");
    printa_array(conjunto_rejeita,indice_rejeita);

    //****************************************************************************************************
    //encerramento do programa.
    printf("Pressione qualquer tecla para encerrar o programa! ");
    getchar();
    printf("Programa Encerrando:\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    sleep(1);
    printf(".\n");
    fclose(stream);


    //encerra_programa();
    return 0;
}
