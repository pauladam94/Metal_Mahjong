#include "../model/hand.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Hand 1]\n");
    reset();
    Hand *h1 = hand_from_string("123m2p3s1m3z");
    Hand *h2 = hand_from_string("123m234p333345s222z");
    Hand *h3 = hand_from_string("123m234p345789s22z");
    Hand *h4 = hand_from_string("11112233m234p333z");
    test(hand_is_complete(h2), "123m234p333345s222z is complete");
    test(!hand_is_complete(h1), "1123m2p3s3z is not complete");
    test(hand_is_complete(h3), "123m234p345789s22z is complete");

    test(hand_is_complete(h4), "11112233m234p333z is complete");

    hand_free(h1);
    hand_free(h2);
    hand_free(h3);
    hand_free(h4);
}
