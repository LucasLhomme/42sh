/*
** EPITECH PROJECT, 2024
** B-PSU-200-LIL-2-1-42sh-lucas.lhomme
** File description:
** handle_arrow_up_down.c
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"
#include <stdlib.h>
#include <string.h>

// history_t *load_history(void)
// {
//     FILE *file = fopen(get_history_file_path(), "r");
//     history_t *history = NULL;
//     if (!file)
//         return NULL;
//     return make_history_linked_list(file, history);
// }

// int handle_up_arrow(int pos)
// {
//     history_t *history = load_history();
//     int nb_node = count_node(history);
    
//     if (pos < 0)
//         return 0;
//     pos++;
//     for (int i = 0; i != nb_node - pos + 1; i++) {
//         history = history->next;
//     }
//     printf("%s", history->command);
//     return pos + 1;
// }

// int history_navigation(char seq[2])
// {
//     static int pos = 0;

//     if (seq[1] == 'A')
//         pos = handle_up_arrow(pos);
//     return 0;
// }

int history_navigation(char seq[2]) {
    static history_t *history_start = NULL;
    static history_t *current = NULL;
    char *path = get_history_file_path();
    FILE *file = fopen(path, "r");
    free(path);

    if (!history_start) {
        if (!file)
            return 0;
        history_start = make_history_linked_list(file, NULL);
        print_history(history_start);
        // Aller à la fin pour démarrer (dernière commande entrée)
        for (current = history_start; current && current->next; current = current->next);
    }
    if (seq == NULL || (seq[1] != 'A' && seq[1] != 'B')) {
        return 0;
    }
    
    if (!history_start) // Si tu as une tête d'historique globale
        return 0;

    if (!current)
        current = history_start; // ou history_tail selon la logique
    
    if (seq[1] == 'A') { // flèche haut
        if (current->prev && current->prev->command) {
            current = current->prev;
            // afficher la commande ici
        }
    } else if (seq[1] == 'B') { // flèche bas
        if (current->next && current->next->command) {
            current = current->next;
            // afficher la commande ici
        }
    }
    return 0;
}
