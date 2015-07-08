#if ! defined( CAR_ )
#define CAR_
/***************************************************************************
 *
 *  $MCD M�dulo de defini��o: CAR  Carta
 *
 *  Arquivo gerado:              CARTA.h
 *  Letras identificadoras:      CAR
 *
 *  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - Programa��o Modular
 *  Autores: EG - Eric Grinstein
             JM - Jordana Mecler
             LW - Leonardo Wajnsztok
 *
 *  $HA Hist�rico de evolu��o:
 *     Vers�o      Autor            Data                Observa��es
 *     1.0       EG,JM,LW        17/abr/2015       Corre��o de condi��es de retorno
 *     1.0       EG,JM,LW        16/abr/2015       in�cio do desenvolvimento
 *
 *  $ED Descri��o do m�dulo
 *     Este m�dulo implementa fun��es para criar e manipular cartas.
 *     A carta possui duas informa��es, o valor e o naipe.
 *     A carta � inicializada com valores vazios para valor e naipe.
 *
 ***************************************************************************/

#if defined( CAR_OWN )
    #define CAR_EXT
#else
    #define CAR_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma carta */

typedef struct CAR_tagCarta * CAR_tppCarta ;

/***********************************************************************
 *
 *  $TC Tipo de dados: CAR Condi��es de retorno
 *
 *
 *  $ED Descri��o do tipo
 *     Condi��es de retorno das fun��es da carta
 *
 ***********************************************************************/

    typedef enum {
    
        CAR_CondRetOK = 0,
        /* Concluiu corretamente */
    
        CAR_CondRetCartaNaoExiste = 1,
        /* A carta n�o existe */
    
        CAR_CondRetFaltouMemoria = 2,
        /* Faltou mem�ria ao tentar criar uma carta */
        
        CAR_CondRetNaipeNaoExiste = 3,
        /* Naipe n�o existe */
        
        CAR_CondRetValorNaoExiste = 4
        /* Valor n�o existe */

    } CAR_tpCondRet ;


/***********************************************************************
 *
 *  $FC Fun��o: CAR  Criar carta
 *
 *  $ED Descri��o da fun��o
 *     Cria uma nova carta com naipe e valor vazios.
 *
 *  $EP Par�metros
 *     $P pCarta - ponteiro para a carta a ser criada.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   criou ok.
 *     CAR_CondRetFaltouMemoria -   faltou mem�ria para alocar espa�o para a carta.
 *
 *  Assertivas de entrada esperadas - nenhuma.
 * 
 *  Assertivas de sa�da esperadas   - CAR_CondRetOK se *pCarta != NULL
 *                                    CAR_CondRetFaltouMemoria se *pCarta == NULL
 *                                    (*pCarta)->naipe = '0'
 *                                    (*pCarta)->valor = 0
 * 
 ***********************************************************************/

CAR_tpCondRet CAR_CriarCarta( CAR_tppCarta * pCarta ) ;


/***********************************************************************
 *
 *  $FC Fun��o: CAR  Preencher carta
 *
 *  $ED Descri��o da fun��o
 *     Preenche uma carta com valor e naipe.
 *
 *  $EP Par�metros
 *     $P pCarta - ponteiro para a carta a ser alterada.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   preencheu ok.
 *     CAR_CondRetCartaNaoExiste -   caso a carta a ser alterada n�o existir.
 *
 *  Assertivas de entrada esperadas - pCarta != NULL
 *                                    naipe v�lido
 *                                    valor v�lido
 * 
 *  Assertivas de sa�da esperadas   - CAR_CondRetOK
 *                                    pCarta->naipe = naipe
 *                                    pCarta->valor = valor
 * 
 ***********************************************************************/

CAR_tpCondRet CAR_PreencheCarta ( CAR_tppCarta pCarta , char naipe , int valor ) ;


/***********************************************************************
 *
 *  $FC Fun��o: CAR  Excluir carta
 *
 *  $ED Descri��o da fun��o
 *     Exclui a carta.
 *     Caso a carta n�o exista, faz nada.
 *
 *  $EP Par�metros
 *     $P pCarta - ponteiro para a carta a ser exclu�da.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   excluiu ok.
 *
 * Assertivas de entrada esperadas - pCarta != NULL
 * 
 *  Assertivas de sa�da esperadas   - pCarta == NULL
 * 
 ***********************************************************************/

CAR_tpCondRet CAR_ExcluirCarta( CAR_tppCarta pCarta ) ;


/***********************************************************************
 *
 *  $FC Fun��o: CAR  Obter naipe da carta
 *
 *  $ED Descri��o da fun��o
 *     Obt�m o naipe da carta.
 *
 *  $EP Par�metros
 *     $P pCarta - ponteiro para a carta a ser analisada.
 *     $P pNaipe - par�metro que receber� o naipe da carta.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   obteve ok.
 *     CAR_CondRetCartaNaoExiste    -   caso a carta analisada n�o existir.
 * 
 * Assertivas de entrada esperadas - pCarta != NULL
 *                                   pNaipe � valido
 * 
 *  Assertivas de sa�da esperadas   - CAR_CondRetOK
 *                                    *pNaipe = pCarta->naipe
 *
 ***********************************************************************/

CAR_tpCondRet CAR_ObterNaipe( CAR_tppCarta pCarta , char * pNaipe ) ;


/***********************************************************************
 *
 *  $FC Fun��o: CAR  Obter valor da carta
 *
 *  $ED Descri��o da fun��o
 *     Obt�m o valor da carta.
 *
 *  $EP Par�metros
 *     $P pCarta - ponteiro para a carta a ser analisada.
 *     $P pValor - par�metro que receber� o valor da carta.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   obteve ok.
 *     CAR_CondRetCartaNaoExiste    -   caso a carta analisada n�o existir.
 * 
 *  Assertivas de entrada esperadas - pCarta != NULL
 *                                    pValor � valido
 * 
 *  Assertivas de sa�da esperadas   - CAR_CondRetOK
 *                                    *pValor = pCarta->valor
 *
 ***********************************************************************/

CAR_tpCondRet CAR_ObterValor( CAR_tppCarta pCarta , int * pValor ) ;


/***********************************************************************
 *
 *  $FC Fun��o: CAR  Imprimir carta
 *
 *  $ED Descri��o da fun��o
 *     Imprime a carta.
 *
 *  $EP Par�metros
 *     $P pCarta - ponteiro para a carta a ser impressa.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   imprimiu ok.
 *     CAR_CondRetCartaNaoExiste    -   caso a carta a ser impressa n�o existir.
 * 
 *  Assertivas de entrada esperadas - pCarta != NULL
 *                                    pCarta->naipe � v�lido
 *                                    pCarta->valor � v�lido
 * 
 *  Assertivas de sa�da esperadas   - CAR_CondRetOK
 *                                    pCarta foi impressa
 *
 ***********************************************************************/

CAR_tpCondRet CAR_ImprimeCarta( CAR_tppCarta pCarta ) ;

#undef CAR_EXT

/********** Fim do m�dulo de defini��o: CAR  Carta **********/

#else
#endif