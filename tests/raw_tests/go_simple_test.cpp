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
	// 使用关键字go创建协程, go后面可以使用:
	//     1.void(*)()函数指针, 比如:foo.
	//     2.也可以使用无参数的lambda, std::bind对象, function对象, 
	//     3.以及一切可以无参调用的仿函数对象
	//   注意不要忘记句尾的分号";".
	go foo;

	go[]{
		printf("lambda\n");
	};

	go std::bind(&A::fA, A());

	std::function<void()> fn(std::bind(&A::fB, A()));
	go fn;

	// 也可以使用go_stack创建指定栈大小的协程
	//   创建拥有10MB大栈的协程
	go_stack(10 * 1024 * 1024) [] {
		printf("large stack\n");
	};

	// 协程创建以后不会立即执行，而是暂存至可执行列表中，等待调度器调度。
	// co_sched是全局唯一的协程调度器，有以下接口可以调度协程：
	//   1.Run 执行单次调度, 返回本次执行的协程数量
	//   2.RunLoop 无限循环执行Run, 不会返回
	//   3.RunUntilNoTask 循环执行Run, 直至协程数量为零.
	//
	// 当仅使用一个线程进行协程调度时, 协程地执行会严格地遵循其创建顺序.
	co_sched.Run();
	return 0;
}