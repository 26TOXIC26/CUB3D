/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amousaid <amousaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:57:07 by amousaid          #+#    #+#             */
/*   Updated: 2023/11/22 08:57:20 by amousaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}
// void del(void *content)
// {
//     free(content);
//     content = NULL;
// }
// int main()
// {

//     char *pt1 = ft_strdup("test1");
//     char *pt2 = ft_strdup("test2");
//     char *pt3 = ft_strdup("test3");
//     t_list *head = NULL;
//     t_list *node1 = ft_lstnew(pt1);
//     t_list *node2 = ft_lstnew(pt2);
//     t_list *node3 = ft_lstnew(pt3);
//     ft_lstadd_back(&head, node1);
// 	ft_lstadd_back(&head, node2);
// 	ft_lstadd_back(&head, node3);
// 	printf("%s", (char *)head -> content);
// 	printf("\n");
//     printf("%s", (char *)head -> next -> content);
// 	printf("\n");
//     printf("%s", (char *)head -> next -> next -> content);
// 	printf("\n");
//     ft_lstclear(&head, del);
//     printf("%s\n", (char *)head ->content);
//     printf("%s\n", (char *)head -> next -> content);
//     printf("%s\n", (char *)head -> next -> next -> content);
// }