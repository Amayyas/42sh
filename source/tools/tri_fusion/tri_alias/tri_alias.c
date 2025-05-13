/*
** EPITECH PROJECT, 2024
** linked list
** File description:
** fusion two linked list
*/

#include "my.h"

alias_t *fusion_node(alias_t *left, alias_t *right,
    bool(*sort_func)(void *value1, void *value2))
{
    if (!left)
        return right;
    if (!right)
        return left;
    if (!sort_func(left->key, right->key)) {
        left->next = fusion_node(left->next, right, sort_func);
        return left;
    } else {
        right->next = fusion_node(left, right->next, sort_func);
        return right;
    }
}

alias_t *split_linked(alias_t *head)
{
    alias_t *node1 = head;
    alias_t *node2 = head;
    alias_t *previous = NULL;

    while (node1 && node1->next) {
        previous = node2;
        node2 = node2->next;
        node1 = node1->next->next;
    }
    if (previous)
        previous->next = NULL;
    return node2;
}

alias_t *tri_fusion(alias_t *head,
    bool(*sort_func)(void *value1, void *value2))
{
    alias_t *center;
    alias_t *left;
    alias_t *right;

    if (head == NULL || head->next == NULL)
        return head;
    center = split_linked(head);
    left = tri_fusion(head, sort_func);
    right = tri_fusion(center, sort_func);
    return fusion_node(left, right, sort_func);
}
