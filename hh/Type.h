#pragma once

enum ObjectType {
    PLAYER, //プレイヤー
    ENEMY, //敵
    BOX,   //ボックス
    Goal,   //ゴール
};

enum class EStateType {
    Patrolling,  // 徘徊
    Lookaround,     //周りを見る
    Turn // 中間地点のフェーズ（例：プレイヤーを見失った後の探索）
};

enum class PStateType {
    STAND,
    SNEAK,
    STANDEYE,
    SNEAKEYE,
};


enum class GameState {
    START,
    UPDATE,
    END,
};

enum class FadeState {
    NO_FADE,
    FADE_IN,
    FADE_OUT,
};
