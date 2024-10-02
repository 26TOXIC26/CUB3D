/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:57:24 by amousaid          #+#    #+#             */
/*   Updated: 2023/11/22 08:57:43 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
	lst = NULL;
}
// void del(void *content)
// {
//     free(content);
//     printf("rani wslt lhna\n");
//     content = NULL;
// }
// int main()
// {
//     char *pt = ft_strdup("test");
//     t_list *head = ft_lstnew(pt);
//     printf("%s\n", head -> content);
//     ft_lstdelone(head, del);
//     printf("%s\n", *((char *)head ->content));
// }