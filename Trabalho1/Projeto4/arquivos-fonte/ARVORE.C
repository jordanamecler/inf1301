
/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			eg - Eric Grinstein
*			jm - Jordana Mecler
*			lw - Leonardo Wajnsztok
*
***************************************************************************/

#include   <stdio.h>
#include   <stdlib.h>

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

 	typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */


	struct tgNoArvore * pProxFolha ;
	/* Ponteiro para próxima folha
	*
	*$EED Assertivas Estruturais
	*    se pProxFolha do nó X == NULL então ou X não é folha, ou função costura
	*    não foi utilizada, ou X é a última folha da costura */

	char Valor ;
	/* Valor do nó */

	char Chave ;
	/* Valor alfanumérico da chave*/


	} tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

typedef struct tgArvore {

	tpNoArvore * pNoRaiz ;
	/* Ponteiro para a raiz da Árvore */

	tpNoArvore * pNoCorr ;
	/* Ponteiro para o nó corrente da árvore */

} tpArvore ;

/*****  Dados encapsulados no módulo  *****/

static tpArvore * pArvore = NULL ;
/* Ponteiro para a cabeça da árvore */

/***** Protótipos das funções encapuladas no módulo *****/

static tpNoArvore * CriarNo( char ValorParm , char ChaveParm ) ;

static ARV_tpCondRet CriarNoRaiz( char ValorParm , char ChaveParm ) ;

static void DestroiArvore( tpNoArvore * pNo ) ;

static int ComparaFolhasAlf( const void * vNo1, const void * vNo2) ;

static int ContaFolhas( tpNoArvore * pNo ) ; 

static void PreencheVetFolhas( tpNoArvore ** vetFolhas , tpNoArvore * pNo ,  int * posVetFolhas ) ;

static void ImprimeCostura( tpNoArvore * pPrimFolha ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar Árvore
*  ****/

ARV_tpCondRet ARV_CriarArvore( void )
{

	if ( pArvore != NULL )
	{
		ARV_DestruirArvore( ) ;
	} /* if */

	pArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
	if ( pArvore == NULL )
	{
		return ARV_CondRetFaltouMemoria ;
	} /* if */

	pArvore->pNoRaiz = NULL ;
	pArvore->pNoCorr = NULL ;

	return ARV_CondRetOK ;

} /* Fim função: ARV Criar Árvore */

/***************************************************************************
*
*  Função: ARV Destruir árvore
*  ****/

void ARV_DestruirArvore( void )
{

	if ( pArvore != NULL )
	{
		if ( pArvore->pNoRaiz != NULL )
		{
			DestroiArvore( pArvore->pNoRaiz ) ;
		} /* if */
		free( pArvore ) ;
		pArvore = NULL ;
	} /* if */

} /* Fim função: ARV Destruir árvore */

/***************************************************************************
*
*  Função: ARV Adicionar filho à  esquerda
*  ****/

ARV_tpCondRet ARV_InserirEsquerda( char ValorParm , char ChaveParm )
{

	ARV_tpCondRet CondRet ;

	tpNoArvore * pCorr ;
	tpNoArvore * pNo ;

	/* Tratar vazio, esquerda */

	CondRet = CriarNoRaiz( ValorParm , ChaveParm ) ;
	if ( CondRet != ARV_CondRetNaoCriouRaiz )
	{
		return CondRet ;
	} /* if */

	/* Criar nó à  esquerda de folha */

	pCorr = pArvore->pNoCorr ;
	if ( pCorr == NULL )
	{
		return ARV_CondRetErroEstrutura ;
	} /* if */

	if ( pCorr->pNoEsq == NULL )
	{
		pNo = CriarNo( ValorParm , ChaveParm ) ;
		if ( pNo == NULL )
		{
			return ARV_CondRetFaltouMemoria ;
		} /* if */
		pNo->pNoPai      = pCorr ;
		pCorr->pNoEsq    = pNo ;
		pArvore->pNoCorr = pNo ;

		return ARV_CondRetOK ;
	} /* if */

	/* Tratar nó folha à  esquerda */

	return ARV_CondRetNaoEhFolha ;

} /* Fim função: ARV Adicionar filho à  esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à  direita
*  ****/

ARV_tpCondRet ARV_InserirDireita( char ValorParm , char ChaveParm )
{

	ARV_tpCondRet CondRet ;

	tpNoArvore * pCorr ;
	tpNoArvore * pNo ;

	/* Tratar vazio, direita */

	CondRet = CriarNoRaiz( ValorParm , ChaveParm ) ;
	if ( CondRet != ARV_CondRetNaoCriouRaiz )
	{
		return CondRet ;
	} /* if */

	/* Criar nó a direita de folha */

	pCorr = pArvore->pNoCorr ;
	if ( pCorr == NULL )
	{
		return ARV_CondRetErroEstrutura ;
	} /* if */

	if ( pCorr->pNoDir == NULL )
	{
		pNo = CriarNo( ValorParm , ChaveParm ) ;
		if ( pNo == NULL )
		{
			return ARV_CondRetFaltouMemoria ;
		} /* if */
		pNo->pNoPai      = pCorr ;
		pCorr->pNoDir    = pNo ;
		pArvore->pNoCorr = pNo ;

		return ARV_CondRetOK ;
	} /* if */

	/* Tratar nó folha à  direita */

	return ARV_CondRetNaoEhFolha ;

} /* Fim função: ARV Adicionar filho à  direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
*  ****/

ARV_tpCondRet ARV_IrPai( void )
{

	if ( pArvore == NULL )
	{
		return ARV_CondRetArvoreNaoExiste ;
	} /* if */
	if ( pArvore->pNoCorr == NULL )
	{
		return ARV_CondRetArvoreVazia ;
	} /* if */

	if ( pArvore->pNoCorr->pNoPai != NULL )
	{
		pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
		return ARV_CondRetOK ;
	} else {
		return ARV_CondRetNohEhRaiz ;
	} /* if */

} /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à  esquerda
*  ****/

ARV_tpCondRet ARV_IrNoEsquerda( void )
{

	if ( pArvore == NULL )
	{
		return ARV_CondRetArvoreNaoExiste ;
	} /* if */

	if ( pArvore->pNoCorr == NULL )
	{
		return ARV_CondRetArvoreVazia ;
	} /* if */

	if ( pArvore->pNoCorr->pNoEsq == NULL )
	{
		return ARV_CondRetNaoPossuiFilho ;

	} /* if */

	pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
	return ARV_CondRetOK ;

} /* Fim função: ARV Ir para nó à  esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó a direita
*  ****/

ARV_tpCondRet ARV_IrNoDireita( void )
{

	if ( pArvore == NULL )
	{
		return ARV_CondRetArvoreNaoExiste ;
	} /* if */

	if ( pArvore->pNoCorr == NULL )
	{
		return ARV_CondRetArvoreVazia ;
	} /* if */

	if ( pArvore->pNoCorr->pNoDir == NULL )
	{
		return ARV_CondRetNaoPossuiFilho ;
	} /* if */

	pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
	return ARV_CondRetOK ;

} /* Fim função: ARV Ir para nó a direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
*  ****/

ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm )
{

	if ( pArvore == NULL )
	{
		return ARV_CondRetArvoreNaoExiste ;
	} /* if */
	if ( pArvore->pNoCorr == NULL )
	{
		return ARV_CondRetArvoreVazia ;
	} /* if */
	* ValorParm = pArvore->pNoCorr->Valor ;

	return ARV_CondRetOK ;

} /* Fim função: ARV Obter valor corrente */

/***************************************************************************
*
*  Função: ARV Costura Folhas Alfabeticamente
*  ****/

ARV_tpCondRet ARV_CosturaFolhasOrdemAlf( void )
{
	tpNoArvore ** pVetFolhas ;
	int tamVetFolhas ,
		posVetFolhas ,
		i ;

	if ( pArvore == NULL )
	{
		return ARV_CondRetArvoreNaoExiste ;
	} /* if */
	if ( pArvore->pNoCorr == NULL )
	{
		return ARV_CondRetArvoreVazia ;
	} /* if */

	tamVetFolhas = ContaFolhas( pArvore->pNoRaiz ) ;


	pVetFolhas = ( tpNoArvore ** ) malloc( tamVetFolhas * sizeof(tpNoArvore *) ) ;
	if(pVetFolhas == NULL)
	{
		return ARV_CondRetFaltouMemoria ;
	}

	posVetFolhas = 0 ;
	PreencheVetFolhas( pVetFolhas , pArvore->pNoRaiz , &posVetFolhas ) ;

	qsort(pVetFolhas, tamVetFolhas, sizeof(tpNoArvore *), ComparaFolhasAlf) ;

	for(i=0 ; i < tamVetFolhas-1 ; i++)
	{
		pVetFolhas[i]->pProxFolha = pVetFolhas[i+1] ;
	}
	
	pVetFolhas[i]->pProxFolha = NULL ;
	
	ImprimeCostura( pVetFolhas[0] ) ; 

	free(pVetFolhas) ;

	return ARV_CondRetOK ;

} /* Fim função: ARV Costura Folhas Alfabeticamente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó.
*     $P ChaveParm - chave a ser inserida no novo nó.
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarÃ£o nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

tpNoArvore * CriarNo( char ValorParm , char ChaveParm )
{

	tpNoArvore * pNo ;

	pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
	if ( pNo == NULL )
	{
		return NULL ;
	} /* if */

	pNo->pNoPai = NULL ;
	pNo->pNoEsq = NULL ;
	pNo->pNoDir = NULL ;
	pNo->Valor  = ValorParm ;
	pNo->pProxFolha = NULL ;
	pNo->Chave = ChaveParm ;
	return pNo ;

} /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no nó.
*     $P ChaveParm - chave a ser inserida no nó.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

ARV_tpCondRet CriarNoRaiz( char ValorParm , char ChaveParm )
{

	ARV_tpCondRet CondRet ;
	tpNoArvore * pNo ;

	if ( pArvore == NULL )
	{
		CondRet = ARV_CriarArvore( ) ;

		if ( CondRet != ARV_CondRetOK )
		{
			return CondRet ;
		} /* if */
	} /* if */

	if ( pArvore->pNoRaiz == NULL )
	{
		pNo = CriarNo( ValorParm , ChaveParm ) ;
		if ( pNo == NULL )
		{
			return ARV_CondRetFaltouMemoria ;
		} /* if */
		pArvore->pNoRaiz = pNo ;
		pArvore->pNoCorr = pNo ;

		return ARV_CondRetOK ;
	} /* if */

	return ARV_CondRetNaoCriouRaiz ;

} /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*     
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

void DestroiArvore( tpNoArvore * pNo )
{

	if ( pNo->pNoEsq != NULL )
	{
		DestroiArvore( pNo->pNoEsq ) ;
	} /* if */

	if ( pNo->pNoDir != NULL )
	{
		DestroiArvore( pNo->pNoDir ) ;
	} /* if */

	free( pNo ) ;

} /* Fim função: ARV Destruir a estrutura da árvore */

/***********************************************************************
*
*  $FC Função: ARV Verifica se é folha
*
*  $EAE Assertivas de entradas esperadas
*     pNo != NULL
*
*  $FV Valor retornado
*     1 caso pNo seja folha
*     0 caso contrário 
*
*
***********************************************************************/

int EhFolha( tpNoArvore * pNo )
{
	if ( pNo->pNoDir == NULL && pNo->pNoEsq == NULL)
	{
		return 1; /* É folha */
	} /* if */

	return 0; /* Não é folha */

} /* Fim função: ARV Verifica se é folha */

/***********************************************************************
*
*  $FC Função: ARV Compara valor de duas folhas alfabeticamente
*
*  $EAE Assertivas de entradas esperadas
*     vNo1 != NULL && vNo2 != NULL
*
*  $FV Valor retornado
*     1 caso a chave do primeiro nó seja maior que a do segundo
*     0 caso as chaves dos nós sejam iguais
*    -1 caso a chave do primeiro nó seja menor que a do segundo
*
*
***********************************************************************/

int ComparaFolhasAlf( const void * vNo1, const void * vNo2)
{

	tpNoArvore ** pNo1 = ( tpNoArvore ** ) vNo1;
	tpNoArvore ** pNo2 = ( tpNoArvore ** ) vNo2;

	if ( (*pNo1)->Chave < (*pNo2)->Chave )
	{
		return -1;
	}
	else if ((*pNo1)->Chave > (*pNo2)->Chave)
	{
		return 1;
	}
	else
	{
		return 0;
	}              

} /* Fim função: ARV Compara valor de duas folhas alfabeticamente */

/***********************************************************************
*
*  $FC Função: ARV Conta Folhas
*
*  $FV Valor retornado
*     Número de folhas abaixo do nó recebido 
*
*
***********************************************************************/

int ContaFolhas( tpNoArvore * pNo )
{
	if ( pNo == NULL )
	{
		return 0 ;
	}
	if ( EhFolha( pNo ) )
	{
		return 1 ;
	}

	return ContaFolhas( pNo->pNoDir )
		+ ContaFolhas( pNo->pNoEsq ) ;

} /* Fim função: ARV Conta Folhas */

/***********************************************************************
*
*  $FC Função: ARV PreencheVetFolhas 
*
*  $EP Parâmetros
*     $P vetFolhas - vetor que receberá as folhas da Árvore
*     $P pNo - Nó inicial da Árvore a ser percorrida
*	  $P posVetFolhas - Posição do vetor a ser retornada, pois 
*                       a próxima folha. Passado por referência,
*                       seu valor deve ser acrescido a cada 
*                       folha inserida.
*
*
***********************************************************************/

void PreencheVetFolhas( tpNoArvore ** vetFolhas , tpNoArvore * pNo ,  int * posVetFolhas )
{
	if ( pNo == NULL )
	{
		return ;
	}
	if ( EhFolha( pNo ) )
	{
		vetFolhas[ * posVetFolhas ] = pNo ;
		( * posVetFolhas ) = ( * posVetFolhas ) + 1 ;
		
		return ; 
	}

	PreencheVetFolhas( vetFolhas , pNo->pNoDir , posVetFolhas ) ;
	PreencheVetFolhas( vetFolhas , pNo->pNoEsq , posVetFolhas ) ;

	

} /* Fim função: ARV Conta Folhas */

/***********************************************************************
*
*  $FC Função: ARV Imprime Costura
*
*  $EP Parâmetros
*     $P pPrimFolha - Primeira folha da costura a ser impressa
*
*     
*
*
***********************************************************************/

void ImprimeCostura( tpNoArvore * pPrimFolha ) 
{
	tpNoArvore * pFolha ;

	pFolha = pPrimFolha ;

	printf("Folhas:");
	while ( pFolha != NULL )
	{
		printf( "%c, ", pFolha->Chave ) ;
		pFolha = pFolha->pProxFolha ;
	}
	printf("\n") ;
}  /* Fim função: ARV Imprime Costura  */


/********** Fim do módulo de implementação: ARV **********/
