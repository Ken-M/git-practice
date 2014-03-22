//簡易統計処理クラス By Ken-M
// 2001/06/03 

#include <math.h>

class toukei{
protected:
	double sum;		//合計値
	double kosuu;	//個数
	double min;		//最小値
	double max;		//最大値
	double sq_sum;	//２乗の合計

public:
	void add_data(double d);	//データ追加
	double get_sum();			//合計をもらう
	double get_ave();			//平均をもらう
	double get_kosuu();			//個数をもらう
	double get_max();			//最大値をもらう
	double get_min();			//最小値をもらう
	double get_sg();			//分散を貰う
	double get_sd();			//標準偏差を貰う
	toukei();					//コンストラクタ
};


//コンストラクタ（変数の初期化）
toukei::toukei()
{
	sum=0;
	kosuu=0;
	sq_sum=0;
	max=0;
	min=0;
}

//データの追加
void toukei::add_data(double d)
{
	//最初のデータを、最小、最大の初期値に設定
	if (kosuu== 0){
		max=d;
		min=d;
	}

	//最大値、最小値の確認
	if (min > d)min = d;
	if (max < d)max = d;

	//値を合計して、データ個数を１つ増やす
	sum += d;
	sq_sum += pow(d,2.0) ;
	kosuu+=1;
}


//最大値をもらう
double toukei::get_max()
{
	return max;
}


//最小値をもらう
double toukei::get_min()
{
	return min;
}

//合計値をもらう
double toukei::get_sum()
{
	return sum;
}

//平均値をもらう
double toukei::get_ave()
{
	return sum / kosuu;
}

//データ個数をもらう
double toukei::get_kosuu()
{
	return kosuu;
}

//分散をもらう
double toukei::get_sg()
{
	return ((sq_sum/kosuu) - pow(get_ave(),2.0));
}


//標準偏差をもらう
double toukei::get_sd()
{
	return sqrt(get_sg());
}

