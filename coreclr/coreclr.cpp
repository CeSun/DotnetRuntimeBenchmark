// coreclr.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define CORECLR 1

#include <iostream>
#include <Windows.h>
#include "coreclr_delegates.h"
#include "hostfxr.h"

int main()
{
#if CORECLR
	auto HostFxrPath = TEXT("coreclr_runtime/hostfxr.dll");
	auto RuntimeConfigPath = TEXT("coreclr_runtime/dotnet.runtimeconfig.json");
#else
	auto HostFxrPath = TEXT("mono_runtime/hostfxr.dll");
	auto RuntimeConfigPath = TEXT("mono_runtime/dotnet.runtimeconfig.json");
#endif // CORECLR

	auto h = ::LoadLibraryW(HostFxrPath);
	auto InitializeFunPtr = (hostfxr_initialize_for_runtime_config_fn)::GetProcAddress(h, "hostfxr_initialize_for_runtime_config");
	auto GetDelegateFunPtr = (hostfxr_get_runtime_delegate_fn)::GetProcAddress(h, "hostfxr_get_runtime_delegate");
	auto CloseFunPtr = (hostfxr_close_fn)::GetProcAddress(h, "hostfxr_close");

	if (InitializeFunPtr(RuntimeConfigPath, nullptr, (hostfxr_handle*)&h))
	{
		std::cout << "Error!" << std::endl;
		return 0;
	} 
	load_assembly_and_get_function_pointer_fn funptr;
	GetDelegateFunPtr(h, hdt_load_assembly_and_get_function_pointer, (void**)&funptr);

	if (funptr == nullptr)
	{
		std::cout << "load_assembly_and_get_function_pointer_fn Error" << std::endl;
		return 0;
	}
	CloseFunPtr(h);
	void(*TestFunc)() = nullptr;
	auto ret = funptr(L"Test.dll", L"Test.Test, Test", L"TestMain", UNMANAGEDCALLERSONLY_METHOD, nullptr, (void**)&TestFunc);
	if (TestFunc == nullptr)
	{
		std::cout << "get fun Error:" << ret << std::endl;
		return 0;
	}
	TestFunc();

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
