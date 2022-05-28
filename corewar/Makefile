ASM_NAME = asm
VM_NAME = corewar

FLAGS = -Wall -g -Wextra -Werror

VM_SRC_DIR = ./vm_src/
VM_OBJ_DIR = ./vm_obj/
ASM_SRC_DIR = ./asm_src/
ASM_OBJ_DIR = ./asm_obj/
LIB_DIR = ./libft/

VM_SRC = $(addprefix $(VM_SRC_DIR),$(VM_SRC_NAMES))
VM_SRC_NAMES = clear_vm.c ft_lst_nocpy.c parse_champion.c virt_m.c lst_functions.c \
		print_memory.c initialize_corewar.c initialize_cars.c op.c \
		introduce_champions.c corewar.c cw_helpers.c action.c \
		action2.c action_bitwise.c action_fork.c get_bits.c action_load.c \
		action_load_store_index.c get_debug_mode.c read_champ.c \
		attach_champ.c corewar_check.c visual.c rew.c car_chat.c \
		print_name_com_im.c other_viz.c
VM_OBJ = $(addprefix $(VM_OBJ_DIR),$(VM_OBJ_NAMES))
VM_OBJ_NAMES = $(VM_SRC_NAMES:.c=.o)

ASM_SRC = $(addprefix $(ASM_SRC_DIR),$(ASM_SRC_NAMES))
ASM_SRC_NAMES = asm_main.c asm_parsing.c asm_parsing2.c auxiliary_functions.c \
		do_bin.c ft_count_chr.c ft_strchr_index.c ft_strsplit_symbols.c \
		new_library_functions.c type_assignment.c do_file.c info_error.c \
		string_functions.c string_functions2.c
ASM_OBJ_NAMES = $(ASM_SRC_NAMES:.c=.o)
ASM_OBJ = $(addprefix $(ASM_OBJ_DIR),$(ASM_OBJ_NAMES))

all: $(VM_NAME) $(ASM_NAME)

$(VM_NAME): $(VM_OBJ)
	make -C $(LIB_DIR)
	gcc $(FLAGS) -o $(VM_NAME) $(VM_OBJ) -L $(LIB_DIR) -lft -lncurses

$(VM_OBJ_DIR)%.o:$(VM_SRC_DIR)%.c
	@mkdir -p $(VM_OBJ_DIR)
	@gcc -I $(LIB_DIR) -o $@ -c $<

$(ASM_NAME): $(ASM_OBJ)
	make -C $(LIB_DIR)
	gcc $(FLAGS) -o $(ASM_NAME) $(ASM_OBJ) -L $(LIB_DIR) -lft

$(ASM_OBJ_DIR)%.o:$(ASM_SRC_DIR)%.c
	@mkdir -p $(ASM_OBJ_DIR)
	@gcc -I $(LIB_DIR) -o $@ -c $<

clean:
	make -C $(LIB_DIR) clean
	rm -rf $(VM_OBJ_DIR)
	rm -rf $(ASM_OBJ_DIR)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(VM_NAME) $(ASM_NAME)

re: fclean all
