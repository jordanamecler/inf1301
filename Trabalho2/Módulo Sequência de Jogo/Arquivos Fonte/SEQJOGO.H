#if ! defined( SEQJOGO_ )
#define SEQJOGO_
/***************************************************************************
 *
 *  $MCD MÃ³dulo de definiÃ§Ã£o: SEQJ SequÃªncia de jogo
 *
 *  Arquivo gerado:              SEQJOGO.h
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
 *     2.0       EG,JM,LW        25/abr/2015       RevisÃ£o das funÃ§Ãµes
 *     1.0       EG,JM,LW        23/abr/2015       InÃ­cio do desenvolvimento
 *     
 *  $ED DescriÃ§Ã£o do mÃ³dulo
 *      Este mÃ³dulo implementa funÃ§Ãµes para criar e manipular uma Sequencia de Jogo.
 *      Uma sequencia de jogo comeÃ§a com 5 ou 6 cartas, criada a partir de uma pilha
 *      distribuÃ­da por um baralho completo.
 *      Ã‰ possivel mover as cartas entre as sequencias de jogo existentes e quando
 *      umas delas possuir uma sequencia completa do mesmo naipe, estÃ¡ sequencia 
 *      serÃ¡ levada a sequencia final.
 *
 ***************************************************************************/

#if defined( SEQJOGO_OWN )
    #define SEQJOGO_EXT
#else
    #define SEQJOGO_EXT extern
#endif

/***** DeclaraÃ§Ãµes exportadas pelo mÃ³dulo *****/

/* Tipo referÃªncia para uma SequÃªncia de jogo */

typedef struct SEQJ_tagSeqJogo * SEQJ_tppSeqJ ;

/***********************************************************************
 *
 *  $TC Tipo de dados: SEQJ CondiÃ§Ãµes de retorno
 *
 *
 *  $ED DescriÃ§Ã£o do tipo
 *     CondiÃ§Ãµes de retorno das funÃ§Ãµes de SequÃªncia de jogo
 *
 ***********************************************************************/

    typedef enum {

        SEQJ_CondRetOK = 0,
               /* Concluiu corretamente */

        SEQJ_CondRetSequenciaVazia = 1,
               /* SequÃªncia nÃ£o contÃ©m elementos */

        SEQJ_CondRetFaltouMemoria = 2,
               /* Faltou memÃ³ria ao tentar criar o sequÃªncia */

        SEQJ_CondRetNumCartasIncorreto = 3,
               /* NÃºmero de cartas a serem movidas estÃ¡ incorreto */

        SEQJ_CondRetCartasForaDaSequencia = 4
               /* Cartas escolhidas estÃ£o fora da sequÃªncia */

   } SEQJ_tpCondRet ;


/***********************************************************************
 *
 *  $FC FunÃ§Ã£o: SEQJ  Criar SequÃªncia de jogo
 *
 *  $ED DescriÃ§Ã£o da funÃ§Ã£o
 *     Cria uma nova sequÃªncia de jogo a partir de uma pilha.
 *
 *  $EP ParÃ¢metros
 *     $P pSeqJ - ponteiro para a sequÃªnca a ser criada.
 *     $P pPilha - pilha a partir da qual a seqÃ»encia irÃ¡ ser criada.
 *
 *  $FV Valor retornado
 *     SEQJ_CondRetOk    -   criou ok.
 *     SEQJ_CondRetFaltouMemoria -   faltou memÃ³ria para alocar espaÃ§o para a sequÃªncia.
 * 
 * 
 *  Assertivas de entrada esperadas - pPilha != NULL
 * 
 *  Assertivas de saÃ­da esperadas   - SEQJ_CondRetOK
 *                                     pSeqJ != NULL
 *           
 *
 ***********************************************************************/

SEQJ_tpCondRet SEQJ_CriarSeqJogo ( SEQJ_tppSeqJ * pSeqJ, PIL_tppPilha pPilha ) ;


/***********************************************************************
 *
 *  $FC FunÃ§Ã£o: SEQJ Destruir SequÃªncia de jogo
 *
 *  $ED DescriÃ§Ã£o da funÃ§Ã£o
 *     Destroi uma sequÃªncia de jogo.
 *
 *  $EP ParÃ¢metros
 *     $P pSeqJ - sequÃªncia de jogo a ser excluÃ­da.
 *
 *  $FV Valor retornado
 *     SEQJ_CondRetOk    -   excluiu ok.
 *
 *  Assertivas de entrada esperadas - pSeqJ != NULL
 * 
 *  Assertivas de saÃ­da esperadas   - SEQJ_CondRetOK
 *                                     pSeqJ == NULL
 * 
 ***********************************************************************/

SEQJ_tpCondRet SEQJ_DestroiSequencia ( SEQJ_tppSeqJ pSeqJ ) ;


/***********************************************************************
*
*  $FC FunÃ§Ã£o: SEQJ Push Carta na sequÃªncia de jogo
*
*  $ED DescriÃ§Ã£o da funÃ§Ã£o
*     A função da push em uma carta no inicio da Sequencia.  
*
*  $EP ParÃ¢metros
*     pSeqJ   - sequÃªncia de jogo.
*     pCarta  - carta a ser colocada na sequÃªncia de jogo.
*              
*
*  $FV Valor retornado
*     SEQJ_CondRetOK      - push com sucesso.
*     SEQJ_CondRetSequenciaVazia - sesquencia nao foi criada.
*     SEQJ_CondRetCartasForaDaSequencia - carta não está na sequência.
* 
*   Assertivas de entrada esperadas - pSeqJ != NULL
*                                      pCarta !=NULL 
*                                     pCarta é sequencia da primeira carta
*                                     de pSeqJ->pPilha
* 
*  Assertivas de saÃ­da esperadas   - SEQJ_CondRetOK
*
***********************************************************************/

SEQJ_tpCondRet SEQJ_PushCartaSequencia( SEQJ_tppSeqJ pSeqJ, CAR_tppCarta pCarta ) ;


/***********************************************************************
*
*  $FC FunÃ§Ã£o: SEQJ Pop Carta na sequÃªncia de jogo
*
*  $ED DescriÃ§Ã£o da funÃ§Ã£o
*     A funÃ§Ã£o da pop em uma carta no inicio da Sequencia.
*     
*
*  $EP ParÃ¢metros
*     pSeqJ   - sequÃªncia de jogo.
*     pCarta  - ponteiro carta a ser retirada da sequÃªncia de jogo.
*              
*
*  $FV Valor retornado
*     SEQJ_CondRetOK      - pop com sucesso.
*     SEQJ_CondRetSequenciaVazia - nao existem carta para pop
* 
*  Assertivas de entrada esperadas - pSeqJ != NULL
* 
*  Assertivas de saÃ­da esperadas   - SEQJ_CondRetOK
*                                      pCarta != NULL
*
***********************************************************************/

SEQJ_tpCondRet SEQJ_PopCartaSequencia( SEQJ_tppSeqJ pSeqJ, CAR_tppCarta * pCarta );

/***********************************************************************
*
*  $FC FunÃ§Ã£o: SEQJ Obtem Pilha da SequÃªncia de jogo
*
*  $ED DescriÃ§Ã£o da funÃ§Ã£o
*     A funÃ§Ã£o irÃ¡ preencher uma pilha com uma sequÃªncia completa.
*     Ã‰ usada para levar a sequÃªncia que foi completa para a sequÃªncia final.
*     
*
*  $EP ParÃ¢metros
*     pSeqJ   - sequÃªncia de jogo.
*     pPilha -  ponteiro para a pilha a ser preenchida.
*              
*
*  $FV Valor retornado
*     SEQJ_CondRetOK                 - preencheu pilha com sucesso com sucesso.
*     SEQJ_CondRetSequenciaVazia     - sequÃªncia vazia.
*     SEQJ_CondRetNumCartasIncorreto - nÃ£o tem 13 cartas viradas.
* 
*  Assertivas de entrada esperadas - pSeqJ != NULL
* 
*  Assertivas de saÃ­da esperadas   - SEQJ_CondRetOK
*                                      pPilha != NULL
*
***********************************************************************/

SEQJ_tpCondRet SEQJ_ObtemPilhaSeqJ( SEQJ_tppSeqJ pSeqJ, PIL_tppPilha *pPilha ) ;

/***********************************************************************
*
*  $FC FunÃ§Ã£o: SEQJ Verifica SequÃªncia completa
*
*  $ED DescriÃ§Ã£o da funÃ§Ã£o
*     A funÃ§Ã£o irÃ¡ verificar se existe uma sequÃªncia de cartas
*     no inÃ­cio da sequÃªncia de jogo, que esteja completa, na 
*     ordem correta e mesmo naipe.
*     
*
*  $EP ParÃ¢metros
*     pSeqJ - sequÃªncia de jogo a ser verificada.
*              
*
*  $FV Valor retornado
*     SEQJ_CondRetOk                      -   existe sequÃªncia.
*     SEQJ_CondRetCartasForaDaSequencia   - nao existe sequÃªncia completa.
* 
* *   Assertivas de entrada esperadas - pSeqJ != NULL
* 
*  Assertivas de saÃ­da esperadas   - SEQJ_CondRetOK se existe uma sequencia completa.
*                                    
*
***********************************************************************/

SEQJ_tpCondRet SEQJ_VerificaSeqCompleta( SEQJ_tppSeqJ pSeqJ );

#undef SEQJ_EXT

/********** Fim do mÃ³dulo de definiÃ§Ã£o: SEQJ SequÃªncia de jogo **********/

#else
#endif