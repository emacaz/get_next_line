#include <stdio.h>

#include <stdio.h>

const char* next_word() {
    const char* words[] = {"Hello", "World", "Example", "Words"};
    static size_t index = 0;

    // Save the current word to return
    const char* current_word = words[index];

    // Move to next word, reset to first word if at end of array
    // index = (index + 1) % (sizeof(words) / sizeof(words[0]));
    index++;
    if (index >= (sizeof(words) / sizeof(words[0])))
        return NULL;
    return current_word;
}

int main() {
    printf("%s ", next_word());
    printf("%s ", next_word());
    printf("%s ", next_word());
    printf("%s ", next_word());
    printf("%s ", next_word());
    printf("%s ", next_word());
    printf("%s ", next_word());
    printf("%s ", next_word());
    printf("%s ", next_word());
    printf("%s ", next_word());
    printf("%s ", next_word()); // Starts over
    return 0;
}
