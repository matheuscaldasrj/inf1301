/***************************************************************************
 *  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
 *
 *  Arquivo gerado:              TESTSEQFIM.C
 *  Letras identificadoras:      TSEQFIM
 *
 *  Autores:
 *       EG - Eric Grinstein
 *       JM - Jordana Mecler
 *       LW - Leonardo Wajnsztok
 *
 *
 *  $ED Descri��o do m�dulo
 *     Este m�dulo cont�m as fun��es espec�ficas para o teste do
 *     m�dulo sequ�ncia final.
 *
 *  $EIU Interface com o usu�rio pessoa
 *     Comandos de teste espec�ficos para testar o m�dulo monte:
 *
 *     =criar 
 *                   - chama a fun��o  SEQFIM_CriarSeqFim.
 *
 *     =preencher
 *                   - chama a fun��o SEQFIM_PreencheSeqFim.
 *                   Ir� preencher uma sequ�ncia final com 3 cartas previamente escolhidas
 *                   a partir de uma pilha criada com tais cartas.
 *
 *     =destruir
 *             - chama a fun��o SEQFIM_DestroiSeqFim.
 *
 ***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "SEQFIM.H"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_SEQFIM_CMD          "=criar"
#define     PREENCHER_SEQFIM_CMD      "=preencher"
#define     DESTRUIR_SEQFIM_CMD       "=destruir"

/* Ponteiro para sequencia final utilizado no teste */

SEQFIM_tppSeqFim pSeqFimDada = NULL;

/***********************************************************************
 *
 *  $FC Fun��o: TSEQFIM Efetuar opera��es de teste espec�ficas para Sequencia final
 *
 *  $ED Descri��o da fun��o
 *     Efetua os diversos comandos de teste espec�ficos para o m�dulo
 *     Sequencia final sendo testado.
 *
 *  $EP Par�metros
 *     $P ComandoTeste - String contendo o comando
 *
 *  $FV Valor retornado
 *     Ver TST_tpCondRet definido em TST_ESPC.H
 *
 ***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
    
    SEQFIM_tpCondRet CondRetObtido   = SEQFIM_CondRetOK ;
    SEQFIM_tpCondRet CondRetEsperada = SEQFIM_CondRetFaltouMemoria ;
    /* inicializa para qualquer coisa */
    
    PIL_tppPilha pilhaAux;
    CAR_tppCarta CartaAux1;
    CAR_tppCarta CartaAux2;
    CAR_tppCarta CartaAux3;
    
    int  NumLidos = -1 ;
    
    /* Testar SEQFIM Criar Sequencia final */
    
    if ( strcmp( ComandoTeste , CRIAR_SEQFIM_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = SEQFIM_CriarSeqFim ( &pSeqFimDada );
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao criar a sequencia final." );
        
    } /* fim ativa: Testar SEQFIM Criar Sequencia final */
    
    /* Testar SEQFIM Destroi Sequencia final */
    
    else if ( strcmp( ComandoTeste , DESTRUIR_SEQFIM_CMD  ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        
        CondRetObtido = SEQFIM_DestroiSeqFim ( pSeqFimDada ) ;

        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao tentar destruir sequencia final." );
        
    } /* fim ativa: Testar SEQFIM Destroi Sequencia final */
    
    /* Testar SEQFIM Preencher Sequencia final */
    
    else if ( strcmp( ComandoTeste , PREENCHER_SEQFIM_CMD ) == 0 )
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
        
        CondRetObtido = SEQFIM_PreencheSeqFim ( pSeqFimDada , pilhaAux );
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao tentar preencher sequencia final." );
        
    } /* fim ativa:  Testar SEQFIM Preencher Sequencia final */
    
    return TST_CondRetNaoConhec ;
    
} /* Fim fun��o: TSEQFIM Efetuar opera��es de teste espec�ficas para sequencia final */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
