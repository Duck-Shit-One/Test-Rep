
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define DICE_MAX		( 10 )

/**
 * コードを整数値に変換(0-9)
 * 
 * @param	c
 * @return	(int)
 */
int toint( int c )
{
	if( c < '0' || c > '9' )
	{
		c = 0;
	}
	else
	{
		c -= 0x30;
	}
	return c;
}

/**
 * コードを整数値に変換(1-6)
 * 
 * @param	c
 * @return	(int)
 */
int toint_dice( int c )
{
	if( c < '1' || c > '6' )
	{
		c = 0;
	}
	else
	{
		c -= 0x30;
	}
	return c;
}

/**
 * サイコロの個数チェック
 * 
 * @param	c
 * @return	(int)
 */
int chk_input( int c )
{
	int ret = 1;
	if( c < '0' || c > '9' )
	{
		ret = 0;
	}
	return ret;
}

/**
 * サイコロの目チェック
 * 
 * @param	c
 * @return	(int)
 */
int chk_input_dice( int c )
{
	int ret = c;
	if( c < '1' || c > '6' )
	{
		ret = 0;
	}
	return ret;
}

/**
 * キーボードから入力された文字を、1文字だけ返す
 * 
 * @return	(int)
 */
int get_onechar( void )
{
	int c;
	int d;
	
	c = getchar();
	d = c;
	while( d != 0x0a )
	{
		d = getchar();
	}
	return c;
}

/**
 * サイコロの個数入力を要求
 * 
 * @return	(int)
 */
int get_numdice( void )
{
	int c;
//	int chk = 0;
	
	while( 1 )
	{
		printf( "How many dice?>> " );
		c = get_onechar();
		if( chk_input( c ) )
		{
			break;
		}
		printf( "*** ERROR *** : Invalid input!\n\n" );
	}
	return toint( c );
}

/**
 * サイコロの目の入力を要求
 * 
 * @param	last
 * @return	(int)
 */
int get_dicenum( int last )
{
	int c;
	while( 1 )
	{
		printf( "Rest input= %d\n", last + 1 );
		printf( "Predict number= " );
		c = get_onechar();
		if( chk_input_dice( c ) )
		{
			break;
		}
		printf( "*** ERROR *** : Out of dice number!\n\n" );
	}
	return toint_dice( c );
}

/**
 * YESかNOの入力を要求
 * 
 * @return	(int)
 */
int get_yesno( void )
{
	int c;
	int ret = 1;
	printf( "[Y/N]>> " );
	c = get_onechar();
	if( c == 'n' || c == 'N' )
	{
		ret = 0;
	}
	return ret;
}

/**
 * サイコロの目を生成
 * 
 * @return	(int)
 */
int dice( void )
{
	int r = rand();
	int dice = (int)((((double)r / (double)(RAND_MAX - 1)) * 6) + 1);
	return dice;
}

/**
 * 乱数を初期化
 * 
 */
void init_rand( void )
{
	srand( (unsigned)time( NULL ) );
}

/**
 * サイコロを振る
 * 
 * @param	numdice
 * @param	dices
 */
void throw_dice( int numdice, int* dices )
{
	int idx;
	for( idx = 0; idx < numdice; idx++ )
	{
		dices[idx] = dice();
	}
}

/**
 * サイコロの目を表示
 * 
 * @param	numidce
 * @param	dices
 */
void show_dice( int numdice, int* dices )
{
	int idx;
	printf( "( " );
	for( idx = 0; idx < numdice; idx++ )
	{
		printf( "%d", dices[idx]);
		if( idx < numdice - 1 )
		{
			printf( ", " );
		}
	}
	printf( " )\n" );
}

/**
 * サイコロの予想目の入力を要求
 * 
 * @param	numdice
 * @param	dices
 */
void predict_dice( int numdice, int* dices )
{
	while( --numdice >= 0 )
	{
		dices[numdice] = get_dicenum( numdice );
	}
}

/**
 * 予想目と実際の目を比較して、正解数を返す
 * 
 * @param	numdice
 * @param	actual
 * @param	predict
 * @return	(int)
 */
int scoring( int numdice, int* actual, int* predict )
{
	int i, j;
	int score = 0;
	for( i = 0; i < numdice; i++ )
	{
		for( j = 0; j < numdice; j++ )
		{
			if( actual[i] == predict[j] )
			{
				score = (score + 1);
			}
		}
	}
	return score;
}

/**
 * main関数
 * 
 */
int main( int argc, char* argv[] )
{
	int endgame = 0;			// ゲームループフラグ
	int numdice = 0;			// 使用するサイコロの個数
	int actual[DICE_MAX];		// 実際に出た目
	int predict[DICE_MAX];		// 予想した目
	int score = 0;				// スコア
	int total = 0;				// トータルスコア
	int round = 0;				// プレイ回数
	
	while( !endgame )
	{
		int com;
		int idx;
		
		// サイコロの数を入力
		if( numdice == 0 )
		{
			++round;
			system( "cls" );
			printf( "Game Starting...\n" );
			printf( "Round %d\n\n", round );
			while( numdice < 2 )
			{
				printf( "Two dice are required at lease!\n" );
				numdice = get_numdice();
			}
			
			// 乱数の初期化
			init_rand();
		}
		
		// 予想目の入力を要求
		printf( "Please predict...\n\n" );
		predict_dice( numdice, predict );
		printf( "Predict dice= " );
		show_dice( numdice, predict );
		
		// サイコロを振る
		throw_dice( numdice, actual );
		printf( "Actual dice= " );
		show_dice( numdice, actual );
		
		// スコア表示
		score = scoring( numdice, actual, predict );
		if( score == numdice )
		{
			score += 3;
		}
		printf( "===============================\n");
		printf( "Your score= %d\n", score );
		printf( "===============================\n");
		total += score;
		
		// 続行確認
		printf( "Try again?\n" );
		com = get_yesno();
		if( !com ) break;
		else numdice = 0;
	}
	
	system( "cls " );
	printf( "===============================\n");
	printf( "Play round= %d\n", round );
	printf( "Your total score= %d\n", total );
//	printf( "Your average score= %6.2f\n", (total / round) );
	printf( "===============================\n");
	printf( "End the game!\n\n" );
	return 0;
}
