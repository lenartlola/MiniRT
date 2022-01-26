/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msegrans <msegrans@student.42lausanne      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:38:20 by msegrans          #+#    #+#             */
/*   Updated: 2022/01/26 23:38:21 by msegrans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_UTILS_H
# define VALIDATE_UTILS_H

# include "types.h"

int	check_range_double(double n, double lb, double hb);

int	check_colour(t_colour c);

int	check_orientation(t_vec3 o);

int	check_brightness(double b);

#endif //VALIDATE_UTILS_H
