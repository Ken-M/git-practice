//ゾロ目加算法実験プログラム　By Ken-M
// 2001/06/09 

#include <fstream>
#include <stdio.h>

#include "toukei.h"
#include "d_dice.h"

using namespace std;


//数字の入力
double input_number()
{
	char str[64];
	double n;
	cin >> str ;
	n = atof(str);
	return n;
}


//Main
void main(void)
{
	int dice_men;
	int dice_kosuu;
	int dice_add=0;
	int disp_mode;
	int re_roll=0;
	double kaisuu;
	double i;
	double sum=0;


	cout << "●ぞろ目加算法●" << endl ;

	//[設定入力]------------------------------------------------------------------------
	cout << "ダイスは何面体ですか？:" ;
	dice_men = (int)input_number();

	cout << "ダイスの個数は？:" ;
	dice_kosuu = (int)input_number();

	cout << "追加ダイス個数は？:" ;
	dice_add = (int)input_number();

	cout << "処理モードは？\n(0:Step-by-step , 1:Display Only , 2:Result Only ):";
	disp_mode = (int)input_number();

	if(dice_kosuu < dice_men + 1)
	{
	cout << "ダイス修正ルールを採用しますか？(ON:1 , OFF:0) :"  ;
	re_roll = (int)input_number();
	}

	cout << "試行回数は？:";
	kaisuu = input_number();
	//--------------------------------------------------------------[設定入力 ここまで]

	//オブジェクトの作成
	zorome roll(dice_kosuu,dice_add,re_roll,dice_men,disp_mode)	;	//ゾロ目加算本体
	toukei deme;													//出目合計
	toukei dice_s;													//ダイス個数合計
	toukei dice_m;													//ダイス個数最大

	//ファイルの準備
	ofstream data_file("data.dat");
	ofstream stat_file("stat.dat");

	for (i=1;i<=kaisuu;i++)
{

	//実行
	sum=roll.run_dice();

	if (sum>=0)
	{
		deme.add_data(sum);
		dice_s.add_data(roll.get_dicekosuu_sum());
		dice_m.add_data(roll.get_dice_max());

		printf("No. %8g -> 結果: %12g /DICE個数合計: %6g /DICE個数最大: %6d\n",i,sum,roll.get_dicekosuu_sum(),roll.get_dice_max()); 

		data_file << sum << endl;
	}

	else
	{
		cout << "No." << i << "\t-> ERROR." << endl ;
	}


}


	//結果の表示
	cout << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "有効回数：" << deme.get_kosuu() << endl << endl ;
	printf("結果の平均：%12f\n",deme.get_ave());
	printf("結果の分散：%10f\n",deme.get_sg());
	printf("結果の標準偏差：%10f\n\n",deme.get_sd());
	printf("平均ダイス個数合計：%8f\n\n",dice_s.get_ave());
	printf("平均ダイス個数最大：%8f\n",dice_m.get_ave());
	cout << endl;
	printf("結果　－＞　最大値: %-12g /最小値: %-12g\n",deme.get_max(),deme.get_min());
	cout << "ダイス個数合計－＞　最大値:" << dice_s.get_max() << " / 最小値:" << dice_s.get_min() << endl;
	cout << "ダイス個数最大－＞　最大値:" << dice_m.get_max() << " / 最小値:" << dice_m.get_min() << endl;

	stat_file << dice_kosuu << "D" << dice_men << "/追加:" << dice_add << "/修正:" << re_roll << endl; 
	stat_file << deme.get_kosuu() << endl;

	stat_file.setf(ios::fixed,ios::floatfield);
	stat_file << deme.get_ave()  << endl ;

	stat_file.setf(ios::dec,ios::basefield);
	stat_file << deme.get_max() << endl ;
	stat_file << deme.get_min() << endl ;

	cout << "\n\n[ Press Any Key to EXIT. ]" << endl;
	_getch();

	return ;
}


