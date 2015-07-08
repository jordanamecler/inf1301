/***************************************************************************
*
*  $MCD M�dulo de Implementa��o: BAR  Baralho de Cartas
*
*  Arquivo gerado:              BAR.C
*  Letras identificadoras:      BAR
*
*  Autores: Eric Grinstein,
*           Jordana Mecler,
*	    Leonardo Wajnsztok
*  
***************************************************************************/
 
#include "PILHA_DE_CARTAS.H"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define BARALHO_DE_CARTAS_OWN
#include "BARALHO.H"
#undef BARALHO_DE_CARTAS_OWN


#define PILHAS_AUX_EMBARALHAMENTO 10

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de baralho
*
*
***********************************************************************/

  typedef struct BAR_tagBaralho {

         int numNaipes ;
               /* N�mero de naipes do baralho */

         PIL_tppPilha pPilCartas ;
			/* Ponteiro para pilha com todas as cartas do baralho */

   } BAR_tpBaralho ;


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: BAR Criar Baralho
*****/

   BAR_tpCondRet BAR_CriarBaralho( BAR_tppBaralho * pBaralho )
   {
      
 
      *pBaralho = NULL ;
	
      *pBaralho = ( BAR_tpBaralho * ) malloc( sizeof( BAR_tpBaralho ) ) ;
      if( *pBaralho == NULL )
      {
          return BAR_CondRetFaltouMemoria ;
      } /* if */

      ( * pBaralho )->numNaipes = 0 ;
      ( * pBaralho )->pPilCartas = NULL ;
      
      return BAR_CondRetOK ;

   } /* Fim fun��o: BAR  &Criar Baralho Vazia */

/***************************************************************************
*
*  Fun��o: BAR Destruir Baralho de Cartas 
*****/

   BAR_tpCondRet BAR_DestruirBaralho( BAR_tppBaralho pBaralho )
   {
	
	if ( pBaralho->pPilCartas != NULL )
		 PIL_DestruirPilha( pBaralho->pPilCartas ) ;

	free( pBaralho ) ;
	pBaralho = NULL ;

	return BAR_CondRetOK ; 	

   }/* Fim fun��o: BAR Destruir Baralho de Cartas */


/***************************************************************************
*
*  Fun��o: BAR Preencher Baralho de Cartas 
*****/

   BAR_tpCondRet BAR_PreencherBaralho( BAR_tppBaralho pBaralho , int numNaipes )
   {	
	PIL_tpCondRet PilRet ;
	CAR_tpCondRet CarRet ;

	CAR_tppCarta cartaCriada ;	
	
	char vetNaipes[ 4 ] = { 'c' , 'e' , 'o' , 'p' } ;
					/* Copas, espadas, ouros, paus */
	int auxNaipes,
		 naipeDaVez;

	int auxValor ;

	int cartasFaltando = TAM_BARALHO ;

	if ( numNaipes > 4 || numNaipes < 1 )
	{
		return BAR_CondRetParamIncorreto ;
	}

	pBaralho->numNaipes = numNaipes ;

	PilRet = PIL_CriarPilhaVazia( &( pBaralho->pPilCartas ) ) ;

	if ( PilRet == PIL_CondRetFaltouMemoria )
	{
		return BAR_CondRetFaltouMemoria ;
	}

	auxNaipes = 0;
	while ( cartasFaltando )
	{
		naipeDaVez = ( auxNaipes % numNaipes ) ;
				/* garante que 0 <= naipeDaVez < numNaipes */

		for (auxValor=1 ; auxValor <= VALORES_POSSIVEIS ; auxValor++ )
		{
			
			CarRet = CAR_CriarCarta( &cartaCriada ) ;
			if ( CarRet == CAR_CondRetFaltouMemoria )
			{
				return BAR_CondRetFaltouMemoria ;
			}

			CAR_PreencheCarta( cartaCriada , vetNaipes[naipeDaVez] , auxValor ) ;
			PIL_PushCarta( pBaralho->pPilCartas , cartaCriada ) ;
			cartasFaltando-- ;
		}
		auxNaipes++ ;
	}
	
	
	return BAR_CondRetOK ;

	
   }/* Fim fun��o: BAR Preencher Baralho de Cartas */

/***************************************************************************
*
*  Fun��o: BAR Embaralhar Baralho de Cartas  
*****/

   BAR_tpCondRet BAR_Embaralhar( BAR_tppBaralho pBaralho )
   {
	PIL_tppPilha pilhaAux[ PILHAS_AUX_EMBARALHAMENTO ] ;
	PIL_tpCondRet Ret ;
	int contPilha ;
		
	CAR_tppCarta cartaAux ;

	int numPilhaAleat ;	 

	if ( pBaralho->pPilCartas == NULL )
	{
	     return BAR_CondRetBaralhoVazio ; 
	}
	

	/* Inicializa��o das pilhas auxiliares */
	for (contPilha = 0 ; contPilha < PILHAS_AUX_EMBARALHAMENTO ; contPilha++ )
	{
		Ret = PIL_CriarPilhaVazia( &pilhaAux[contPilha] ) ;
		if ( Ret == PIL_CondRetFaltouMemoria )
		{
			return BAR_CondRetFaltouMemoria ;
		}
	}	

	/* Inicializa��o das pilhas auxiliares */


	/* Distribui��o dos baralhos nas pilhas auxiliares */

	srand( time(NULL) );
		/* usa o tempo atual como 
		   semente para a randomiza��o */

	while ( PIL_PopCarta( pBaralho->pPilCartas , &cartaAux )
			!= PIL_CondRetPilhaVazia )
	{
		numPilhaAleat = rand() % PILHAS_AUX_EMBARALHAMENTO ;
		PIL_PushCarta( pilhaAux[ numPilhaAleat ] , cartaAux ) ;
	}

	/* Distribui��o dos baralhos nas pilhas auxiliares */

	
	/* Reinser��o das cartas no baralho */
	for ( contPilha = 0 ; contPilha < PILHAS_AUX_EMBARALHAMENTO ;
								 contPilha++ )	
	{
		while ( PIL_PopCarta( pilhaAux[ contPilha ] , &cartaAux )
			       != PIL_CondRetPilhaVazia )
		{
			PIL_PushCarta( pBaralho->pPilCartas , cartaAux ) ;
		}
		
		PIL_DestruirPilha( pilhaAux[ contPilha ] ) ;
	}

	/* Fim Reinser��o das cartas no baralho */

	return BAR_CondRetOK ;

   }/* Fim fun��o: BAR Embaralhar Baralho de Cartas */

/***************************************************************************
*
*  Fun��o: BAR PopCarta 
*****/

   BAR_tpCondRet BAR_PopCarta( BAR_tppBaralho pBaralho , CAR_tppCarta * pCarta )
   {
	    if ( pBaralho->pPilCartas == NULL )
	    {
			* pCarta = NULL ;
			return BAR_CondRetBaralhoVazio ; 
	    }

	    if ( PIL_PopCarta( pBaralho->pPilCartas , pCarta )
			 == PIL_CondRetPilhaVazia )
		{
			* pCarta = NULL ;
			return BAR_CondRetBaralhoVazio ;
		}

	    return BAR_CondRetOK ;

   }/* Fim fun��o: BAR Pop Carta */

/********** Fim do m�dulo de implementa��o: BAR  Baralho de cartas  **********/