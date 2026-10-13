#include <SysRT/SysRTUtils.hpp>

namespace SystemConsole
{
    void SystemConsoleOut(const v8::FunctionCallbackInfo<v8::Value> &args)
    {
	bool first = true;

	for (int i = 0; i < args.Length(); i++)
	{
	    v8::HandleScope hs(args.GetIsolate());
	    if (first)
	    {
		    first = false;
	    }
	    else
	    {
		    std::cout << " ";
	    }
	    v8::String::Utf8Value str(args.GetIsolate(), args[i]);
	    const char* out_string = ToCString(str);
	    std::cout << out_string;
	}
	std::cout << std::endl;
	std::cout << std::flush;
    }

    void SystemConsoleIn(const v8::FunctionCallbackInfo<v8::Value> &args)
    {
	bool first = true;

	for (int i = 0; i < args.Length(); i++)
	{
	    v8::HandleScope hs(args.GetIsolate());
	    if (first)
	    {
		first = false;
	    }
	    else
	    {
		std::cout << " ";
	    }

	    v8::String::Utf8Value str(args.GetIsolate(), args[i]);
	    const char* out_string = ToCString(str);
	    std::cout << out_string;
	}

	std::string input;
	std::cin >> input;
	args.GetReturnValue().Set(ToV8String(input.c_str()));
    }
}
