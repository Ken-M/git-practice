//�]���ډ��Z�@�����N���X By Ken-M
// 2001/06/09 

//������_�C�X�̍ő��
//�K�v�ɉ����ĕύX���Ă��������B
//���ʂ́A�T�O������Ώ[���ł��傤�i�΁j
#define MAX_D 10000


//�C���N���[�h�t�@�C��
#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;


//���בւ��̏��� for qsort�֐�
int comp(const void *data1, const void *data2)
{
    return (*(int *)data2 - *(int *)data1);
}


//�y����ډ��Z�@�N���X�z�|���|���|���|���|���|���|���|���|���|	
class zorome
{
protected:
	int dice_kosuu_base;	//������{�_�C�X��
	int dice_kosuu_back;	//�����_�C�X��
	int dice_men;			//�_�C�X�̕�
	int dice_kosuu;			//���ݍő�_�C�X�i���o�[
	int dice[MAX_D + 1];	//�_�C�X
	int mode;				//�ǉ���
	int d_mode;				//�\�����[�h
	int group_number ;		//�O���[�v�ԍ�
	int check_group();		//�����c��O���[�v�`�F�b�N
	int r_kaisuu;			//���[����
	int r_rule;				//�_�C�X�C�����[���̃I���E�I�t
	int dice_max ;			//�K�v�������_�C�X���̍ő�
	double deme_sum;		//���܂ł̏o�ڍ��v
	double dicekosuu_sum;	//�_�C�X���v��

	double dice_cast();						//�_�C�X��U��
	void dice_disp();						//�_�C�X�\��
	int add_dice();							//�_�C�X�ǉ�����
	void key_wait();						//���[�U�[�L�[���͑҂�
	void reset_stat();						//�X�e�[�^�X�̏�����
	double run_dice_main();					//���s���C��

public:
																		//�R���X�g���N�^
	zorome(int kosuu=2,int the_mode=0,int re_rule=0,int dice_m=6,int dispmode=2);
	double get_dice_sum();												//�_�C�X���v�����炤
	double get_dicekosuu_sum();											//�_�C�X���v�������炤
	double run_dice(int kosuu);											//�����C�����Ď��s
	double run_dice();													//��{���Ŏ��s
	int get_dice_max();													//�_�C�X�ő�������炤
};
//���|���|���|���|���|���|���|���|���|���|���|���|���|���|���|




//�L�[���͂�҂�
void zorome::key_wait()
{
	if (d_mode == 0){
	cout << "[ Press Any Key... ] \n" << endl ;
	_getch();
	}
	return;
}



//�_�C�X�ő����Ⴄ
int zorome::get_dice_max()
{
	return dice_max ;
}



//���s����
double zorome::run_dice_main(){
	int i=1;
	reset_stat();

	while (i > 0){
		dice_cast();		//�_�C�X��U��
		i = check_group();	//�O���[�v�����A�����c��O���[�v�������炤
		key_wait();			//S-b-S���[�h�Ȃ烆�[�U�҂�
	}

	if (i == -1) return -1;	//�_�C�X���ӂ�̎��́A�����I���B

	if (d_mode != 2) cout << "�o�ڍ��v��" << deme_sum << "�ł����B" << endl;

	return deme_sum;
}


//�����w�肵�Ď��s
double zorome::run_dice(int kosuu){
	double re=0;
	dice_kosuu_back=kosuu ;
	re=run_dice_main();
	return re;
}


//�����w�肵�Ȃ��Ŏ��s�i��{���Ŏ��s�j
double zorome::run_dice(){
	double re=0;
	dice_kosuu_back=dice_kosuu_base;
	re=run_dice_main();
	return re;
}


//�o�ڍ��v�����炤
double zorome::get_dice_sum(){
	return deme_sum ;
}



//�_�C�X���v�������炤
double zorome::get_dicekosuu_sum(){
	return dicekosuu_sum;
}



//�X�e�[�^�X�̏�����
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



//�R���X�g���N�^
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
		cout << "�P�O�O�ʑ̂��傫���͂ł��܂���B�P�O�O�ʑ̂ɏC�����܂��B" << endl;
		dice_men=100;
	}

	if(dice_men<2){
		cout << "�_�C�X��ނ��s���ł��B" << endl;
		dice_men=2;
	}

	if(dice_kosuu_base > MAX_D - 1){
		cout << "�_�C�X�̌����ُ�ł��I\n�_�C�X����" << MAX_D << "�ɏC�����܂��B" << endl;
		dice_kosuu_base = MAX_D - 1;
		dice_kosuu_back = MAX_D - 1;
	}

	if(mode > dice_men - 2){
		cout << "�_�C�X�̐U�葫�������ُ�ł��B\n�U�葫������" << dice_men - 2 << "�ɏC�����܂��B" << endl;
		mode = dice_men - 2;
	}

	reset_stat();
}



//�_�C�X��U��
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
	cout << endl << "����U�����_�C�X:" << roll_t  << endl ;
	}

	//�_�C�X���ő�̃`�F�b�N����������
	if ( dice_max < roll_t ) dice_max=roll_t ;

	return deme_sum;
}



//�_�C�X�\��
void zorome::dice_disp()
{
	int gf=group_number * 1000 ;
	int gn=0;
	int i=0;

	for (i=0;i<=dice_kosuu;i++)
	{

			//����ł���_�C�X�͕\�����Ȃ�
			if ( dice[i] == 0 )break ; 

			//�O���[�v�\��
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



//�O���[�v�m�F
int zorome::check_group(){

	int live_flag = 0 ;
	int i = 0 ;
	int k = dice_kosuu ;
	dice_kosuu = -1 ;
	group_number = 1 ;

	for (i=0;i<=k;i++){

		//�����Ă���_�C�X���̃J�E���g
		if ( dice[i] > 0 ) dice_kosuu++ ;
			else break ;

		//���ɂȂ����Ă���Ƃ��B
		if (dice[i] == dice[i+1]){
			dice[i] = group_number * 1000;
			live_flag=1;
			continue;
		}

		//���S�ɐ؂ꂽ�Ƃ��i�P�ƌ���j
		if (dice[i] != dice[i+1] && live_flag == 0){
			
			//�_�C�X�C�����[���K�p�H
			if(k - 1 == i && r_kaisuu == 1 && group_number == 1 && r_rule == 1){
				if(d_mode != 2)cout << "�g�ݍ��킹���Ȃ��̂� " << i+1 << "�Ԗڂ́u" << dice[i] % 1000 << "�v���u" << dice[i+1] % 1000 << "�v�ɕύX���܂��B" << endl; 
				live_flag=1;
				deme_sum -= dice[i] - dice[i+1] ;
				dice[i] = group_number * 1000;
				continue ;
			}

			dice[i] = 0;
			continue ;
		}

		//�؂ꂽ�B���ǁA�O���[�v�̍Ō�B
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
	cout << "�����c�����O���[�v��:" << group_number - 1 << endl;


	//�_�C�X����������
	if (mode >= 1 ){
		if(add_dice() == -1)return -1;
	}

	if (d_mode != 2)cout << endl;

	return group_number - 1 ;
}



//�_�C�X�ǉ�����
int zorome::add_dice(){

		int i;
		int j=-1;
		int k;

		for (i=1 ; i <= group_number - 1 ;i++){
			
			for (k=1;k<=mode;k++){

				//�󂫔ԍ��T�[�`
				do{
				j++ ;

					//�_�C�X���ӂ�`�F�b�N
					if(j>MAX_D - 1){
						if(d_mode != 2)
						{
						cout << endl ;
						cout << "ERROR!! �K�v�T�C�R������" << MAX_D << "���z���܂����B\n�����I�ɏI�����܂��I�I\n" << endl;
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

