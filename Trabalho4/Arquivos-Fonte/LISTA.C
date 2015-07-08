/***************************************************************************
*  $MCI Módulo de implementação: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*           EG
*           JM
*           LW
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     5    EG,JM,LW 27/abr/2015 todas as funções de acesso retornam condição de retorno.
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <stdlib.h>
#include   <assert.h>

#define LISTA_OWN
#include "LISTA.h"
#undef LISTA_OWN

#ifdef _DEBUG
#include "CESPDIN.h"
#endif


/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

   struct tagElemLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento */

         struct tagElemLista * pAnt ;
               /* Ponteiro para o elemento predecessor */

         struct tagElemLista * pProx ;
               /* Ponteiro para o elemento sucessor */

   };
#ifndef _DEBUG
   typedef struct tagElemLista tpElemLista ; 
#endif

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabeça de lista
*
*
***********************************************************************/

   typedef struct LIS_tagLista {

         tpElemLista * pOrigemLista ;
               /* Ponteiro para a origem da lista */

         tpElemLista * pFimLista ;
               /* Ponteiro para o final da lista */

         tpElemLista * pElemCorr ;
               /* Ponteiro para o elemento corrente da lista */

         int numElem ;
               /* Numero de elementos da lista */

         void ( * ExcluirValor ) ( void * pValor ) ;
               /* Ponteiro para a função de destruição do valor contido em um elemento */

   }LIS_tpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarElemento( LIS_tppLista   pLista ,
                                tpElemLista  * pElem   ) ;

   static tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                       void *       pValor  ) ;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LIS  &Criar lista
*  ****/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista *pLista ,
             void   ( * ExcluirValor ) ( void * pDado ) )
   {

      if( * pLista != NULL )
      {
          LIS_DestruirLista( *pLista ) ;
      }

      *pLista = ( LIS_tpLista * ) malloc( sizeof( LIS_tpLista )) ;
      if ( *pLista == NULL )
      {
         return LIS_CondRetFaltouMemoria ;
      } /* if */

        #ifdef _DEBUG
        
          CED_MarcarEspacoAtivo(pLista);

        #endif
       (*pLista)->pOrigemLista = NULL ;
       (*pLista)->pFimLista = NULL ;
       (*pLista)->pElemCorr = NULL ;
       (*pLista)->numElem   = 0 ;

      (*pLista)->ExcluirValor = ExcluirValor ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Criar lista */

/***************************************************************************
*
*  Função: LIS  &Destruir lista
*  ****/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
       
       if( pLista != NULL )
       {
           LIS_tpCondRet CondRet ;
           
           CondRet = LIS_EsvaziarLista( pLista ) ;
           if( CondRet != LIS_CondRetOK )
           {
               return CondRet ;
           } /* if */

       } /* if */
       
       free( pLista ) ;

        #ifdef _DEBUG
        
          CED_MarcarEspacoNaoAtivo(pLista);

        #endif
       
       pLista = NULL ;
       
       return LIS_CondRetOK ;

   } /* Fim função: LIS  &Destruir lista */

/***************************************************************************
*
*  Função: LIS  &Esvaziar lista
*  ****/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;
      tpElemLista * pProx ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
       
       if( pLista == NULL )
       {
           return LIS_CondRetListaNaoExiste ;
       } /* if */

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarElemento( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

       pLista->pOrigemLista = NULL ;
       pLista->pFimLista = NULL ;
       pLista->pElemCorr = NULL ;
       pLista->numElem   = 0 ;
       
       return LIS_CondRetOK ;

   } /* Fim função: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento antes
*  ****/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pAnt != NULL )
            {
               pElem->pAnt  = pLista->pElemCorr->pAnt ;
               pLista->pElemCorr->pAnt->pProx = pElem ;
            } else
            {
               pLista->pOrigemLista = pElem ;
            } /* if */

            pElem->pProx = pLista->pElemCorr ;
            pLista->pElemCorr->pAnt = pElem ;
         } /* if */

         pLista->pElemCorr = pElem ;

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Função: LIS  &Inserir elemento após
*  ****/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
      
   {

      tpElemLista * pElem ;

      /* Criar elemento a inerir apÛs */

         pElem = CriarElemento( pLista , pValor ) ;
         if ( pElem == NULL )
         {
            return LIS_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento apÛs o elemento */

         if ( pLista->pElemCorr == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
            if ( pLista->pElemCorr->pProx != NULL )
            {
               pElem->pProx  = pLista->pElemCorr->pProx ;
               pLista->pElemCorr->pProx->pAnt = pElem ;
            } else
            {
               pLista->pFimLista = pElem ;
            } /* if */

            pElem->pAnt = pLista->pElemCorr ;
            pLista->pElemCorr->pProx = pElem ;

         } /* if */
                  
         pLista->pElemCorr = pElem ;
                  
         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Inserir elemento após */

/***************************************************************************
*
*  Função: LIS  &Excluir elemento
*  ****/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      pElem = pLista->pElemCorr ;

      /* Desencadeia à esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pElemCorr    = pElem->pAnt ;
         } else {
            pLista->pElemCorr    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pElemCorr ;
         } /* if */

      /* Desencadeia à direita */

         if ( pElem->pProx != NULL )
         {
            pElem->pProx->pAnt = pElem->pAnt ;
         } else
         {
            pLista->pFimLista = pElem->pAnt ;
         } /* if */

      LiberarElemento( pLista , pElem ) ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Excluir elemento */

/***************************************************************************
*
*  Função: LIS  &Obter referência para o valor contido no elemento
*  ****/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista , void ** pValor )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
       
       if ( pLista == NULL )
       {
           return LIS_CondRetListaNaoExiste ;
       } /* if */

	   if ( pLista->pElemCorr == NULL )
      {
        *pValor = NULL ;
          return LIS_CondRetListaVazia ;
      } /* if */
       
       *pValor = pLista->pElemCorr->pValor ;

      return LIS_CondRetOK ;

   } /* Fim função: LIS  &Obter referência para o valor contido no elemento */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento inicial
*  ****/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista )
   {

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif
       
       if( pLista == NULL )
       {
           return LIS_CondRetListaNaoExiste ;
       } /* if */
       
       if( pLista->pElemCorr == NULL )
       {
           return LIS_CondRetListaVazia ;
       }

      pLista->pElemCorr = pLista->pOrigemLista ;
       
       return LIS_CondRetOK ;

   } /* Fim função: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Função: LIS  &Ir para o elemento final
*  ****/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista )
   {
       
       if( pLista == NULL )
       {
           return LIS_CondRetListaNaoExiste ;
       } /* if */
       
       if( pLista->pElemCorr == NULL )
       {
           return LIS_CondRetListaVazia ;
       } /* if */

      pLista->pElemCorr = pLista->pFimLista ;
       
       return LIS_CondRetOK ;

   } /* Fim função: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Função: LIS  &Avançar elemento
*  ****/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem )
   {

      int i ;

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista != NULL ) ;
      #endif

      /* Tratar lista vazia */

         if ( pLista->pElemCorr == NULL )
         {

            return LIS_CondRetListaVazia ;

         } /* fim ativa: Tratar lista vazia */

      /* Tratar avançar para frente */

         if ( numElem > 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i > 0 ; i-- )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pProx ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pFimLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para frente */

      /* Tratar avançar para trás */

         else if ( numElem < 0 )
         {

            pElem = pLista->pElemCorr ;
            for( i = numElem ; i < 0 ; i++ )
            {
               if ( pElem == NULL )
               {
                  break ;
               } /* if */
               pElem    = pElem->pAnt ;
            } /* for */

            if ( pElem != NULL )
            {
               pLista->pElemCorr = pElem ;
               return LIS_CondRetOK ;
            } /* if */

            pLista->pElemCorr = pLista->pOrigemLista ;
            return LIS_CondRetFimLista ;

         } /* fim ativa: Tratar avançar para trás */

      /* Tratar não avançar */

         return LIS_CondRetOK ;

   } /* Fim função: LIS  &Avançar elemento */

/***************************************************************************
*
*  Função: LIS  &Procurar elemento contendo valor
*  ****/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        )
   {

      tpElemLista * pElem ;

      #ifdef _DEBUG
         assert( pLista  != NULL ) ;
      #endif

      if ( pLista->pElemCorr == NULL )
      {
         return LIS_CondRetListaVazia ;
      } /* if */

      for ( pElem  = pLista->pElemCorr ;
            pElem != NULL ;
            pElem  = pElem->pProx )
      {
         if ( pElem->pValor == pValor )
         {
            pLista->pElemCorr = pElem ;
            return LIS_CondRetOK ;
         } /* if */
      } /* for */

      return LIS_CondRetNaoAchou ;

   } /* Fim função: LIS  &Procurar elemento contendo valor */

#ifdef _DEBUG
   tpElemLista * LIS_RetornaSucessor( LIS_tppLista pLista )
   {
	   return pLista->pElemCorr->pProx;
   }

   tpElemLista * LIS_RetornaAntecessor( LIS_tppLista pLista )
   {
	   return pLista->pElemCorr->pAnt;
   }

   CAR_tppCarta LIS_RetornaCartaCorrente( LIS_tppLista pLista )
   {
	   return (CAR_tppCarta)pLista->pElemCorr->pValor;
   }

   tpElemLista * LIS_RetornaCorrente( LIS_tppLista pLista  )
   {
	   return (CAR_tppCarta)pLista->pElemCorr;
   }

   char LIS_RetornaTipoCarta( LIS_tppLista pLista )
   {
	   return CAR_ObterTipo((CAR_tppCarta)pLista->pElemCorr->pValor);
   }
   int LIS_VerificaCorrenteNull( LIS_tppLista pLista)
   {
	   if ( pLista->pElemCorr == NULL )
		   return 1;
	   return 0;
   }
   int LIS_QtdNos(LIS_tppLista pLista)
   {
	   return pLista->numElem;
   }
   int LIS_OrigemNula(LIS_tppLista pLista)
   {
	   if (pLista->pOrigemLista == NULL)
		   return 1;
	   return 0;
   }
   

   void LIS_LiberaElemCorr( LIS_tppLista pLista )
   {
	//free( pLista->pElemCorr ) ;
	pLista->pElemCorr = 'x';
   }
   void LIS_AlteraSucessor( LIS_tppLista pLista )
   {
	pLista->pElemCorr->pProx = NULL ;
   }
   void LIS_AlteraPredecessor( LIS_tppLista pLista )
   {
	pLista->pElemCorr->pAnt = NULL ;
   }
   void LIS_AtribuiLixoSucessor( LIS_tppLista pLista )
   {
	//free( pLista->pElemCorr->pProx ) ;
	   pLista->pElemCorr->pProx = 'x';
   }
   void LIS_AtribuiLixoPredecessor( LIS_tppLista pLista )
   {
		//free( pLista->pElemCorr->pAnt ) ;
		pLista->pElemCorr->pAnt = 'x';
   }
   void LIS_AtribuiNULLCarta( LIS_tppLista pLista )
   {
		pLista->pElemCorr->pValor = NULL ;
   }
   void LIS_AlteraTipoCarta( LIS_tppLista pLista )
   {
	   AlteraTipoCarta((CAR_tppCarta)pLista->pElemCorr->pValor, 'x');
   }
   void LIS_DestacaCarta( LIS_tppLista pLista )
   {
		pLista->numElem--;
		pLista->pElemCorr->pAnt->pProx = pLista->pElemCorr->pProx ;
		pLista->pElemCorr->pProx->pAnt = pLista->pElemCorr->pAnt ;
   }
   void LIS_AtribuiNULLCorrente( LIS_tppLista pLista )
   {
	   //FALTANDO
		pLista->pElemCorr = NULL ;
   }
   void LIS_AtribuiNULLOrigem( LIS_tppLista pLista )
   {
		pLista->pOrigemLista = NULL ;
   }

#endif

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LIS  -Liberar elemento da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

   void LiberarElemento( LIS_tppLista   pLista ,
                         tpElemLista  * pElem   )
   {

      if ( ( pLista->ExcluirValor != NULL )
        && ( pElem->pValor != NULL        ))
      {
         pLista->ExcluirValor( pElem->pValor ) ;
      } /* if */

      free( pElem ) ;

       #ifdef _DEBUG
        
          CED_MarcarEspacoAtivo(pElem);

        #endif

      pLista->numElem-- ;

   } /* Fim função: LIS  -Liberar elemento da lista */


/***********************************************************************
*
*  $FC Função: LIS  -Criar o elemento
*
***********************************************************************/

   tpElemLista * CriarElemento( LIS_tppLista pLista ,
                                void *       pValor  )
   {

      tpElemLista * pElem ;

      pElem = ( tpElemLista * ) malloc( sizeof( tpElemLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

          #ifdef _DEBUG
        
          CED_MarcarEspacoAtivo(pValor);

        #endif

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElem ++ ;

      return pElem ;

   } /* Fim função: LIS  -Criar o elemento */


/********** Fim do módulo de implementação: LIS  Lista duplamente encadeada **********/
