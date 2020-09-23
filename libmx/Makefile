NAMEA = libmx.a

INC = libmx.h

SRC = mx_create_node.c \
mx_itoa.c \
mx_list_size.c \
mx_nbr_to_hex.c \
mx_pow.c \
mx_printchar.c \
mx_printerr.c \
mx_printint.c \
mx_printspaces.c \
mx_printstr.c \
mx_push_back.c \
mx_sort_list.c \
mx_str_reverse.c \
mx_strcat.c \
mx_strcmp.c \
mx_strcpy.c \
mx_strdel.c \
mx_strdup.c \
mx_strjoin.c \
mx_strlen.c \
mx_strncpy.c \
mx_strnew.c \
mx_swap_char.c \
mx_isalpha.c

OBJ = mx_create_node.o \
mx_itoa.o \
mx_list_size.o \
mx_nbr_to_hex.o \
mx_pow.o \
mx_printchar.o \
mx_printerr.o \
mx_printint.o \
mx_printspaces.o \
mx_printstr.o \
mx_push_back.o \
mx_sort_list.o \
mx_str_reverse.o \
mx_strcat.o \
mx_strcmp.o \
mx_strcpy.o \
mx_strdel.o \
mx_strdup.o \
mx_strjoin.o \
mx_strlen.o \
mx_strncpy.o \
mx_strnew.o \
mx_swap_char.o \
mx_isalpha.o

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean

install:
	@cp $(addprefix src/, $(SRC)) .
	@cp $(addprefix inc/, $(INC)) .
	@clang $(CFLAGS) -c $(SRC)
	@ar rcs $(NAMEA) $(OBJ)
	@mkdir obj
	@mv $(OBJ) ./obj

uninstall: clean
	@rm -rf $(NAMEA)

clean:
	@rm -rf $(INC) $(SRC) ./obj

reinstall: uninstall install
