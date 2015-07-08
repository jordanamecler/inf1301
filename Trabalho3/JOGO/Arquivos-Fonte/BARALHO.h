#if ! defined( BARALHO_DE_CARTAS_ )
#define BARALHO_DE_CARTAS_
/***************************************************************************
*
*  $MCD Módulo de definição: BAR  Baralho de Cartas
*
*  Arquivo gerado:              BAR.H
*  Letras identificadoras:      BAR
*
*  Autores: Eric Grinstein,
*           Jordana Mecler,
*	    Leonardo Wajnsztok
*
*
*  $ED Descrição do módulo
*     Cria um baralho de 104 cartas com número de naipes 
*     podendo variar de 1 a 4. Cada carta possui também um valor, 
*     que varia de 1 (Ás) a 13 (Rei)
*     
***************************************************************************/
 
#if defined( BARALHO_DE_CARTAS_OWN )
   #define BARALHO_DE_CARTAS_EXT
#else
   #define BARALHO_DE_CARTAS_EXT extern
#endif

#include "CARTA.h"

/***** Definições exportadas pelo módulo *****/

#define TAM_BARALHO 104
#define VALORES_POSSIVEIS 13
	/* A=1, 2=2 ... K=13 */

/* Tipo referência para um baralho de cartas */

typedef struct BAR_tagBaralho * BAR_tppBaralho ;

/***********************************************************************
*
*  $TC Tipo de dados: BAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         BAR_CondRetOK ,
               /* Concluiu corretamente */

         BAR_CondRetBaralhoVazio ,
               /* O baralho não foi preenchido */

		 BAR_CondRetParamIncorreto ,
               /* Número de naipes incorretos  */

         BAR_CondRetFaltouMemoria
               /* Faltou memória ao criar baralho */

   } BAR_tpCondRet ;


/***********************************************************************
*
*  $FC Função: BAR Criar Baralho de Cartas
*
*  $ED Descrição da função
*     Cria um baralho de cartas de baralho vazio
*
*  $EP Parâmetros
*	pBaralho - Endereço que receberá um ponteiro para o baralho criado 
*	
*  $FV Valor retornado
*	BAR_CondRetOK - Criou sem problemas
*	BAR_CondRetFaltouMemoria - Faltou memória na criação do baralho
*
*  $AE Assertivas de Entrada - Nenhuma
*
*  $AS Assertivas de Saída - Caso falte memória (A função retorna BAR_CondRetFaltouMemoria),
*							 pBaralho = NULL
*                            Caso contrário (A função retorna BAR_CondRetOK)
*                            um baralho de 0 naipes e uma pilha de cartas nula é criado.
*
***********************************************************************/

    BAR_tpCondRet BAR_CriarBaralho( BAR_tppBaralho * pBaralho ) ;

/***********************************************************************
*
*  $FC Função: BAR Destruir baralho
*
*  $ED Descrição da função
*	Destrói baralho de cartas
*
*  $EP Parâmetros
*     pBaralho de Cartas - ponteiro para o baralho a ser destruído
*
*  $FV Valor retornado
*     BAR_CondRetOK    - destruiu sem problemas
*
*  $AE Assertivas de Entrada - pBaralho != NULL
*
*  $AS Assertivas de Saída - pBaralho = NULL
*
***********************************************************************/

   BAR_tpCondRet BAR_DestruirBaralho( BAR_tppBaralho pBaralho ) ;


/***********************************************************************
*
*  $FC Função: BAR Preencher Baralho de Cartas
*
*  $ED Descrição da função
*      Preenche baralho de cartas homogêneamente com
*      os naipes fornecidos na criação do baralho.
*
*  $EP Parâmetros
*     pBaralho - ponteiro para o baralho a ser preenchido
*     numNaipes - número de naipes que terá o baralho
*
*  $FV Valor retornado
*     BAR_CondRetOK    - preencheu sem problemas
*	  BAR_CondRetParamIncorreto - Número de naipes diferente de [1,4]
*     BAR_CondRetFaltouMemória - Faltou memória no 
*				 preenchimento do baralho
*
*  $AE Assertivas de Entrada - pBaralho é um baralho vazio, isto é,
*							   com 0 naipes e uma pilha de cartas vazia.
*
*  $AS Assertivas de Saída - Se condRet == OK
*                            Baralho com numNaipes e pilha de cartas de
*                            tamanho TAM_BARALHO é criada. O número de 
*                            cartas de cada naipe é TAM_BARALHO/numNaipes
*
*							 Se condRet == paramIncorreto:
*							 Baralho continua com 0 naipes e pilha de cartas nula.
*
*							 Se condRet == FaltouMemória:
*	                         Baralho possui naipes = numNaipes. A pilha de cartas pode
*							 ser nula, vazia ou ter de 1 a TAM_BARALHO - 1 cartas.
*                            nada se pode dizer sobre a distribuição dos naipes.
*
*
***********************************************************************/

      BAR_tpCondRet BAR_PreencherBaralho( BAR_tppBaralho pBaralho , int numNaipes ) ;


/***********************************************************************
*
*  $FC Função: BAR Pop Carta
*
*  $ED Descrição da função
*     Remove carta do topo do baralho
*     
*
*  $EP Parâmetros
*     pBaralho de Cartas - ponteiro para o baralho onde o topo deve ser removido
*     pCarta - endereço que receberá a carta removida.
*              
*
*  $FV Valor retornado
*     BAR_CondRetOK
*     BAR_CondRetBaralhoVazio
*
*  $AE Assertivas de Entrada - pBaralho != NULL
*
*  $AS Assertivas de Saída - Se condRet == BaralhoVazio:
*							 *pCarta = NULL
*
*                            Caso contrário (A função retorna BAR_CondRetOK)
*                            *pCarta é uma carta de baralho válida (naipe
*							 válido e valor válido)
*
***********************************************************************/

      BAR_tpCondRet BAR_PopCarta( BAR_tppBaralho pBaralho , CAR_tppCarta * pCarta );

/***********************************************************************
*
*  $FC Função: BAR Embaralhar
*
*  $ED Descrição da função
*      Randomiza a posição das cartas no baralho. Para a randomização,
*      as cartas são separadas aleatoriamente em 5 pilhas e depois juntas.
*      
*
*  $EP Parâmetros
*     pBaralho de Cartas - ponteiro para o baralho a ser embaralhado
*
*  $FV Valor retornado
*     BAR_CondRetOK
*     BAR_CondRetBaralhoVazio
*     BAR_CondRetFaltouMemoria - Faltou memória durante o embaralhamento
*
*  $AE Assertivas de Entrada - pBaralho != NULL
*
*  $AS Assertivas de Saída - Se condRet == BaralhoVazio:
*							 Baralho continua da mesma forma em que estava
*							 antes da chamada da função
*
*							 Se condRet == Faltou Memória:
*							 Nada se pode dizer; o baralho pode com menos cartas
*							 do que antes da chamada da função
*
*                            Se condRet == OK:
*							 O novo baralho possui uma ordem diferente 
*							 em sua pilha de cartas de antes da chamada da 
*							 função.
*
*
***********************************************************************/

     BAR_tpCondRet BAR_Embaralhar( BAR_tppBaralho pBaralho );

#undef BARALHO_DE_CARTAS_EXT

/********** Fim do módulo de definição: BAR Baralho de Cartas  **********/

#else
#endif