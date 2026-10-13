#pragma once

#include <v8.h>
#include <bits/stdc++.h>
#include <libplatform/libplatform.h>
#include <uv.h>
#include <cassert>

v8::Local<v8::String> ToV8String(const char* cstr)
{
	return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), cstr).ToLocalChecked();
}

const char* ToCString(const v8::String::Utf8Value &str)
{
	return *str ? *str : "<str_failed>";
}
