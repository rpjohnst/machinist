import os

env = Environment(ENV = { "PATH": os.environ["PATH"] }, tools = [ "c++", "link" ])

vars = Variables()
vars.AddVariables(
	("CXX", "compiler to use."),
	EnumVariable(
		"build", "set to debug for syms.", "debug",
		allowed_values = [ "debug", "profile", "release" ]
	),
	EnumVariable(
		"platform", "target api.", {
			"win32": "win32",
			"posix": "xlib"
		}[env["PLATFORM"]],
		allowed_values = [ "win32", "xlib" ]
	),
	EnumVariable(
		"graphics", "target graphics engine.", "opengl",
		allowed_values = [ "opengl", "directx" ]
	)
)
vars.Update(env)
if GetOption("help"):
	Help(vars.GenerateHelpText(env))

env.Append(
	CPPDEFINES = [
		"PLATFORM_" + env["platform"].upper(),
		"GRAPHICS_" + env["graphics"].upper()
	],
	CPPPATH = [ "#engine" ]
)
env.Append(**{
	"release": { "CCFLAGS": "-O3" },
	"debug": { "CCFLAGS": "-g", "CPPDEFINES": [ "DEBUG" ] },
	"profile": { "CCFLAGS": "-O3 -pg", "LINKFLAGS": "-pg" }
}[env["build"]])

env.SConscript(
	"engine/SConscript", exports = [ "env" ],
	variant_dir = "$build/engine", duplicate = False,
)
