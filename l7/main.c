#include "trie.h"

#include <stdio.h>

int main(void)
{
    trie_node *trie = create_trie();

    printf("[ADD & SEARCH TEST]\n");

    add_word(trie, "ana");
    add_word(trie, "ananas");
    add_word(trie, "ana");
    add_word(trie, "ananas");
    add_word(trie, "banana");
    add_word(trie, "ban");
    add_word(trie, "cat");
    add_word(trie, "word");
    add_word(trie, "cathering");
    add_word(trie, "cat");
    add_word(trie, "cat");
    add_word(trie, "ana");
    add_word(trie, "car");
    add_word(trie, "cars");
    add_word(trie, "cars");
    add_word(trie, "weather");
    add_word(trie, "wonderful");
    add_word(trie, "woo");
    add_word(trie, "wonderful");
    add_word(trie, "ban");
    add_word(trie, "ban");
    add_word(trie, "banned");
    add_word(trie, "banned");
    add_word(trie, "weather");
    add_word(trie, "cathering");
    add_word(trie, "banned");
    add_word(trie, "banned");
    add_word(trie, "ban");
    add_word(trie, "banned");
    add_word(trie, "weather");
    add_word(trie, "weather");
    add_word(trie, "weather");
  
    printf("ana apare de %d ori, ar trebui sa apara de 3 ori\n",
           search_word(trie, "ana"));

    printf("ananas apare de %d ori, ar trebui sa apara de 2 ori\n",
           search_word(trie, "ananas"));

    printf("banana apare de %d ori, ar trebui sa apara de 1 ori\n",
           search_word(trie, "banana"));
       
    printf("ban apare de %d ori, ar trebui sa apara de 4 ori\n",
           search_word(trie, "ban"));
    
    printf("banned apare de %d ori, ar trebui sa apara de 5 ori\n",
           search_word(trie, "banned"));

    printf("cat apare de %d ori, ar trebui sa apara de 3 ori\n",
           search_word(trie, "cat"));
    
    printf("car apare de %d ori, ar trebui sa apara de 1 ori\n",
           search_word(trie, "car"));
    
    printf("cars apare de %d ori, ar trebui sa apara de 2 ori\n",
           search_word(trie, "cars"));
    
    printf("cathering apare de %d ori, ar trebui sa apara de 2 ori\n",
           search_word(trie, "cathering"));
    
    printf("weather apare de %d ori, ar trebui sa apara de 5 ori\n",
           search_word(trie, "weather"));
    
    printf("wonderful apare de %d ori, ar trebui sa apara de 2 ori\n",
           search_word(trie, "wonderful"));
    
    printf("woo apare de %d ori, ar trebui sa apara de 1 ori\n",
           search_word(trie, "woo"));

    destroy_trie(trie);

    printf("\n[MEMCHECK TEST]\n");
    printf("Check with 'make memcheck'. There should be no memory leaks now!\n");

    return 0;
}
