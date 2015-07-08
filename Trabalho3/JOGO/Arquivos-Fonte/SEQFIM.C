/***************************************************************************
 *
 *  $MCD Módulo de Implementação: SEQFIM  Sequência final
 *
 *  Arquivo gerado:              SEQFIM.C
 *  Letras identificadoras:      SEQFIM
 *
 *  Autores: Eric Grinstein,
 *           Jordana Mecler,
 *	    Leonardo Wajnsztok
 *
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#define SEQUENCIA_FINAL_OWN
#include "SEQFIM.H"
#undef SEQUENCIA_FINAL_OWN

/***********************************************************************
 *
 *  $TC Tipo de dados: SEQFIM Sequencia final
 *
 *
 ***********************************************************************/

typedef struct SEQFIM_tagSeqFim {
    
    PIL_tppPilha pPilha ;
    
} SEQFIM_tpSeqFim ;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: SEQFIM Criar Sequencia final
 *****/

SEQFIM_tpCondRet SEQFIM_CriarSeqFim ( SEQFIM_tppSeqFim * pSeqFim )
{
    PIL_tpCondRet PilRet ;
    
    *pSeqFim = ( SEQFIM_tpSeqFim * ) malloc( sizeof( SEQFIM_tppSeqFim ) ) ;
    if ( pSeqFim == NULL )
    {
        return SEQFIM_CondRetFaltouMemoria ;
    }
    
    PilRet = PIL_CriarPilhaVazia( &((*pSeqFim)->pPilha ));
    
    if ( PilRet == PIL_CondRetFaltouMemoria )
    {
        return SEQFIM_CondRetFaltouMemoria ;
    }
    
    return SEQFIM_CondRetOK ;
    
} /* Fim função: SEQFIM  Criar Sequencia final */

/***************************************************************************
 *
 *  Função: SEQFIM Destruir Sequencia final
 *****/

SEQFIM_tpCondRet SEQFIM_DestroiSeqFim ( SEQFIM_tppSeqFim pSeqFim )
{
	
	if( pSeqFim->pPilha != NULL )
	{
		PIL_DestruirPilha( pSeqFim->pPilha ) ;
	} /* if */
    
	free(pSeqFim);
    
    return SEQFIM_CondRetOK ;
    
}/* Fim função: SEQFIM Destruir Sequencia final */


/***************************************************************************
 *
 *  Função: SEQFIM Preencher Sequencia final
 *****/

SEQFIM_tpCondRet SEQFIM_PreencheSeqFim ( SEQFIM_tppSeqFim pSeqFim , PIL_tppPilha pPilha )
{

    CAR_tppCarta pCartaAux;

	if( pSeqFim == NULL )
	{
        return SEQFIM_CondRetSeqNaoExiste ;
    }
    
    while( PIL_PopCarta( pPilha, &pCartaAux )  == PIL_CondRetOK )
    {
        PIL_PushCarta( pSeqFim->pPilha, pCartaAux );
    }
    
    return SEQFIM_CondRetOK ;
    
}/* Fim função: SEQFIM Preencher Sequencia final */

/********** Fim do módulo de implementação: SEQFIM  Sequencia final  **********/