def generate(env):
	for tool in [ "cc", "c++", "link", "ar" ]:
		env.Tool(tool)
	
	env["CC"] = env.Detect("llvm-gcc")
	env["CXX"] = env.Detect("llvm-g++")
	
	env["OBJSUFFIX"] = ".o"
	env["LIBPREFIX"] = "lib"
	env["LIBSUFFIX"] = ".a"

def exists(env):
	for compiler in [ "clang", "clang++" ]:
		if not env.Detect(compiler): return False
	return True
