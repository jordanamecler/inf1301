/***************************************************************************
 *  $MCI MÃƒÂ³dulo de implementaÃƒÂ§ÃƒÂ£o: SEQJ SequÃƒÂªncia de Jogo
 *
 *  Arquivo gerado:              SEQJOGO.c
 *  Letras identificadoras:      SEQJ
 *
 *  Nome da base de software:    ArcabouÃƒÂ§o para a automaÃƒÂ§ÃƒÂ£o de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - ProgramaÃƒÂ§ÃƒÂ£o Modular
 *  Autores: EG - Eric Grinstein
 JM - Jordana Mecler
 LW - Leonardo Wajnsztok
 *
 *  $HA HistÃƒÂ³rico de evoluÃƒÂ§ÃƒÂ£o:
 *     VersÃƒÂ£o      Autor            Data                ObservaÃƒÂ§ÃƒÂµes
 *     1.0       EG,JM,LW        22/abr/2015       InÃƒÂ­cio do desenvolvimento
 *
 ***************************************************************************/

#include "PILHA_DE_CARTAS.h"
#include "CARTA.h"
#include <stdlib.h>
#include <stdio.h>

#define SEQJOGO_OWN
#include "SEQJOGO.h"
#undef SEQJOGO_OWN


/***********************************************************************
 *
 *  $TC Tipo de dados: SEQJ SequÃƒÂªncia de Jogo
 *
 *
 ***********************************************************************/

typedef struct SEQJ_tagSeqJogo {
    
    PIL_tppPilha pPilha;
    /*Pontei para pilha de cartas*/
    
    int numCartasViradas ;
    /* NÃƒÂºmero de cartas viradas. Cada sequÃƒÂªncia irÃƒÂ¡ comeÃƒÂ§ar com uma carta virada. */
    
} SEQJ_tpSeqJ ;

/***** ProtÃƒÂ³tipos das funÃƒÂ§ÃƒÂµes encapuladas no mÃƒÂ³dulo *****/

int totalCartasNaSeq( SEQJ_tppSeqJ pSeqJ );

int ehSequenciaValor( CAR_tppCarta carta1, CAR_tppCarta carta2 ) ;

int ehMesmoNaipe( CAR_tppCarta carta1, CAR_tppCarta carta2 ) ;

/*****  CÃƒÂ³digo das funÃƒÂ§ÃƒÂµes exportadas pelo mÃƒÂ³dulo  *****/

/***************************************************************************
 *
 *  FunÃƒÂ§ÃƒÂ£o: SEQJ &Criar sequÃƒÂªncia de jogo a partir de pilha
 *  ****/
SEQJ_tpCondRet SEQJ_CriarSeqJogo ( SEQJ_tppSeqJ * pSeqJ, PIL_tppPilha pPilha )
{
    PIL_tpCondRet condRet;
    CAR_tppCarta pCartaAux;
    
    *pSeqJ = (SEQJ_tpSeqJ *)malloc(sizeof(SEQJ_tpSeqJ));
    if( *pSeqJ == NULL)
    {
        return SEQJ_CondRetFaltouMemoria;
    }
    
    (*pSeqJ)->numCartasViradas = 1;
    
    condRet = PIL_CriarPilhaVazia( &((*pSeqJ)->pPilha) );
    
    if( condRet == PIL_CondRetFaltouMemoria )
    {
        return SEQJ_CondRetFaltouMemoria;
    }
    
    while( PIL_PopCarta( pPilha, &pCartaAux) == PIL_CondRetOK)
    {
        PIL_PushCarta((*pSeqJ)->pPilha,pCartaAux);
    }
    
    return SEQJ_CondRetOK;
}

/* Fim funÃƒÂ§ÃƒÂ£o: SEQJ  &Criar sequÃƒÂªnca de jogo a partir de pilha */

/***************************************************************************
 *
 *  FunÃƒÂ§ÃƒÂ£o: SEQJ  &Destruir sequÃƒÂªncia de jogo
 *  ****/

SEQJ_tpCondRet SEQJ_DestroiSequencia ( SEQJ_tppSeqJ pSeqJ )
{
    if(pSeqJ->pPilha != NULL)
    {
        PIL_DestruirPilha(pSeqJ->pPilha);
        
    }
    free(pSeqJ);
    
    return SEQJ_CondRetOK;
}

/* Fim funÃƒÂ§ÃƒÂ£o: SEQJ  &Destruir sequÃƒÂªncia de jogo */


/***************************************************************************
 *
 *  FunÃƒÂ§ÃƒÂ£o: SEQJ &Push carta na sequencia
 *****/

SEQJ_tpCondRet SEQJ_PushCartaSequencia( SEQJ_tppSeqJ pSeqJ, CAR_tppCarta pCarta , int operacao )
{
    CAR_tppCarta cartaAux;
    
    if (pSeqJ == NULL)
    {
        return SEQJ_CondRetSequenciaVazia;
    }
    
    // se tiverem cartas na seq, verificar se pode colocar
    if ( operacao == 1 )
    {
        if( totalCartasNaSeq( pSeqJ ) != 0 )
        {
            PIL_VerCarta( pSeqJ->pPilha, &cartaAux, 0 );
            
            if ( !ehSequenciaValor( cartaAux, pCarta ))
            {
                return SEQJ_CondRetCartasForaDaSequencia;
            }
        }
    }
    
    //senao apenas dar push
    
    PIL_PushCarta( pSeqJ->pPilha, pCarta);
    
    
    //pSeqJ->numCartasViradas++;
    
    return SEQJ_CondRetOK;
}

/* Fim funÃƒÂ§ÃƒÂ£o: SEQJ &Push carta na sequencia */


/***************************************************************************
 *
 *  FunÃƒÂ§ÃƒÂ£o: SEQJ &Pop carta na sequencia
 *****/

SEQJ_tpCondRet SEQJ_PopCartaSequencia( SEQJ_tppSeqJ pSeqJ, CAR_tppCarta * pCarta )
{
    PIL_tpCondRet ret;
    
    if (pSeqJ == NULL)
    {
        return SEQJ_CondRetSequenciaVazia ;
    }
    
    ret = PIL_PopCarta( pSeqJ->pPilha, pCarta);
    if (ret != PIL_CondRetOK)
    {
        return SEQJ_CondRetSequenciaVazia ;
    }

    return SEQJ_CondRetOK;
}

/* Fim funÃƒÂ§ÃƒÂ£o: SEQJ &Pop carta na sequencia */

/***************************************************************************
 *
 *  FunÃƒÂ§ÃƒÂ£o: SEQJ &Obtem pilha da sequÃƒÂªncia de jogo
 *****/

SEQJ_tpCondRet SEQJ_ObtemPilhaSeqJ( SEQJ_tppSeqJ pSeqJ, PIL_tppPilha *pPilha )
{
    PIL_tppPilha pilhaAux;
    CAR_tppCarta cartaAux;
    int i;
    
    if(pSeqJ == NULL || totalCartasNaSeq( pSeqJ ) == 0 )
    {
        return SEQJ_CondRetSequenciaVazia;
    }
    
    if (  pSeqJ->numCartasViradas < 13)
    {
        return SEQJ_CondRetNumCartasIncorreto;
    }
    /* fazer sÃƒÂ³ para 13 cartas */
    
    PIL_CriarPilhaVazia( &pilhaAux );
    for( i = 0 ; i < 13 ; i++ )
    {
        PIL_PopCarta( pSeqJ->pPilha, &cartaAux );
        PIL_PushCarta( pilhaAux, cartaAux );
    }
    
    *pPilha = pilhaAux;
    
    pSeqJ->numCartasViradas -= 13 ;
    
    
    if( pSeqJ->numCartasViradas == 0  && totalCartasNaSeq( pSeqJ ) > 0)
    {
        pSeqJ->numCartasViradas++;
    }
    
    return SEQJ_CondRetOK;
}

/* Fim funÃƒÂ§ÃƒÂ£o: SEQJ &Obtem pilha da sequÃƒÂªncia de jogo */

SEQJ_tpCondRet SEQJ_ViraCarta( SEQJ_tppSeqJ pSeqJ, int numCartas )
{
    pSeqJ->numCartasViradas += numCartas;
    
    return 0;
}

SEQJ_tpCondRet SEQJ_NumCartasViradas( SEQJ_tppSeqJ pSeqJ, int *numCartasViradas )
{
    
    *numCartasViradas = pSeqJ->numCartasViradas;
    
    return 0;
}



/***************************************************************************
 *
 *  FunÃƒÂ§ÃƒÂ£o: SEQJ &Verifica sequÃƒÂªncia completa
 *****/

SEQJ_tpCondRet SEQJ_VerificaSeqCompleta( SEQJ_tppSeqJ pSeqJ )
{
    int i ;
    int seqComecou ;
    int valor ;
    CAR_tppCarta cartaAux;
    CAR_tppCarta cartaAnterior;
    
    seqComecou = 0;
    valor = 0;
    
    if (pSeqJ == NULL)
    {
        return SEQJ_CondRetSequenciaVazia;
    }
    
	if(totalCartasNaSeq( pSeqJ ) == 0)
	{
		return SEQJ_CondRetSequenciaVazia;
	}
    for (i = 0 ; i < 13 ; i++)
    {
        PIL_VerCarta( pSeqJ->pPilha, &cartaAux, i );
        CAR_ObterValor(cartaAux, &valor);
        if( valor != i+1 )
        {
            return SEQJ_CondRetCartasForaDaSequencia;
        }
        
        if( seqComecou )
        {
            if( !ehSequenciaValor(cartaAux, cartaAnterior) || !ehMesmoNaipe(cartaAux, cartaAnterior))
            {
                return SEQJ_CondRetCartasForaDaSequencia;
            }
        }
        cartaAnterior = cartaAux;
        if( !seqComecou ) seqComecou = 1;
    }
    
    return SEQJ_CondRetOK;
}

/* Fim funÃƒÂ§ÃƒÂ£o: SEQJ &Verifica sequÃƒÂªncia completa */


/*****  CÃƒÂ³digo das funÃƒÂ§ÃƒÂµes encapsuladas no mÃƒÂ³dulo  *****/

/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ  -Total de cartas na sequÃƒÂªncia
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *    Dada um sequÃƒÂªncia, a funÃƒÂ§ÃƒÂ£o conta o total de cartas em sua pilha.
 *
 ***********************************************************************/

int totalCartasNaSeq( SEQJ_tppSeqJ pSeqJ )
{
    CAR_tppCarta cartaAux ;
    int numCartasSeq = 0 ;
    
    while( PIL_VerCarta( pSeqJ->pPilha, &cartaAux, numCartasSeq ) == PIL_CondRetOK )
    {
        numCartasSeq++;
    }
    
    return numCartasSeq ;
}

/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ  Verifica cartas sequÃƒÂªncia relaÃƒÂ§ÃƒÂ£o ao valor
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *    Dadas duas cartas, a funÃƒÂ§ÃƒÂ£o verifica se a primeira ÃƒÂ© maior e  sequÃƒÂªncia da segunda.
 *    Ex: carta1 = 6 de ouro e carta2 = 5 de ouro ÃƒÂ© sequencia
 *    Ex: carta1 = 6 de ouro e carta2 = 5 de copas ÃƒÂ© sequencia
 *    Ex: carta1 = 4 de ouro e carta2 = 6 de ouro nÃƒÂ£o ÃƒÂ© sequencia
 *
 ***********************************************************************/

int ehSequenciaValor( CAR_tppCarta carta1, CAR_tppCarta carta2 )
{
    int valor1 = 0 ;
    int valor2 = 0 ;
    
    CAR_ObterValor(carta1, &valor1);
    CAR_ObterValor(carta2, &valor2);
    
    if( valor1 -1  == valor2 )
    {
        return 1;   // carta1 ÃƒÂ© sequencia e maior do que carta2
    }
    return 0;
}

/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ  Verifica cartas possuem mesmo naipe
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *    Dadas duas cartas, a funÃƒÂ§ÃƒÂ£o verifica ambas possuem mesmo naipe.
 *
 ***********************************************************************/

int ehMesmoNaipe( CAR_tppCarta carta1, CAR_tppCarta carta2 )
{
    char naipe1 = '?' ;
    char naipe2 = '!' ;
    
    CAR_ObterNaipe(carta1, &naipe1);
    CAR_ObterNaipe(carta2, &naipe2);
    
    if( naipe1 == naipe2 )
    {
        return 1;
    }
    return 0;
}

/*************** Fim do mÃƒÂ³dulo de implementaÃƒÂ§ÃƒÂ£o: SEQJ SequÃƒÂªncia de jogo *****************/
