#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define TAM_MAX_SIMBOLOS 10
#define QTD_MAX_ESTADO 10
#define QTD_MAX_PROX_ESTADO 5
#define F 'F'
#define V 'V'

/* ====================== Tabela Automato Finito ============================================================================== */
typedef struct
{
    char simbolo;
    int proximo_estado[QTD_MAX_PROX_ESTADO];
    int estado_atual;

}AF;
/* ============================================================================================================================ */



/*======================================= Variaveis Globais =================================================================== */
AF afnd[QTD_MAX_ESTADO][TAM_MAX_SIMBOLOS];
AF afd[30][30];


int qtd_Estados;
int qtd_Simbolos;
int estados_finais[QTD_MAX_ESTADO];
/* ============================================================================================================================ */



/* =========================== inicializa o vetor de próximo estado, preenchendo com F ======================================== */
inicializa()
{
    int indice_Linha = 1, indice_Coluna, indice_Prox_Estado = 0;

    for ( ; indice_Linha < qtd_Estados ; indice_Linha++ )
    {
        indice_Coluna = 1;

        for ( ; indice_Coluna < qtd_Simbolos ; indice_Coluna++ )
        {
            indice_Prox_Estado = 0;
            afd[indice_Linha][indice_Coluna].proximo_estado[0] = 0;
            for ( ; indice_Prox_Estado < QTD_MAX_PROX_ESTADO ; indice_Prox_Estado++ )
            {
                afnd[indice_Linha][indice_Coluna].proximo_estado[indice_Prox_Estado] = F;

            }
        }
    }
}
/* ============================================================================================================================ */



/* ==================================== Recebe os primeiros dados ============================================================= */
void recebe_simbolo_qtdEstados ()
{
    int indiceLinha = 0, indiceColuna = 1, aux = 0;

    printf ( "Informe os Simbolos do alfabeto (Informe B no final para Branco):  \n" );
    printf ( "Ex: abcdB\n" );

    do /* tabela AFND recebe os símbolos do alfabeto na LINHA 0 */
    {
        printf("# \n");
        scanf( "%c", &afnd[indiceLinha][indiceColuna].simbolo );
        afd[indiceLinha][indiceColuna].simbolo = afnd[indiceLinha][indiceColuna].simbolo;
        indiceColuna++;
    }while ( afnd[indiceLinha][indiceColuna-1].simbolo == 'B' );
    fflush(stdin);
    system("cls");

    qtd_Simbolos = indiceColuna - 1;
    indiceLinha = 1;
    indiceColuna = 0;

    printf( "Informe a Quantidade de Estados: \n" );
    scanf( "%d", &qtd_Estados );

    for ( ; indiceLinha < qtd_Estados; indiceLinha++ ) /* tabela afnd recebe os estados na COLUNA 0 */
    {
        afnd[indiceLinha][indiceColuna].estado_atual = aux;
        aux++;
    }

    afd[1][0].estado_atual = 0; /* a tabela afd recebe 0 nestes indices porque é o estado 0, e o estado 0 não muda */

    system("cls");
    fflush(stdin);
}
/* ============================================================================================================================ */

/* ============ Preenche tabela com F para FALSO. Recebe os estados finais. Insere V nos indices dos estados finais) ========== */
void preenche_F()
{
    int indiceLinha = 1;
    int indiceColuna = 1;
    int qtd_Estados_Finais, indiceBranco, aux;

    for ( ; indiceLinha < qtd_Estados; indiceLinha++)
    {

        indiceColuna = 1;
        for ( ; indiceColuna < qtd_Simbolos; indiceColuna++ )          /* Preenche tabela com F */
        {
            for ( aux = 0 ; aux < QTD_MAX_PROX_ESTADO ; aux++ )
            {
            afnd[indiceLinha][indiceColuna].proximo_estado[aux] = F;
            }
        }
    }

    printf( "Quantos Estados Finais a Tabela AFND Possui?  " );
    scanf( "%d", &qtd_Estados_Finais );                                /* Recebe a quantidade de estados finais */

 /*   for ( indiceColuna = 0; ; indiceColuna++)                          // Localize o indice do Simbolo BRANCO
    {
        if (afnd[0][indiceColuna].simbolo == 'B')
        {
            indiceBranco = indiceColuna;
            break;
        }
    }  */

    printf( "Informe-os:\n" );
    for ( aux = 0; aux < qtd_Estados_Finais; aux++ )            /* Recebe os estados finais e insere o V lendo B nos estados finais */
    {
        printf( "# " );
        scanf( "%d", &estados_finais[aux] );
      //  afnd[estados_finais[aux]][indiceBranco].proximo_estado[0] = V;  /* Atribui V para o estado final, lendo o branco */
    }
    fflush( stdin );
    system( "cls" );
}
/* ============================================================================================================================ */




/* ============================================================================================================================ */

void informa_transicao()
{
    int indice_Linha_EstadoAtual = 1, indice_Coluna_Simbolos = 1, qtd_ProxEstado = 1, aux;

    fflush(stdin);
    printf( "Informe as Transicoes da Tabela AFND: \n" );
    while ( indice_Linha_EstadoAtual < qtd_Estados )
    {
        indice_Coluna_Simbolos = 1;
        while ( indice_Coluna_Simbolos < qtd_Simbolos )
        {
            printf( "--> No Estado   %d   , Lendo   %c   , vai para o(s) Estado(s) :  ", afnd[indice_Linha_EstadoAtual][0].estado_atual, afnd[0][indice_Coluna_Simbolos].simbolo );
            scanf( "%d%d%d%d%d" ,&afnd[indice_Linha_EstadoAtual][indice_Coluna_Simbolos].proximo_estado[1],
                                 &afnd[indice_Linha_EstadoAtual][indice_Coluna_Simbolos].proximo_estado[2],
                                 &afnd[indice_Linha_EstadoAtual][indice_Coluna_Simbolos].proximo_estado[3],
                                 &afnd[indice_Linha_EstadoAtual][indice_Coluna_Simbolos].proximo_estado[4] );

            indice_Coluna_Simbolos++;
        }
        indice_Linha_EstadoAtual++;
    }
}
/* ============================================================================================================================ */



/* ==================================== Conversão AFND para AFD =============================================================== */
void converte()
{
    int indice_LinhaEstado_afnd = 1, indice_ColunaEstado_afnd = 0, indice_LinhaSimbolo_afnd = 0, indice_ColunaSimbolo_afnd = 1;
    int indice_LinhaEstado_afd = 1, indice_ColunaEstado_afd = 0, indice_LinhaSimbolo_afd = 0, indice_ColunaSimbolo_afd = 1;
    int indice_Linha_proxEstado = 1, indice_Coluna_proxEstado = 1;
    int aux, aux2, aux3, flag;
    int qtd_Estados_AFD = 1;


    for ( indice_ColunaSimbolo_afnd = 1 ; indice_ColunaSimbolo_afnd < qtd_Simbolos ; indice_ColunaSimbolo_afnd++ )   /* concatena os numeros dos estados na primeira linha (estado 0) na tabela afd porque o primeiro estado não muda */
    {
        aux2 = 0;
        while ( afnd[1][indice_ColunaSimbolo_afnd].proximo_estado[aux2] != F )
        {
            afd[1][indice_ColunaSimbolo_afnd].proximo_estado[0] += afnd[1][indice_ColunaSimbolo_afnd].proximo_estado[aux2];
            if ( afnd[1][indice_ColunaSimbolo_afnd].proximo_estado[aux2+1] != F )
            {
                afd[1][1].proximo_estado[0] *= 10;
                aux2++;
            }
            /* else
            {
                afnd[1][indice_ColunaSimbolo_afnd].proximo_estado[aux2+1] = F;
            } */

        }
        if (afnd[1][indice_ColunaSimbolo_afnd].proximo_estado[aux2] == F)
        {
            afd[1][indice_ColunaSimbolo_afnd].proximo_estado[0] = F;
        }
    }

    for (indice_LinhaEstado_afd = 1, aux2 = 2 ; indice_LinhaEstado_afd <= qtd_Estados_AFD ; indice_LinhaEstado_afd++ )
    {

        for (indice_ColunaSimbolo_afd = 1 ; indice_ColunaSimbolo_afd < qtd_Simbolos ; indice_ColunaSimbolo_afd++ )
        {

            for ( aux = 1 ; aux <= qtd_Estados_AFD ; )
            {
                if ( ( afd[indice_LinhaEstado_afd][indice_ColunaEstado_afd].proximo_estado[0] == afd[aux][0].estado_atual )
                    || (afd[indice_LinhaEstado_afd][indice_ColunaEstado_afd].proximo_estado[0] == F) )
                {
                    flag = 1;
                }
                else
                {
                    flag = 0;
                    aux++;
                }
            }
            if ( flag )
            {
                qtd_Estados_AFD++;
                afd[aux2][0].estado_atual =  afd[indice_LinhaEstado_afd][indice_ColunaEstado_afd].proximo_estado[0];
                aux2++;


            }
        }

        indice_LinhaEstado_afd++;

        //continuar...

    }




}
/* ============================================================================================================================ */



/* ====================================== MAIN (preparado para ser implementado futuramente se preciso ======================== */
int main()
{

            inicializa();

            recebe_simbolo_qtdEstados ();

            preenche_F();

            informa_transicao();

            converte();

}
