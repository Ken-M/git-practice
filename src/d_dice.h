//ゾロ目加算法処理クラス By Ken-M
// 2001/06/09 

//許可するダイスの最大個数
//必要に応じて変更してください。
//普通は、５０個もあれば充分でしょう（笑）
#define MAX_D 10000


//インクルードファイル
#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;


//並べ替えの条件 for qsort関数
int comp(const void *data1, const void *data2)
{
    return (*(int *)data2 - *(int *)data1);
}


//【ぞろ目加算法クラス】－＊－＊－＊－＊－＊－＊－＊－＊－＊－	
class zorome
{
protected:
	int dice_kosuu_base;	//初期基本ダイス個数
	int dice_kosuu_back;	//初期ダイス個数
	int dice_men;			//ダイスの幅
	int dice_kosuu;			//現在最大ダイスナンバー
	int dice[MAX_D + 1];	//ダイス
	int mode;				//追加個数
	int d_mode;				//表示モード
	int group_number ;		//グループ番号
	int check_group();		//生き残りグループチェック
	int r_kaisuu;			//ロール回数
	int r_rule;				//ダイス修正ルールのオン・オフ
	int dice_max ;			//必要だったダイス個数の最大
	double deme_sum;		//今までの出目合計
	double dicekosuu_sum;	//ダイス合計個数

	double dice_cast();						//ダイスを振る
	void dice_disp();						//ダイス表示
	int add_dice();							//ダイス追加処理
	void key_wait();						//ユーザーキー入力待ち
	void reset_stat();						//ステータスの初期化
	double run_dice_main();					//実行メイン

public:
																		//コンストラクタ
	zorome(int kosuu=2,int the_mode=0,int re_rule=0,int dice_m=6,int dispmode=2);
	double get_dice_sum();												//ダイス合計をもらう
	double get_dicekosuu_sum();											//ダイス合計個数をもらう
	double run_dice(int kosuu);											//個数を修正して実行
	double run_dice();													//基本個数で実行
	int get_dice_max();													//ダイス最大個数をもらう
};
//＊－＊－＊－＊－＊－＊－＊－＊－＊－＊－＊－＊－＊－＊－＊－




//キー入力を待つ
void zorome::key_wait()
{
	if (d_mode == 0){
	cout << "[ Press Any Key... ] \n" << endl ;
	_getch();
	}
	return;
}



//ダイス最大個数を貰う
int zorome::get_dice_max()
{
	return dice_max ;
}



//実行処理
double zorome::run_dice_main(){
	int i=1;
	reset_stat();

	while (i > 0){
		dice_cast();		//ダイスを振る
		i = check_group();	//グループ分け、生き残りグループ数をもらう
		key_wait();			//S-b-Sモードならユーザ待ち
	}

	if (i == -1) return -1;	//ダイスあふれの時は、強制終了。

	if (d_mode != 2) cout << "出目合計は" << deme_sum << "でした。" << endl;

	return deme_sum;
}


//個数を指定して実行
double zorome::run_dice(int kosuu){
	double re=0;
	dice_kosuu_back=kosuu ;
	re=run_dice_main();
	return re;
}


//個数を指定しないで実行（基本個数で実行）
double zorome::run_dice(){
	double re=0;
	dice_kosuu_back=dice_kosuu_base;
	re=run_dice_main();
	return re;
}


//出目合計をもらう
double zorome::get_dice_sum(){
	return deme_sum ;
}



//ダイス合計個数をもらう
double zorome::get_dicekosuu_sum(){
	return dicekosuu_sum;
}



//ステータスの初期化
void zorome::reset_stat()
{
	int i=0;
	dice_kosuu=dice_kosuu_back;
	deme_sum=0;
	r_kaisuu=0;
	group_number=2;
	dicekosuu_sum=0;
	dice_max = 0 ;

	for(i=0 ; i < MAX_D + 1 ; i++){
		if(i <= dice_kosuu)dice[i]=1000;
		else dice[i]=0;
	}

}



//コンストラクタ
zorome::zorome(int kosuu,int the_mode,int re_rule,int dice_m,int dispmode)
{
	d_mode=dispmode;
	dice_kosuu_base=kosuu - 1;
	dice_kosuu_back=kosuu - 1;
	mode=the_mode;
	r_rule=re_rule;
	dice_men=dice_m;

	time_t mytime;
	srand(time(&mytime));

	if(dice_men>100){
		cout << "１００面体より大きくはできません。１００面体に修正します。" << endl;
		dice_men=100;
	}

	if(dice_men<2){
		cout << "ダイス種類が不正です。" << endl;
		dice_men=2;
	}

	if(dice_kosuu_base > MAX_D - 1){
		cout << "ダイスの個数が異常です！\nダイス個数を" << MAX_D << "に修正します。" << endl;
		dice_kosuu_base = MAX_D - 1;
		dice_kosuu_back = MAX_D - 1;
	}

	if(mode > dice_men - 2){
		cout << "ダイスの振り足し個数が異常です。\n振り足し個数を" << dice_men - 2 << "個に修正します。" << endl;
		mode = dice_men - 2;
	}

	reset_stat();
}



//ダイスを振る
double zorome::dice_cast(){
	int i=0,d=0,roll_t=0;

	r_kaisuu++ ;

	for (i=0;i<=dice_kosuu;i++){
		if (dice[i] == 0) continue;

			d = rand() % dice_men;
			d++ ;
			dice[i] += d ;
			deme_sum += d ;
			roll_t++ ;

	}

	qsort(dice , dice_kosuu + 1 , sizeof(int) , comp);

	dice_disp();

	dicekosuu_sum += roll_t ;
	
	if (d_mode != 2){
	cout << endl ;
	cout << endl << "今回振ったダイス:" << roll_t  << endl ;
	}

	//ダイス個数最大のチェック＆書き換え
	if ( dice_max < roll_t ) dice_max=roll_t ;

	return deme_sum;
}



//ダイス表示
void zorome::dice_disp()
{
	int gf=group_number * 1000 ;
	int gn=0;
	int i=0;

	for (i=0;i<=dice_kosuu;i++)
	{

			//死んでいるダイスは表示しない
			if ( dice[i] == 0 )break ; 

			//グループ表示
			if ((dice[i] - (dice[i] % 1000))  != gf){
				gf -= 1000;
				gn++ ;
				if (d_mode != 2)
				cout << endl << "**Group No." << gn << "**" << endl;
			}
			else 
				if(d_mode != 2)cout << "," ;
			
			if (d_mode != 2)
			cout << dice[i] % 1000 ;
	}
}



//グループ確認
int zorome::check_group(){

	int live_flag = 0 ;
	int i = 0 ;
	int k = dice_kosuu ;
	dice_kosuu = -1 ;
	group_number = 1 ;

	for (i=0;i<=k;i++){

		//生きているダイス個数のカウント
		if ( dice[i] > 0 ) dice_kosuu++ ;
			else break ;

		//次につながっているとき。
		if (dice[i] == dice[i+1]){
			dice[i] = group_number * 1000;
			live_flag=1;
			continue;
		}

		//完全に切れたとき（単独決定）
		if (dice[i] != dice[i+1] && live_flag == 0){
			
			//ダイス修正ルール適用？
			if(k - 1 == i && r_kaisuu == 1 && group_number == 1 && r_rule == 1){
				if(d_mode != 2)cout << "組み合わせがないので " << i+1 << "番目の「" << dice[i] % 1000 << "」を「" << dice[i+1] % 1000 << "」に変更します。" << endl; 
				live_flag=1;
				deme_sum -= dice[i] - dice[i+1] ;
				dice[i] = group_number * 1000;
				continue ;
			}

			dice[i] = 0;
			continue ;
		}

		//切れた。けど、グループの最後。
		if (dice[i] != dice[i+1] && live_flag == 1){
			dice[i] = group_number *1000 ;
			live_flag=0;
			group_number += 1;
			continue ;
		}

		cout << "Group Check ERROR!! " << endl ;
		key_wait();
	}


	if (d_mode != 2)
	cout << "生き残ったグループ数:" << group_number - 1 << endl;


	//ダイス個数足し処理
	if (mode >= 1 ){
		if(add_dice() == -1)return -1;
	}

	if (d_mode != 2)cout << endl;

	return group_number - 1 ;
}



//ダイス追加処理
int zorome::add_dice(){

		int i;
		int j=-1;
		int k;

		for (i=1 ; i <= group_number - 1 ;i++){
			
			for (k=1;k<=mode;k++){

				//空き番号サーチ
				do{
				j++ ;

					//ダイスあふれチェック
					if(j>MAX_D - 1){
						if(d_mode != 2)
						{
						cout << endl ;
						cout << "ERROR!! 必要サイコロ数が" << MAX_D << "個を越えました。\n強制的に終了します！！\n" << endl;
						}
					dicekosuu_sum = -1 ;
					return -1 ;}
				
				}while ( dice[j] != 0 );

			dice[j] = i*1000 ;

			if(j>dice_kosuu)dice_kosuu = j ;

			}
		}
		return 0;
}

