/***************************************************************************
 *  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
 *
 *  Arquivo gerado:              TESTCAR.C
 *  Letras identificadoras:      TCAR
 *
 *  Autores:
 *			EG - Eric Grinstein
 *			JM - Jordana Mecler
 *			LW - Leonardo Wajnsztok
 *
 *
 *  $ED Descri��o do m�dulo
 *     Este m�dulo cont�m as fun��es espec�ficas para o teste do
 *     m�dulo carta.
 *
 *  $EIU Interface com o usu�rio pessoa
 *     Comandos de teste espec�ficos para testar o m�dulo carta:
 *
 *     =criar
 *                   - chama a fun��o CAR_CriarCarta,
 *                   o par�metro � a condi��o de retorno.
 *     =preenche <char> <int>
 *                   - chama a fun��o CAR_PreencheCarta,
 *					onde o primeiro par�metro � o naipe da carta a ser
 *					preenchida, o segundo seu valor e o terceiro � a condi��o de retorno.
 *     =excluir
 *					- chama a fun��o CAR_ExcluirCarta,
 *                  o par�metro � a condi��o de retorno.
 *
 *     =obternaipe
 *                   - chama a fun��o CAR_ObterNaipe,
 *                   o par�metro � a condi��o de retorno.
 *
 *     =obtervalor
 *                   - chama a fun��o CAR_ObterValor,
 *                   o par�metro � a condi��o de retorno.
 *
 *     =imprime
 *                    - chama a fun��o CAR_ImprimeCarta,
 *                    o par�metro � a condi��o de retorno.
 *
 ***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "CARTA.H"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_CAR_CMD       "=criar"
#define     PREENCHE_CMD        "=preenche"
#define     EXCLUIR_CMD         "=excluir"
#define     OBTERNAIPE_CMD		"=obternaipe"
#define     OBTERVALOR_CMD      "=obtervalor"
#define     IMPRIME_CMD         "=imprime"

/* Ponteiro para carta auxiliar utilizada no teste */

CAR_tppCarta CartaDada = NULL ;

/***********************************************************************
 *
 *  $FC Fun��o: TCAR Efetuar opera��es de teste espec�ficas para cartas
 *
 *  $ED Descri��o da fun��o
 *     Efetua os diversos comandos de teste espec�ficos para o m�dulo
 *     carta sendo testado.
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
    
    CAR_tpCondRet CondRetObtido   = CAR_CondRetOK ;
    CAR_tpCondRet CondRetEsperada = CAR_CondRetFaltouMemoria ;
    /* inicializa para qualquer coisa */
    
    
    
    char NaipeEsperado = '?'  ;
    char NaipeDado     = '\0' ;
    
    int ValorEsperado = -1  ;
    int ValorDado     = 0 ;

    int  NumLidos = -1 ;
    
    
    
    /* Testar CAR Criar carta */
    
    if ( strcmp( ComandoTeste , CRIAR_CAR_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = CAR_CriarCarta( &CartaDada ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao criar carta." );
        
    } /* fim ativa: Testar CAR Criar carta*/
    
    /* Testar CAR Preenche Carta */
    
    else if ( strcmp( ComandoTeste , PREENCHE_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "cii" ,
                                     &NaipeDado , &ValorDado , &CondRetEsperada ) ;
        if ( NumLidos != 3 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        
        CondRetObtido = CAR_PreencheCarta( CartaDada , NaipeDado , ValorDado ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao preencher carta" );
        
    } /* fim ativa: Testar CAR Preenche Carta */
    
    /* Testar CAR Excluir Carta */
    
    else if ( strcmp( ComandoTeste , EXCLUIR_CMD ) == 0 )
    {
    
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = CAR_ExcluirCarta( CartaDada ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                              "Retorno errado ao tentar excluir carta") ;
        
    } /* Testar CAR Obter Naipe da Carta */
    
    else if ( strcmp( ComandoTeste , OBTERNAIPE_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = CAR_ObterNaipe( CartaDada , &NaipeEsperado ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                              "Retorno errado ao obter naipe da carta") ;
        
    } /* Testar CAR Obter Naipe da Carta */
    
    /* Testar CAR Obter Valor da Carta */
    else if ( strcmp( ComandoTeste , OBTERVALOR_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = CAR_ObterValor( CartaDada , &ValorEsperado ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado obter valor da carta" ) ;
        
    } /* fim ativa: Testar CAR Obter Valor da Carta */
    
    /* Testar CAR Imprime Carta */
    else if ( strcmp( ComandoTeste , IMPRIME_CMD ) == 0 )
    {
        
        NumLidos = LER_LerParametros( "i" ,
                                     &CondRetEsperada ) ;
        
        if ( NumLidos != 1 )
        {
            return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = CAR_ImprimeCarta( CartaDada ) ;
        
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                               "Retorno errado ao imprimir carta" ) ;
    } /* fim ativa: Testar CAR Imprime Carta */
    
    /* Testar PIL Destruir Pilha */
    
    return TST_CondRetNaoConhec ;
    
} /* Fim fun��o: TCAR Efetuar opera��es de teste espec�ficas para cartas */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
