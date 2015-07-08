#if ! defined( CAR_ )
#define CAR_
/***************************************************************************
 *
 *  $MCD Módulo de definição: CAR  Carta
 *
 *  Arquivo gerado:              CARTA.h
 *  Letras identificadoras:      CAR
 *
 *  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - Programação Modular
 *  Autores: EG - Eric Grinstein
             JM - Jordana Mecler
             LW - Leonardo Wajnsztok
 *
 *  $HA Histórico de evolução:
 *     Versão      Autor            Data                Observações
 *     1.0       EG,JM,LW        17/abr/2015       Correção de condições de retorno
 *     1.0       EG,JM,LW        16/abr/2015       início do desenvolvimento
 *
 *  $ED Descrição do módulo
 *     Este módulo implementa funções para criar e manipular cartas.
 *     A carta possui duas informações, o valor e o naipe.
 *     A carta é inicializada com valores vazios para valor e naipe.
 *
 ***************************************************************************/

#if defined( CAR_OWN )
    #define CAR_EXT
#else
    #define CAR_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma carta */

typedef struct CAR_tagCarta * CAR_tppCarta ;

/***********************************************************************
 *
 *  $TC Tipo de dados: CAR Condições de retorno
 *
 *
 *  $ED Descrição do tipo
 *     Condições de retorno das funções da carta
 *
 ***********************************************************************/

    typedef enum {
    
        CAR_CondRetOK = 0,
        /* Concluiu corretamente */
    
        CAR_CondRetCartaNaoExiste = 1,
        /* A carta não existe */
    
        CAR_CondRetFaltouMemoria = 2,
        /* Faltou memória ao tentar criar uma carta */
        
        CAR_CondRetNaipeNaoExiste = 3,
        /* Naipe não existe */
        
        CAR_CondRetValorNaoExiste = 4
        /* Valor não existe */

    } CAR_tpCondRet ;


/***********************************************************************
 *
 *  $FC Função: CAR  Criar carta
 *
 *  $ED Descrição da função
 *     Cria uma nova carta com naipe e valor vazios.
 *
 *  $EP Parâmetros
 *     $P pCarta - ponteiro para a carta a ser criada.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   criou ok.
 *     CAR_CondRetFaltouMemoria -   faltou memória para alocar espaço para a carta.
 *
 *  Assertivas de entrada esperadas - nenhuma.
 * 
 *  Assertivas de saída esperadas   - CAR_CondRetOK se *pCarta != NULL
 *                                    CAR_CondRetFaltouMemoria se *pCarta == NULL
 *                                    (*pCarta)->naipe = '0'
 *                                    (*pCarta)->valor = 0
 * 
 ***********************************************************************/

CAR_tpCondRet CAR_CriarCarta( CAR_tppCarta * pCarta ) ;


/***********************************************************************
 *
 *  $FC Função: CAR  Preencher carta
 *
 *  $ED Descrição da função
 *     Preenche uma carta com valor e naipe.
 *
 *  $EP Parâmetros
 *     $P pCarta - ponteiro para a carta a ser alterada.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   preencheu ok.
 *     CAR_CondRetCartaNaoExiste -   caso a carta a ser alterada não existir.
 *
 *  Assertivas de entrada esperadas - pCarta != NULL
 *                                    naipe válido
 *                                    valor válido
 * 
 *  Assertivas de saída esperadas   - CAR_CondRetOK
 *                                    pCarta->naipe = naipe
 *                                    pCarta->valor = valor
 * 
 ***********************************************************************/

CAR_tpCondRet CAR_PreencheCarta ( CAR_tppCarta pCarta , char naipe , int valor ) ;


/***********************************************************************
 *
 *  $FC Função: CAR  Excluir carta
 *
 *  $ED Descrição da função
 *     Exclui a carta.
 *     Caso a carta não exista, faz nada.
 *
 *  $EP Parâmetros
 *     $P pCarta - ponteiro para a carta a ser excluída.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   excluiu ok.
 *
 * Assertivas de entrada esperadas - pCarta != NULL
 * 
 *  Assertivas de saída esperadas   - pCarta == NULL
 * 
 ***********************************************************************/

CAR_tpCondRet CAR_ExcluirCarta( CAR_tppCarta pCarta ) ;


/***********************************************************************
 *
 *  $FC Função: CAR  Obter naipe da carta
 *
 *  $ED Descrição da função
 *     Obtém o naipe da carta.
 *
 *  $EP Parâmetros
 *     $P pCarta - ponteiro para a carta a ser analisada.
 *     $P pNaipe - parâmetro que receberá o naipe da carta.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   obteve ok.
 *     CAR_CondRetCartaNaoExiste    -   caso a carta analisada não existir.
 * 
 * Assertivas de entrada esperadas - pCarta != NULL
 *                                   pNaipe é valido
 * 
 *  Assertivas de saída esperadas   - CAR_CondRetOK
 *                                    *pNaipe = pCarta->naipe
 *
 ***********************************************************************/

CAR_tpCondRet CAR_ObterNaipe( CAR_tppCarta pCarta , char * pNaipe ) ;


/***********************************************************************
 *
 *  $FC Função: CAR  Obter valor da carta
 *
 *  $ED Descrição da função
 *     Obtém o valor da carta.
 *
 *  $EP Parâmetros
 *     $P pCarta - ponteiro para a carta a ser analisada.
 *     $P pValor - parâmetro que receberá o valor da carta.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   obteve ok.
 *     CAR_CondRetCartaNaoExiste    -   caso a carta analisada não existir.
 * 
 *  Assertivas de entrada esperadas - pCarta != NULL
 *                                    pValor é valido
 * 
 *  Assertivas de saída esperadas   - CAR_CondRetOK
 *                                    *pValor = pCarta->valor
 *
 ***********************************************************************/

CAR_tpCondRet CAR_ObterValor( CAR_tppCarta pCarta , int * pValor ) ;


/***********************************************************************
 *
 *  $FC Função: CAR  Imprimir carta
 *
 *  $ED Descrição da função
 *     Imprime a carta.
 *
 *  $EP Parâmetros
 *     $P pCarta - ponteiro para a carta a ser impressa.
 *
 *  $FV Valor retornado
 *     CAR_CondRetOk    -   imprimiu ok.
 *     CAR_CondRetCartaNaoExiste    -   caso a carta a ser impressa não existir.
 * 
 *  Assertivas de entrada esperadas - pCarta != NULL
 *                                    pCarta->naipe é válido
 *                                    pCarta->valor é válido
 * 
 *  Assertivas de saída esperadas   - CAR_CondRetOK
 *                                    pCarta foi impressa
 *
 ***********************************************************************/

CAR_tpCondRet CAR_ImprimeCarta( CAR_tppCarta pCarta ) ;

#undef CAR_EXT

/********** Fim do módulo de definição: CAR  Carta **********/

#else
#endif