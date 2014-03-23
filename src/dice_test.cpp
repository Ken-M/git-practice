//�]���ډ��Z�@�����v���O�����@By Ken-M
// 2001/06/09 

#include <fstream>
#include <stdio.h>

#include "toukei.h"
#include "d_dice.h"

using namespace std;


//�����̓���
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


	cout << "������ډ��Z�@��" << endl ;

	//[�ݒ����]------------------------------------------------------------------------
	cout << "�_�C�X�͉��ʑ̂ł����H:" ;
	dice_men = (int)input_number();

	cout << "�_�C�X�̌��́H:" ;
	dice_kosuu = (int)input_number();

	cout << "�ǉ��_�C�X���́H:" ;
	dice_add = (int)input_number();

	cout << "�������[�h�́H\n(0:Step-by-step , 1:Display Only , 2:Result Only ):";
	disp_mode = (int)input_number();

	if(dice_kosuu < dice_men + 1)
	{
	cout << "�_�C�X�C�����[�����̗p���܂����H(ON:1 , OFF:0) :"  ;
	re_roll = (int)input_number();
	}

	cout << "���s�񐔂́H:";
	kaisuu = input_number();
	//--------------------------------------------------------------[�ݒ���� �����܂�]

	//�I�u�W�F�N�g�̍쐬
	zorome roll(dice_kosuu,dice_add,re_roll,dice_men,disp_mode)	;	//�]���ډ��Z�{��
	toukei deme;													//�o�ڍ��v
	toukei dice_s;													//�_�C�X�����v
	toukei dice_m;													//�_�C�X���ő�

	//�t�@�C���̏���
	ofstream data_file("data.dat");
	ofstream stat_file("stat.dat");

	for (i=1;i<=kaisuu;i++)
{

	//���s
	sum=roll.run_dice();

	if (sum>=0)
	{
		deme.add_data(sum);
		dice_s.add_data(roll.get_dicekosuu_sum());
		dice_m.add_data(roll.get_dice_max());

		printf("No. %8g -> ����: %12g /DICE�����v: %6g /DICE���ő�: %6d\n",i,sum,roll.get_dicekosuu_sum(),roll.get_dice_max()); 

		data_file << sum << endl;
	}

	else
	{
		cout << "No." << i << "\t-> ERROR." << endl ;
	}


}


	//���ʂ̕\��
	cout << endl;
	cout << "---------------------------------------------------------------------" << endl;
	cout << "�L���񐔁F" << deme.get_kosuu() << endl << endl ;
	printf("���ʂ̕��ρF%12f\n",deme.get_ave());
	printf("���ʂ̕��U�F%10f\n",deme.get_sg());
	printf("���ʂ̕W���΍��F%10f\n\n",deme.get_sd());
	printf("���σ_�C�X�����v�F%8f\n\n",dice_s.get_ave());
	printf("���σ_�C�X���ő�F%8f\n",dice_m.get_ave());
	cout << endl;
	printf("���ʁ@�|���@�ő�l: %-12g /�ŏ��l: %-12g\n",deme.get_max(),deme.get_min());
	cout << "�_�C�X�����v�|���@�ő�l:" << dice_s.get_max() << " / �ŏ��l:" << dice_s.get_min() << endl;
	cout << "�_�C�X���ő�|���@�ő�l:" << dice_m.get_max() << " / �ŏ��l:" << dice_m.get_min() << endl;

	stat_file << dice_kosuu << "D" << dice_men << "/�ǉ�:" << dice_add << "/�C��:" << re_roll << endl; 
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


