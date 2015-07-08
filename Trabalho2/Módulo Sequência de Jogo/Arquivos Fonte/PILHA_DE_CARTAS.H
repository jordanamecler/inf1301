#if ! defined( PILHA_DE_CARTAS_ )
#define PILHA_DE_CARTAS_
/***************************************************************************
*
*  $MCD Módulo de definição: PIL  Pilha de Cartas
*
*  Arquivo gerado:              PIL.H
*  Letras identificadoras:      PIL
*
*  Autores: Eric Grinstein,
*           Jordana Mecler,
*	    Leonardo Wajnsztok
*
*
*  $ED Descrição do módulo
*     Cria pilha homogênea armazenadora de tipo cartas de baralho.
*     O módulo permite a criação de múltiplas pilhas.
*   
***************************************************************************/
 
#if defined( PILHA_DE_CARTAS_OWN )
   #define PILHA_DE_CARTAS_EXT
#else
   #define PILHA_DE_CARTAS_EXT extern
#endif

#include "CARTA.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma pilha de cartas */

typedef struct PIL_tagPilha * PIL_tppPilha ;

/***********************************************************************
*
*  $TC Tipo de dados: PIL Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         PIL_CondRetOK = 0,
               /* Concluiu corretamente */

         PIL_CondRetPilhaVazia = 1 ,
               /* A pilha não contém elementos */

		 PIL_CondRetParamIncorreto = 2,
               /* Parâmetro incorreto ao tentar ver carta na pilha */
	
         PIL_CondRetFimPilha = 3,
	       /* Fim da pilha atingido ao tentar ver carta */

         PIL_CondRetFaltouMemoria = 4
               /* Faltou memória ao tentar inserir na pilha */

   } PIL_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PIL Criar Pilha de Cartas Vazia
*
*  $ED Descrição da função
*     Cria uma pilha de cartas de baralho vazia
*
*  $EP Parâmetros
*	pPilha - Endereço que receberá um ponteiro para a pilha criada. 
*	
*  $FV Valor retornado
*	PIL_CondRetOK - Criou sem problemas
*	PIL_CondRetFaltouMemoria - Faltou memória na criação da pilha
*
*  $AE Assertivas de Entrada - nenhuma
*
*  $AS Assertivas de Saída - Se condRet == OK:
*							 ponteiro para pilha vazia é criada em *pPilha
*		
*							 CondRet == FaltouMemória:
*							 * pPilha = NULL
***********************************************************************/

    PIL_tpCondRet PIL_CriarPilhaVazia( PIL_tppPilha * pPilha ) ;

/***********************************************************************
*
*  $FC Função: PIL Destruir pilha
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a pilha resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*     pPilha de Cartas - ponteiro para a pilha a ser destruída
*
*  $FV Valor retornado
*     PIL_CondRetOK    - destruiu sem problemas
*
*  $AE Assertivas de Entrada - pPilha != NULL
*
*  $AS Assertivas de Saída - pPilha = NULL
***********************************************************************/

   PIL_tpCondRet PIL_DestruirPilha( PIL_tppPilha pPilha );


/***********************************************************************
*
*  $FC Função: PIL Push Carta
*
*  $ED Descrição da função
*      Insere carta no topo da pilha de cartas
*
*  $EP Parâmetros
*     pPilha de Cartas - ponteiro para a pilha onde a carta será inserida
*     pCarta - Carta a ser inserida no topo da pilha
*
*  $FV Valor retornado
*     PIL_CondRetOK    - inseriu sem problemas
*	  PIL_CondRetFaltouMemoria
*
*  $AE Assertivas de Entrada - pCarta é uma carta válida
*							   pPilha é uma pilha válida
*							   (pode ser vazia)
*
*  $AS Assertivas de Saída - se CondRet == OK
*							 pCarta é inserido no topo da pilha
*
*							 se CondRet == Faltou Memória
*							 pCarta não é inserido. Pilha continua
*							 no estado que estava.
*
***********************************************************************/

      PIL_tpCondRet PIL_PushCarta( PIL_tppPilha pPilha , CAR_tppCarta pCarta );


/***********************************************************************
*
*  $FC Função: PIL Pop Carta
*
*  $ED Descrição da função
*     Remove carta do topo da pilha
*     
*
*  $EP Parâmetros
*     pPilha de Cartas - ponteiro para a pilha onde o topo deve ser removido
*     pCarta - endereço que receberá a carta removida.
*              
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetPilhaVazia
*
*  $AE Assertivas de Entrada - pPilha é uma pilha válida (pode ser vazia)
*
*  $AS Assertivas de Saída - Se condRet == OK:
*							 carta é removida do topo da pilha e colocada em
*							 *pCarta.
*		
*							 Se condRet == PilhaVazia
*							 *pCarta = NULL
*
***********************************************************************/

      PIL_tpCondRet PIL_PopCarta( PIL_tppPilha pPilha , CAR_tppCarta * pCarta );

/***********************************************************************
*
*  $FC Função: PIL  VerCarta
*
*  $ED Descrição da função
*      Permite ver uma carta da pilha, mesmo que não o topo;
*      Essa função não destrói a carta vista.
*
*  $EP Parâmetros
*     pPilha de Cartas - ponteiro para a pilha onde será vista a carta
*     pCarta - ponteiro que guardará o endereço da carta a ser vista.
*     posicao - distância do topo da pilha à carta a ser vista.
*
*  $FV Valor retornado
*     PIL_CondRetOK
*     PIL_CondRetPilhaVazia
*     PIL_CondRetParamIncorreto - posicao é um valor negativo
*     PIL_CondRetFimPilha - a carta a ser vista está além do tamanho da pilha
*
*  $AE Assertivas de Entrada - pPilha é uma pilha válida (pode ser vazia)
*
*  $AS Assertivas de Saída - Se condRet == OK:
*							 pCarta recebe ponteiro para carta da posição 'posição' da 
*							 pPilha. A carta continua na pilha.
*		
*							 Caso contrário:
*							 * pCarta = NULL
***********************************************************************/

     PIL_tpCondRet PIL_VerCarta( PIL_tppPilha pPilha , CAR_tppCarta * pCarta , int posicao );

#undef PILHA_DE_CARTAS_EXT

/********** Fim do módulo de definição: PIL Pilha de Cartas  **********/

#else
#endif