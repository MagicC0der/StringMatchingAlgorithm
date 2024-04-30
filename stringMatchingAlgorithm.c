#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256

void buildFiniteAutomaton(char *pattern, int M, int FA[][NO_OF_CHARS]) {
    int state, x;

    for (state = 0; state <= M; ++state) {
        for (x = 0; x < NO_OF_CHARS; ++x)
            FA[state][x] = getNextState(pattern, M, state, x);
    }
}
int getNextState(char *pattern, int M, int state, int x) {
    if (state < M && x == pattern[state])
        return state + 1;

    int nextState, i;
    for (nextState = state; nextState > 0; nextState--) {
        if (pattern[nextState - 1] == x) {
            for (i = 0; i < nextState - 1; i++) {
                if (pattern[i] != pattern[state - nextState + 1 + i])
                    break;
            }
            if (i == nextState - 1)
                return nextState;
        }
    }

    return 0;
}
void searchPattern(char *text, char *pattern) {
    int M = strlen(pattern);
    int N = strlen(text);

    int FA[M + 1][NO_OF_CHARS];

    buildFiniteAutomaton(pattern, M, FA);

    int i, state = 0;
    for (i = 0; i < N; i++) {
        state = FA[state][text[i]];
        if (state == M) {
            printf("Pattern found at index %d\n", i - M + 1);
        }
    }
}

int main() {
    char text[] = "AABAACAADAABAAABAA";
    char pattern[] = "AABA";

    searchPattern(text, pattern);
    return 0;
}
