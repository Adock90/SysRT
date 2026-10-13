#pragma once

#include <SysRT/SysRTUtils.hpp>

namespace SysRTExeception
{
    void SysRTReportException(v8::Isolate *isolate, v8::TryCatch *try_catch)
    {
	v8::HandleScope hs(isolate);
	v8::String::Utf8Value exception(isolate, try_catch->Exception());
	const char* c_format_exception = ToCString(exception);
	v8::Local<v8::Message> msg = try_catch->Message();
	if (msg.IsEmpty())
	{
	    std::cerr << c_format_exception << std::endl;
	}
	else
	{
	    v8::String::Utf8Value filename(isolate, msg->GetScriptOrigin().ResourceName());
	    v8::Local<v8::Context> context(isolate->GetCurrentContext());
	    const char* c_format_filename = ToCString(filename);
	    int error_line = msg->GetLineNumber(context).FromJust();
	    std::cerr << c_format_filename << "> on line: " << error_line << "\n\tError: " << c_format_exception << std::endl;
	    int start = msg->GetStartColumn(context).FromJust();
	    for (int i = 0; i < start; i++)
	    {
		std::cerr << " ";
	    }
	    int end = msg->GetEndColumn(context).FromJust();
	    for (int j = start; j < end; j++)
	    {
		std::cerr << "*";
	    }

	    std::cerr << std::endl;

	    v8::Local<v8::Value> stack_trace;
	    if (try_catch->StackTrace(context).ToLocal(&stack_trace) 
			    && stack_trace->IsString() 
			    && stack_trace.As<v8::String>()->Length() > 0)
	    {
		v8::String::Utf8Value actual_stack_trace(isolate, stack_trace);
		const char* c_format_error = ToCString(actual_stack_trace);
		std::cerr << c_format_error << std::endl;
	    }
	}
    }
}
