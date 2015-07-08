/***************************************************************************
 *  $MCI MÃƒÂ³dulo de implementaÃƒÂ§ÃƒÂ£o: MON Monte
 *
 *  Arquivo gerado:              MONTE.c
 *  Letras identificadoras:      MON
 *
 *  Nome da base de software:    ArcabouÃƒÂ§o para a automaÃƒÂ§ÃƒÂ£o de testes de programas redigidos em C
 *
 *  Projeto: Trabalho 2 - ProgramaÃƒÂ§ÃƒÂ£o Modular
 *  Autores: EG - Eric Grinstein
 JM - Jordana Mecler
 LW - Leonardo Wajnsztok
 *
 *  $HA HistÃƒÂ³rico de evoluÃƒÂ§ÃƒÂ£o:
 *     VersÃƒÂ£o      Autor            Data                ObservaÃƒÂ§ÃƒÂµes
 *     1.0       EG,JM,LW        17/abr/2015       InÃƒÂ­cio do desenvolvimento
 *
 ***************************************************************************/

#include "CARTA.h"
#include <stdlib.h>
#include <stdio.h>

#define MONTE_OWN
#include "MONTE.h"
#undef MONTE_OWN


/***********************************************************************
 *
 *  $TC Tipo de dados: MON Monte Pilha de Carta
 *
 *
 ***********************************************************************/

typedef struct MON_tagMonte
{
    PIL_tppPilha pPilha;
    /*Pontei para pilha de cartas*/
    
}MON_tpMonte ;


/*****  CÃƒÂ³digo das funÃƒÂ§ÃƒÂµes exportadas pelo mÃƒÂ³dulo  *****/

/***************************************************************************
 *
 *  FunÃƒÂ§ÃƒÂ£o: MON  &Criar monte a partir de pilha
 *  ****/

MON_tpCondRet MON_CriarMonte ( MON_tppMonte * pMonte , PIL_tppPilha pPilha)
{
    PIL_tpCondRet condRet;
    CAR_tppCarta pCartaAux;
    
    *pMonte = (MON_tpMonte *) malloc(sizeof(MON_tppMonte));
    if( *pMonte == NULL)
    {
        return MON_CondRetFaltouMemoria;
    }
    
    condRet = PIL_CriarPilhaVazia( &((*pMonte)->pPilha) );
    
    if ( condRet == PIL_CondRetFaltouMemoria )
    {
        return MON_CondRetFaltouMemoria ;
    }
    
    while( PIL_PopCarta( pPilha, &pCartaAux )  == PIL_CondRetOK )
    {
        PIL_PushCarta( (*pMonte)->pPilha, pCartaAux );
    }
    
    return MON_CondRetOK ;
}

/* Fim funÃƒÂ§ÃƒÂ£o: MON  &Criar monte */

/***************************************************************************
 *
 *  FunÃƒÂ§ÃƒÂ£o: MON  &Destruir monte
 *  ****/
MON_tpCondRet MON_DestruirMonte ( MON_tppMonte pMonte )
{
    
    if(pMonte->pPilha == NULL)
    {
        free(pMonte);
        return MON_CondRetOK;
    }
    
    PIL_DestruirPilha( pMonte->pPilha );
    free(pMonte);
    
    return MON_CondRetOK ;
}

/* Fim funÃƒÂ§ÃƒÂ£o: MON  &Destruir monte */

/***************************************************************************
 *
 *  FunÃƒÂ§ÃƒÂ£o: MON  &Pop carta do monte
 *  ****/

MON_tpCondRet MON_PopCartaMonte ( MON_tppMonte pMonte, CAR_tppCarta * pCarta )
{
    PIL_tpCondRet condRet;
    
    condRet = PIL_PopCarta( pMonte->pPilha, pCarta );
    
    if (condRet != PIL_CondRetOK)
    {
        return MON_CondRetMonteVazio;
    }
    
    return MON_CondRetOK ;
}

/* Fim funÃƒÂ§ÃƒÂ£o: MON  &Pop carta do monte */

/*************** Fim do mÃƒÂ³dulo de implementaÃƒÂ§ÃƒÂ£o: MON Monte *****************/