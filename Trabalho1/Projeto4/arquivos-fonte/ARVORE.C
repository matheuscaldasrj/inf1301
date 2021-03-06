
/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo �rvore
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
*  $TC Tipo de dados: ARV Descritor do n� da �rvore
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

 	typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   � NULL sse o n� � raiz
               *   Se n�o for raiz, um de pNoEsq ou pNoDir de pNoPai do n�
               *   corrente apontam para o n� corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho � esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do n� X != NULL ent�o pNoPai de pNoEsq aponta para o n� X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho � direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do n� X != NULL ent�o pNoPai de pNoDir aponta para o n� X */


	struct tgNoArvore * pProxFolha ;
	/* Ponteiro para pr�xima folha
	*
	*$EED Assertivas Estruturais
	*    se pProxFolha do n� X == NULL ent�o ou X n�o � folha, ou fun��o�costura
	*    n�o foi utilizada, ou X � a �ltima folha da costura */

	char Valor ;
	/* Valor do n� */

	char Chave ;
	/* Valor alfanum�rico da chave*/


	} tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabe�a de uma �rvore
*
*
*  $ED Descri��o do tipo
*     A cabe�a da �rvore � o ponto de acesso para uma determinada �rvore.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a �rvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a �rvore em forma de co-rotina.
*
***********************************************************************/

typedef struct tgArvore {

	tpNoArvore * pNoRaiz ;
	/* Ponteiro para a raiz da �rvore */

	tpNoArvore * pNoCorr ;
	/* Ponteiro para o n� corrente da �rvore */

} tpArvore ;

/*****  Dados encapsulados no m�dulo  *****/

static tpArvore * pArvore = NULL ;
/* Ponteiro para a cabe�a da �rvore */

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static tpNoArvore * CriarNo( char ValorParm , char ChaveParm ) ;

static ARV_tpCondRet CriarNoRaiz( char ValorParm , char ChaveParm ) ;

static void DestroiArvore( tpNoArvore * pNo ) ;

static int ComparaFolhasAlf( const void * vNo1, const void * vNo2) ;

static int ContaFolhas( tpNoArvore * pNo ) ; 

static void PreencheVetFolhas( tpNoArvore ** vetFolhas , tpNoArvore * pNo ,  int * posVetFolhas ) ;

static void ImprimeCostura( tpNoArvore * pPrimFolha ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: ARV Criar �rvore
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

} /* Fim fun��o: ARV Criar �rvore */

/***************************************************************************
*
*  Fun��o: ARV Destruir �rvore
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

} /* Fim fun��o: ARV Destruir �rvore */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho � esquerda
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

	/* Criar n� � esquerda de folha */

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

	/* Tratar n� folha � esquerda */

	return ARV_CondRetNaoEhFolha ;

} /* Fim fun��o: ARV Adicionar filho � esquerda */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho � direita
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

	/* Criar n� a direita de folha */

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

	/* Tratar n� folha � direita */

	return ARV_CondRetNaoEhFolha ;

} /* Fim fun��o: ARV Adicionar filho � direita */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� pai
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

} /* Fim fun��o: ARV Ir para n� pai */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� � esquerda
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

} /* Fim fun��o: ARV Ir para n� � esquerda */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� a direita
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

} /* Fim fun��o: ARV Ir para n� a direita */

/***************************************************************************
*
*  Fun��o: ARV Obter valor corrente
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

} /* Fim fun��o: ARV Obter valor corrente */

/***************************************************************************
*
*  Fun��o: ARV Costura Folhas Alfabeticamente
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

} /* Fim fun��o: ARV Costura Folhas Alfabeticamente */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� da �rvore
*
*  $EP Par�metros
*     $P ValorParm - valor a ser inserido no novo n�.
*     $P ChaveParm - chave a ser inserida no novo n�.
*
*  $FV Valor retornado
*     Ponteiro para o n� criado.
*     Ser� NULL caso a mem�ria tenha se esgotado.
*     Os ponteiros do n� criado estarão nulos e o valor � igual ao do
*     par�metro.
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

} /* Fim fun��o: ARV Criar n� da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� raiz da �rvore
*
*  $EP Par�metros
*     $P ValorParm - valor a ser inserido no n�.
*     $P ChaveParm - chave a ser inserida no n�.
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

} /* Fim fun��o: ARV Criar n� raiz da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Destruir a estrutura da �rvore
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

} /* Fim fun��o: ARV Destruir a estrutura da �rvore */

/***********************************************************************
*
*  $FC Fun��o: ARV Verifica se � folha
*
*  $EAE Assertivas de entradas esperadas
*     pNo != NULL
*
*  $FV Valor retornado
*     1 caso pNo seja folha
*     0 caso contr�rio 
*
*
***********************************************************************/

int EhFolha( tpNoArvore * pNo )
{
	if ( pNo->pNoDir == NULL && pNo->pNoEsq == NULL)
	{
		return 1; /* � folha */
	} /* if */

	return 0; /* N�o � folha */

} /* Fim fun��o: ARV Verifica se � folha */

/***********************************************************************
*
*  $FC Fun��o: ARV Compara valor de duas folhas alfabeticamente
*
*  $EAE Assertivas de entradas esperadas
*     vNo1 != NULL && vNo2 != NULL
*
*  $FV Valor retornado
*     1 caso a chave do primeiro n� seja maior que a do segundo
*     0 caso as chaves dos n�s sejam iguais
*    -1 caso a chave do primeiro n� seja menor que a do segundo
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

} /* Fim fun��o: ARV Compara valor de duas folhas alfabeticamente */

/***********************************************************************
*
*  $FC Fun��o: ARV Conta Folhas
*
*  $FV Valor retornado
*     N�mero de folhas abaixo do n� recebido 
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

} /* Fim fun��o: ARV Conta Folhas */

/***********************************************************************
*
*  $FC Fun��o: ARV PreencheVetFolhas 
*
*  $EP Par�metros
*     $P vetFolhas - vetor que receber� as folhas da �rvore
*     $P pNo - N� inicial da �rvore a ser percorrida
*	  $P posVetFolhas - Posi��o do vetor a ser retornada, pois 
*                       a pr�xima folha. Passado por refer�ncia,
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

	

} /* Fim fun��o: ARV Conta Folhas */

/***********************************************************************
*
*  $FC Fun��o: ARV Imprime Costura
*
*  $EP Par�metros
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
}  /* Fim fun��o: ARV Imprime Costura  */


/********** Fim do m�dulo de implementa��o: ARV **********/
