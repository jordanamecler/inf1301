/***************************************************************************
 *  $MCI Módulo de implementação: Módulo de teste específico
 *
 *  Arquivo gerado:              TESTMON.C
 *  Letras identificadoras:      TMON
 *
 *  Autores:
 *       EG - Eric Grinstein
 *       JM - Jordana Mecler
 *       LW - Leonardo Wajnsztok
 *
 *
 *  $ED Descrição do módulo
 *     Este módulo contém as funções específicas para o teste do
 *     módulo monte.
 *
 *  $EIU Interface com o usuário pessoa
 *     Comandos de teste específicos para testar o módulo monte:
 *
 *     =criar
 *                   - chama a função  MON_CriarMonte.
 *                   Irá criar um monte com 3 cartas previamente escolhidas
 *                   a partir de uma pilha criada com tais cartas.
 *                   Como só podemos retirar cartas e não colocá-las
 *                   no monte, não importa quais serão elas.
 *
 *     =pop
 *                   - chama a função MON_PopCartaMonte.
 *
 *     =destruir
 *             - chama a função MON_DestruirMonte.
 *
 ***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "CARTA.H"
#include    "PILHA_DE_CARTAS.H"
#include    "MONTE.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_MON_CMD       "=criar"
#define     POP_MON_CMD         "=pop"
#define     DESTRUIR_MON_CMD    "=destruir"

/* Ponteiro para monte utilizado no teste */

MON_tppMonte monteDado = NULL;

/***********************************************************************
 *
 *  $FC Função: TCAR Efetuar operações de teste específicas para Monte
 *
 *  $ED Descrição da função
 *     Efetua os diversos comandos de teste específicos para o módulo
 *     Monte sendo testado.
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
    
    MON_tpCondRet CondRetObtido   = MON_CondRetOK ;
    MON_tpCondRet CondRetEsperada = MON_CondRetFaltouMemoria ;
    /* inicializa para qualquer coisa */
    
   char NaipeEsperado = '?'  ;
   char NaipeObtido   = '!'  ;  

   int ValorEsperado = -1  ;
   int ValorObtido   = -2  ;  

    PIL_tppPilha pilhaAux;
    CAR_tppCarta CartaObtida;
    CAR_tppCarta CartaAux1;
    CAR_tppCarta CartaAux2;
    CAR_tppCarta CartaAux3;

    TST_tpCondRet Ret ;

    int  NumLidos = -1 ;
    
    /* Testar MON Criar Monte */
    
    if ( strcmp( ComandoTeste , CRIAR_MON_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        PIL_CriarPilhaVazia( &pilhaAux );

        CAR_CriarCarta( &CartaAux1 ) ;
        CAR_PreencheCarta( CartaAux1, 'o' , 12 );
        CAR_CriarCarta( &CartaAux2 ) ;
        CAR_PreencheCarta( CartaAux2, 'e' , 5 );
        CAR_CriarCarta( &CartaAux3 ) ;
        CAR_PreencheCarta( CartaAux3, 'c' , 11 );

        PIL_PushCarta( pilhaAux , CartaAux1 ) ;
        PIL_PushCarta( pilhaAux , CartaAux2 ) ;
        PIL_PushCarta( pilhaAux , CartaAux3 ) ;

        CondRetObtido = MON_CriarMonte ( &monteDado , pilhaAux);
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao criar o monte." );
        
    } /* fim ativa: Testar MON Criar Monte*/
    
    /* Testar MON Pop carta */
    
    else if ( strcmp( ComandoTeste , POP_MON_CMD  ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        
        CondRetObtido = MON_PopCartaMonte ( monteDado, &CartaObtida ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao dar pop no Monte." );


    } /* fim ativa: Testar MON Pop carta */
    
    /* Testar MON Destruir Monte */
    
    else if ( strcmp( ComandoTeste , DESTRUIR_MON_CMD ) == 0 )
    {
    
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = MON_DestruirMonte( monteDado ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                              "Retorno errado ao tentar destruir monte.") ;
        
    } /* fim ativa:  Testar MON Destruir monte*/
    
    return TST_CondRetNaoConhec ;
    
} /* Fim função: TMON Efetuar operações de teste específicas para monte */

/********** Fim do módulo de implementação: Módulo de teste específico **********/