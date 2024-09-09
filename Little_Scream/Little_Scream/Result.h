#pragma once

class CheckDevice;
class ControlSound;

class Result
{
private:
    int select;         //�I��
    int gameOverImg;    //�Q�[���I�[�o�[���̉摜
    int gameClearImg;   //�Q�[���N���A���̉摜
    bool pushFlg;       //�A���ŉ����Ȃ��悤�ɂ��邽�߂̃t���O
public:
    Result();
    ~Result();
    void selectCommand(int& scene,CheckDevice checkDevice,ControlSound& sound);     //�I������

    //�Q�b�^�[�֐�
    int getSelectCommand() { return select; }
    int getGameOverImg() { return gameOverImg; }
    int getGameClearImg() { return gameClearImg; }
};

