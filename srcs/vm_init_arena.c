
#include "../includes/vm.h"

void ft_print_arena(t_all *vm)
{
    int i = -1; 
    int j = -1;
    int colour = 0;
    int x = 0;
 
    while (++i < MEM_SIZE - 1)
    {
        if (i >= vm->champs[x].start &&
            i < vm->champs[x].start + (int)vm->champs[x].len_exec_code)
            {
                printf("\033[0;35m%02x ", vm->arena[i]);
                if (i == vm->champs[x].start + (int)vm->champs[x].len_exec_code - 1)
                    ++x;
            }
        else
            printf("\033[0m%02x ", vm->arena[i]);
        if (++j == 64)
        {
            printf("\n");
            j = -1;
        }
    }
}

int init_arena(t_all *vm)
{
  //  t_arena *a;
    int     i;
    int     divide;

    i = 0;
    divide = 0;
    vm->cycles = 0;
    vm->last_alive = CYCLE_TO_DIE;
    if (!(vm->arena = ft_memalloc((sizeof(unsigned char)) * MEM_SIZE)))
        return (-1);
    printf ("%d\n", vm->total_champ);
    while (i < vm->total_champ)
    {
        vm->champs[i].start = divide;
        ft_memcpy(&vm->arena[divide], vm->champs[i].exec_code, vm->champs[i].len_exec_code);
        ++i;
        divide = divide + MEM_SIZE / vm->total_champ;
    }
   ft_print_arena(vm);
   return (0);
}