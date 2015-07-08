/***************************************************************************
 *  $MCI Módulo de implementação: CAR  Carta
 *
 *  Arquivo gerado:              CARTA.c
 *  Letras identificadoras:      CAR
 *
 *  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - Programação Modular
 *  Autores: EG - Eric Grinstein
 JM - Jordana Mecler
 LW - Leonardo Wajnsztok
 *
 *  $HA Histórico de evolução:
 *     Versão      Autor            Data                Observações
 *     1.0       EG,JM,LW        17/abr/2015       Correção de condições de retorno
 *     1.0       EG,JM,LW        16/abr/2015       início do desenvolvimento
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define CARTA_OWN
#include "CARTA.h"
#undef CARTA_OWN

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
    
} CAR_tpCarta ;

/***** Protótipos das funções encapuladas no módulo *****/

int VerificarNaipe( char naipe ) ;

int VerificarValor( char valor ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: CAR  Criar carta
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
    
    return CAR_CondRetOK ;
    
} /* Fim função: CAR  Criar carta */

/***************************************************************************
 *
 *  Função: CAR  Preencher carta
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
    
} /* Fim função: CAR  Preencher carta */

/***************************************************************************
 *
 *  Função: CAR  Excluir carta
 *  ****/

CAR_tpCondRet CAR_ExcluirCarta( CAR_tppCarta pCarta )
{
    
    if( pCarta != NULL )
    {
        free( pCarta ) ;
        pCarta = NULL ;
    } /* if */
    
    return CAR_CondRetOK ;
    
} /* Fim função: CAR  Excluir carta */

/***************************************************************************
 *
 *  Função: CAR  Obter naipe da carta
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
    
} /* Fim função: CAR  Obter naipe da carta */

/***************************************************************************
 *
 *  Função: CAR  Obter valor da carta
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
    
} /* Fim função: CAR  Obter valor da carta */

/***************************************************************************
 *
 *  Função: CAR  Imprimir carta
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
    
} /* Fim função: CAR  Imprimir carta */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
 *
 *  $FC Função: CAR  -Verificar naipe da carta
 *
 *  $ED Descrição da função
 *    Verifica se o naipe está de acordo
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
 *  $FC Função: CAR  -Verificar valor da carta
 *
 *  $ED Descrição da função
 *    Verifica se o valor está de acordo
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

/********** Fim do módulo de implementação: CAR  Carta **********/