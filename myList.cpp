#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "myList.h"

typedef struct Student
{
	enum SIZE_T { len = 15 };
	int number;
	char name[len];
	list_head list;
}Student, *pStudent;

void registerChain(list_head *myList, pStudent val, int position)
{
	if(position == 1) list_add(&val->list, myList); //添加在链表表头(头插法)
	else list_add_tail(&val->list, myList); //添加在链表末尾(尾插法)
}

void visit(list_head *myList) //正向遍历
{
	pStudent var;
	list_for_each_entry(var, Student, myList, list) //遍历链表
	{
		printf("%d, %s\n", var->number, var->name);
	}
}

void reverseVisit(list_head *myList) //逆向遍历
{
	pStudent var;
	list_for_each_entry_reverse(var, Student, myList, list) //逆向遍历链表
	{
		printf("%d, %s\n", var->number, var->name);
	}
}

void delLinkNode(list_head *myList) //删除链表节点
{
	pStudent var, n = 0;
	list_for_each_entry_safe(var, Student, n, Student, myList, list) //安全删除节点
	{
		if(strcmp(var->name, "zdf") == 0)
		{
			list_del(&var->list);
			free(var);
		}
		else printf("%d, %s\n", var->number, var->name);
	}
}

void delLink(list_head *myList) //删除整个链表
{
	pStudent var, n = 0;
	list_for_each_entry_safe(var, Student, n, Student, myList, list) //安全删除链表
	{
		list_del(&var->list);
		free(var);
	}
}

int main(int argc, char*  argv[])
{
	LIST_HEAD(myList); //创建链表
	// assert(list_empty(&myList)); //判断链表是否为空
	printf("%x, %x, %x\n", &myList, myList.next, myList.prev);

	// list_head myList;
	// INIT_LIST_HEAD(&myList); //初始化链表表头
	// printf("%x, %x, %x\n", &myList, myList.next, myList.prev);

	pStudent stu = 0;
	pStudent var = 0;
	int number;
	printf("please input student number:");
	scanf("%d", &number);

	for(int i = 0; i < number; i++)
	{
		stu = (pStudent)malloc(sizeof(Student));
		scanf("%d%s", &stu->number, stu->name);

		registerChain(&myList, stu, i); //注册节点到链表中

		// if(i == 1) list_add(&stu->list, &myList); //添加在链表表头(头插法)
		// else list_add_tail(&stu->list, &myList); //添加在链表末尾(尾插法)
	}
	// assert(list_empty(&myList)); //判断链表是否为空
	printf("\n");

	visit(&myList);
	// list_for_each_entry(var, Student, &myList, list) //遍历链表
	// {
		// printf("%d, %s\n", var->number, var->name);
	// }
	
	printf("\n");
	
	reverseVisit(&myList);
	// list_for_each_entry_reverse(var, Student, &myList, list) //逆向遍历链表
	// {
		// printf("%d, %s\n", var->number, var->name);
	// }
	
	printf("+-------------+\n");
	
	// pStudent n = 0;
	// list_for_each_entry_safe(var, Student, n, Student, &myList, list) //安全删除节点
	// {
		// if(strcmp(var->name, "zdf") == 0)
		// {
			// list_del(&var->list);
			// free(var);
		// }
		// else printf("%d, %s\n", var->number, var->name);
	// }
	delLinkNode(&myList);
	
	printf("+-------------+\n");
	
	// list_for_each_entry(var, Student, &myList, list) //遍历链表
	// {
		// printf("%d, %s\n", var->number, var->name);
	// }
	visit(&myList);
	
	// list_for_each_entry_safe(var, Student, n, Student, &myList, list) //安全删除链表
	// {
		// list_del(&var->list);
		// free(var);
	// }
	delLink(&myList);

	assert(list_empty(&myList) == 1); //判断链表是否为空
	return 0;
}