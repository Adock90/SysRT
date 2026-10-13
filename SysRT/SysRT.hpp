//The main header for SysRT

#include <SysRT/SysRTUtils.hpp>
#include <SysRT/SysRTConsole.hpp>
#include <SysRT/SysRTFiles.hpp>

namespace SysRT
{
    uv_loop_t *sys_rt_loop = uv_default_loop();

    const char* ReadJSFile(const char* filename)
    {
	FILE* fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
	    return "<file_not_found>";
	}
	
	fseek(fptr, 0, SEEK_END);
	size_t fsize = ftell(fptr);
	rewind(fptr);
	char* js = new char[fsize + 1];
	js[fsize] = '\0';

	for (size_t i = 0; i < fsize; i+=0)
	{
	    i += fread(&js[i], 1, fsize - i, fptr);
	}

	fclose(fptr);

	return js;
    }

    class SysRTObj
    {
    private:
        std::unique_ptr<v8::Platform> platform;
	v8::Isolate* isolate;
	v8::Isolate::CreateParams params;
	void SysRTSetCallbackTable(v8::Local<v8::ObjectTemplate> global);
    public:
	void SysRTCleanup();
	void SysRTInit(int argc, char* argv[]);
	void SysRTCreateInstance(const char* filename);
    };

    void SysRTObj::SysRTSetCallbackTable(v8::Local<v8::ObjectTemplate> global)
    {
	v8::Local<v8::ObjectTemplate> console_obj = v8::ObjectTemplate::New(isolate);
	v8::Local<v8::ObjectTemplate> file_obj = v8::ObjectTemplate::New(isolate);

	console_obj->Set(isolate, "log", v8::FunctionTemplate::New(isolate, SystemConsole::SystemConsoleOut));
	console_obj->Set(isolate, "getinput", v8::FunctionTemplate::New(isolate, SystemConsole::SystemConsoleIn));
	global->Set(isolate, "terminal", console_obj);


	file_obj->Set(isolate, "read", v8::FunctionTemplate::New(isolate, SysRTFiles::ReadFile));
	file_obj->Set(isolate, "write", v8::FunctionTemplate::New(isolate, SysRTFiles::WriteFile));
	global->Set(isolate, "file", file_obj);
    }

    void SysRTObj::SysRTInit(int argc, char* argv[])
    {
        v8::V8::InitializeICUDefaultLocation(argv[0]);
	v8::V8::InitializeExternalStartupData(argv[0]);

	platform = v8::platform::NewDefaultPlatform();
	v8::V8::InitializePlatform(platform.get());

	v8::V8::Initialize();

	params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
	isolate = v8::Isolate::New(params);
    }

    void SysRTObj::SysRTCreateInstance(const char* filename)
    {
        v8::Isolate::Scope scope(isolate);
	v8::TryCatch try_catch(isolate);

	v8::HandleScope handle_scope(isolate);
	v8::ScriptOrigin origin(v8::String::NewFromUtf8(isolate, filename).ToLocalChecked());
	
	v8::Local<v8::ObjectTemplate> global_object = v8::ObjectTemplate::New(isolate);

	this->SysRTSetCallbackTable(global_object);

	v8::Local<v8::Context> local_context = v8::Context::New(isolate, NULL, global_object);
	v8::Context::Scope c_scope(local_context);

	const char* js = SysRT::ReadJSFile(filename);
	if (strcmp(js, "<file_not_found>") == 0)
	{
	    std::cerr << "Cannot find JS file: " << filename << std::endl;
	    std::exit(1);
	}

	v8::Local<v8::String> js_source = v8::String::NewFromUtf8(isolate, js).ToLocalChecked();
	v8::Local<v8::Script> compilation;
	if (!v8::Script::Compile(local_context, js_source, &origin).ToLocal(&compilation))
	{
	    SysRTExeception::SysRTReportException(isolate, &try_catch);
	    std::exit(1);
	}

	v8::Local<v8::Value> result;
	if (!compilation->Run(local_context).ToLocal(&result))
	{
	    assert(try_catch.HasCaught());
	    SysRTExeception::SysRTReportException(isolate, &try_catch);
	}

	v8::String::Utf8Value utf8(isolate, result);

	uv_run(sys_rt_loop, UV_RUN_DEFAULT);
    }
    
    void SysRTObj::SysRTCleanup()
    {
	this->isolate->Dispose();
	v8::V8::Dispose();
	v8::V8::DisposePlatform();
	delete this->params.array_buffer_allocator;
    }
}
