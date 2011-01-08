env = Environment()

var = Variables()
var.AddVariables(
	EnumVariable(
		"build", "set to debug for syms.", "debug",
		allowed_values = [ "debug", "profile", "release" ]
	),
	EnumVariable(
		"compiler", "toolchain to use.", "clang",
		allowed_values = [ "clang", "llvm", "g++" ]
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

env = Environment(variables = var)
env.Tool("$compiler")
env.Append(
	CPPDEFINES = [
		"PLATFORM_" + env["platform"].upper(),
		"GRAPHICS_" + env["graphics"].upper()
	],
	CPPPATH = [ "#engine" ]
)

env.Append(**{
	"release": { "CCFLAGS": "-O4", "LINKFLAGS": "-use-gold-plugin" },
	"debug": { "CCFLAGS": "-g", "CPPDEFINES": [ "DEBUG" ] },
	"profile": { "CCFLAGS": "-O4 -pg", "LINKFLAGS": "-pg" }
}[env["build"]])

if GetOption("help"):
	Help(var.GenerateHelpText(env))
else:
	env.SConscript(
		"engine/SConscript", exports = [ "env" ],
		variant_dir = "$build/engine", duplicate = False,
	)
