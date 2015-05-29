#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "myList.h"

#define  HASHFUNCTION(num, mod) ((num) % (mod))

typedef struct hlist_user //使用哈希链表的用户结构
{
	hlist_node hlist;
	int data;
}hlist_user, *hlist_user_ptr;

void registerHashTable(hlist_head* head, hlist_user_ptr var)
{
	hlist_add_head(&var->hlist, head);
}

void visitHashTable(hlist_head* hashTable, int mod)
{
	hlist_user_ptr var = 0;
	hlist_node* linkNode = 0;
	// hlist_head* head = 0;
	for(int i = 0; i < mod; i++)
	{
		// head = &hashTable[i];
		printf("Hash[%d]--- ", i);
		// hlist_for_each_entry(var, hlist_user, linkNode, head, hlist)
		hlist_for_each_entry(var, hlist_user, linkNode, &hashTable[i], hlist)
		{
			printf("%d ", var->data);
		}
		printf("\n");
	}
}

void delHashTable(hlist_head* hashTable, int mod)
{
	hlist_user_ptr var = 0;
	hlist_node* temp = 0;
	hlist_node* linkNode = 0;
	hlist_head* head = 0;
	for(int i = 0; i < mod; i++)
	{
		// 参数顺序<tpos, typeof_tpos, pos, n, head, member>
		head = &hashTable[i];
		hlist_for_each_entry_safe(var, hlist_user, linkNode, temp, head, hlist)
		{
			hlist_del(&var->hlist);
			free(var);
		}
		
		printf("Hash[%d]--- ", i);
		hlist_for_each_entry(var, hlist_user, linkNode, head, hlist)
		{
			printf("%d ", var->data);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	int mod;
	printf("please input mod:");
	scanf("%d", &mod);
	
	hlist_head* hashTable = new hlist_head[mod];
	for(int i = 0; i < mod; i++)
	{
		INIT_HLIST_HEAD(&hashTable[i]);
	}
	
	int number;
	printf("please input number:");
	scanf("%d", &number);
	
	int hash = -1;
	hlist_user_ptr var = 0;
	for(i = 0; i < number; i++)
	{
		var = (hlist_user_ptr)malloc(sizeof(hlist_user));
		scanf("%d", &var->data);
		hash = HASHFUNCTION(var->data, mod);
		registerHashTable(&hashTable[hash], var); //添加节点到哈希表中
		// hlist_add_head(&var->hlist, &hashTable[hash]);
	}
	
	visitHashTable(hashTable, mod);
	
	// hlist_node* linkNode = 0;
	// hlist_head* head = 0;
	// for(i = 0; i < mod; i++)
	// {
		// head = &hashTable[i];
		// printf("Hash[%d]--- ", i);
		// hlist_for_each_entry(var, hlist_user, linkNode, head, hlist)
		// {
			// printf("%d ", var->data);
		// }
		// printf("\n");
	// }
	
	delHashTable(hashTable, mod);
	
	// hlist_node* temp = 0;
	// for(i = 0; i < mod; i++)
	// {
		// 参数顺序<tpos, typeof_tpos, pos, n, head, member>
		// head = &hashTable[i];
		// hlist_for_each_entry_safe(var, hlist_user, linkNode, temp, head, hlist)
		// {
			// hlist_del(&var->hlist);
			// free(var);
		// }
		
		// printf("Hash[%d]--- ", i);
		// hlist_for_each_entry(var, hlist_user, linkNode, head, hlist)
		// {
			// printf("%d ", var->data);
		// }
		// printf("\n");
	// }
	
	delete[] hashTable;
	return 0;
}
/*
19 14 23 1 68 20 84 27 55 11 10 79 0
14 1 27 14 79
*/