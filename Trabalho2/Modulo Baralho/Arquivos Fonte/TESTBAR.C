/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTBAR.C
*  Letras identificadoras:      TBAR
*
*  Autores: 
*			eg - Eric Grinstein
*			jm - Jordana Mecler
*			lw - Leonardo Wajnsztok
*
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo baralho de cartas. É possível testar com esse módulo a 
*     criação de 10 baralhos de cartas (que serão armazenados internamente
*     em um vetor.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo baralho de cartas:
*
*     =criar  <int> - chama a função BAR_CriarBaralho, criando um baralho
*					  no slot dado pelo parâmetro fornecido.
*					  O baralho pode ser criada do slot 0 ao slot 9. 
*					  Qualquer número fornecido fora deste intervalo é tratado como parâmetro incorreto.
*					  O mesmo vale para os outros comandos de teste.
*     =preencher <int> <int> 
*                   - chama a função BAR_PreencherBaralho,
*					onde o primeiro parâmetro é o número da baralho
*					a ser alterado, o segundo é o número de naipes que
*					o baralho terá.
*     =pop <int>
*					- chama a função BAR_PopCarta,
*					onde o parâmetro se refere ao número da baralho a ser removido
*					seu topo. 
*     
*     =embaralhar <int> 
*                   - chama a função BAR_Embaralhar, onde o primeiro parâmetro
*                     se refere ao número da baralho a ser embaralhado.
*
*     =destroi <int>  - chama a função BAR_DestruirBaralho, onde o inteiro dado se refere ao
*                     número da baralho a ser destruído.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "CARTA.H"
#include    "BARALHO.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_BAR_CMD       "=criar"
#define     PREENCHER_CMD       "=preencher"
#define     POP_CMD				"=pop"
#define     EMBARALHAR_CMD		"=embaralhar"
#define     DESTROI_CMD         "=destruir"

/* Máximo de baralhos a serem testadas simultâneamente */

#define     MAX_BARS            10

BAR_tppBaralho vBaralhos[10];

/*****  Código das funcões exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TBAR Efetuar operações de teste específicas para baralho de cartas
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     baralho sendo testado.
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

         BAR_tpCondRet CondRetObtido   = BAR_CondRetOK ;
         BAR_tpCondRet CondRetEsperada = BAR_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
		 BAR_tpCondRet CondRetEsperadaCarta = BAR_CondRetOK ;

         

         char NaipeEsperado = '?'  ;
         char NaipeObtido   = '!'  ;  
         char NaipeDado     = '\0' ;

         int ValorEsperado = -1  ;
         int ValorObtido   = -2  ;  
         int ValorDado     = 0 ;

         int PosicaoBaralho = -1 ;
         int NumBaralho = -1 ;
         int NumLidos = -1 ;

         CAR_tppCarta CartaObtida ;
         CAR_tppCarta CartaDada ;

         TST_tpCondRet Ret ;

         /* Testar BAR Criar Baralho de Cartas */

         if ( strcmp( ComandoTeste , CRIAR_BAR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &NumBaralho  , 
                               &CondRetEsperada ) ;
            if ( NumLidos != 2 || NumBaralho >= MAX_BARS || NumBaralho < 0 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = BAR_CriarBaralho( &vBaralhos[NumBaralho] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar baralho." );

         } /* fim ativa: Testar BAR Criar Baralho de cartas*/

         /* Testar BAR Preencher baralho */

         else if ( strcmp( ComandoTeste , PREENCHER_CMD ) == 0 )
         {
			
            NumLidos = LER_LerParametros( "iii" ,
                               &NumBaralho , &ValorDado ,  &CondRetEsperada ) ;
            if ( NumLidos != 3 || NumBaralho >= MAX_BARS || NumBaralho < 0 )
            {
               return TST_CondRetParm ;
            } /* if */
		
			CondRetObtido = BAR_PreencherBaralho( vBaralhos[NumBaralho] , ValorDado );
			
   
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao preencher baralho" );

         } /* fim ativa: Testar BAR Preencher baralho */

      /* Testar BAR Pop Carta da Baralho */

         else if ( strcmp( ComandoTeste , POP_CMD ) == 0 )
         {			
            NumLidos = LER_LerParametros( "ii" ,
                               &NumBaralho , &CondRetEsperada ) ;
            if ( NumLidos != 2 || NumBaralho >= MAX_BARS || NumBaralho < 0 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = BAR_PopCarta( vBaralhos[NumBaralho] , &CartaObtida ) ;

			
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                            "Retorno errado ao operar 'pop' no baralho") ;

         } /* fim ativa: Testar BAR Pop Carta da Baralho */


        /* Testar BAR Embaralhar Baralho de cartas */

         else if ( strcmp( ComandoTeste , EMBARALHAR_CMD ) == 0 )
         {
			
            NumLidos = LER_LerParametros( "ii" ,
                               &NumBaralho , &CondRetEsperada ) ;
            if ( NumLidos != 2 || NumBaralho >= MAX_BARS || NumBaralho < 0 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = BAR_Embaralhar( vBaralhos[NumBaralho] ) ;
            return TST_CompararInt( CondRetEsperada , CondRetObtido,
												"Retorno errado ao embaralhar") ;
	

         } /* Fim ativa: Testar BAR Embaralhar Baralho de cartas*/

      /* Testar BAR Destruir baralho de cartas */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &NumBaralho , 
                               &CondRetEsperada ) ;
            if ( NumLidos != 2 || NumBaralho >= MAX_BARS || NumBaralho < 0 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = BAR_DestruirBaralho( vBaralhos[NumBaralho] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado destruir baralho." );

         } /* fim ativa: Testar BAR Destruir Baralho de Cartas */

      /* Testar BAR Destruir Baralho */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TBAR Efetuar operações de teste específicas para baralho de cartas */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
