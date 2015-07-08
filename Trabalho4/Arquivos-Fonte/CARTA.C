/***************************************************************************
 *  $MCI MÛdulo de implementaÁ„o: CAR  Carta
 *
 *  Arquivo gerado:              CARTA.c
 *  Letras identificadoras:      CAR
 *
 *  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - ProgramaÁ„o Modular
 *  Autores: EG - Eric Grinstein
 JM - Jordana Mecler
 LW - Leonardo Wajnsztok
 *
 *  $HA HistÛrico de evoluÁ„o:
 *     Vers„o      Autor            Data                ObservaÁ?es
 *     1.0       EG,JM,LW        17/abr/2015       CorreÁ„o de condiÁ?es de retorno
 *     1.0       EG,JM,LW        16/abr/2015       inÌcio do desenvolvimento
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define CARTA_OWN
#include "CARTA.h"
#undef CARTA_OWN

#ifdef _DEBUG
    #include "Generico.h"
    #include "Conta.h"
    #include "CESPDIN.H"
#endif


/***********************************************************************
 *
 *  $TC Tipo de dados: CAR Carta
 *
 *
 ***********************************************************************/

typedef struct CAR_tagCarta {
    
    char naipe ;
    /* Naipe da carta
     */
    
    int valor ;
    /* Valor da carta
     */
    
    #ifdef _DEBUG
    
        char tipo;
        int tamBytes;
    
    #endif
    
} CAR_tpCarta ;

/***** ProtÛtipos das funÁ?es encapuladas no mÛdulo *****/

int VerificarNaipe( char naipe ) ;

int VerificarValor( char valor ) ;

/*****  CÛdigo das funÁ?es exportadas pelo mÛdulo  *****/

#ifdef _DEBUG

    /***************************************************************************
     *
     *  Função: CAR  Obter tipo
     *  ****/
	void AlteraTipoCarta( CAR_tppCarta pCarta, char tipo )
	{
		pCarta->tipo = tipo;
	}

    char CAR_ObterTipo(CAR_tppCarta pCarta)
    {
        if (pCarta != NULL)
        {
            return pCarta->tipo;
        }
        
        return '0';
    }

    /***************************************************************************
     *
     *  Função: CAR  Obter tamanho em bytes
     *  ****/

    int CAR_ObterTamBytes(CAR_tppCarta pCarta)
    {
        if (pCarta != NULL)
        {
            return pCarta->tamBytes;
        }
        return 0;
    }

#endif

/***************************************************************************
 *
 *  FunÁ„o: CAR  Criar carta
 *  ****/

CAR_tpCondRet CAR_CriarCarta( CAR_tppCarta * pCarta )
{
    
    *pCarta = NULL ;
    
    *pCarta = ( CAR_tpCarta * ) malloc( sizeof( CAR_tpCarta )) ;
    if( *pCarta == NULL )
    {
        return CAR_CondRetFaltouMemoria ;
    } /* if */
    
    (*pCarta)->naipe = '0' ;
    (*pCarta)->valor = 0 ;
    
    #ifdef _DEBUG
    
        (*pCarta)->tipo = 'c';
        (*pCarta)->tamBytes = sizeof(CAR_tpCarta);  //struct carta e nao o ponteiro
	   CED_MarcarEspacoAtivo(pCarta);
    
    #endif
    
    return CAR_CondRetOK ;
    
} /* Fim funÁ„o: CAR  Criar carta */

/***************************************************************************
 *
 *  FunÁ„o: CAR  Preencher carta
 *  ****/

CAR_tpCondRet CAR_PreencheCarta ( CAR_tppCarta pCarta , char naipe , int valor )
{
    
    if( pCarta == NULL )
    {
        return CAR_CondRetCartaNaoExiste ;
    } /* if */
    
    if( VerificarNaipe( naipe ) == 0 )
    {
        return CAR_CondRetNaipeNaoExiste ;
    } /* if */
    
    if( VerificarValor( valor ) == 0 )
    {
        return CAR_CondRetValorNaoExiste ;
    } /* if */
    
    pCarta->naipe = naipe ;
    pCarta->valor = valor ;
    
    return CAR_CondRetOK ;
    
} /* Fim funÁ„o: CAR  Preencher carta */

/***************************************************************************
 *
 *  FunÁ„o: CAR  Excluir carta
 *  ****/

CAR_tpCondRet CAR_ExcluirCarta( CAR_tppCarta pCarta )
{
    
    if( pCarta != NULL )
    {
        free( pCarta ) ;
        pCarta = NULL ;
    } /* if */

    #ifdef _DEBUG

        CED_MarcarEspacoNaoAtivo(pCarta);

    #endif
    
    return CAR_CondRetOK ;
    
} /* Fim funÁ„o: CAR  Excluir carta */

/***************************************************************************
 *
 *  FunÁ„o: CAR  Obter naipe da carta
 *  ****/

CAR_tpCondRet CAR_ObterNaipe( CAR_tppCarta pCarta , char * pNaipe )
{
    
    if( pCarta == NULL )
    {
        return CAR_CondRetCartaNaoExiste ;
    } /* if */
    
    if( !VerificarNaipe( pCarta->naipe ) )
    {
        return CAR_CondRetNaipeNaoExiste ;
    } /* if */
    
    *pNaipe = pCarta->naipe ;
    
    return CAR_CondRetOK ;
    
} /* Fim funÁ„o: CAR  Obter naipe da carta */

/***************************************************************************
 *
 *  FunÁ„o: CAR  Obter valor da carta
 *  ****/

CAR_tpCondRet CAR_ObterValor( CAR_tppCarta pCarta , int * pValor )
{
    
    if( pCarta == NULL )
    {
        return CAR_CondRetCartaNaoExiste ;
    } /* if */
    
    if( !VerificarValor( pCarta->valor ) )
    {
        return CAR_CondRetValorNaoExiste ;
    } /* if */
    
    *pValor = pCarta->valor ;
    
    return CAR_CondRetOK ;
    
} /* Fim funÁ„o: CAR  Obter valor da carta */

/***************************************************************************
 *
 *  FunÁ„o: CAR  Imprimir carta
 *  ****/

CAR_tpCondRet CAR_ImprimeCarta( CAR_tppCarta pCarta )
{
    
    if( pCarta == NULL )
    {
        return CAR_CondRetCartaNaoExiste ;
    } /* if */
    
    if( VerificarNaipe( pCarta->naipe ) == 0 )
    {
        return CAR_CondRetNaipeNaoExiste ;
    } /* if */
    
    if( VerificarValor( pCarta->valor ) == 0 )
    {
        return CAR_CondRetValorNaoExiste ;
    } /* if */
    
    printf("%2d%c " , pCarta->valor , pCarta->naipe ) ;
    
    return CAR_CondRetOK ;
    
} /* Fim funÁ„o: CAR  Imprimir carta */




/*****  CÛdigo das funÁ?es encapsuladas no mÛdulo  *****/


/***********************************************************************
 *
 *  $FC FunÁ„o: CAR  -Verificar naipe da carta
 *
 *  $ED DescriÁ„o da funÁ„o
 *    Verifica se o naipe est· de acordo
 *
 ***********************************************************************/

int VerificarNaipe( char naipe )
{
    
    if( naipe == 'o' || naipe == 'e' || naipe == 'p' || naipe == 'c' )
    {
        return 1;
    } /* if */
    
    return 0;
}

/***********************************************************************
 *
 *  $FC FunÁ„o: CAR  -Verificar valor da carta
 *
 *  $ED DescriÁ„o da funÁ„o
 *    Verifica se o valor est· de acordo
 *
 ***********************************************************************/

int VerificarValor( char valor )
{
    
    if( valor >= 1 && valor <= 13 )
    {
        return 1;
    } /* if */
    
    return 0;
}

/********** Fim do mÛdulo de implementaÁ„o: CAR  Carta **********/
