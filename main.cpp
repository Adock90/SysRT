#include <SysRT/SysRT.hpp>

void Help(bool help_required)
{
    if (help_required)
    {
	std::cout << "[SysRT] Help" << std::endl;
    }
    
    std::cout << "SysRT:\n"
	    << "\tAuthor: Adam.Croft (@adock90)\n"
	    << "\tWritten in: C++\n"
	    << "SysRT [<file>] [<options>]:\n"
	    << "\t[<file>]: Target file.\n"
	    << "\t\t\neg: SysRT hi.js\n"
	    << "\t[<options>] OPTIONAL: for help, type --h at the end"
	    << std::endl;
    std::exit(1);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
	Help(true);
    }
    for (int i = 0; i < argc; i++)
    {
	if (strcmp(argv[i], "--h") < 1)
	{
	    Help(false);
	}
    }

    SysRT::SysRTObj sys_rt_instance;
    sys_rt_instance.SysRTInit(argc, argv);
    sys_rt_instance.SysRTCreateInstance(argv[1]);
    sys_rt_instance.SysRTCleanup();
    
    return 0;
}
