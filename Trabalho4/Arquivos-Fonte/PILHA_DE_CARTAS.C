/***************************************************************************
*
*  $MCD Módulo de Implementação: PIL  Pilha de Cartas
*
*  Arquivo gerado:          	PIL.C
*  Letras identificadoras:  	PIL
*
*  Autores: Eric Grinstein,
*       	Jordana Mecler,
*    	Leonardo Wajnsztok
*
***************************************************************************/

#include "lista.h"

#include <stdlib.h>
#include <stdio.h>

#define PILHA_DE_CARTAS_OWN
#include "PILHA_DE_CARTAS.H"
#undef PILHA_DE_CARTAS_OWN

#ifdef _DEBUG
#include "Generico.h"
#include "Conta.h"
#include "CESPDIN.H"
#endif

/* Definições encapsuladas no módulo */

/* Tipo referência para uma pilha de cartas */

typedef struct PIL_tagPilha {

#ifdef _DEBUG
	int tipo;
	int qtdNos;
#endif

	LIS_tppLista pListaCartas ;
	/*Ponteiro para lista que guardará as cartas*/
} PIL_tpPilha ;

/***** Protótipos das funções encapsuladas no módulo *****/

void ExcluirCarta( void * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/

#ifdef _DEBUG

PIL_tpCondRet PIL_Deturpa ( PIL_tppPilha pPilha , int acao )
{

	if( acao == 1 )
	{
		LIS_IrInicioLista( pPilha->pListaCartas );
		LIS_AvancarElementoCorrente( pPilha->pListaCartas , 1);
		LIS_LiberaElemCorr( pPilha->pListaCartas ) ;
	}
	else if( acao == 2 )
	{
		LIS_IrInicioLista( pPilha->pListaCartas );
		LIS_AvancarElementoCorrente( pPilha->pListaCartas , 1);
		LIS_AlteraSucessor( pPilha->pListaCartas ) ;
	}
	else if( acao == 3 )
	{
		LIS_IrInicioLista( pPilha->pListaCartas );
		LIS_AvancarElementoCorrente( pPilha->pListaCartas , 1);
		LIS_AlteraPredecessor( pPilha->pListaCartas ) ;
	}
	else if( acao == 4 )
	{
		LIS_IrInicioLista( pPilha->pListaCartas );
		LIS_AvancarElementoCorrente( pPilha->pListaCartas , 1);
		LIS_AtribuiLixoSucessor( pPilha->pListaCartas ) ;
	}
	else if( acao == 5 )
	{
		LIS_IrInicioLista( pPilha->pListaCartas );
		LIS_AvancarElementoCorrente( pPilha->pListaCartas , 1);
		LIS_AtribuiLixoPredecessor( pPilha->pListaCartas ) ;
	}
	else if( acao == 6 )
	{
		LIS_IrInicioLista( pPilha->pListaCartas );
		LIS_AvancarElementoCorrente( pPilha->pListaCartas , 1);
		LIS_AtribuiNULLCarta( pPilha->pListaCartas ) ;
	}
	else if( acao == 7 )
	{
		LIS_IrInicioLista( pPilha->pListaCartas );
		LIS_AvancarElementoCorrente( pPilha->pListaCartas , 1);
		LIS_AlteraTipoCarta( pPilha->pListaCartas ) ;
	}
	else if( acao == 8 )
	{
		LIS_IrInicioLista( pPilha->pListaCartas );
		LIS_AvancarElementoCorrente( pPilha->pListaCartas , 1);
		LIS_DestacaCarta( pPilha->pListaCartas ) ;
	}
	else if( acao == 9 )
	{
		LIS_IrInicioLista( pPilha->pListaCartas );
		LIS_AvancarElementoCorrente( pPilha->pListaCartas , 1);
		LIS_AtribuiNULLCorrente( pPilha->pListaCartas ) ;
	}
	else if( acao == 10 )
	{
		LIS_AtribuiNULLOrigem( pPilha->pListaCartas ) ;
	}
	return PIL_CondRetOK ;
}

PIL_tpCondRet PIL_Verifica ( PIL_tppPilha pPilha , int *numErros )
{
	LIS_tpCondRet retLis;
	CAR_tppCarta pCarta;
	int numCartasAntes;
	int i = 0;
	(*numErros) = 0;

	if( pPilha != NULL && pPilha->qtdNos > 0)
	{
		if( LIS_VerificaCorrenteNull( pPilha->pListaCartas ))
		{
			CNT_CONTAR("erro-no-corrente-nulo");
			(*numErros) ++;
		}
		else if (LIS_RetornaCorrente(pPilha->pListaCartas) == 'x')
		{
			CNT_CONTAR("erro-no-corrente-com-lixo");
			(*numErros) ++;
		}
	}
	else
	{
		CNT_CONTAR("ok-no-corrente-consistente");
	}
	retLis = LIS_IrInicioLista(pPilha->pListaCartas);
	if( retLis == 1 && pPilha->qtdNos == 0)
	{
		CNT_CONTAR("ok-pilha-existe-mas-nao-tem-nos");
	}

	//evita o problema da origem nula
	if( !LIS_VerificaCorrenteNull( pPilha->pListaCartas ))
	{
		numCartasAntes = pPilha->qtdNos;
		// nao entra quando um no eh destacado
		if(pPilha != NULL)
		{
			if(LIS_QtdNos(pPilha->pListaCartas) == numCartasAntes)
			{
				// Teste tipo da pilha e celula
				i=0;
				LIS_IrInicioLista(pPilha->pListaCartas);
				if(LIS_RetornaCorrente(pPilha->pListaCartas) != 'x')
				{
					do
					{
						i++;
						if(LIS_RetornaCorrente(pPilha->pListaCartas) != 'x')
						{
							retLis = LIS_ObterValor( pPilha->pListaCartas,(void **) &pCarta);
							if ( retLis == 0 && pCarta != NULL )
							{
								//printf("%c %d",CAR_ObterTipo(pCarta),i);
								if (pPilha->tipo == CAR_ObterTipo(pCarta))
								{
									CNT_CONTAR("ok-tipo-da-pilha-e-o-mesmo-dos-seus-nos");
								}
								else
								{
									CNT_CONTAR("erro-tipo-da-pilha-e-diferente-dos-seus-nos");
									(*numErros) ++;
								}
							}
						}
					}while((i < (pPilha->qtdNos))  &&  LIS_AvancarElementoCorrente( pPilha->pListaCartas, 1 ) == 0); //tirei -1 do qtdnos

					if( pPilha->qtdNos > 0)
					{
						CNT_CONTAR("ok-pilha-correta-quando-qtdNos-maior-0");

						/*Teste do sucessor altera*/

						LIS_IrInicioLista(pPilha->pListaCartas);
						i = 0 ;
						do
						{
							i++;
							if ( LIS_RetornaSucessor( pPilha->pListaCartas ) == NULL )
							{
								CNT_CONTAR("erro-sucessor-nulo-quando-nao-deveria");
								(*numErros) ++;
							}
							else
							{
								CNT_CONTAR("ok-sucessor-nao-nulo");
							}
							if (LIS_RetornaSucessor(pPilha->pListaCartas) == 'x')
							{
								CNT_CONTAR("erro-sucessor-com-lixo");
								(*numErros) ++;
							}
							else
							{
								CNT_CONTAR("ok-sucessor-sem-lixo");
							}
						} while( (i < (pPilha->qtdNos -1))  && LIS_AvancarElementoCorrente( pPilha->pListaCartas, 1 ) == 0);


						/*Teste do antecessor - lixo atribuído ou altera*/
						i = 0;
						LIS_IrFinalLista( pPilha->pListaCartas );
						do
						{
							i++;
							if ( LIS_RetornaAntecessor( pPilha->pListaCartas ) == NULL )
							{
								CNT_CONTAR("erro-antecessor-nulo-quando-nao-deveria");
								(*numErros) ++;
							}
							else 
							{
								CNT_CONTAR("ok-antecessor-nao-nulo");
							}
							if (LIS_RetornaAntecessor(pPilha->pListaCartas) == 'x')
							{
								CNT_CONTAR("erro-antecessor-com-lixo");
								(*numErros) ++;
							}
							else
							{
								CNT_CONTAR("ok-antecessor-sem-lixo");
							}
						} while((i < pPilha->qtdNos -1) && LIS_AvancarElementoCorrente( pPilha->pListaCartas, -1 ) == 0);


						/* Teste da carta corrente - altera */
						i=0;
						LIS_IrInicioLista( pPilha->pListaCartas );
						do
						{
							if(LIS_RetornaCorrente(pPilha->pListaCartas) != 'x')
							{
								if ( LIS_RetornaCartaCorrente(pPilha->pListaCartas) == NULL )
								{
									CNT_CONTAR("erro-carta-corrente-alterada");
									(*numErros) ++;
								}
								else
								{
									CNT_CONTAR("ok-carta-corrente-consistente");
								}
							}
						}while((i < pPilha->qtdNos -1)&& LIS_RetornaCorrente(pPilha->pListaCartas) != 'x' && LIS_AvancarElementoCorrente( pPilha->pListaCartas, 1 ) == 0);
					}
				}
			}

		}

		/*Teste Corrente Destacado*/
		numCartasAntes = pPilha->qtdNos;
		if (LIS_QtdNos(pPilha->pListaCartas) != numCartasAntes )
		{
			CNT_CONTAR("erro-no-corrente-destacado");
			(*numErros)++;
		}
		else
		{
			CNT_CONTAR("ok-no-corrente-encadeado");
		}
	}

	/*Teste Origem Nula*/
	if ( LIS_OrigemNula(pPilha->pListaCartas) && pPilha->qtdNos > 0 )
	{
		CNT_CONTAR("erro-origem-nula");
		(*numErros)++;
	}
	else
	{
		CNT_CONTAR("ok-origem-consistente");
	}

	return PIL_CondRetOK;
}

#endif

/***************************************************************************
*
*  Função: PIL Criar Pilha Vazia
*****/

PIL_tpCondRet PIL_CriarPilhaVazia( PIL_tppPilha * pPilha )
{
	LIS_tpCondRet condRet ;

	*pPilha = NULL ;

	*pPilha = ( PIL_tpPilha * ) malloc( sizeof( PIL_tpPilha ) ) ;
	if( *pPilha == NULL )
	{
		return PIL_CondRetFaltouMemoria ;
	} /* if */


	(*pPilha)->pListaCartas = NULL;
#ifdef _DEBUG

	(*pPilha)->tipo = 'c';
	(*pPilha)->qtdNos = 0;

#endif

	condRet = LIS_CriarLista( &((*pPilha)->pListaCartas) , ExcluirCarta ) ;

	if ( condRet == LIS_CondRetFaltouMemoria )
	{
		return PIL_CondRetFaltouMemoria ;
	}

#ifdef _DEBUG
	CED_MarcarEspacoAtivo(pPilha) ;
#endif

	return PIL_CondRetOK ;

} /* Fim função: PIL  &Criar Pilha Vazia */

/***************************************************************************
*
*  Função: PIL Destruir Pilha de Cartas
*****/

PIL_tpCondRet PIL_DestruirPilha( PIL_tppPilha pPilha )
{

	LIS_tpCondRet Ret ;

	if ( pPilha->pListaCartas == NULL )
	{
		return PIL_CondRetOK ;
	}


	Ret = LIS_DestruirLista( pPilha->pListaCartas ) ;

	if( Ret != LIS_CondRetOK )
	{
		return PIL_CondRetPilhaVazia ;

	} /* if */

	free(pPilha) ;

#ifdef _DEBUG
	CED_MarcarEspacoNaoAtivo(pPilha);
#endif

	return PIL_CondRetOK ;

}/* Fim função: PIL Destruir Pilha de Cartas */


/***************************************************************************
*
*  Função: PIL Push Carta
*****/

PIL_tpCondRet PIL_PushCarta( PIL_tppPilha pPilha , CAR_tppCarta pCarta )
{
	LIS_tpCondRet Ret ;


	LIS_IrFinalLista( pPilha->pListaCartas ) ;

	Ret = LIS_InserirElementoApos( pPilha->pListaCartas , pCarta ) ;
	if( Ret != LIS_CondRetOK )
	{
		return PIL_CondRetFaltouMemoria ;
	} /* if */

#ifdef _DEBUG
	pPilha->qtdNos++;
#endif

	return PIL_CondRetOK ;



}/* Fim função: PIL Push Carta */

/***************************************************************************
*
*  Função: PIL VerCarta
*****/

PIL_tpCondRet PIL_VerCarta( PIL_tppPilha pPilha , CAR_tppCarta * pCarta , int posicao )
{
	LIS_tpCondRet Ret ;

	if ( posicao < 0 )
	{
		return PIL_CondRetParamIncorreto ;
	}

	LIS_IrFinalLista( pPilha->pListaCartas ) ;

	Ret = LIS_AvancarElementoCorrente( pPilha->pListaCartas , - posicao ) ;

	if ( Ret == LIS_CondRetFimLista )
	{
		return PIL_CondRetFimPilha ;
	}

	if ( Ret == LIS_CondRetListaVazia )
	{
		return PIL_CondRetPilhaVazia ;
	}

	LIS_ObterValor( pPilha->pListaCartas , (void**)pCarta ) ;

	return PIL_CondRetOK ;

}/* Fim função: PIL VerCarta */

/***************************************************************************
*
*  Função: PIL PopCarta
*****/

PIL_tpCondRet PIL_PopCarta( PIL_tppPilha pPilha , CAR_tppCarta * pCarta )
{
	int valor ;
	char naipe ;

	PIL_tpCondRet condRet = PIL_VerCarta( pPilha , pCarta , 0 ) ;

	LIS_IrFinalLista( pPilha->pListaCartas ) ;

	if ( condRet != PIL_CondRetOK )
	{
		return condRet ;
	}


	CAR_ObterNaipe( *pCarta, &naipe );
	CAR_ObterValor( *pCarta, &valor );

	LIS_ExcluirElemento( pPilha->pListaCartas );

	/*LIS_ExcluirElemento irá destruir a carta junto do nó.
	É necessário que ela seja criada novamente*/

	CAR_CriarCarta( pCarta ) ;
	CAR_PreencheCarta( *pCarta , naipe, valor ) ;
#ifdef _DEBUG
	pPilha->qtdNos--;
#endif

	return PIL_CondRetOK ;

}/* Fim função: PIL Pop Carta */

/*****  Código das funções encapsuladas no módulo  *****/


void ExcluirCarta( void * pValor )
{
	CAR_ExcluirCarta( (CAR_tppCarta) pValor ) ;

#ifdef _DEBUG
	CED_MarcarEspacoNaoAtivo(pValor);
#endif
}


/********** Fim do módulo de implementação: PIL  Pilha de cartas  **********/
