/***************************************************************************
*  $MCI Módulo de implementação: PRIN	Principal
*
*  Arquivo gerado:              PRINCIPAL.c
*  Letras identificadoras:      PRIN
*
*
*  Projeto: Trabalho 3 - Programação Modular
*  Autores: EG - Eric Grinstein
*           JM - Jordana Mecler
*           LW - Leonardo Wajnsztok
*
*  $HA Histórico de evolução:
*     Versão  Autor     Data     Observações
*     5     JM,LW    28/mai/2015 carregar jogo
*     4       JM	 27/mai/2015 salvar jogo
*     3    EG,JM,LW  21/mai/2015 criação das funções auxiliares de jogo
*     2    EG,JM,LW  19/mai/2015 criação da lista principal e de novo jogo
*     1    EG,JM,LW  15/mai/2015 início desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "LISTA.H"
#include "BARALHO.H"
#include "CARTA.H"
#include "MONTE.H"
#include "PILHA_DE_CARTAS.H"
#include "SEQFIM.H"
#include "SEQJOGO.H"
#include <conio.h>

#define TAM_NOME_ARQUIVO 20
#define TAM_X 30
#define TAM_Y 104

/***************************************************************************
 *
 *  Função: PRIN Criar Pilha
 *****/

void CriaPilha( PIL_tppPilha *pilha , BAR_tppBaralho baralho , int numCartas )
{
    CAR_tppCarta carta ;
    int i ;
    PIL_CriarPilhaVazia( pilha ) ;
    for( i=0 ; i<numCartas ; i++)
    {
        BAR_PopCarta( baralho , &carta ) ;
        PIL_PushCarta( *pilha , carta ) ;
    }
} /* Fim função: PRIN  Criar Pilha */

/***************************************************************************
 *
 *  Função: PRIN Criar Montes
 *****/

void CriarMontes( MON_tppMonte monte[] , BAR_tppBaralho baralho )
{
    int i;
    PIL_tppPilha pilhasAux[5];
    
    for( i = 0 ; i < 5 ; i++ )
    {
        CriaPilha( &pilhasAux[i] , baralho, 10 );
        MON_CriarMonte( &monte[i] , pilhasAux[i] );
        PIL_DestruirPilha(pilhasAux[i]) ;
    }
} /* Fim função: PRIN  Criar Montes */

/***************************************************************************
 *
 *  Função: PRIN Criar SeqsJogo
 *****/

void CriarSeqsJogo( SEQJ_tppSeqJ seqsJogo[] ,BAR_tppBaralho baralho )
{
    int i;
    int numCartas;
    PIL_tppPilha pilhasAux[10];
    
    for( i = 0 ; i < 10 ; i++ )
    {
        if ( i < 4 ) numCartas = 6;
        else numCartas = 5;
        
        CriaPilha( &pilhasAux[i] , baralho, numCartas );
        SEQJ_CriarSeqJogo( &seqsJogo[i] , pilhasAux[i] );
        PIL_DestruirPilha(pilhasAux[i]) ;
    }
}  /* Fim função: PRIN  Criar SeqsJogo */

/***************************************************************************
 *
 *  Função: PRIN Criar SeqsFinais
 *****/

void CriarSeqsFinais( SEQFIM_tppSeqFim seqsFinais[] )
{
    int i ;
    
    for( i = 0 ; i < 5 ; i++ )
    {
        SEQFIM_CriarSeqFim( &seqsFinais[i] );
    }
    
}  /* Fim função: PRIN  Criar SeqsFinais */

/***************************************************************************
 *
 *  Função: PRIN Excluir Lista
 *****/

void ExcluirLista( void * pLista )
{
    LIS_DestruirLista( (LIS_tppLista) pLista );
} /* Fim função: PRIN  Excluir Lista */

/***************************************************************************
 *
 *  Função: PRIN Excluir Monte
 *****/

void ExcluirMonte( void * pMonte )
{
    MON_DestruirMonte( (MON_tppMonte) pMonte );
} /* Fim função: PRIN  Excluir Monte */

/***************************************************************************
 *
 *  Função: PRIN Excluir SeqJogo
 *****/

void ExcluirSeqJogo( void * pSeqJogo )
{
    SEQJ_DestroiSequencia( (SEQJ_tppSeqJ) pSeqJogo );
} /* Fim função: PRIN  Excluir SeqJogo */

/***************************************************************************
 *
 *  Função: PRIN Excluir SeqFim
 *****/

void ExcluirSeqFim( void * pSeqFim )
{
    SEQFIM_DestroiSeqFim( (SEQFIM_tppSeqFim) pSeqFim );
} /* Fim função: PRIN  Excluir SeqFim */

/***************************************************************************
 *
 *  Função: PRIN Excluir Baralho
 *****/

void ExcluirBaralho( void * pBaralho )
{
    BAR_DestruirBaralho( (BAR_tppBaralho) pBaralho);
} /* Fim função: PRIN  Excluir Baralho */

/***************************************************************************
 *
 *  Função: PRIN Novo Jogo
 *****/

int novoJogo ( LIS_tppLista * listaPrincipal)
{
    int numNaipes ;
    int i ;
    LIS_tppLista listaMonte = NULL;
    LIS_tppLista listaBaralho = NULL;
    LIS_tppLista listaSeqJogo = NULL;
    LIS_tppLista listaSeqFim = NULL;
    BAR_tppBaralho baralho = NULL;
    MON_tppMonte montes[5] ;
    SEQJ_tppSeqJ seqsJogo[10] ;
    SEQFIM_tppSeqFim seqsFinais[8] ;
    CAR_tppCarta carta;
    
    printf( "Escolha o numero de naipes [1-4]:\n" ) ;
    scanf( "%d", &numNaipes ) ;
    while (getchar() != '\n');
    while( numNaipes < 1 || numNaipes > 4 )
    {
        printf("Numero de naipes invalido\n") ;
        
        printf( "Escolha o numero de naipes [1-4]:\n" ) ;
        scanf( "%d", &numNaipes ) ;
        while (getchar() != '\n');
    }
    
    LIS_CriarLista( listaPrincipal , ExcluirLista ) ;
    LIS_CriarLista( &listaMonte , ExcluirMonte ) ;
    LIS_CriarLista( &listaBaralho , ExcluirBaralho ) ;
    LIS_CriarLista( &listaSeqJogo , ExcluirSeqJogo ) ;
    LIS_CriarLista( &listaSeqFim , ExcluirSeqFim ) ;
    
    LIS_InserirElementoApos( * listaPrincipal , listaBaralho ) ;
    LIS_InserirElementoApos( * listaPrincipal , listaMonte ) ;
    LIS_InserirElementoApos( * listaPrincipal , listaSeqJogo ) ;
    LIS_InserirElementoApos( * listaPrincipal , listaSeqFim ) ;
    
    
    BAR_CriarBaralho( &baralho ) ;
    BAR_PreencherBaralho ( baralho , numNaipes ) ;
    BAR_Embaralhar( baralho ) ;
    LIS_InserirElementoApos( listaBaralho , baralho ) ;
    
    CriarMontes( montes , baralho ) ;
    for (i=0 ; i < 5 ; i++)
    {
        LIS_InserirElementoAntes( listaMonte , montes[i] ) ;
    }

    CriarSeqsJogo( seqsJogo, baralho ) ;
    for (i=0 ; i < 10 ; i++)
    {
        LIS_InserirElementoAntes( listaSeqJogo , seqsJogo[i] ) ;
    }
   
    CriarSeqsFinais( seqsFinais ) ;
    for (i=0 ; i < 4 ; i++)
    {
        LIS_InserirElementoAntes( listaSeqFim , seqsFinais[i] ) ;
    }
    
    return 1;
} /* Fim função: PRIN  Novo Jogo */

/***************************************************************************
 *
 *  Função: PRIN Captura Opcao
 *****/

int CapturaOpcao(int *SeqOrigem, int *SeqDestino, int *NumCartas)
{
    printf("Escolha a pilha origem (0-9), destino (0-9) e o numero de cartas\n");
    scanf(" %d %d %d", SeqOrigem, SeqDestino, NumCartas);
    while (getchar() != '\n');
    if( *SeqOrigem < 0 || *SeqOrigem > 9 )
    {
        return -1;
    } /* if */
    if (*SeqDestino < 0 || *SeqDestino > 9 )
    {
        return -1;
    } /* if */
    if (*NumCartas < 1 || *NumCartas > 12 )
    {
        return -1;
    } /* if */
    return 0;
} /* Fim função: PRIN  Captura Opcao */

/***************************************************************************
 *
 *  Função: PRIN Verifica Cartas Consecutivas
 *****/

int verificaCartasConsecutivas( CAR_tppCarta carta , CAR_tppCarta cartaAnt )
{
    int valorCarta ;
    int valorCartaAnt ;
    char naipeCarta ;
    char naipeCartaAnt ;
    
    CAR_ObterValor( carta, &valorCarta );
    CAR_ObterNaipe( carta, &naipeCarta );
    
    CAR_ObterValor( cartaAnt, &valorCartaAnt );
    CAR_ObterNaipe( cartaAnt, &naipeCartaAnt );
    
    if( valorCarta == (valorCartaAnt+1))
    {
        if( naipeCarta == naipeCartaAnt)
            return 2 ;
        else
            return 1;
    } /* if */
    return 0 ;
} /* Fim função: PRIN  Verifica Cartas Consecutivas */

/***************************************************************************
 *
 *  Função: PRIN Tratar Move Monte
 *****/

void tratarMoveMonte( LIS_tppLista listaPrincipal )
{
    int i ;
    LIS_tppLista ListaDeMontes ;
    MON_tppMonte monte ;
    CAR_tppCarta cartaAux ;
    LIS_tppLista ListaDeSeq ;
    SEQJ_tppSeqJ SeqAtual ;
    
    LIS_IrInicioLista( listaPrincipal ) ;
    LIS_AvancarElementoCorrente( listaPrincipal , 1 ) ; /* a lista de montes » o segundo
                                                         elemento da lista principal*/
    LIS_ObterValor( listaPrincipal , ( void **)&ListaDeMontes ) ;
    
    LIS_IrInicioLista( listaPrincipal ) ;
    LIS_AvancarElementoCorrente( listaPrincipal , 2 ) ; /* a lista de sequencias de jogo » o 3ô
                                                         elemento da lista principal*/
    LIS_ObterValor( listaPrincipal , ( void **)&ListaDeSeq );
    
    LIS_IrFinalLista( ListaDeMontes ) ;
    LIS_ObterValor( ListaDeMontes , ( void **)&monte ) ;
    
    LIS_IrInicioLista( ListaDeSeq ) ;
    LIS_ObterValor( ListaDeSeq , ( void **)&SeqAtual );
    
    for( i = 0 ; i < 10 ;i++)
    {
        LIS_ObterValor( ListaDeSeq , ( void** )&SeqAtual) ;
        if( totalCartasNaSeq( SeqAtual ) == 0 )
            return;
        LIS_AvancarElementoCorrente( ListaDeSeq, 1 ) ;
    }
    
    LIS_IrInicioLista( ListaDeSeq ) ;
    LIS_ObterValor( ListaDeSeq , ( void **)&SeqAtual );
    
    for( i = 0 ; i < 10 ; i++ )
    {
        SEQJ_ViraCarta(SeqAtual, 1);
        MON_PopCartaMonte ( monte, &cartaAux ) ;
        SEQJ_PushCartaSequencia( SeqAtual , cartaAux , 0) ;
        LIS_AvancarElementoCorrente( ListaDeSeq, 1 ) ;
        LIS_ObterValor( ListaDeSeq , ( void** )&SeqAtual) ;
    }
    LIS_ExcluirElemento( ListaDeMontes ) ;
} /* Fim função: PRIN Tratar Move Monte */

/***************************************************************************
 *
 *  Função: PRIN Tratar Move Sequencia
 *****/

int tratarMoveSequencia(LIS_tppLista listaPrincipal, int NumSeqOrigem, int NumSeqDestino, int NumCartas, int *numSeqFins)
{
    int i = 0 ;
    int verSeq ;
    CAR_tppCarta cartaAux ;
    CAR_tppCarta cartaAnt ;
    
    SEQJ_tpCondRet Ret ;
    
    PIL_tppPilha pilhaAux ;
    PIL_tppPilha pilhaFim ;
    
    LIS_tppLista ListaDeSeq ;
    SEQJ_tppSeqJ SeqOrigem ;
    SEQJ_tppSeqJ SeqDestino ;
    SEQFIM_tppSeqFim seqFim ;
    
    PIL_CriarPilhaVazia( &pilhaAux );
    
    LIS_IrInicioLista( listaPrincipal ) ;
    LIS_AvancarElementoCorrente( listaPrincipal , 2 ) ;
    LIS_ObterValor(listaPrincipal, (void**)&ListaDeSeq) ;
    
    LIS_IrInicioLista( ListaDeSeq ) ;
    LIS_AvancarElementoCorrente( ListaDeSeq , NumSeqOrigem ) ;
    LIS_ObterValor( ListaDeSeq, (void**)&SeqOrigem ) ;
    
    LIS_IrInicioLista( ListaDeSeq ) ;
    LIS_AvancarElementoCorrente( ListaDeSeq , NumSeqDestino ) ;
    LIS_ObterValor( ListaDeSeq, (void**)&SeqDestino ) ;
    
    if( SEQJ_PopCartaSequencia( SeqOrigem , &cartaAux) != 0 )
    {
        return 0;
    }
    SEQJ_PushCartaSequencia( SeqOrigem , cartaAux , 0 );
    
    if( totalCartasNaSeq( SeqOrigem ) < NumCartas )
    {
        return 0;
    }
    
    for( i = 0 ; i < NumCartas ; i++ )
    {
        SEQJ_PopCartaSequencia( SeqOrigem, &cartaAux ) ;
        
        PIL_PushCarta( pilhaAux , cartaAux ) ;
        
        if(i > 0)
        {
            verSeq = verificaCartasConsecutivas(cartaAux, cartaAnt); // ver
            if( verSeq != 2 )
            {
                while( PIL_PopCarta( pilhaAux, &cartaAux) == 0 )
                {
                    SEQJ_PushCartaSequencia( SeqOrigem , cartaAux , 0 ) ;
                }
                return 0;
            }
        }
        cartaAnt = cartaAux ;
    }
    
    Ret = SEQJ_PopCartaSequencia( SeqDestino, &cartaAnt ) ;
    
    verSeq = 2 ;
    if( Ret != 1 ) // nao entra se seq vazia
    {
        verSeq = verificaCartasConsecutivas(cartaAnt, cartaAux );
        SEQJ_PushCartaSequencia( SeqDestino, cartaAnt , 0) ;
    }
    
    if( verSeq > 0 )
    {
        for( i = 0 ; i < NumCartas ; i++ )
        {
            PIL_PopCarta( pilhaAux , &cartaAux ) ;
            
            SEQJ_PushCartaSequencia( SeqDestino , cartaAux , 0) ;
        }
        SEQJ_ViraCarta(SeqDestino, NumCartas);
        SEQJ_ViraCarta(SeqOrigem, -NumCartas);
        SEQJ_NumCartasViradas(SeqOrigem, &i);
        if ( i == 0 && (totalCartasNaSeq( SeqOrigem )>0) )
        {
            SEQJ_ViraCarta(SeqOrigem, 1);
        }
        if( SEQJ_VerificaSeqCompleta(SeqDestino ) == 0)
        {
            PIL_CriarPilhaVazia( &pilhaFim );
            SEQJ_ObtemPilhaSeqJ( SeqDestino ,  &pilhaFim );
            SEQFIM_CriarSeqFim( &seqFim );
            SEQFIM_PreencheSeqFim ( seqFim , pilhaFim );
            (*numSeqFins)++;
        }
    }
    else
    {
        for( i = 0 ; i < NumCartas ; i++ )
        {
            PIL_PopCarta( pilhaAux , &cartaAux ) ;
            SEQJ_PushCartaSequencia( SeqOrigem , cartaAux , 0) ;
        }
        return 0 ;
    }
    
    return 1 ;
} /* Fim função: PRIN Tratar Move Sequencia */

/***************************************************************************
 *
 *  Função: PRIN Clear Screen
 *****/

void clearScreen(void)
{
    system("cls");
} /* Fim função: PRIN Clear Screen */

/***************************************************************************
 *
 *  Função: PRIN Imprime Jogo
 *****/

void imprimeJogo(LIS_tppLista listaPrincipal, int numMontes, int numSeqFins)
{
    int i = 0, j = 0, k =0, z=0;
    
    LIS_tppLista listaSeqJogo;
    LIS_tppLista listaAux;
    SEQJ_tppSeqJ seqJogoAux;
    PIL_tppPilha pilhaAux;
    PIL_tppPilha pilhaAux2;
    CAR_tppCarta cartaAux;
    CAR_tppCarta matrizDisplay[10][6];
    CAR_tppCarta matrizNova[6][10];
    CAR_tpCondRet ret;
    SEQJ_tpCondRet retSeqJogo;
    int numCartasViradas;
    int valor;
    char naipe;
    
    clearScreen();
    
    LIS_IrInicioLista( listaPrincipal ) ;
    LIS_AvancarElementoCorrente( listaPrincipal , 2 ) ; /* a lista de sequencias de jogo » o 3ô
                                                         elemento da lista principal*/
    LIS_ObterValor( listaPrincipal , ( void **)&listaSeqJogo );
    
    PIL_CriarPilhaVazia( &pilhaAux );
    PIL_CriarPilhaVazia( &pilhaAux2 );
    SEQJ_CriarSeqJogo( &seqJogoAux, pilhaAux );
    
    LIS_IrInicioLista( listaSeqJogo );
    LIS_ObterValor( listaSeqJogo , (void **)&seqJogoAux);
    printf("************  PACIENCIA SPIDER  ************\n");
    printf("Montes: %d\n", numMontes);
    printf("Sequencias Completas: %d de 8\n\n", numSeqFins);
    for(i=0;i<10;i++)
    {
        printf("%d  ", i);
        SEQJ_NumCartasViradas( seqJogoAux , &numCartasViradas );
        j = totalCartasNaSeq( seqJogoAux );
        k = j - numCartasViradas;
        while (SEQJ_PopCartaSequencia(seqJogoAux, &cartaAux) == 0) {
            PIL_PushCarta(pilhaAux, cartaAux);
            while(PIL_PopCarta(pilhaAux, &cartaAux) == 0)
            {
                PIL_PushCarta(pilhaAux2, cartaAux);
            }
        }
        while(PIL_PopCarta(pilhaAux2, &cartaAux) == 0)
        {
            if( k > 0 )
            {
                printf("* ");
                k--;
            }
            else
            {
                CAR_ObterValor(cartaAux, &valor);
                CAR_ObterNaipe(cartaAux, &naipe);
                if( valor == 1 )
                {
                    printf(" A%c ", naipe);
                }
                else if( valor == 11 )
                    printf(" J%c ", naipe);
                else if( valor == 12 )
                    printf(" Q%c ", naipe);
                else if( valor == 13 )
                    printf(" K%c ", naipe);
                else
                    CAR_ImprimeCarta(cartaAux);
            }
            PIL_PushCarta(pilhaAux, cartaAux);
            while (PIL_PopCarta(pilhaAux, &cartaAux)==0) {
                SEQJ_PushCartaSequencia(seqJogoAux, cartaAux, 0);
            }
        }
        printf("\n");
        LIS_AvancarElementoCorrente(listaSeqJogo, 1);
        LIS_ObterValor( listaSeqJogo , (void**)&seqJogoAux);
    }
} /* Fim função: PRIN Imprime Jogo */

/***************************************************************************
 *
 *  Função: PRIN Ver Se Ganhou
 *****/

int verSeGanhou( LIS_tppLista listaPrincipal)
{
    int i=0;
    LIS_tppLista ListaSeqJogo;
    SEQJ_tppSeqJ SeqJogoAtual;
    
    LIS_IrInicioLista(listaPrincipal);
    LIS_AvancarElementoCorrente( listaPrincipal , 2 ) ; /* a lista de sequencias de jogo » o 3ô
                                                         elemento da lista principal*/
    LIS_ObterValor( listaPrincipal , ( void **)&ListaSeqJogo );
    
    LIS_IrInicioLista( ListaSeqJogo );
    LIS_ObterValor( ListaSeqJogo, (void**)&SeqJogoAtual);
    
    for(i=0;i<10;i++)
    {
        if(totalCartasNaSeq( SeqJogoAtual ) != 0)
        {
            return 1;
        }
        LIS_AvancarElementoCorrente(ListaSeqJogo, 1);
        LIS_ObterValor( ListaSeqJogo , ( void **)&SeqJogoAtual );
    }
    return 0;
} /* Fim função: PRIN Ver Se Ganhou */

/***************************************************************************
 *
 *  Função: PRIN Carrega Jogo Salvo
 *****/

int carregaJogoSalvo (LIS_tppLista * listaPrincipal, char arquivoSalvo[] , int *numMontes, int *numSeqFins )
{
    FILE *arqSalvo;
    int i=0, j=0, x=0,
    valor;
    char naipe;
    LIS_tppLista listaMonte = NULL;
    LIS_tppLista listaBaralho = NULL;
    LIS_tppLista listaSeqJogo = NULL;
    LIS_tppLista listaSeqFim = NULL;
    BAR_tppBaralho baralho = NULL;
    MON_tppMonte montes[5] ;
    SEQJ_tppSeqJ seqsJogo[10] ;
    SEQFIM_tppSeqFim seqsFinais[8] ;
    CAR_tppCarta cartaAux[104];
    PIL_tppPilha pilhaAux[15];
    int numCartas, numCartasViradas, numTotal=0;
    
	arqSalvo = fopen(arquivoSalvo, "r");

    if(arqSalvo == NULL )
    {
        printf("Arquivo nao existe \n");
        return 1;
    }
    for(i=0;i<15;i++)
    {
        PIL_CriarPilhaVazia( &pilhaAux[i] );
    }
    
    LIS_CriarLista( listaPrincipal , ExcluirLista ) ;
    
    LIS_CriarLista( &listaMonte , ExcluirMonte ) ;
    LIS_CriarLista( &listaBaralho , ExcluirBaralho ) ;
    LIS_CriarLista( &listaSeqJogo , ExcluirSeqJogo ) ;
    LIS_CriarLista( &listaSeqFim , ExcluirSeqFim ) ;
    
    LIS_InserirElementoApos( * listaPrincipal , listaBaralho ) ;
    LIS_InserirElementoApos( * listaPrincipal , listaMonte ) ;
    LIS_InserirElementoApos( * listaPrincipal , listaSeqJogo ) ;
    LIS_InserirElementoApos( * listaPrincipal , listaSeqFim ) ;
    
    LIS_IrInicioLista( *listaPrincipal );
    LIS_AvancarElementoCorrente( *listaPrincipal, 2 );
    LIS_ObterValor( *listaPrincipal, (void**)&listaSeqJogo);
    
    for(i=0;i<10;i++)
    {
        SEQJ_CriarSeqJogo( &seqsJogo[i] , pilhaAux[i] );
        LIS_InserirElementoApos( listaSeqJogo, seqsJogo[i]);
    }
    for(i=0;i<104;i++)
    {
        CAR_CriarCarta( &cartaAux[i]);
    }
    for(i=0;i<10;i++)
    {
        fscanf(arqSalvo, "%d %d ", &numCartas, &numCartasViradas);
        numTotal+=numCartas;
        for(j=0; j<numCartas;j++)
        {
            fscanf(arqSalvo, "%d%c ", &valor, &naipe);
            CAR_PreencheCarta( cartaAux[x], naipe, valor );
            SEQJ_PushCartaSequencia( seqsJogo[i], cartaAux[x] , 0 );
            x++;
        }
        SEQJ_ViraCarta( seqsJogo[i] , numCartasViradas-1 );
    }
    
    fscanf(arqSalvo, "%d", numMontes );
    
    LIS_IrInicioLista( *listaPrincipal );
    LIS_AvancarElementoCorrente( *listaPrincipal, 1 );
    LIS_ObterValor( *listaPrincipal, (void**)&listaMonte);

    
    for(i=0;i<(*numMontes);i++)
    {
        j=0;
        while( j < 10 )
        {
            fscanf(arqSalvo, "%d%c ", &valor, &naipe);
            CAR_PreencheCarta( cartaAux[x], naipe, valor );
            PIL_PushCarta( pilhaAux[i+10], cartaAux[x] );
            j++;
            x++;
        }
        MON_CriarMonte( &montes[i] , pilhaAux[i+10]);
    }
    
    for(i=0;i<(*numMontes);i++)
        LIS_InserirElementoApos( listaMonte, montes[i]);
    
	for(i=0;i<5;i++)
	{
		PIL_DestruirPilha( pilhaAux[i+10] );
	}

    fscanf(arqSalvo, "%d", numSeqFins);
    fclose(arqSalvo);
    return 0;
} /* Fim função: PRIN Carrega Jogo Salvo */

/***************************************************************************
 *
 *  Função: PRIN Salvar Jogo
 *****/

void SalvarJogo (LIS_tppLista listaPrincipal, int numMontes, int numSeqFins )
{
    char arquivo[TAM_NOME_ARQUIVO];
    FILE *arquivoSalvo = NULL;
    LIS_tppLista LisSeqJogo;
    LIS_tppLista LisMontes;
    SEQJ_tppSeqJ SeqJogoAtual;
    PIL_tppPilha pilhaAux;
    MON_tppMonte MonteAtual;
    CAR_tppCarta cartaAux;
    int i = 0;
    int numCartasViradas;
    int valor;
    char naipe;
    
    printf( "Digite o nome do arquivo a ser salvo: ex: JOGO1.txt\n" ) ;
    scanf(" %s", arquivo);
    arquivoSalvo = fopen(arquivo, "w");
	if( arquivoSalvo == NULL )
	{
		printf("Erro ao abrir arquivo\n");
		return;
	}
    
    PIL_CriarPilhaVazia( &pilhaAux );
    
    LIS_IrInicioLista(listaPrincipal);
    LIS_AvancarElementoCorrente(listaPrincipal, 2);
    LIS_ObterValor(listaPrincipal, (void**)&LisSeqJogo);
    
    LIS_IrInicioLista(LisSeqJogo);
    LIS_ObterValor(LisSeqJogo, (void**)&SeqJogoAtual);
    
    for(i=0;i<10;i++)
    {
        SEQJ_NumCartasViradas( SeqJogoAtual , &numCartasViradas );
        fprintf(arquivoSalvo, "%d ", totalCartasNaSeq( SeqJogoAtual));
        fprintf(arquivoSalvo, "%d ", numCartasViradas );
        while( totalCartasNaSeq( SeqJogoAtual ) > 0 )
        {
            SEQJ_PopCartaSequencia( SeqJogoAtual, &cartaAux );
            CAR_ObterValor(cartaAux, &valor);
            CAR_ObterNaipe(cartaAux, &naipe);
            PIL_PushCarta( pilhaAux, cartaAux );
        }
        while(PIL_PopCarta(pilhaAux, &cartaAux ) == 0)
        {
            CAR_ObterValor(cartaAux, &valor);
            CAR_ObterNaipe(cartaAux, &naipe);
            fprintf(arquivoSalvo, "%d%c ", valor, naipe);
        }
        fprintf(arquivoSalvo, "\n");
        LIS_AvancarElementoCorrente(LisSeqJogo, 1);
        LIS_ObterValor(LisSeqJogo, (void**)&SeqJogoAtual);
    }
    
    fprintf(arquivoSalvo, "%d\n", numMontes);
    
    LIS_IrInicioLista(listaPrincipal);
    LIS_AvancarElementoCorrente( listaPrincipal, 1);
    LIS_ObterValor(listaPrincipal, (void**)&LisMontes);
    
    LIS_IrInicioLista( LisMontes );
    LIS_ObterValor( LisMontes, (void**)&MonteAtual);
    
    for(i=0;i<numMontes;i++)
    {
        
        while( MON_PopCartaMonte( MonteAtual, &cartaAux) == 0)
        {
            CAR_ObterValor(cartaAux, &valor);
            CAR_ObterNaipe(cartaAux, &naipe);
            PIL_PushCarta(pilhaAux, cartaAux );
        }
        while(PIL_PopCarta(pilhaAux, &cartaAux ) == 0)
        {
            CAR_ObterValor(cartaAux, &valor);
            CAR_ObterNaipe(cartaAux, &naipe);
            fprintf(arquivoSalvo, "%d%c ", valor, naipe);
        }
        fprintf(arquivoSalvo, "\n");
        LIS_AvancarElementoCorrente(LisMontes, 1);
        LIS_ObterValor(LisMontes, (void**)&MonteAtual);
    }
    
    fprintf(arquivoSalvo, "%d\n", numSeqFins );
    fclose(arquivoSalvo);
} /* Fim função: PRIN Salvar Jogo */

int main (void)
{
    char arquivoSalvo[TAM_NOME_ARQUIVO] ;
    char opcaoEscolhida ;
    char caracterLido ;
    int SeqOrigem, SeqDestino, NumCartas;
    int retMoveSeq ;
    int retMoveMonte ;
    int numSeqFins = 0;
    int numMontes = 5;
    LIS_tppLista listaPrincipal = NULL;
    
    system("color 2f");
    
    printf( "Bem vindo ao paciencia spider.\n" ) ;
    printf( "Digite c para carregar um jogo salvou ou n para iniciar um novo jogo:\n" ) ;
    scanf(" %c", &opcaoEscolhida) ;
    while((opcaoEscolhida != 'c') && (opcaoEscolhida != 'n'))
    {
        printf( "Digite c para carregar um jogo salvou ou n para iniciar um novo jogo:\n" ) ;
        scanf(" %c", &opcaoEscolhida);
    }
    if( opcaoEscolhida == 'c' )
    {
        printf( "Digite o nome do arquivo a ser carregado: ex: JOGO1.txt\n" ) ;
        scanf( "%s", arquivoSalvo ) ;
        
        while( carregaJogoSalvo( &listaPrincipal, arquivoSalvo, &numMontes, &numSeqFins ) != 0)
		{
			printf( "Digite o nome do arquivo a ser carregado: ex: JOGO1.txt\n" ) ;
			scanf( "%s", arquivoSalvo ) ;
		}
    }
    else
    {
        novoJogo( &listaPrincipal ) ;
    }
    clearScreen();
    imprimeJogo( listaPrincipal , numMontes ,numSeqFins);
    
    printf("'t' para mover entre sequencias\n'm' para comprar do monte\n's' para salvar o jogo\n'q' para sair\n");
    scanf(" %c",&caracterLido);
    
    while( caracterLido != 's' && caracterLido != 'q' )
    {
        if( caracterLido == 't' )
        {
            if(CapturaOpcao(&SeqOrigem, &SeqDestino, &NumCartas) == 0)
            {
                retMoveSeq = tratarMoveSequencia(listaPrincipal, SeqOrigem, SeqDestino, NumCartas, &numSeqFins);
            } /* if */
            else
            {
                printf("Erro de leitura\n");
            }
        }
        if( caracterLido == 'm' )
        {
            if(numMontes > 0)
            {
                tratarMoveMonte( listaPrincipal ) ;
                numMontes--;
            }
            else
            {
                printf("Nao existem mais montes para mover\n") ;
            }
        }
        imprimeJogo( listaPrincipal ,numMontes ,numSeqFins );
        if( verSeGanhou(listaPrincipal) == 0)
        {
            clearScreen();
            printf("\n\n\n****** GANHOU ******\n\n");
            break;
        }
        printf("'t' para mover entre sequencias\n'm' para comprar do monte\n's' para salvar o jogo\n'q' para sair\n");
        scanf(" %c",&caracterLido);
    }
    if(caracterLido == 's')
    {
        SalvarJogo( listaPrincipal , numMontes, numSeqFins );
    }

	LIS_DestruirLista( listaPrincipal );

    return 0 ;
}

