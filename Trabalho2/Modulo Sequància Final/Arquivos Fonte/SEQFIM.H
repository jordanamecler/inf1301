#if ! defined( SEQFIM_ )
#define SEQFIM_
/***************************************************************************
 *
 *  $MCD M�dulo de defini��o: SEQFIM Sequencia Final
 *
 *  Arquivo gerado:              SEQFIM.h
 *  Letras identificadoras:      SEQFIM
 *
 *  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - Programa��o Modular
 *  Autores: EG - Eric Grinstein
 *           JM - Jordana Mecler
 *           LW - Leonardo Wajnsztok
 *
 *  $HA Hist�rico de evolu��o:
 *     Vers�o      Autor            Data                Observa��es
 *     1.0       EG,JM,LW        18/abr/2015       In�cio do desenvolvimento
 *
 *  $ED Descri��o do m�dulo
 *     Este m�dulo implementa fun��es para criar e manipular uma Sequencia Final.
 *     Uma Sequencia Final � uma pilha de 13 cartas.
 *     A Sequencia Final � criada a partir de uma pilha de cartas.
 *
 ***************************************************************************/

#if defined( SEQFIM_OWN )
#define SEQFIM_EXT
#else
#define SEQFIM_EXT extern
#endif

#include "PILHA_DE_CARTAS.H"
#include "CARTA.H"

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma sequencia final */

typedef struct SEQFIM_tagSeqFim * SEQFIM_tppSeqFim ;

/***********************************************************************
 *
 *  $TC Tipo de dados: SEQFIM Condi��es de retorno
 *
 *
 *  $ED Descri��o do tipo
 *     Condi��es de retorno das fun��es de Sequencia Final
 *
 ***********************************************************************/

typedef enum {
    
    SEQFIM_CondRetOK ,
    /* Concluiu corretamente */
    
    SEQFIM_CondRetFaltouMemoria ,
    /* Faltou mem�ria ao tentar criar o monte */

	SEQFIM_CondRetSeqNaoExiste
	/* Sequencia final nao existe */
    
} SEQFIM_tpCondRet ;


/***********************************************************************
 *
 *  $FC Fun��o: SEQFIM  Criar sequencia final
 *
 *  $ED Descri��o da fun��o
 *     Cria uma nova sequencia final a partir de uma pilha.
 *
 *  $EP Par�metros
 *     $P pSeqFim - ponteiro para a sequencia final a ser criada.
 *
 *  $FV Valor retornado
 *     SEQFIM_CondRetOk    -   criou ok.
 *     SEQFIM_CondRetFaltouMemoria -   faltou mem�ria para alocar espa�o para a sequencia final.
 * 
 *  Assertivas de entrada esperadas - nenhuma.
 * 
 *  Assertivas de sa�da esperadas   - SEQFIM_CondRetOK se *pSeqFim != NULL
 *                                    SEQFIM_CondRetFaltouMemoria se *pSeqFim == NULL
 *
 ***********************************************************************/

SEQFIM_tpCondRet SEQFIM_CriarSeqFim ( SEQFIM_tppSeqFim * pSeqFim ) ;


/***********************************************************************
 *
 *  $FC Fun��o: SEQFIM  Destruir sequencia final
 *
 *  $ED Descri��o da fun��o
 *     Destroi uma sequencia final.
 *
 *  $EP Par�metros
 *     $P pSeqFim - ponteiro para a sequencia final a ser exclu�da.
 *
 *  $FV Valor retornado
 *     SEQFIM_CondRetOk    -   excluiu ok.
 * 
 *  Assertivas de entrada esperadas - pSeqFim != NULL
 * 
 *  Assertivas de sa�da esperadas   - pSeqFim->pPilha == NULL
 * 				      pSeqFim == NULL
 *
 ***********************************************************************/

SEQFIM_tpCondRet SEQFIM_DestroiSeqFim ( SEQFIM_tppSeqFim pSeqFim ) ;


/***********************************************************************
 *
 *  $FC Fun��o: SEQFIM Preenche sequencia final
 *
 *  $ED Descri��o da fun��o
 *     Preenche a sequencia final
 *
 *
 *  $EP Par�metros
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
 *  Assertivas de sa�da esperadas   - SEQFIM_CondRetOK
 *
 ***********************************************************************/

SEQFIM_tpCondRet SEQFIM_PreencheSeqFim ( SEQFIM_tppSeqFim pSeqFim , PIL_tppPilha pPilha ) ;

#undef MON_EXT

/********** Fim do m�dulo de defini��o: SEQFIM Sequencia final **********/

#else
#endif