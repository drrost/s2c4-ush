//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

// --- Pair

typedef struct {
    char *key;
    char *value;
} t_pair;

t_pair *mx_pair_new(char *key, char *value) {
    t_pair *instance = (t_pair *)malloc(sizeof(t_pair));

    mx_memset(instance, 0, sizeof(t_pair));
    instance->key = mx_strdup(key);
    instance->value = mx_strdup(value);

    return instance;
}

void mx_pair_delete(t_pair **pair) {
    t_pair *instance = *pair;
    mx_strdel(&(instance->key));
    mx_strdel(&(instance->value));
    free(instance);
    *pair = 0;
}

void mx_pair_print(t_pair *pair) {
    mx_printstr("key: \"");
    mx_printstr(pair->key);
    mx_printstr("\", value: \"");
    mx_printstr(pair->value);
    mx_printstr("\"\n");
}

// MAP --

typedef struct s_map {
    t_list *content;
    int size;

    void (*set)(struct s_map *, char *, char *);
    void (*remove)(struct s_map *, char *);
    char *(*get)(struct s_map *, char *);
    void (*print)(struct s_map *);
} t_map;

t_pair *mx_map_get_pair(t_map *this, char *key) {
    t_list *list = this->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        if (mx_streq(key, pair->key))
            return pair;
        list = list->next;
    }
    return 0;
}

char *mx_map_get(t_map *this, char *key) {
    t_pair *pair = mx_map_get_pair(this, key);
    if (pair)
        return pair->value;
    return 0;
}

void mx_map_set(t_map *this, char *key, char *value) {
    t_pair *pair = mx_map_get_pair(this, key);

    if (pair == 0) {
        pair = mx_pair_new(key, value);
        mx_push_back(&(this->content), pair);
        this->size++;
    }
    else {
        mx_strdel(&(pair->value));
        pair->value = mx_strdup(value);
    }
}

void mx_map_remove(t_map *this, char *key) {
    // TODO: implement the method.
    key++;
    this->size--;
}

void mx_map_print(t_map *this) {
    mx_printstr("Map 0x");
    char *address = mx_nbr_to_hex((unsigned long)this);
    mx_printline(address);
    mx_strdel(&address);

    mx_printstr("  size: ");
    mx_printint(this->size);
    mx_printstr("\n\n");

    t_list *list = this->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        mx_printstr("  ");
        mx_pair_print(pair);
        list = list->next;
    }
}

// --- MAP

t_map *mx_map_new() {
    t_map *instance = (t_map *)malloc(sizeof(t_map));
    mx_memset(instance, 0, sizeof(t_map));
    return instance;
}

void mx_map_delete(t_map **map) {
    t_map *instance = (t_map *)*map;
    t_list *list = instance->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        mx_pair_delete(&pair);
        mx_pop_front(&list);
    }
    free(instance);
    *map = 0;
}

t_map *mx_map_str_str() {
    t_map *instance = mx_map_new();

    instance->get = mx_map_get;
    instance->set = mx_map_set;
    instance->remove = mx_map_remove;

    return instance;
}

static void print_prompt() {
    t_map *map = mx_map_str_str();
    map->set(map, "pwd", "/usr/local/bin");
    map->set(map, "TMPDIR",
             "/var/folders/1q/6yl13mjx38g2jgfhx6072t180000gn/T/");
    char *pwd = map->get(map, "pwd");
    pwd++;

    mx_map_print(map);
    mx_map_delete(&map);

    printf("u$l> ");
}

void mx_run_algorithm() {
    while (true) {
        // Read
        print_prompt();
        char *line = mx_read_next();

        // Parse
        t_input *input = mx_parse_input_simple(line);
        mx_strdel(&line);

        // Execute
        int result = mx_execute(input);

        // Next
        mx_input_delete(&input);
        if (result == MX_SHOULD_EXIT)
            break;
    }
}
