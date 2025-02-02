#pragma once

enum ObjectType {
    PLAYER, //プレイヤー
    ENEMY, //敵
    BOX,   //ボックス
    PPLATE, //音が出る床
    Goal,   //ゴール
    BOOK,
};

enum class EStateType {
    Patrolling,     //徘徊
    Fixed,          //警戒右向き
    FixedLeft,      //警戒左向き
    Turn,            //敵の向きをかえる
    Bookconnection, //本を読むまで
    BookRead,       //本を読んでるとき
    Serch,          //探しに来るとき
    Back,
};

enum class PStateType {
    STAND,
    SNEAK,
    STIKY,
    STANDEYE,
    SNEAKEYE,
};
