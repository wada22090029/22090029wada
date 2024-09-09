#pragma once

class Player;
class ControlGemObject;
class CheckClear;

class Compass
{
private:
	VECTOR minDistance;			//�ڕW�Ƃ̍ŏ�����
	VECTOR pos;					//�R���p�X�̍��W
	bool target[STAGE_SIZE][STAGE_SIZE];	//�ڕW�Ƃ���I�u�W�F�N�g
	float objectDirection;		//�I�u�W�F�N�g�̌�������
	int model;					//�I�u�W�F�N�g���f�����f��
public:
	Compass();
	~Compass();
	//�ڕW�Ƃ���I�u�W�F�N�g�܂ł̋����Ɗp�x�����߂�
	void findObjectDistanceAndDirection(Player player, ControlGemObject ControlGemObject, CheckClear checkClear);

	//�Q�b�^�[�֐�
	float getObjectDirection() { return objectDirection; }
	int getModel() { return model; }
private:
	//�萔
	const VECTOR INITIALIZE_MIN_DISTANCE = VGet(1000.0f, 1000.0f, 1000.0f);	//�ŏ��ڕW���������l
	const float INITIALIZE_COMPAS_POSITION_Y = 5.0f;						//�R���p�Xy���W�̏����l
	const VECTOR COMPAS_MODEL_SIZE = VGet(0.001f, 0.001f, 0.001f);			//�R���p�X���f���T�C�Y
};

