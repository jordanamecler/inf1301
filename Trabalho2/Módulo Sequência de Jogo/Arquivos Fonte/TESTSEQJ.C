/***************************************************************************
 *  $MCI MÃ³dulo de implementaÃ§Ã£o: MÃ³dulo de teste especÃ­fico
 *
 *  Arquivo gerado:              TESTSEQJ.C
 *  Letras identificadoras:      TSEQJ
 *
 *  Autores:
 *       EG - Eric Grinstein
 *       JM - Jordana Mecler
 *       LW - Leonardo Wajnsztok
 *
 *
 *  $ED DescriÃ§Ã£o do mÃ³dulo
 *     Este mÃ³dulo contÃ©m as funÃ§Ãµes especÃ­ficas para o teste do
 *     mÃ³dulo sequÃªncia de jogo.
 *
 *  $EIU Interface com o usuÃ¡rio pessoa
 *     Comandos de teste especÃ­ficos para testar o mÃ³dulo sequÃªncia de jogo:
 *
 *     =criarIncompleta <int>
 *                   - chama a funÃ§Ã£o  SEQJ_CriarSeqJogo.
 *                   IrÃ¡ criar uma sequÃªncia de jogo com uma carta K de copas.
 *                   O parametro indica a posicao de um vetor, onde cabem 3 
 *                   sequÃªncias de jogo para os testes.
 *
 *      =criarCompleta <int>
 *                    - chama a funÃ§Ã£o SEQJ_CriarSeqJogo.
 *                    IrÃ¡ criar um sequÃªncia de jogo com 13 cartas de Ãs a K de espadas.
 *                    O parametro indica a posicao de um vetor, onde cabem 3 
 *                   sequÃªncias de jogo para os testes.
 * 
 *      =destruir <int>
 *                    - chama a funÃ§Ã£o SEQJ_DestroiSequencia. O parametro indica a posicao
 *                    de um vetor, onde cabem 3 sequÃªncias de jogo para os testes.
 *                    
 *      =pushCarta <char> <char> <int>
 *                    - chama a funÃ§Ã£o SEQJ_PushCartaSequencia. O primeiro parametro
 *                    Ã© o naipe da carta, depois seu valor. Por ultimo, a posicao de um vetor, onde cabem 3 
 *                   sequÃªncias de jogo para os testes.
 *                    
 *      =popCarta   <int>
 *                    - chama a funÃ§Ã£o SEQJ_PopCartaSequencia.O parÃ¢metro Ã© a posicao de um vetor, onde cabem 3 
 *                   sequÃªncias de jogo para os testes.
 *                    
 *      =obterPilha <int>
 *                    - chama a funÃ§Ã£o SEQJ_ObtemPilhaSeqJ. O parametro indica a posicao de um vetor, onde cabem 3 
 *                   sequÃªncias de jogo para os testes.
 *                    
 *      =verificarCompleta <int>
 *                    - chama a funÃ§Ã£o  SEQJ_VerificaSeqCompleta. O parametro indica a posicao de um vetor, onde cabem 3 
 *                   sequÃªncias de jogo para os testes.
 *
 ***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "CARTA.H"
#include    "PILHA_DE_CARTAS.H"
#include    "SEQJOGO.H"

/* Tabela dos nomes dos comandos de teste especÃ­ficos */

#define     CRIARINCOMPLETA_SEQJ_CMD  "=criarIncompleta"
#define     CRIARCOMPLETA_SEQJ_CMD  "=criarCompleta"
#define     DESTRUIR_SEQJ_CMD       "=destruir"
#define     PUSH_SEQJ_CMD           "=pushCarta"
#define     POP_SEQJ_CMD           "=popCarta"
#define     OBTER_SEQJ_CMD          "=obterPilha"
#define     VERIFICAR_SEQJ_CMD      "=verificarCompleta"


/* Ponteiro para monte utilizado no teste */

SEQJ_tppSeqJ vSeqJ[3] ;

/***********************************************************************
 *
 *  $FC FunÃ§Ã£o: TCAR Efetuar operaÃ§Ãµes de teste especÃ­ficas para Monte
 *
 *  $ED DescriÃ§Ã£o da funÃ§Ã£o
 *     Efetua os diversos comandos de teste especÃ­ficos para o mÃ³dulo
 *     Monte sendo testado.
 *
 *  $EP ParÃ¢metros
 *     $P ComandoTeste - String contendo o comando
 *
 *  $FV Valor retornado
 *     Ver TST_tpCondRet definido em TST_ESPC.H
 *
 ***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
    
    SEQJ_tpCondRet CondRetObtido   = SEQJ_CondRetOK ;
    SEQJ_tpCondRet CondRetEsperada = SEQJ_CondRetFaltouMemoria ;
    /* inicializa para qualquer coisa */
    
   char NaipeEsperado = '?'  ;
   char NaipeObtido   = '!'  ;  

   int ValorEsperado = -1  ;
   int ValorObtido   = -2  ;  
   int posVetorSeqJ  = -1  ;
   int posVetorSeqJ2  = -1  ;
   int numCartasMover = -1 ;
   int i = 0;

    PIL_tppPilha pilhaAux;
    CAR_tppCarta cartaDada;
    CAR_tppCarta CartaAux[13];
    CAR_tppCarta CartaAux2[13];

    TST_tpCondRet Ret ;

    int  NumLidos = -1 ;
    
    /* Testar SEQJ Criar SequÃªncia de jogo completa */
    
    if ( strcmp( ComandoTeste , CRIARCOMPLETA_SEQJ_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "ii" , &posVetorSeqJ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 2 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        if (posVetorSeqJ > 2 || posVetorSeqJ < 0 || vSeqJ[posVetorSeqJ] != NULL)
        {
            return TST_CondRetParm ;
        }

        PIL_CriarPilhaVazia( &pilhaAux );

        for(i = 0 ; i < 13 ; i++)
        {
            CAR_CriarCarta( &(CartaAux[i]) ) ;
            CAR_PreencheCarta( CartaAux[i], 'e' , i+1 );
            PIL_PushCarta( pilhaAux , CartaAux[i] ) ;
        }

        CondRetObtido = SEQJ_CriarSeqJogo ( &(vSeqJ[posVetorSeqJ]) , pilhaAux);

        PIL_DestruirPilha(pilhaAux);
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao criar a sequencia de jogo." );
        
    } /* fim ativa: Testar SEQJ Criar SequÃªncia de jogo completa*/
    
    /* Testar SEQJ Criar SequÃªncia de jogo incompleta */
    
    else if ( strcmp( ComandoTeste , CRIARINCOMPLETA_SEQJ_CMD  ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "ii" ,&posVetorSeqJ, &CondRetEsperada ) ;
        if ( NumLidos != 2 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        if (posVetorSeqJ > 2 || posVetorSeqJ < 0 || vSeqJ[posVetorSeqJ] != NULL)
        {
            return TST_CondRetParm ;
        }
        
        PIL_CriarPilhaVazia( &pilhaAux );
    
        CAR_CriarCarta( &(CartaAux2[0]) ) ;
        CAR_PreencheCarta( CartaAux2[0], 'c' , 13 );
        PIL_PushCarta( pilhaAux , CartaAux2[0] ) ;

        CondRetObtido = SEQJ_CriarSeqJogo ( &(vSeqJ[posVetorSeqJ]) , pilhaAux);

        PIL_DestruirPilha(pilhaAux);
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao criar a sequencia de jogo." );
       
    } /* fim ativa: Testar SEQJ Criar SequÃªncia de jogo incompleta */
    
    /* Testar SEQJ Destruir SequÃªncia de jogo */
    
    else if ( strcmp( ComandoTeste , DESTRUIR_SEQJ_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "ii" ,&posVetorSeqJ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 2 )
        {
            return TST_CondRetParm ;
        } /* if */

        if (posVetorSeqJ > 2 || posVetorSeqJ < 0 )
        {
            return TST_CondRetParm ;
        }
        
        CondRetObtido = SEQJ_DestroiSequencia(vSeqJ[posVetorSeqJ]) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                              "Retorno errado ao tentar destruir a sequencia.") ;
        
    } /* fim ativa:  Testar SEQJ Destruir SequÃªncia de jogo*/

    /* Testar SEQJ Push carta Sequencia*/

    else if ( strcmp( ComandoTeste , PUSH_SEQJ_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "ciii" ,&NaipeEsperado, &ValorEsperado,&posVetorSeqJ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 4 )
        {
            return TST_CondRetParm ;
        } /* if */

        if (posVetorSeqJ > 2 || posVetorSeqJ < 0 )
        {
            return TST_CondRetParm ;
        }
        
        CAR_CriarCarta( &cartaDada );
        CAR_PreencheCarta(cartaDada, NaipeEsperado, ValorEsperado) ;

        CondRetObtido = SEQJ_PushCartaSequencia(vSeqJ[posVetorSeqJ], cartaDada ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                              "Retorno errado ao dar push na sequencia.") ;
        
    } /* fim ativa:  Testar SEQJ Push carta Sequencia*/

    /* Testar SEQJ Pop carta Sequencia*/

    else if ( strcmp( ComandoTeste , POP_SEQJ_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "ii" , 
								&posVetorSeqJ, &CondRetEsperada ) ;
        if ( NumLidos != 2 )
        {
            return TST_CondRetParm ;
        } /* if */

        if (posVetorSeqJ > 2 || posVetorSeqJ < 0 )
        {
            return TST_CondRetParm ;
        }
        
		CondRetObtido = SEQJ_PopCartaSequencia( vSeqJ[posVetorSeqJ] , &cartaDada ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao dar pop na sequencia." );
        
    } /* fim ativa:  Testar SEQJ Pop carta Sequencia*/

     /* Testar SEQJ Obtem pilha da sequÃªncia de jogo*/

    else if ( strcmp( ComandoTeste , OBTER_SEQJ_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "ii" ,&posVetorSeqJ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 2 )
        {
            return TST_CondRetParm ;
        } /* if */

        if (posVetorSeqJ > 2 || posVetorSeqJ < 0 )
        {
            return TST_CondRetParm ;
        }


        CondRetObtido = SEQJ_ObtemPilhaSeqJ(vSeqJ[posVetorSeqJ], &pilhaAux ) ;
        //PIL_DestruirPilha(pilhaAux);

        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                              "Retorno errado ao obter pilha.") ;
        
    } /* fim ativa:  Testar SEQJ Obtem pilha da sequÃªncia de jogo*/

    /* Testar SEQJ Verifica sequÃªncia completa */

    else if ( strcmp( ComandoTeste ,  VERIFICAR_SEQJ_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "ii" ,&posVetorSeqJ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 2 )
        {
            return TST_CondRetParm ;
        } /* if */

        if (posVetorSeqJ > 2 || posVetorSeqJ < 0 )
        {
            return TST_CondRetParm ;
        }


        CondRetObtido = SEQJ_VerificaSeqCompleta( vSeqJ[posVetorSeqJ] ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                              "Retorno errado ao verificar se pilha completa.") ;
        
    } /* fim ativa:  Testar SEQJ Verifica sequÃªncia completa */

    return TST_CondRetNaoConhec ;
    
} /* Fim funÃ§Ã£o: TSEQJ Efetuar operaÃ§Ãµes de teste especÃ­ficas para sequÃªncia de jogo  */

/********** Fim do mÃ³dulo de implementaÃ§Ã£o: MÃ³dulo de teste especÃ­fico **********/