//�ȈՓ��v�����N���X By Ken-M
// 2001/06/03 

#include <math.h>

class toukei{
protected:
	double sum;		//���v�l
	double kosuu;	//��
	double min;		//�ŏ��l
	double max;		//�ő�l
	double sq_sum;	//�Q��̍��v

public:
	void add_data(double d);	//�f�[�^�ǉ�
	double get_sum();			//���v�����炤
	double get_ave();			//���ς����炤
	double get_kosuu();			//�������炤
	double get_max();			//�ő�l�����炤
	double get_min();			//�ŏ��l�����炤
	double get_sg();			//���U��Ⴄ
	double get_sd();			//�W���΍���Ⴄ
	toukei();					//�R���X�g���N�^
};


//�R���X�g���N�^�i�ϐ��̏������j
toukei::toukei()
{
	sum=0;
	kosuu=0;
	sq_sum=0;
	max=0;
	min=0;
}

//�f�[�^�̒ǉ�
void toukei::add_data(double d)
{
	//�ŏ��̃f�[�^���A�ŏ��A�ő�̏����l�ɐݒ�
	if (kosuu== 0){
		max=d;
		min=d;
	}

	//�ő�l�A�ŏ��l�̊m�F
	if (min > d)min = d;
	if (max < d)max = d;

	//�l�����v���āA�f�[�^�����P���₷
	sum += d;
	sq_sum += pow(d,2.0) ;
	kosuu+=1;
}


//�ő�l�����炤
double toukei::get_max()
{
	return max;
}


//�ŏ��l�����炤
double toukei::get_min()
{
	return min;
}

//���v�l�����炤
double toukei::get_sum()
{
	return sum;
}

//���ϒl�����炤
double toukei::get_ave()
{
	return sum / kosuu;
}

//�f�[�^�������炤
double toukei::get_kosuu()
{
	return kosuu;
}

//���U�����炤
double toukei::get_sg()
{
	return ((sq_sum/kosuu) - pow(get_ave(),2.0));
}


//�W���΍������炤
double toukei::get_sd()
{
	return sqrt(get_sg());
}

