/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:38:49 by adietric          #+#    #+#             */
/*   Updated: 2019/12/11 18:42:23 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

size_t		dasm_hexalen(uint8_t *cor_content, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		if (cor_content[i] == 0)
			break ;
	return (i);
}

unsigned char*	recup_name(uint8_t *cor_content)
{
	size_t			name_len;
	unsigned char	*name;

	name = NULL;
	name_len = dasm_hexalen(&(cor_content[4]), 128);
	name = (unsigned char*)ft_strsub((const char *)cor_content, 4, name_len);
	return (name);
}

unsigned char*	recup_comment(uint8_t *cor_content)
{
	size_t			com_len;
	unsigned char	*com;

	com = NULL;
	com_len = dasm_hexalen(&(cor_content[140]), 2048);
	com = (unsigned char*)ft_strsub((const char *)cor_content, 140, com_len);
	return (com);
}

unsigned char*	recup_ex_code(size_t *len, uint8_t *cor_content)
{
	unsigned char	*code;

	code = NULL;
	(*len) = (size_t)dasm_get_exec_code(&(cor_content[136]), 4);

	if (!(code = (unsigned char *)malloc(sizeof(unsigned char) * (*len))))
		return (NULL);
	ft_memcpy(code, &(cor_content[2192]), (*len));
	return (code);
}

void		dasm_get_header(t_all *all, size_t cor_size, uint8_t **cor_content
						, t_champs *champs)
{
	char	*exec_code;

	if (cor_size < 2192)
		error(all, "Fichier trop petit! (pas assez d'informations)\n");
	if (cor_size > CHAMP_MAX_SIZE + 2192)
		error_size(all, champs->path, cor_size);
	if (cor_content[0][0] != 0x00 || cor_content[0][1] != 0xea
		|| cor_content[0][2] != 0x83 || cor_content[0][3] != 0xf3)
		error(all, "Magic_Number (0xea83f3) inexistant\n");
	champs->name = recup_name(cor_content[0]);
	if ((cor_content[0][132] | cor_content[0][133] | cor_content[0][134]		//attention aux index !
		| cor_content[0][135]) != 0)
		error(all, "Invalid File\n");
	champs->comment = recup_comment(cor_content[0]);
	if ((cor_content[0][2188] | cor_content[0][2189] | cor_content[0][2190]		//attention aux index !
		| cor_content[0][2191]) != 0)
		error(all, "Invalid File\n");
	champs->exec_code = recup_ex_code(&(champs->len_exec_code), cor_content[0]);
	if (!(champs->name) || !(champs->comment) || !(champs->exec_code))
		error(all, "Malloc error\n");
}
