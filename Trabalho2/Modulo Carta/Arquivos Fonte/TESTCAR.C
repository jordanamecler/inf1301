/***************************************************************************
 *  $MCI Módulo de implementação: Módulo de teste específico
 *
 *  Arquivo gerado:              TESTCAR.C
 *  Letras identificadoras:      TCAR
 *
 *  Autores:
 *			EG - Eric Grinstein
 *			JM - Jordana Mecler
 *			LW - Leonardo Wajnsztok
 *
 *
 *  $ED Descrição do módulo
 *     Este módulo contém as funções específicas para o teste do
 *     módulo carta.
 *
 *  $EIU Interface com o usuário pessoa
 *     Comandos de teste específicos para testar o módulo carta:
 *
 *     =criar
 *                   - chama a função CAR_CriarCarta,
 *                   o parâmetro é a condição de retorno.
 *     =preenche <char> <int>
 *                   - chama a função CAR_PreencheCarta,
 *					onde o primeiro parâmetro é o naipe da carta a ser
 *					preenchida, o segundo seu valor e o terceiro é a condição de retorno.
 *     =excluir
 *					- chama a função CAR_ExcluirCarta,
 *                  o parâmetro é a condição de retorno.
 *
 *     =obternaipe
 *                   - chama a função CAR_ObterNaipe,
 *                   o parâmetro é a condição de retorno.
 *
 *     =obtervalor
 *                   - chama a função CAR_ObterValor,
 *                   o parâmetro é a condição de retorno.
 *
 *     =imprime
 *                    - chama a função CAR_ImprimeCarta,
 *                    o parâmetro é a condição de retorno.
 *
 ***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "CARTA.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_CAR_CMD       "=criar"
#define     PREENCHE_CMD        "=preenche"
#define     EXCLUIR_CMD         "=excluir"
#define     OBTERNAIPE_CMD		"=obternaipe"
#define     OBTERVALOR_CMD      "=obtervalor"
#define     IMPRIME_CMD         "=imprime"

/* Ponteiro para carta auxiliar utilizada no teste */

CAR_tppCarta CartaDada = NULL ;

/***********************************************************************
 *
 *  $FC Função: TCAR Efetuar operações de teste específicas para cartas
 *
 *  $ED Descrição da função
 *     Efetua os diversos comandos de teste específicos para o módulo
 *     carta sendo testado.
 *
 *  $EP Parâmetros
 *     $P ComandoTeste - String contendo o comando
 *
 *  $FV Valor retornado
 *     Ver TST_tpCondRet definido em TST_ESPC.H
 *
 ***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
    
    CAR_tpCondRet CondRetObtido   = CAR_CondRetOK ;
    CAR_tpCondRet CondRetEsperada = CAR_CondRetFaltouMemoria ;
    /* inicializa para qualquer coisa */
    
    
    
    char NaipeEsperado = '?'  ;
    char NaipeDado     = '\0' ;
    
    int ValorEsperado = -1  ;
    int ValorDado     = 0 ;

    int  NumLidos = -1 ;
    
    
    
    /* Testar CAR Criar carta */
    
    if ( strcmp( ComandoTeste , CRIAR_CAR_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = CAR_CriarCarta( &CartaDada ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao criar carta." );
        
    } /* fim ativa: Testar CAR Criar carta*/
    
    /* Testar CAR Preenche Carta */
    
    else if ( strcmp( ComandoTeste , PREENCHE_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "cii" ,
                                     &NaipeDado , &ValorDado , &CondRetEsperada ) ;
        if ( NumLidos != 3 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        
        CondRetObtido = CAR_PreencheCarta( CartaDada , NaipeDado , ValorDado ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao preencher carta" );
        
    } /* fim ativa: Testar CAR Preenche Carta */
    
    /* Testar CAR Excluir Carta */
    
    else if ( strcmp( ComandoTeste , EXCLUIR_CMD ) == 0 )
    {
    
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = CAR_ExcluirCarta( CartaDada ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                              "Retorno errado ao tentar excluir carta") ;
        
    } /* Testar CAR Obter Naipe da Carta */
    
    else if ( strcmp( ComandoTeste , OBTERNAIPE_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = CAR_ObterNaipe( CartaDada , &NaipeEsperado ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                              "Retorno errado ao obter naipe da carta") ;
        
    } /* Testar CAR Obter Naipe da Carta */
    
    /* Testar CAR Obter Valor da Carta */
    else if ( strcmp( ComandoTeste , OBTERVALOR_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = CAR_ObterValor( CartaDada , &ValorEsperado ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado obter valor da carta" ) ;
        
    } /* fim ativa: Testar CAR Obter Valor da Carta */
    
    /* Testar CAR Imprime Carta */
    else if ( strcmp( ComandoTeste , IMPRIME_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = CAR_ImprimeCarta( CartaDada ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao imprimir carta" ) ;
    } /* fim ativa: Testar CAR Imprime Carta */
    
    /* Testar PIL Destruir Pilha */
    
    return TST_CondRetNaoConhec ;
    
} /* Fim função: TCAR Efetuar operações de teste específicas para cartas */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
