#pragma once
#include "Component.h"

enum enumState {
    IDLE_RIGHT,
    IDLE_LEFT,
    RUN_RIGHT,
    RUN_LEFT,
    JUMP_RIGHT,
    JUMP_LEFT,
    WALL_RIGHT,
    WALL_LEFT,
    FALL_RIGHT,
    FALL_LEFT
};
class PlayerControler :
    public Component
{
public:
    PlayerControler() {};
    ~PlayerControler() {};
    Animator* animator;
    BoxCollider* collider;
    enumState state;
    float gravity;
    float jumpPower;
    float speed;
    float wallJumpPower;
    bool isJump;
    bool isWall;
    bool isDive;
    bool dir;
    int diveTime;
    RECT groundRc;
    void Init();
    void Update();
    void Render();
    bool CheckGround();
    void DebugState();
};

