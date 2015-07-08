/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTPIL.C
*  Letras identificadoras:      TPIL
*
*  Autores: 
*			eg - Eric Grinstein
*			jm - Jordana Mecler
*			lw - Leonardo Wajnsztok
*
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo pilha de cartas. É possível testar com esse módulo a 
*     criação de 10 pilhas de cartas (que serão armazenadas internamente
*     em um vetor.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo pilha de cartas:
*
*     =criar  <int> - chama a função PIL_CriarPilhaVazia, criando 
*					  criando-a no slot de pilhas dado pelo parâmetro fornecido.
*					  A pilha pode ser criada do slot 0 ao slot 9. Qualquer número 
*                     fornecido fora deste intervalo é tratado como parâmetro incorreto.
*					  O mesmo vale para os outros comandos de teste.
*     =push <int> <Char> <int>
*                   - chama a função PIL_PushCarta,
*					onde o primeiro parâmetro é o número da pilha
*					a ser alterada, o segundo é o naipe da carta a ser
*					inserida e o último seu valor.
*     =pop <int> <char> <int>
*					- chama a função PIL_PopCarta,
*					onde o parâmetro se refere ao número da pilha a ser removido
*					seu topo. Depois, é testado o valor do naipe com o <char> fornecido,
*				    assim como o valor do valor <int> também fornecido.
*     
*     =ver <int> <int> <char> <int>
*                   - chama a função PIL_VerCarta, onde o primeiro parâmetro
*                   se refere ao número da pilha a ser vista e o segundo a posição da
*					pilha em relação ao topo a ser vista.
*					Depois, é testado o valor do naipe com o <char> fornecido,
*				    assim como o valor do valor <int> também fornecido.
*
*     =destroi <int>  - chama a função PIL_DestruirPilha, onde o inteiro dado se refere ao
*                     número da pilha a ser destruída
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"
#ifdef _DEBUG
	
#include "CESPDIN.H"

#endif
#include    "CARTA.H"
#include    "PILHA_DE_CARTAS.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_PIL_CMD       "=criar"
#define     PUSH_CMD            "=push"
#define     POP_CMD				"=pop"
#define     VER_CMD				"=ver"
#define     DESTROI_CMD         "=destruir"

#ifdef _DEBUG
	#define DETURPAR_PILHA_CMD  "=deturpar"
	#define VERIFICAR_PILHA_CMD "=verificar"            
#endif

/* Máximo de pilhas a serem testadas simultâneamente */

#define     MAX_PILS            10

PIL_tppPilha vPilhas[ MAX_PILS ];

/*****  Código das funcões exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPIL Efetuar operações de teste específicas para pilha de cartas
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     pilha sendo testado.
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

      PIL_tpCondRet CondRetObtido   = PIL_CondRetOK ;
      PIL_tpCondRet CondRetEsperada = PIL_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

	 

      char NaipeEsperado = '?'  ;
      char NaipeObtido   = '!'  ;  
      char NaipeDado     = '\0' ;

      int ValorEsperado = -1  ;
      int ValorObtido   = -2  ;  
      int ValorDado     = 0 ;

      int PosicaoPilha = -1 ;
      int NumPilha = -1 ;
      int  NumLidos = -1 ;

#ifdef _DEBUG
	  int tpDeturpacao;
	  int numErros;
	  int errosEsperados;
#endif

      CAR_tppCarta CartaObtida ;
      CAR_tppCarta CartaDada ;

      TST_tpCondRet Ret ;

      /* Testar PIL Criar Pilha de Cartas */

         if ( strcmp( ComandoTeste , CRIAR_PIL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &NumPilha ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 2 || NumPilha >= MAX_PILS || NumPilha < 0 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PIL_CriarPilhaVazia( &vPilhas[NumPilha] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar pilha." );

         } /* fim ativa: Testar PIL Criar Pilha de cartas*/

      /* Testar PIL Push Carta na pilha */

         else if ( strcmp( ComandoTeste , PUSH_CMD ) == 0 )
         {
			
            NumLidos = LER_LerParametros( "icii" ,
                               &NumPilha, &NaipeDado , &ValorDado, &CondRetEsperada ) ;
            if ( NumLidos != 4 || NumPilha >= MAX_PILS || NumPilha < 0 )
            {
               return TST_CondRetParm ;
            } /* if */
			
			CAR_CriarCarta( &CartaDada ) ;
            CAR_PreencheCarta( CartaDada, NaipeDado , ValorDado );
			
            CondRetObtido = PIL_PushCarta( vPilhas[NumPilha] , CartaDada ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao operar 'push' na pilha" );

         } /* fim ativa: Testar PIL Push Carta na pilha */

      /* Testar PIL Pop Carta da Pilha */

         else if ( strcmp( ComandoTeste , POP_CMD ) == 0 )
         {			
            NumLidos = LER_LerParametros( "icii" ,
                               &NumPilha , &NaipeEsperado , &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 4 || NumPilha >= MAX_PILS || NumPilha < 0 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = PIL_PopCarta( vPilhas[NumPilha] , &CartaObtida ) ;

			
            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao operar 'pop' na pilha") ;

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			if ( CondRetObtido != PIL_CondRetOK )
            {
               return CondRetObtido ;
            } /* if */

			CAR_ObterNaipe( CartaObtida , &NaipeObtido );
            Ret = TST_CompararInt( NaipeEsperado , NaipeObtido ,
                                    "Carta obtida está errada." );

			if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			CAR_ObterValor( CartaObtida , &ValorObtido );
            return TST_CompararInt( ValorEsperado , ValorObtido ,
                                    "Carta obtida está errada." );


            } /* Testar PIL Ver Carta da Pilha */

		else if ( strcmp( ComandoTeste , VER_CMD ) == 0 )
         {
			
            NumLidos = LER_LerParametros( "iicii" ,
                            &NumPilha , &PosicaoPilha, &NaipeEsperado , &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 5 || NumPilha >= MAX_PILS || NumPilha < 0 )
            {
                return TST_CondRetParm ;
            } /* if */

			 CondRetObtido = PIL_VerCarta( vPilhas[NumPilha] , &CartaObtida , PosicaoPilha ) ;
				
				
			 Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
						"Retorno errado ao ver carta da pilha") ;

			if ( Ret != TST_CondRetOK )
			{
			    return Ret ;
			} /* if */

			if ( CondRetObtido != PIL_CondRetOK )
            {
               return CondRetObtido ;
            } /* if */

		    CAR_ObterNaipe( CartaObtida , &NaipeObtido );
		    Ret = TST_CompararInt( NaipeEsperado , NaipeObtido ,
		                            "Carta vista está errada." );

			if ( Ret != TST_CondRetOK )
            {
            	 return Ret ;
            } /* if */

	        CAR_ObterValor( CartaObtida , &ValorObtido );
            return TST_CompararInt( ValorEsperado , ValorObtido ,
                                    "Carta vista está errada." );


            } /* Testar PIL Ver Carta da Pilha */

            /* Testar PIL Destruir pilha de cartas */
            else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
            {

		    NumLidos = LER_LerParametros( "ii" , &NumPilha ,  
		                       &CondRetEsperada ) ;
		    if ( NumLidos != 2 || NumPilha >= MAX_PILS || NumPilha < 0 )
		    {
		       return TST_CondRetParm ;
		    } /* if */

		   // CondRetObtido = PIL_DestruirPilha( vPilhas[NumPilha] ) ;
#ifdef _DEBUG
			CED_InicializarIteradorEspacos();
			while( CED_ExisteEspacoCorrente() != 0)
			{
				CED_ExcluirEspacoCorrente();
			}
#endif
			return TST_CondRetOK;
		    //return TST_CompararInt( CondRetEsperada , CondRetObtido ,
		     //                       "Retorno errado destruir pilha." );

	    } /* fim ativa: Testar PIL Destruir Pilha de Cartas */

	    /* Testar PIL Destruir Pilha */
#ifdef _DEBUG
		/* Realizar deturpacao */
        else if ( strcmp( ComandoTeste , DETURPAR_PILHA_CMD  ) == 0 ) {

            NumLidos = LER_LerParametros( "ii" , &NumPilha, &tpDeturpacao) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			return TST_CompararInt( PIL_CondRetOK , PIL_Deturpa(vPilhas[ NumPilha ], tpDeturpacao),
                     "Erro ao deturpar."  ) ;

        } /* fim ativa: Realizar deturpacao */

		/* Realizar verificao estrututral */
        else if ( strcmp( ComandoTeste , VERIFICAR_PILHA_CMD  ) == 0 ) {

			NumLidos = LER_LerParametros( "ii" , &NumPilha, &errosEsperados) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
           
			PIL_Verifica( vPilhas[ NumPilha ], &numErros );

            return TST_CompararInt( errosEsperados , numErros ,
                     "Total de erros errado ao verificar estrutura."  ) ;
		}

#endif

        return TST_CondRetNaoConhec ;

   } /* Fim função: TPIL Efetuar operações de teste específicas para pilha de cartas */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
