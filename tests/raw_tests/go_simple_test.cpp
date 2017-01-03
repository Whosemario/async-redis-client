/************************************************
* libgo sample1
*************************************************/
#include "coroutine.h"
#include <stdio.h>
#include <functional>

void foo()
{
	printf("function pointer\n");
}

struct A {
	void fA() { printf("std::bind\n"); }
	void fB() { printf("std::function\n"); }
};

int main()
{
	// ʹ�ùؼ���go����Э��, go�������ʹ��:
	//     1.void(*)()����ָ��, ����:foo.
	//     2.Ҳ����ʹ���޲�����lambda, std::bind����, function����, 
	//     3.�Լ�һ�п����޲ε��õķº�������
	//   ע�ⲻҪ���Ǿ�β�ķֺ�";".
	go foo;

	go[]{
		printf("lambda\n");
	};

	go std::bind(&A::fA, A());

	std::function<void()> fn(std::bind(&A::fB, A()));
	go fn;

	// Ҳ����ʹ��go_stack����ָ��ջ��С��Э��
	//   ����ӵ��10MB��ջ��Э��
	go_stack(10 * 1024 * 1024) [] {
		printf("large stack\n");
	};

	// Э�̴����Ժ󲻻�����ִ�У������ݴ�����ִ���б��У��ȴ����������ȡ�
	// co_sched��ȫ��Ψһ��Э�̵������������½ӿڿ��Ե���Э�̣�
	//   1.Run ִ�е��ε���, ���ر���ִ�е�Э������
	//   2.RunLoop ����ѭ��ִ��Run, ���᷵��
	//   3.RunUntilNoTask ѭ��ִ��Run, ֱ��Э������Ϊ��.
	//
	// ����ʹ��һ���߳̽���Э�̵���ʱ, Э�̵�ִ�л��ϸ����ѭ�䴴��˳��.
	co_sched.Run();
	return 0;
}