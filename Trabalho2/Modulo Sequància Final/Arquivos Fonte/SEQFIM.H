#if ! defined( SEQFIM_ )
#define SEQFIM_
/***************************************************************************
 *
 *  $MCD Módulo de definição: SEQFIM Sequencia Final
 *
 *  Arquivo gerado:              SEQFIM.h
 *  Letras identificadoras:      SEQFIM
 *
 *  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - Programação Modular
 *  Autores: EG - Eric Grinstein
 *           JM - Jordana Mecler
 *           LW - Leonardo Wajnsztok
 *
 *  $HA Histórico de evolução:
 *     Versão      Autor            Data                Observações
 *     1.0       EG,JM,LW        18/abr/2015       Início do desenvolvimento
 *
 *  $ED Descrição do módulo
 *     Este módulo implementa funções para criar e manipular uma Sequencia Final.
 *     Uma Sequencia Final é uma pilha de 13 cartas.
 *     A Sequencia Final é criada a partir de uma pilha de cartas.
 *
 ***************************************************************************/

#if defined( SEQFIM_OWN )
#define SEQFIM_EXT
#else
#define SEQFIM_EXT extern
#endif

#include "PILHA_DE_CARTAS.H"
#include "CARTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma sequencia final */

typedef struct SEQFIM_tagSeqFim * SEQFIM_tppSeqFim ;

/***********************************************************************
 *
 *  $TC Tipo de dados: SEQFIM Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções de Sequencia Final
 *
 ***********************************************************************/

typedef enum {
    
    SEQFIM_CondRetOK ,
    /* Concluiu corretamente */
    
    SEQFIM_CondRetFaltouMemoria ,
    /* Faltou memória ao tentar criar o monte */

	SEQFIM_CondRetSeqNaoExiste
	/* Sequencia final nao existe */
    
} SEQFIM_tpCondRet ;


/***********************************************************************
 *
 *  $FC Função: SEQFIM  Criar sequencia final
 *
 *  $ED Descrição da função
 *     Cria uma nova sequencia final a partir de uma pilha.
 *
 *  $EP Parâmetros
 *     $P pSeqFim - ponteiro para a sequencia final a ser criada.
 *
 *  $FV Valor retornado
 *     SEQFIM_CondRetOk    -   criou ok.
 *     SEQFIM_CondRetFaltouMemoria -   faltou memória para alocar espaço para a sequencia final.
 * 
 *  Assertivas de entrada esperadas - nenhuma.
 * 
 *  Assertivas de saída esperadas   - SEQFIM_CondRetOK se *pSeqFim != NULL
 *                                    SEQFIM_CondRetFaltouMemoria se *pSeqFim == NULL
 *
 ***********************************************************************/

SEQFIM_tpCondRet SEQFIM_CriarSeqFim ( SEQFIM_tppSeqFim * pSeqFim ) ;


/***********************************************************************
 *
 *  $FC Função: SEQFIM  Destruir sequencia final
 *
 *  $ED Descrição da função
 *     Destroi uma sequencia final.
 *
 *  $EP Parâmetros
 *     $P pSeqFim - ponteiro para a sequencia final a ser excluída.
 *
 *  $FV Valor retornado
 *     SEQFIM_CondRetOk    -   excluiu ok.
 * 
 *  Assertivas de entrada esperadas - pSeqFim != NULL
 * 
 *  Assertivas de saída esperadas   - pSeqFim->pPilha == NULL
 * 				      pSeqFim == NULL
 *
 ***********************************************************************/

SEQFIM_tpCondRet SEQFIM_DestroiSeqFim ( SEQFIM_tppSeqFim pSeqFim ) ;


/***********************************************************************
 *
 *  $FC Função: SEQFIM Preenche sequencia final
 *
 *  $ED Descrição da função
 *     Preenche a sequencia final
 *
 *
 *  $EP Parâmetros
 *     pSeqFim - ponteiro para a sequencia final.
 *     pPilha - pilha a ser usada para preencher a sequencia final.
 *
 *
 *  $FV Valor retornado
 *     SEQFIM_CondRetOk     -   preenchido com sucesso.
 * 
 *  Assertivas de entrada esperadas - pSeqFim != NULL
 * 			              pPilha != NULL
 * 
 *  Assertivas de saída esperadas   - SEQFIM_CondRetOK
 *
 ***********************************************************************/

SEQFIM_tpCondRet SEQFIM_PreencheSeqFim ( SEQFIM_tppSeqFim pSeqFim , PIL_tppPilha pPilha ) ;

#undef MON_EXT

/********** Fim do módulo de definição: SEQFIM Sequencia final **********/

#else
#endif