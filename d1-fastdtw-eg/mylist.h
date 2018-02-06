#pragma once

struct agios_list_head
{
	struct agios_list_head *prev,*next;
};

#define AGIOS_LIST_HEAD_INIT(name) { &(name), &(name) }

#define AGIOS_LIST_HEAD(name) \
         struct agios_list_head name = AGIOS_LIST_HEAD_INIT(name)

#define agios_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define agios_container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - agios_offsetof(type,member) );})

#define agios_list_entry(ptr, type, member) \
        agios_container_of(ptr, type, member)

#define agios_list_for_each_entry(pos, head, member)                          \
         for (pos = agios_list_entry((head)->next, typeof(*pos), member);      \
              &pos->member != (head);        \
              pos = agios_list_entry(pos->member.next, typeof(*pos), member))

void init_agios_list_head(struct agios_list_head *list);
void __agios_list_add(struct agios_list_head *new, struct agios_list_head *prev, struct agios_list_head *next);
void agios_list_add(struct agios_list_head *new, struct agios_list_head *head);
void agios_list_add_tail(struct agios_list_head *new, struct agios_list_head *head);
void __agios_list_del(struct agios_list_head * prev, struct agios_list_head * next);
void agios_list_del(struct agios_list_head *entry);
void __agios_list_del_entry(struct agios_list_head *entry);
void agios_list_del_init(struct agios_list_head *entry);
int agios_list_empty(const struct agios_list_head *head);
