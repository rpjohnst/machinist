def generate(env):
	for tool in [ "cc", "c++", "link", "ar" ]:
		env.Tool(tool)
	
	env["CC"] = env.Detect("clang")
	env["CXX"] = env.Detect("clang++")
	
	env["OBJSUFFIX"] = ".o"
	env["LIBPREFIX"] = "lib"
	env["LIBSUFFIX"] = ".a"

def exists(env):
	return env.Detect(compilers)
