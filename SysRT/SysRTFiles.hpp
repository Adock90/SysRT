#include <SysRT/SysRTUtils.hpp>
#include <SysRT/SysRTException.hpp>

namespace SysRTFiles
{
    void ReadFile(const v8::FunctionCallbackInfo<v8::Value> &args)
    {
	v8::Isolate* isolate = args.GetIsolate();
	if (args.Length() != 1)
	{
	    isolate->ThrowError("Bad Params");
	    exit(1);
	}

	v8::String::Utf8Value filename(isolate, args[0]);
	if (*filename == nullptr)
	{
	    isolate->ThrowError("Error Loading File");
	    exit(1);
	}

	FILE* fptr = fopen(*filename, "r");
	if (fptr == NULL)
	{
	    isolate->ThrowError("Error Loading File");
	    exit(1);
	}

	fseek(fptr, 0, SEEK_END);
	size_t fsize = ftell(fptr);
	rewind(fptr);
	char* buffer = new char[fsize + 1];
	buffer[fsize] = '\0';

	for (size_t i = 0; i < fsize;)
	{
	    i += fread(&buffer[i], 1, fsize - i, fptr);
	    if (ferror(fptr))
	    {
		fclose(fptr);
		exit(1);
	    }
	}
	fclose(fptr);
	args.GetReturnValue().Set(ToV8String(buffer));
	delete[] buffer;
    }

    void WriteFile(const v8::FunctionCallbackInfo<v8::Value> &args)
    {
	v8::Isolate* isolate = args.GetIsolate();
	if (args.Length() != 1)
        {
            isolate->ThrowError("Bad Params");
            exit(1);
        }

	v8::String::Utf8Value filename(isolate, args[0]);
        if (*filename == nullptr)
        {
            isolate->ThrowError("Error Loading File");
            exit(1);
        }

	FILE* fptr = fopen(*filename, "w");
        if (fptr == NULL)
        {
            isolate->ThrowError("Error Loading File");
            exit(1);
        }
	v8::String::Utf8Value data_string(isolate, args[1]);
	const char* content_c_format = ToCString(data_string);
	fprintf(fptr, "%s", content_c_format);
	fclose(fptr);
    }
}
