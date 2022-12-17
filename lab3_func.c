#include <stdlib.h>

char * mystrchr(const char * s, const int c) { // поиск первого вхождения символа
    return (*s) ? ((*s == c) ? (char*)s : mystrchr(s + 1, c)) : NULL;
}
char * mystrtok(char * str, const char * delim) { // разбить строку
    static char * ptr;
    if ( str )
        for (ptr = str; mystrchr(delim, *ptr); ptr++);
    if (*ptr == '\0') return NULL;
    str = ptr;
    while (*ptr && ! mystrchr(delim, *ptr)) ptr++;
    while ( *ptr && mystrchr(delim, *ptr) ) *ptr++ = '\0';
    return str;
}
char* mystrcpy(char* destination, const char* source) { // копировать строку
    char *tempPtr = destination;
    while (*source) { *tempPtr++ = *source++; }
    *tempPtr++ = '\0';
    return destination;
}
size_t mystrlen(const char* str) { // длина строки
    size_t length = 0;
    while (*str++) length++;
    return length;
}
int mystrcmp(const char* firstString, const char* secondString) { // сравнение строк
    while (*firstString && *secondString) {
        if (*firstString > *secondString) return 1;
        if (*firstString < *secondString) return -1;
        firstString++;
        secondString++;
    }
    if (mystrlen(firstString) == mystrlen(secondString)) return 0;
    if (mystrlen(firstString) > mystrlen(secondString)) return 1;
    if (mystrlen(firstString) < mystrlen(secondString)) return -1;
    return 0;
}
void* mymemcpy(void* dest, const void* src, size_t count) {
    char* dst8 = (char*)dest;
    char* src8 = (char*)src;
    while (count--) *dst8++ = *src8++;
    return dest;
}
char* myreadline(){ // считать строку
    char* res_string = NULL;
    char buffer[81] = {0};
    int final_len = 0;
    int new_len = 0;
    do{
       new_len = scanf("%80[^\n]", buffer);
       if (new_len < 0) return NULL;
       else if (new_len > 0) {
            int buffer_len = mystrlen(buffer);
            int str_len = final_len + buffer_len;
            res_string = realloc(res_string, str_len + 1);
            mymemcpy(res_string + final_len, buffer, buffer_len);
            final_len = str_len;
        } else scanf("%*c");
    } while(new_len > 0);
    if (final_len > 0) res_string[final_len] = '\0';
    else res_string = calloc(1, sizeof(char));
    return res_string;
}
char** string_to_array(char* res_string, int* words_counter) { // строка в массив
    size_t arr_size = 10;
    char *istr;
    int counter = 0;
    char** words;
    words = (char**)malloc(arr_size * sizeof(char*));
    istr = mystrtok(res_string, " ");
    while (istr != NULL){
        if(istr == " " || !istr || istr == "") continue;
        if(arr_size < counter){
             arr_size +=10;
             words = (char**) realloc(words, arr_size * sizeof(char*));
        }
        words[counter] = (char*) malloc(mystrlen(istr) + 1);
        mystrcpy(words[counter], istr);
        istr = mystrtok(NULL," ");
        counter++;
    }
    *words_counter = counter;
    return words;
}
void alphabet_sort(char** words, int count){ // сортировка по алфавиту
    char* x;
    for (int i = 0 ; i < count; i++){
        for (int j = i + 1; j < count; j++){// printf("%s %s \n", words[i], words[j]);
        if (mystrcmp(words[i], words[j]) <= 0) continue;
               x = words[j];
               words[j] = words[i];
               words[i] = x;
        }
    }
}
char* mystrcat(char* dest, const char* source){ // конкатанация
    dest += mystrlen(dest);
    while (*dest++ = *source++);
    return dest;
}
char * array_to_string(char **words, int count){ // массив в строку
    int i; size_t len = 0;
    char * ptr;
    for (i = 0; i < count; i++) len += mystrlen(words[i]) + 1;
    ptr = (char*)malloc(len + 1);
    *ptr = '\0';
    for (i = 0; i < count; i++) {
        if(i + 1 < count){
            size_t word_len = mystrlen(words[i]);
            char *word;
            word = (char*) malloc(word_len + 3);
            mymemcpy(word, words[i], word_len);
            word[word_len] = ' ';
            word[word_len + 1] = '\0';
            mystrcat(ptr, word);
            free(word);
        } else mystrcat(ptr, words[i]);
        free(words[i]);
    }
    ptr[len] = '\0';
    return ptr;
}