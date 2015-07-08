#if ! defined( SEQJOGO_ )
#define SEQJOGO_
/***************************************************************************
 *
 *  $MCD MÃƒÂ³dulo de definiÃƒÂ§ÃƒÂ£o: SEQJ SequÃƒÂªncia de jogo
 *
 *  Arquivo gerado:              SEQJOGO.h
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
 *     2.0       EG,JM,LW        25/abr/2015       RevisÃƒÂ£o das funÃƒÂ§ÃƒÂµes
 *     1.0       EG,JM,LW        23/abr/2015       InÃƒÂ­cio do desenvolvimento
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o do mÃƒÂ³dulo
 *      Este mÃƒÂ³dulo implementa funÃƒÂ§ÃƒÂµes para criar e manipular uma Sequencia de Jogo.
 *      Uma sequencia de jogo comeÃƒÂ§a com 5 ou 6 cartas, criada a partir de uma pilha
 *      distribuÃƒÂ­da por um baralho completo.
 *      Ãƒâ€° possivel mover as cartas entre as sequencias de jogo existentes e quando
 *      umas delas possuir uma sequencia completa do mesmo naipe, estÃƒÂ¡ sequencia
 *      serÃƒÂ¡ levada a sequencia final.
 *
 ***************************************************************************/

#if defined( SEQJOGO_OWN )
#define SEQJOGO_EXT
#else
#define SEQJOGO_EXT extern
#endif

/***** DeclaraÃƒÂ§ÃƒÂµes exportadas pelo mÃƒÂ³dulo *****/

/* Tipo referÃƒÂªncia para uma SequÃƒÂªncia de jogo */

typedef struct SEQJ_tagSeqJogo * SEQJ_tppSeqJ ;

/***********************************************************************
 *
 *  $TC Tipo de dados: SEQJ CondiÃƒÂ§ÃƒÂµes de retorno
 *
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o do tipo
 *     CondiÃƒÂ§ÃƒÂµes de retorno das funÃƒÂ§ÃƒÂµes de SequÃƒÂªncia de jogo
 *
 ***********************************************************************/

typedef enum {
    
    SEQJ_CondRetOK = 0,
    /* Concluiu corretamente */
    
    SEQJ_CondRetSequenciaVazia = 1,
    /* SequÃƒÂªncia nÃƒÂ£o contÃƒÂ©m elementos */
    
    SEQJ_CondRetFaltouMemoria = 2,
    /* Faltou memÃƒÂ³ria ao tentar criar o sequÃƒÂªncia */
    
    SEQJ_CondRetNumCartasIncorreto = 3,
    /* NÃƒÂºmero de cartas a serem movidas estÃƒÂ¡ incorreto */
    
    SEQJ_CondRetCartasForaDaSequencia = 4
    /* Cartas escolhidas estÃƒÂ£o fora da sequÃƒÂªncia */
    
} SEQJ_tpCondRet ;


/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ  Criar SequÃƒÂªncia de jogo
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *     Cria uma nova sequÃƒÂªncia de jogo a partir de uma pilha.
 *
 *  $EP ParÃƒÂ¢metros
 *     $P pSeqJ - ponteiro para a sequÃƒÂªnca a ser criada.
 *     $P pPilha - pilha a partir da qual a seqÃƒÂ»encia irÃƒÂ¡ ser criada.
 *
 *  $FV Valor retornado
 *     SEQJ_CondRetOk    -   criou ok.
 *     SEQJ_CondRetFaltouMemoria -   faltou memÃƒÂ³ria para alocar espaÃƒÂ§o para a sequÃƒÂªncia.
 *
 *
 *  Assertivas de entrada esperadas - pPilha != NULL
 *
 *  Assertivas de saÃƒÂ­da esperadas   - SEQJ_CondRetOK
 *                                     pSeqJ != NULL
 *
 *
 ***********************************************************************/

SEQJ_tpCondRet SEQJ_CriarSeqJogo ( SEQJ_tppSeqJ * pSeqJ, PIL_tppPilha pPilha ) ;


/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ Destruir SequÃƒÂªncia de jogo
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *     Destroi uma sequÃƒÂªncia de jogo.
 *
 *  $EP ParÃƒÂ¢metros
 *     $P pSeqJ - sequÃƒÂªncia de jogo a ser excluÃƒÂ­da.
 *
 *  $FV Valor retornado
 *     SEQJ_CondRetOk    -   excluiu ok.
 *
 *  Assertivas de entrada esperadas - pSeqJ != NULL
 *
 *  Assertivas de saÃƒÂ­da esperadas   - SEQJ_CondRetOK
 *                                     pSeqJ == NULL
 *
 ***********************************************************************/

SEQJ_tpCondRet SEQJ_DestroiSequencia ( SEQJ_tppSeqJ pSeqJ ) ;


/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ Push Carta na sequÃƒÂªncia de jogo
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *     A funÃ§Ã£o da push em uma carta no inicio da Sequencia.
 *
 *  $EP ParÃƒÂ¢metros
 *     pSeqJ   - sequÃƒÂªncia de jogo.
 *     pCarta  - carta a ser colocada na sequÃƒÂªncia de jogo.
 *	  operacao - tipo da operacao: 1 caso seja uma transferencia entre
 *					sequencias, 0 caso seja uma carta vinda de um monte
 *
 *
 *  $FV Valor retornado
 *     SEQJ_CondRetOK      - push com sucesso.
 *     SEQJ_CondRetSequenciaVazia - sesquencia nao foi criada.
 *     SEQJ_CondRetCartasForaDaSequencia - carta nÃ£o estÃ¡ na sequÃªncia.
 *
 *   Assertivas de entrada esperadas - pSeqJ != NULL
 *                                      pCarta !=NULL
 *                                     pCarta Ã© sequencia da primeira carta
 *                                     de pSeqJ->pPilha
 *                                     operacao == 0 || operacao == 1
 *
 *  Assertivas de saÃƒÂ­da esperadas   - SEQJ_CondRetOK
 *
 ***********************************************************************/

SEQJ_tpCondRet SEQJ_PushCartaSequencia( SEQJ_tppSeqJ pSeqJ, CAR_tppCarta pCarta , int operacao ) ;


/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ Pop Carta na sequÃƒÂªncia de jogo
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *     A funÃƒÂ§ÃƒÂ£o da pop em uma carta no inicio da Sequencia.
 *
 *
 *  $EP ParÃƒÂ¢metros
 *     pSeqJ   - sequÃƒÂªncia de jogo.
 *     pCarta  - ponteiro carta a ser retirada da sequÃƒÂªncia de jogo.
 *
 *
 *  $FV Valor retornado
 *     SEQJ_CondRetOK      - pop com sucesso.
 *     SEQJ_CondRetSequenciaVazia - nao existem carta para pop
 *
 *  Assertivas de entrada esperadas - pSeqJ != NULL
 *
 *  Assertivas de saÃƒÂ­da esperadas   - SEQJ_CondRetOK
 *                                      pCarta != NULL
 *
 ***********************************************************************/

SEQJ_tpCondRet SEQJ_PopCartaSequencia( SEQJ_tppSeqJ pSeqJ, CAR_tppCarta * pCarta );

/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ Obtem Pilha da SequÃƒÂªncia de jogo
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *     A funÃƒÂ§ÃƒÂ£o irÃƒÂ¡ preencher uma pilha com uma sequÃƒÂªncia completa.
 *     Ãƒâ€° usada para levar a sequÃƒÂªncia que foi completa para a sequÃƒÂªncia final.
 *
 *
 *  $EP ParÃƒÂ¢metros
 *     pSeqJ   - sequÃƒÂªncia de jogo.
 *     pPilha -  ponteiro para a pilha a ser preenchida.
 *
 *
 *  $FV Valor retornado
 *     SEQJ_CondRetOK                 - preencheu pilha com sucesso com sucesso.
 *     SEQJ_CondRetSequenciaVazia     - sequÃƒÂªncia vazia.
 *     SEQJ_CondRetNumCartasIncorreto - nÃƒÂ£o tem 13 cartas viradas.
 *
 *  Assertivas de entrada esperadas - pSeqJ != NULL
 *
 *  Assertivas de saÃƒÂ­da esperadas   - SEQJ_CondRetOK
 *                                      pPilha != NULL
 *
 ***********************************************************************/

SEQJ_tpCondRet SEQJ_ObtemPilhaSeqJ( SEQJ_tppSeqJ pSeqJ, PIL_tppPilha *pPilha ) ;

/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ Verifica SequÃƒÂªncia completa
 *
 *  $ED DescriÃƒÂ§ÃƒÂ£o da funÃƒÂ§ÃƒÂ£o
 *     A funÃƒÂ§ÃƒÂ£o irÃƒÂ¡ verificar se existe uma sequÃƒÂªncia de cartas
 *     no inÃƒÂ­cio da sequÃƒÂªncia de jogo, que esteja completa, na
 *     ordem correta e mesmo naipe.
 *
 *
 *  $EP ParÃƒÂ¢metros
 *     pSeqJ - sequÃƒÂªncia de jogo a ser verificada.
 *
 *
 *  $FV Valor retornado
 *     SEQJ_CondRetOk                      -   existe sequÃƒÂªncia.
 *     SEQJ_CondRetCartasForaDaSequencia   - nao existe sequÃƒÂªncia completa.
 *
 * *   Assertivas de entrada esperadas - pSeqJ != NULL
 *
 *  Assertivas de saÃƒÂ­da esperadas   - SEQJ_CondRetOK se existe uma sequencia completa.
 *
 *
 ***********************************************************************/

SEQJ_tpCondRet SEQJ_VerificaSeqCompleta( SEQJ_tppSeqJ pSeqJ );

/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ Num Cartas Viradas
 *
 *  $ED Descri��o da fun��o
 *     A fun��o retorna o n�mero de cartas viradas de uma sequ�ncia de jogo.
 *
 *
 *  $EP Par�metros
 *     pSeqJ - sequÃƒÂªncia de jogo a ser verificada.
 *	   numCartasViradas - ponteiro para o numero de cartas viradas.
 *
 *
 *  $FV Valor retornado
 *     SEQJ_CondRetOk                      -   existe sequÃƒÂªncia.
 *
 *
 *
 ***********************************************************************/

SEQJ_tpCondRet SEQJ_NumCartasViradas( SEQJ_tppSeqJ pSeqJ, int *numCartasViradas );

/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ Vira Carta
 *
 *  $ED Descri��o da fun��o
 *     A fun��o vira n cartas de uma sequencia.
 *
 *
 *  $EP Par�metros
 *     pSeqJ - sequÃƒÂªncia de jogo a ser verificada.
 *	   numCartas - numero de cartas a serem viradas.
 *
 *
 *  $FV Valor retornado
 *     SEQJ_CondRetOk                      -   existe sequÃƒÂªncia.
 *
 *
 *
 ***********************************************************************/

SEQJ_tpCondRet SEQJ_ViraCarta( SEQJ_tppSeqJ pSeqJ, int numCartas );

/***********************************************************************
 *
 *  $FC FunÃƒÂ§ÃƒÂ£o: SEQJ Total de Cartas na Sequencia
 *
 *  $ED Descri��o da fun��o
 *     A fun��o diz o numero total de cartas em uma sequencia.
 *
 *
 *  $EP Par�metros
 *     pSeqJ - sequÃƒÂªncia de jogo a ser verificada.
 *
 *
 *  $FV Valor retornado
 *     numCartas                      -   numero de cartas.
 *
 *
 *
 ***********************************************************************/

int totalCartasNaSeq( SEQJ_tppSeqJ pSeqJ );

#undef SEQJ_EXT

/********** Fim do mÃƒÂ³dulo de definiÃƒÂ§ÃƒÂ£o: SEQJ SequÃƒÂªncia de jogo **********/

#else
#endif
