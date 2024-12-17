#include "../model/hand.h"
#include "../model/yaku.h"
#include "../model/patterns.h"
#include "../utils/error.h"

void free_patterns(vec(Pattern *) patterns) {
    // for (u64 i = 0; i < vec_len(patterns); i++) {
    //     pattern_free(patterns[i]);
    // }
    vec_free(patterns);
}

int main() {
    purple();
    printf("[TEST Yakus 1]\n");
    reset();

    //lipeikou
    Hand *h = hand_from_string("789789m111222p33s");
    vec(Pattern *) patterns = hand_patterns(h);

    test(vec_len(patterns) >= 1, "Almost one pattern from 789789m111222p33s");
    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(lipeikou(pat) == 1, "789789m111222p33s is lipeikou");

    free_patterns(patterns);
    hand_free(h);

    //ryanpeikou
    h = hand_from_string("789789m123123p33s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(ryanpeikou(pat) == 3, "789789m123123p33s is ryanpeikou");

    free_patterns(patterns);
    hand_free(h);

    //pinfu
    // TODO

    //shanshoku_doujun
    h = hand_from_string("123m123p12355566s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(shanshoku_doujun(pat) == 2, "123m123p12355566s is shanshoku_doujun");

    free_patterns(patterns);
    hand_free(h);

    //ittsuu
    h = hand_from_string("123456789m111p99s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(ittsuu(pat) == 2, "123456789m111p99s is ittsuu");

    free_patterns(patterns);
    hand_free(h);

    //tanyao
    h = hand_from_string("222456777m222p88s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(tanyao(pat) == 1, "222456777m222p88s is tanyao");

    free_patterns(patterns);
    hand_free(h);

    //yakuhai
    // TODO

    //shousangen
    h = hand_from_string("111m222p555z666z77z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(shousangen(pat) == 2, "111m222p555z666z77z is shousangen");

    free_patterns(patterns);
    hand_free(h);

    //daisangen
    h = hand_from_string("111m22p555z666z777z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(daisangen(pat) == 13, "111m222p555z666z77z is daisangen");

    free_patterns(patterns);
    hand_free(h);

    //shousuushi
    h = hand_from_string("111m111z222z333z44z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(shousuushi(pat) == 13, "111m111z222z333z44z is shousuushi");

    free_patterns(patterns);
    hand_free(h);

    //daisuushi
    h = hand_from_string("11m111z222z333z444z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(daisuushi(pat) == 13, "11m111z222z333z444z is daisuushi");

    free_patterns(patterns);
    hand_free(h);

    //chanta
    h = hand_from_string("123789m111p11z777z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(chanta(pat) == 2, "123789m111p11z777z is chanta");

    free_patterns(patterns);
    hand_free(h);

    //junchan
    h = hand_from_string("123789m111p11789s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(junchan(pat) == 3, "123789m111p11789s is junchan");

    free_patterns(patterns);
    hand_free(h);

    //honroutou
    h = hand_from_string("111999m111p999s11z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(honroutou(pat) == 2, "111999m111p999s11z is honroutou");

    free_patterns(patterns);
    hand_free(h);

    //chinroutou
    h = hand_from_string("111999m111p11999s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(chinroutou(pat) == 13, "111999m111p11999s is chinroutou");

    free_patterns(patterns);
    hand_free(h);

    //tsuuiisou
    h = hand_from_string("11122233344455z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(tsuuiisou(pat) == 13, "11122233344455z is tsuuiisou");

    free_patterns(patterns);
    hand_free(h);

    //kokuushi_musou
    // TODO

    //chiitoitsu
    // TODO

    //toitoi
    h = hand_from_string("11122233344455z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(toitoi(pat) == 2, "11122233344455z is toitoi");

    free_patterns(patterns);
    hand_free(h);

    //sanankou
    h = hand_from_string("123m222333555s55z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(sanankou(pat) == 2, "123m222333555s55z is sanankou");

    free_patterns(patterns);
    hand_free(h);

    //suuankou
    h = hand_from_string("111222888444s55z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(suuankou(pat) == 13, "111222888444s55z is suuankou");

    free_patterns(patterns);
    hand_free(h);

    //sanshoku_doukou
    h = hand_from_string("111m111p11123455s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(sanshoku_doukou(pat) == 2, "111m111p11123455s is sanshoku_doukou");

    free_patterns(patterns);
    hand_free(h);

    //sankatsu
    // TODO

    //suukantsu
    // TODO

    //honitsu
    h = hand_from_string("111222333444m11z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(honitsu(pat) == 3, "111222333444m11z is honitsu");

    free_patterns(patterns);
    hand_free(h);

    //chinitsu
    h = hand_from_string("11122233344455m");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(chinitsu(pat) == 6, "11122233344455m is chinitsu");

    free_patterns(patterns);
    hand_free(h);

    //ryuuiisou
    h = hand_from_string("222333444666s66z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(ryuuiisou(pat) == 13, "222333444666s66z is ryuuiisou");

    free_patterns(patterns);
    hand_free(h);

    //churen_poutou
    // TODO

    return 0;
}
