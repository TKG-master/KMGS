#pragma once

enum ObjectType {
    PLAYER, //プレイヤー
    ENEMY, //敵
    BOX,   //ボックス
    Goal,   //ゴール
};

enum class EStateType {
    Patrolling,     //徘徊
    Lookaround,     //周りを見る
    Turn,            //敵の向きを戻す
    Fixed,
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
