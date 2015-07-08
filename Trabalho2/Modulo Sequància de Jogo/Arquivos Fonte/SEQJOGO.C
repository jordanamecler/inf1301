/***************************************************************************
 *  $MCI MÃ³dulo de implementaÃ§Ã£o: SEQJ SequÃªncia de Jogo
 *
 *  Arquivo gerado:              SEQJOGO.c
 *  Letras identificadoras:      SEQJ
 *
 *  Nome da base de software:    ArcabouÃ§o para a automaÃ§Ã£o de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - ProgramaÃ§Ã£o Modular
 *  Autores: EG - Eric Grinstein
             JM - Jordana Mecler
             LW - Leonardo Wajnsztok
 *
 *  $HA HistÃ³rico de evoluÃ§Ã£o:
 *     VersÃ£o      Autor            Data                ObservaÃ§Ãµes
 *     1.0       EG,JM,LW        22/abr/2015       InÃ­cio do desenvolvimento
 *
 ***************************************************************************/

#include "PILHA_DE_CARTAS.h"
#include "CARTA.h"
#include <malloc.h>
#include <stdio.h>

#define SEQJOGO_OWN
#include "SEQJOGO.h"
#undef SEQJOGO_OWN


/***********************************************************************
*
*  $TC Tipo de dados: SEQJ SequÃªncia de Jogo
*
*
***********************************************************************/

   typedef struct SEQJ_tagSeqJogo {
    
     PIL_tppPilha pPilha; 
      /*Pontei para pilha de cartas*/
    
     int numCartasViradas ;
      /* NÃºmero de cartas viradas. Cada sequÃªncia irÃ¡ comeÃ§ar com uma carta virada. */
    
} SEQJ_tpSeqJ ;

/***** ProtÃ³tipos das funÃ§Ãµes encapuladas no mÃ³dulo *****/

int totalCartasNaSeq( SEQJ_tppSeqJ pSeqJ );

int ehSequenciaValor( CAR_tppCarta carta1, CAR_tppCarta carta2 ) ;

int ehMesmoNaipe( CAR_tppCarta carta1, CAR_tppCarta carta2 ) ;

/*****  CÃ³digo das funÃ§Ãµes exportadas pelo mÃ³dulo  *****/

/***************************************************************************
*
*  FunÃ§Ã£o: SEQJ &Criar sequÃªncia de jogo a partir de pilha
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

    /* Fim funÃ§Ã£o: SEQJ  &Criar sequÃªnca de jogo a partir de pilha */

/***************************************************************************
*
*  FunÃ§Ã£o: SEQJ  &Destruir sequÃªncia de jogo
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

  /* Fim funÃ§Ã£o: SEQJ  &Destruir sequÃªncia de jogo */


 /***************************************************************************
 * 
 *  FunÃ§Ã£o: SEQJ &Push carta na sequencia
 *****/

   SEQJ_tpCondRet SEQJ_PushCartaSequencia( SEQJ_tppSeqJ pSeqJ, CAR_tppCarta pCarta )
   {
      CAR_tppCarta cartaAux;

      if (pSeqJ == NULL)
      {
        return SEQJ_CondRetSequenciaVazia;
      }

           // se tiverem cartas na seq, verificar se pode colocar

      if( totalCartasNaSeq( pSeqJ ) != 0 )  
      {
        PIL_VerCarta( pSeqJ->pPilha, &cartaAux, 0 ); 

        if ( !ehSequenciaValor( cartaAux, pCarta ))
        {
            return SEQJ_CondRetCartasForaDaSequencia;
        }
      }  

      //senao apenas dar push
	  
      PIL_PushCarta( pSeqJ->pPilha, pCarta);

      pSeqJ->numCartasViradas++;

      return SEQJ_CondRetOK;
   }

/* Fim funÃ§Ã£o: SEQJ &Push carta na sequencia */

/***************************************************************************
 * 
 *  FunÃ§Ã£o: SEQJ &Pop carta na sequencia
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

      pSeqJ->numCartasViradas--;

      return SEQJ_CondRetOK;
   }

/* Fim funÃ§Ã£o: SEQJ &Pop carta na sequencia */

/***************************************************************************
* 
*  FunÃ§Ã£o: SEQJ &Obtem pilha da sequÃªncia de jogo
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
     /* fazer sÃ³ para 13 cartas */

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

/* Fim funÃ§Ã£o: SEQJ &Obtem pilha da sequÃªncia de jogo */

/***************************************************************************
* 
*  FunÃ§Ã£o: SEQJ &Verifica sequÃªncia completa     
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

/* Fim funÃ§Ã£o: SEQJ &Verifica sequÃªncia completa */


  /*****  CÃ³digo das funÃ§Ãµes encapsuladas no mÃ³dulo  *****/

/***********************************************************************
 *
 *  $FC FunÃ§Ã£o: SEQJ  -Total de cartas na sequÃªncia
 *
 *  $ED DescriÃ§Ã£o da funÃ§Ã£o
 *    Dada um sequÃªncia, a funÃ§Ã£o conta o total de cartas em sua pilha.
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
 *  $FC FunÃ§Ã£o: SEQJ  Verifica cartas sequÃªncia relaÃ§Ã£o ao valor
 *
 *  $ED DescriÃ§Ã£o da funÃ§Ã£o
 *    Dadas duas cartas, a funÃ§Ã£o verifica se a primeira Ã© maior e  sequÃªncia da segunda.
 *    Ex: carta1 = 6 de ouro e carta2 = 5 de ouro Ã© sequencia
 *    Ex: carta1 = 6 de ouro e carta2 = 5 de copas Ã© sequencia
 *    Ex: carta1 = 4 de ouro e carta2 = 6 de ouro nÃ£o Ã© sequencia
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
      return 1;   // carta1 Ã© sequencia e maior do que carta2
   }
   return 0;
}

/***********************************************************************
 *
 *  $FC FunÃ§Ã£o: SEQJ  Verifica cartas possuem mesmo naipe
 *
 *  $ED DescriÃ§Ã£o da funÃ§Ã£o
 *    Dadas duas cartas, a funÃ§Ã£o verifica ambas possuem mesmo naipe.
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

/*************** Fim do mÃ³dulo de implementaÃ§Ã£o: SEQJ SequÃªncia de jogo *****************/