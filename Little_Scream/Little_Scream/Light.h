#pragma once
class Player;
class Light
{
private:
    int playerLightHandle; //���C�g�n���h��
public:
    Light();
    ~Light();
    void setPlayerLight(Player player);     //���C�g��z�u
    void deletePlayerLight() { DeleteLightHandle(playerLightHandle); }      //���C�g���폜

private:
    const float LIGHT_RANGE = 40.0f;    //���C�g���͂�����
    const float ATTAN_1 = 0.05f;        //�������� 1
    const float ATTAN_2 = 0.02f;        //�������� 2
    const float ATTAN_3 = 0.0002f;      //�������� 3
};

