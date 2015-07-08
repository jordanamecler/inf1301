#if ! defined( PILHA_DE_CARTAS_ )
#define PILHA_DE_CARTAS_
/***************************************************************************
 *
 *  $MCD MÃƒÂ³dulo de definiÃƒÂ§ÃƒÂ£o: PIL  Pilha de Cartas
 *
 *  Arquivo gerado:              PIL.H
 *  Letras identificadoras:      PIL
 *
 *  Autores: Eric Grinstein,
 *           Jordana Mecler,
 *	    Leonardo Wajnsztok
 *
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o do mÃƒÂ³dulo
 *     Cria pilha homogÃƒÂªnea armazenadora de tipo cartas de baralho.
 *     O mÃƒÂ³dulo permite a criaÃƒÂ§ÃƒÂ£o de mÃƒÂºltiplas pilhas.
 *
 ***************************************************************************/

#if defined( PILHA_DE_CARTAS_OWN )
#define PILHA_DE_CARTAS_EXT
#else
#define PILHA_DE_CARTAS_EXT extern
#endif

#include "CARTA.h"

/***** DeclaraÃƒÂ§ÃƒÂµes exportadas pelo mÃƒÂ³dulo *****/

/* Tipo referÃƒÂªncia para uma pilha de cartas */

typedef struct PIL_tagPilha * PIL_tppPilha ;

/***********************************************************************
 *
 *  $TC Tipo de dados: PIL CondiÃƒÂ§ÃƒÂµes de retorno
 *
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o do tipo
 *     CondiÃƒÂ§ÃƒÂµes de retorno das funÃƒÂ§ÃƒÂµes da lista
 *
 ***********************************************************************/

typedef enum {
    
    PIL_CondRetOK = 0,
    /* Concluiu corretamente */
    
    PIL_CondRetPilhaVazia = 1 ,
    /* A pilha nÃƒÂ£o contÃƒÂ©m elementos */
    
    PIL_CondRetParamIncorreto = 2,
    /* ParÃƒÂ¢metro incorreto ao tentar ver carta na pilha */
    
    PIL_CondRetFimPilha = 3,
    /* Fim da pilha atingido ao tentar ver carta */
    
    PIL_CondRetFaltouMemoria = 4
    /* Faltou memÃƒÂ³ria ao tentar inserir na pilha */
    
} PIL_tpCondRet ;


/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: PIL Criar Pilha de Cartas Vazia
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *     Cria uma pilha de cartas de baralho vazia
 *
 *  $EP ParÃƒÂ¢metros
 *	pPilha - EndereÃƒÂ§o que receberÃƒÂ¡ um ponteiro para a pilha criada.
 *
 *  $FV Valor retornado
 *	PIL_CondRetOK - Criou sem problemas
 *	PIL_CondRetFaltouMemoria - Faltou memÃƒÂ³ria na criaÃƒÂ§ÃƒÂ£o da pilha
 *
 *  $AE Assertivas de Entrada - nenhuma
 *
 *  $AS Assertivas de SaÃƒÂ­da - Se condRet == OK:
 *							 ponteiro para pilha vazia ÃƒÂ© criada em *pPilha
 *
 *							 CondRet == FaltouMemÃƒÂ³ria:
 *							 * pPilha = NULL
 ***********************************************************************/

PIL_tpCondRet PIL_CriarPilhaVazia( PIL_tppPilha * pPilha ) ;

/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: PIL Destruir pilha
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *     DestrÃƒÂ³i a lista fornecida.
 *     O parÃƒÂ¢metro ponteiro para a lista nÃƒÂ£o ÃƒÂ© modificado.
 *     Se ocorrer algum erro durante a destruiÃƒÂ§ÃƒÂ£o, a pilha resultarÃƒÂ¡
 *     estruturalmente incorreta.
 *     OBS. nÃƒÂ£o existe previsÃƒÂ£o para possÃƒÂ­veis falhas de execuÃƒÂ§ÃƒÂ£o.
 *
 *  $EP ParÃƒÂ¢metros
 *     pPilha de Cartas - ponteiro para a pilha a ser destruÃƒÂ­da
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK    - destruiu sem problemas
 *
 *  $AE Assertivas de Entrada - pPilha != NULL
 *
 *  $AS Assertivas de SaÃƒÂ­da - pPilha = NULL
 ***********************************************************************/

PIL_tpCondRet PIL_DestruirPilha( PIL_tppPilha pPilha );


/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: PIL Push Carta
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *      Insere carta no topo da pilha de cartas
 *
 *  $EP ParÃƒÂ¢metros
 *     pPilha de Cartas - ponteiro para a pilha onde a carta serÃƒÂ¡ inserida
 *     pCarta - Carta a ser inserida no topo da pilha
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK    - inseriu sem problemas
 *	  PIL_CondRetFaltouMemoria
 *
 *  $AE Assertivas de Entrada - pCarta ÃƒÂ© uma carta vÃƒÂ¡lida
 *							   pPilha ÃƒÂ© uma pilha vÃƒÂ¡lida
 *							   (pode ser vazia)
 *
 *  $AS Assertivas de SaÃƒÂ­da - se CondRet == OK
 *							 pCarta ÃƒÂ© inserido no topo da pilha
 *
 *							 se CondRet == Faltou MemÃƒÂ³ria
 *							 pCarta nÃƒÂ£o ÃƒÂ© inserido. Pilha continua
 *							 no estado que estava.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_PushCarta( PIL_tppPilha pPilha , CAR_tppCarta pCarta );


/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: PIL Pop Carta
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *     Remove carta do topo da pilha
 *
 *
 *  $EP ParÃƒÂ¢metros
 *     pPilha de Cartas - ponteiro para a pilha onde o topo deve ser removido
 *     pCarta - endereÃƒÂ§o que receberÃƒÂ¡ a carta removida.
 *
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetPilhaVazia
 *
 *  $AE Assertivas de Entrada - pPilha ÃƒÂ© uma pilha vÃƒÂ¡lida (pode ser vazia)
 *
 *  $AS Assertivas de SaÃƒÂ­da - Se condRet == OK:
 *							 carta ÃƒÂ© removida do topo da pilha e colocada em
 *							 *pCarta.
 *
 *							 Se condRet == PilhaVazia
 *							 *pCarta = NULL
 *
 ***********************************************************************/

PIL_tpCondRet PIL_PopCarta( PIL_tppPilha pPilha , CAR_tppCarta * pCarta );

/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: PIL  VerCarta
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *      Permite ver uma carta da pilha, mesmo que nÃƒÂ£o o topo;
 *      Essa funÃƒÂ§ÃƒÂ£o nÃƒÂ£o destrÃƒÂ³i a carta vista.
 *
 *  $EP ParÃƒÂ¢metros
 *     pPilha de Cartas - ponteiro para a pilha onde serÃƒÂ¡ vista a carta
 *     pCarta - ponteiro que guardarÃƒÂ¡ o endereÃƒÂ§o da carta a ser vista.
 *     posicao - distÃƒÂ¢ncia do topo da pilha ÃƒÂ  carta a ser vista.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetPilhaVazia
 *     PIL_CondRetParamIncorreto - posicao ÃƒÂ© um valor negativo
 *     PIL_CondRetFimPilha - a carta a ser vista estÃƒÂ¡ alÃƒÂ©m do tamanho da pilha
 *
 *  $AE Assertivas de Entrada - pPilha ÃƒÂ© uma pilha vÃƒÂ¡lida (pode ser vazia)
 *
 *  $AS Assertivas de SaÃƒÂ­da - Se condRet == OK:
 *							 pCarta recebe ponteiro para carta da posiÃƒÂ§ÃƒÂ£o 'posiÃƒÂ§ÃƒÂ£o' da
 *							 pPilha. A carta continua na pilha.
 *
 *							 Caso contrÃƒÂ¡rio:
 *							 * pCarta = NULL
 ***********************************************************************/

PIL_tpCondRet PIL_VerCarta( PIL_tppPilha pPilha , CAR_tppCarta * pCarta , int posicao );

#undef PILHA_DE_CARTAS_EXT

/********** Fim do mÃƒÂ³dulo de definiÃƒÂ§ÃƒÂ£o: PIL Pilha de Cartas  **********/

#else
#endif