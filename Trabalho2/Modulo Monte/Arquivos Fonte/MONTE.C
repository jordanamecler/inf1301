/***************************************************************************
 *  $MCI Módulo de implementação: MON Monte
 *
 *  Arquivo gerado:              MONTE.c
 *  Letras identificadoras:      MON
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
 *     1.0       EG,JM,LW        17/abr/2015       Início do desenvolvimento
 *
 ***************************************************************************/


#include "PILHA_DE_CARTAS.h"
#include "CARTA.h"
#include <malloc.h>
#include <stdio.h>

#define MONTE_OWN
#include "MONTE.h"
#undef MONTE_OWN


/***********************************************************************
*
*  $TC Tipo de dados: MON Monte Pilha de Carta
*
*
***********************************************************************/

   typedef struct MON_tagMonte
   {
     PIL_tppPilha pPilha; 
     /*Pontei para pilha de cartas*/

   }MON_tpMonte ;
   

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MON  &Criar monte a partir de pilha
*  ****/

   MON_tpCondRet MON_CriarMonte ( MON_tppMonte * pMonte , PIL_tppPilha pPilha)
   {
      PIL_tpCondRet condRet;
      CAR_tppCarta pCartaAux;

      *pMonte = (MON_tpMonte *) malloc(sizeof(MON_tppMonte));
      if( *pMonte == NULL)
      {
        return MON_CondRetFaltouMemoria;
      }

      condRet = PIL_CriarPilhaVazia( &((*pMonte)->pPilha) );
       
      if ( condRet == PIL_CondRetFaltouMemoria )
      {
        return MON_CondRetFaltouMemoria ; 
      }         

      while( PIL_PopCarta( pPilha, &pCartaAux )  == PIL_CondRetOK )
      {
        PIL_PushCarta( (*pMonte)->pPilha, pCartaAux );
      }

      return MON_CondRetOK ;
   }

    /* Fim função: MON  &Criar monte */

/***************************************************************************
*
*  Função: MON  &Destruir monte
*  ****/
   MON_tpCondRet MON_DestruirMonte ( MON_tppMonte pMonte )
   {

      if(pMonte->pPilha == NULL)
      {
        free(pMonte);
        return MON_CondRetOK;
      }

      PIL_DestruirPilha( pMonte->pPilha );
      free(pMonte);

      return MON_CondRetOK ; 
   }

  /* Fim função: MON  &Destruir monte */

/***************************************************************************
*
*  Função: MON  &Pop carta do monte
*  ****/

   MON_tpCondRet MON_PopCartaMonte ( MON_tppMonte pMonte, CAR_tppCarta * pCarta ) 
   {
      PIL_tpCondRet condRet;

      condRet = PIL_PopCarta( pMonte->pPilha, pCarta );

      if (condRet != PIL_CondRetOK)
      {
        return MON_CondRetMonteVazio;
      }

      return MON_CondRetOK ; 
   }
  
   /* Fim função: MON  &Pop carta do monte */

/*************** Fim do módulo de implementação: MON Monte *****************/