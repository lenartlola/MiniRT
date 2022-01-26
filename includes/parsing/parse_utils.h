/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 00:36:25 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/26 00:36:27 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by segransm on 1/26/22.
//

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include <libft.h>
# include <types.h>

void	skip_spaces(char **line);

int		check_exist(char type, t_list **head);

int		new_lst(t_list **head);

char	*chop_word(char **line, int (fn)(int));

int		parse_vec3(char **line, t_vec3 *elem);

#endif //PARSE_UTILS_H
